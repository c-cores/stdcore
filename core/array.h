/*
 * array.h
 *
 *  Created on: Feb 4, 2014
 *      Author: nbingham
 */

#pragma once

#include "memory.h"
#include "slice.h"
#include "math.h"
#include <csignal>
#include "stdio.h"
#include "stdlib.h"
#include <stdarg.h>
#include <stdint.h>
#include <new>

namespace core
{

template <class value_type>
struct array
{
	array()
	{
		data = NULL;
		count = 0;
		capacity = 0;
	}

	/* Initialize this array as a copy of another */
	array(const array<value_type> &a)
	{
		capacity = a.count + log2i(a.count);
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		for (count = 0; count < a.count; count++)
			new (data+count) value_type(a.data[count]);
	}

	/* Initialize this array with n spaces reserved */
	array(int n)
	{
		capacity = n;
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		count = 0;
	}

	/* Initialize this array with n elements each assigned the value t */
	array(int n, const value_type &t)
	{
		capacity = n + log2i(n);
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		for (count = 0; count < n; count++)
			new (data+count) value_type(t);
	}

	template <int num>
	static array<value_type> join(value_type first, ...)
	{
		array<value_type> result;
		va_list arguments;

		va_start(arguments, first);
		result.reserve(num);
		result.push_back(first);
		for (int i = 1; i < num; i++)
			result.push_back(va_arg(arguments, value_type));
		va_end(arguments);
		return result;
	}

	template <int num>
	static array<value_type> join()
	{
		return array<value_type>();
	}

	virtual ~array()
	{
		if (data != NULL)
		{
			for (int i = 0; i < count; i++)
				data[i].~value_type();

			free(data);
		}
		data = NULL;
		capacity = 0;
		count = 0;
	}

	value_type *data;
	int count;
	int capacity;

	struct iterator;
	struct const_iterator;

	struct iterator
	{
		typedef value_type type;
		iterator()
		{
			arr = NULL;
			offset = 0;
		}

		~iterator() {}

		array<value_type> *arr;
		int offset;

		value_type &operator*()
		{
			return *(arr->data + offset);
		}
		value_type *operator->()
		{
			return arr->data + offset;
		}

		iterator &operator++(int)
		{
			offset++;
			return *this;
		}

		iterator &operator--(int)
		{
			offset--;
			return *this;
		}

		iterator &operator++()
		{
			++offset;
			return *this;
		}

		iterator &operator--()
		{
			--offset;
			return *this;
		}

		iterator &operator+=(int n)
		{
			offset += n;
			return *this;
		}

		iterator &operator-=(int n)
		{
			offset -= n;
			return *this;
		}

		iterator operator+(int n) const
		{
			iterator result;
			result.arr = arr;
			result.offset = offset + n;
			return result;
		}

		iterator operator-(int n) const
		{
			iterator result;
			result.arr = arr;
			result.offset = offset - n;
			return result;
		}

		iterator &operator=(iterator i)
		{
			arr = i.arr;
			offset = i.offset;
			return *this;
		}

		bool operator==(iterator i) const
		{
			return arr == i.arr && offset == i.offset;
		}

		bool operator!=(iterator i) const
		{
			return arr != i.arr || offset != i.offset;
		}

		int operator-(iterator i) const
		{
			return offset - i.offset;
		}

		bool operator==(const_iterator i) const
		{
			return arr == i.arr && offset == i.offset;
		}

		bool operator!=(const_iterator i) const
		{
			return arr != i.arr || offset != i.offset;
		}

		int operator-(const_iterator i) const
		{
			return offset - i.offset;
		}

		template <class iterator_type>
		void swap(iterator_type i)
		{
			value_type temp;
			memcpy(&temp, arr->data+offset, sizeof(value_type));
			memcpy(arr->data+offset, &*i, sizeof(value_type));
			memcpy(&*i, &temp, sizeof(value_type));
		}

		void push(value_type v)
		{
			if (arr == NULL)
			{
				printf("Error: undefined parent array\n");
				exit(1);
			}

			if (arr->count > 0 && arr->count < arr->capacity)
				memmove(arr->data+offset+2, arr->data+offset+1, (arr->count-offset-1)*sizeof(value_type));
			else if (arr->count >= arr->capacity)
			{
				arr->capacity = arr->count + 1 + log2i(arr->count + 1);
				value_type *newdata = (value_type*)malloc(sizeof(value_type)*arr->capacity);

				if (arr->data != NULL)
				{
					memcpy(newdata, arr->data, (offset+1)*sizeof(value_type));
					memcpy(newdata+offset+2, arr->data+offset+1, (arr->count-offset-1)*sizeof(value_type));
					free(arr->data);
				}
				arr->data = newdata;
			}

			arr->count++;
			new (arr->data+offset+1) value_type(v);
		}

		template <class container>
		void merge(const container &c)
		{
			slice<typename container::const_iterator> b = c.bound();
			int n = (b.right+1) - b.left;
			if (arr->count > 0 && arr->count + n <= arr->capacity)
				memmove(arr->data+offset+1+n, arr->data+offset+1, (arr->count-offset-1)*sizeof(value_type));
			else if (arr->count + n > arr->capacity)
			{
				arr->capacity = arr->count + n + log2i(arr->count + n);
				value_type *newdata = (value_type*)malloc(sizeof(value_type)*arr->capacity);

				if (arr->data != NULL)
				{
					memcpy(newdata, arr->data, (offset+1)*sizeof(value_type));
					memcpy(newdata+offset+1+n, arr->data+offset+1, (arr->count-offset-1)*sizeof(value_type));
					free(arr->data);
				}
				arr->data = newdata;
			}

			arr->count += n;
			int j = offset+1;
			for (typename container::const_iterator i = b.left; i != b.right+1; i++, j++)
				new (arr->data+j) value_type(*i);
		}

		/* Erase all elements in the range [this, this+n) */
		void pop(int n = 1)
		{
			if (n > 0)
			{
				n = min(offset + n, arr->count) - offset;
				for (int i = offset; i < offset+n; i++)
					arr->data[i].~value_type();
				memmove(arr->data+offset, arr->data+offset+n, (arr->count-offset-n)*sizeof(value_type));
				arr->count -= n;
			}
			else if (n < 0)
			{
				n = max(n, -offset-1);
				for (int i = offset+n+1; i < offset+1; i++)
					arr->data[i].~value_type();
				memmove(arr->data+offset+n+1, arr->data+offset+1, (arr->count-offset-1)*sizeof(value_type));
				arr->count += n;
				offset += n+1;
			}
		}

		/* Erase all elements in the range [this, last) */
		void pop(iterator &last)
		{
			int n = last.offset - offset;
			if (n > 0)
			{
				for (int i = offset; i < last.offset; i++)
					arr->data[i].~value_type();
				memmove(arr->data+offset, arr->data+last.offset, (arr->count-last.offset)*sizeof(value_type));
				arr->count -= n;
				last.offset = offset;
			}
			else if (n < 0)
			{
				for (int i = last.offset+1; i < offset+1; i++)
					arr->data[i].~value_type();
				memmove(arr->data+last.offset+1, arr->data+offset+1, (arr->count-offset-1)*sizeof(value_type));
				arr->count += n;
				offset = last.offset+1;
			}
		}

		void rpush(value_type v)
		{
			if (arr->count > 0 && arr->count < arr->capacity)
				memmove(arr->data+offset+1, arr->data+offset, (arr->count-offset)*sizeof(value_type));
			else if (arr->count >= arr->capacity)
			{
				arr->capacity = arr->count + 1 + log2i(arr->count + 1);
				value_type *newdata = (value_type*)malloc(sizeof(value_type)*arr->capacity);

				if (arr->data != NULL)
				{
					memcpy(newdata, arr->data, offset*sizeof(value_type));
					memcpy(newdata+offset+1, arr->data+offset, (arr->count-offset)*sizeof(value_type));
					free(arr->data);
				}
				arr->data = newdata;
			}

			arr->count++;
			new (arr->data+offset) value_type(v);
			offset++;
		}

		template <class container>
		void rmerge(const container &c)
		{
			slice<typename container::const_iterator> b = c.bound();
			int n = (b.right+1) - b.left;
			if (arr->count > 0 && arr->count + n <= arr->capacity)
				memmove(arr->data+offset+n, arr->data+offset, (arr->count-offset)*sizeof(value_type));
			else if (arr->count + n > arr->capacity)
			{
				arr->capacity = arr->count + n + log2i(arr->count + n);
				value_type *newdata = (value_type*)malloc(sizeof(value_type)*arr->capacity);

				if (arr->data != NULL)
				{
					memcpy(newdata, arr->data, offset*sizeof(value_type));
					memcpy(newdata+offset+n, arr->data+offset, (arr->count-offset)*sizeof(value_type));
					free(arr->data);
				}
				arr->data = newdata;
			}

			arr->count += n;
			int j = offset;
			for (typename container::const_iterator i = b.left; i != b.right+1; i++, j++)
				new (arr->data+j) value_type(*i);
			offset += n;
		}
	};

	struct const_iterator
	{
		typedef value_type type;
		const_iterator()
		{
			arr = NULL;
			offset = 0;
		}

		~const_iterator() {}

		const array<value_type> *arr;
		int offset;

		const value_type &operator*()
		{
			return *(arr->data + offset);
		}
		const value_type *operator->()
		{
			return arr->data + offset;
		}

		const_iterator &operator++(int)
		{
			offset++;
			return *this;
		}

		const_iterator &operator--(int)
		{
			offset--;
			return *this;
		}

		const_iterator &operator++()
		{
			++offset;
			return *this;
		}

		const_iterator &operator--()
		{
			--offset;
			return *this;
		}

		const_iterator &operator+=(int n)
		{
			offset += n;
			return *this;
		}

		const_iterator &operator-=(int n)
		{
			offset -= n;
			return *this;
		}

		const_iterator operator+(int n) const
		{
			const_iterator result;
			result.arr = arr;
			result.offset = offset + n;
			return result;
		}

		const_iterator operator-(int n) const
		{
			const_iterator result;
			result.arr = arr;
			result.offset = offset - n;
			return result;
		}

		const_iterator &operator=(const_iterator i)
		{
			arr = i.arr;
			offset = i.offset;
			return *this;
		}

		bool operator==(const_iterator i) const
		{
			return arr == i.arr && offset == i.offset;
		}

		bool operator!=(const_iterator i) const
		{
			return arr != i.arr || offset != i.offset;
		}

		int operator-(const_iterator i) const
		{
			return offset - i.offset;
		}

		const_iterator &operator=(iterator i)
		{
			arr = i.arr;
			offset = i.offset;
			return *this;
		}

		bool operator==(iterator i) const
		{
			return arr == i.arr && offset == i.offset;
		}

		bool operator!=(iterator i) const
		{
			return arr != i.arr || offset != i.offset;
		}

		int operator-(iterator i) const
		{
			return offset - i.offset;
		}
	};

	int size() const
	{
		return count;
	}

	value_type &at(int i) const
	{
		if (i < 0)
			i += count;

		return *(data + i);
	}

	value_type &operator[](int i) const
	{
		if (i < 0)
			i += count;

		return *(data + i);
	}

	value_type &front() const
	{
		return data[0];
	}

	value_type &back() const
	{
		return data[count-1];
	}

	iterator begin()
	{
		iterator result;
		result.arr = this;
		result.offset = 0;
		return result;
	}

	iterator end()
	{
		iterator result;
		result.arr = this;
		result.offset = count;
		return result;
	}

	iterator rbegin()
	{
		iterator result;
		result.arr = this;
		result.offset = count-1;
		return result;
	}

	iterator rend()
	{
		iterator result;
		result.arr = this;
		result.offset = -1;
		return result;
	}

	const_iterator begin() const
	{
		const_iterator result;
		result.arr = this;
		result.offset = 0;
		return result;
	}

	const_iterator end() const
	{
		const_iterator result;
		result.arr = this;
		result.offset = count;
		return result;
	}

	const_iterator rbegin() const
	{
		const_iterator result;
		result.arr = this;
		result.offset = count-1;
		return result;
	}

	const_iterator rend() const
	{
		const_iterator result;
		result.arr = this;
		result.offset = -1;
		return result;
	}

	slice<iterator> bound()
	{
		return slice<iterator>(begin(), rbegin());
	}

	slice<const_iterator> bound() const
	{
		return slice<const_iterator>(begin(), rbegin());
	}

	template <class container>
	void merge_back(const container &c)
	{
		rbegin().merge(c);
	}

	template <class container>
	void merge_front(const container &c)
	{
		begin().rmerge(c);
	}

	void push_back(value_type v)
	{
		rbegin().push(v);
	}

	void push_front(value_type v)
	{
		begin().rpush(v);
	}

	void push(int i, value_type v)
	{
		(begin() + i).push(v);
	}

	void rpush(int i, value_type v)
	{
		(begin() + i).rpush(v);
	}

	void pop_back(unsigned int n = 1)
	{
		rbegin().pop(-n);
	}

	void pop_front(unsigned int n = 1)
	{
		begin().pop(n);
	}

	void pop(int i, int n = 1)
	{
		(begin() + i).pop(n);
	}

	/**
	 * \fn void array<value_type>::reserve(int n)
	 * \brief Increase the capacity of the array to at least n possible elements.
	 */
	void resize(int n)
	{
		reserve(n);
		for (int i = n; i < count; i++)
			data[i].~value_type();
		for (int i = count; i < n; i++)
			new (data+i) value_type();
		count = n;
	}

	/**
	 * \fn void array<value_type>::reserve(int n)
	 * \brief Increase the capacity of the array to at least count + n possible elements.
	 */
	void extend(int n)
	{
		n = count + n;
		resize(n);
	}

	/**
	 * \fn void array<value_type>::reserve(int n)
	 * \brief Increase the capacity of the array to at least n possible elements.
	 */
	void reserve(int n)
	{
		if (n > capacity)
		{
			capacity = n + log2i(n);
			value_type *newdata = (value_type*)malloc(sizeof(value_type)*capacity);

			if (data != NULL)
			{
				memcpy(newdata, data, count*sizeof(value_type));
				free(data);
			}
			data = newdata;
		}
	}

	/**
	 * \fn void array<value_type>::reserve(int n)
	 * \brief Increase the capacity of the array to at least count + n possible elements.
	 */
	void extend_reserve(int n)
	{
		n = count + n;
		reserve(n);
	}

	/**
	 * \fn void array<value_type>::clear()
	 * \brief Erase all elements from the array.
	 */
	void clear()
	{
		if (data != NULL)
		{
			for (int i = 0; i < count; i++)
				data[i].~value_type();
			free(data);
		}
		data = NULL;
		capacity = 0;
		count = 0;
	}

	array<value_type> &operator=(const array<value_type> &c)
	{
		for (int i = 0; i < count; i++)
			data[i].~value_type();

		if (c.count > capacity)
		{
			if (data != NULL)
				free(data);

			capacity = c.count + log2i(c.count);
			data = (value_type*)malloc(sizeof(value_type)*capacity);
		}

		for (count = 0; count < c.count; count++)
			new (data+count) value_type(c.data[count]);

		return *this;
	}
};

template<class value_type>
bool operator<(array<value_type> a0, array<value_type> a1)
{
	for (typename array<value_type>::iterator i0 = a0.begin(), i1 = a1.begin(); i0 != a0.end() && i1 != a1.end(); i0++, i1++)
	{
		if (*i0 < *i1)
			return true;
		else if (*i0 > *i1)
			return false;
	}

	if (a0.size() < a1.size())
		return true;

	return false;
}

template<class value_type>
bool operator>(array<value_type> a0, array<value_type> a1)
{
	for (typename array<value_type>::iterator i0 = a0.begin(), i1 = a1.begin(); i0 != a0.end() && i1 != a1.end(); i0++, i1++)
	{
		if (*i0 > *i1)
			return true;
		else if (*i0 < *i1)
			return false;
	}

	if (a0.size() > a1.size())
		return true;

	return false;
}

template<class value_type>
bool operator<=(array<value_type> a0, array<value_type> a1)
{
	for (typename array<value_type>::iterator i0 = a0.begin(), i1 = a1.begin(); i0 != a0.end() && i1 != a1.end(); i0++, i1++)
	{
		if (*i0 < *i1)
			return true;
		else if (*i0 > *i1)
			return false;
	}

	if (a0.size() > a1.size())
		return false;

	return true;
}


template<class value_type>
bool operator>=(array<value_type> a0, array<value_type> a1)
{
	for (typename array<value_type>::iterator i0 = a0.begin(), i1 = a1.begin(); i0 != a0.end() && i1 != a1.end(); i0++, i1++)
	{
		if (*i0 > *i1)
			return true;
		else if (*i0 < *i1)
			return false;
	}

	if (a0.size() < a1.size())
		return false;

	return true;
}

template<class value_type>
bool operator==(array<value_type> a0, array<value_type> a1)
{
	if (a0.size() != a1.size())
		return false;

	for (typename array<value_type>::iterator i0 = a0.begin(), i1 = a1.begin(); i0 != a0.end() && i1 != a1.end(); i0++, i1++)
		if (*i0 != *i1)
			return false;

	return true;
}

template<class value_type>
bool operator!=(array<value_type> a0, array<value_type> a1)
{
	if (a0.size() != a1.size())
		return true;

	for (typename array<value_type>::iterator i0 = a0.begin(), i1 = a1.begin(); i0 != a0.end() && i1 != a1.end(); i0++, i1++)
		if (*i0 != *i1)
			return true;

	return false;
}

}

