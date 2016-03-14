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
	template <class container>
	array(const container &a)
	{
		count = a.size();
		capacity = count + log2i(count);
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		value_type *ptr = data;
		for (typename container::const_iterator i = a.begin(); i != a.end(); i++, ptr++)
			new (ptr) value_type(*i);
	}

	/* Initialize this array with n spaces reserved */
	array(int n)
	{
		capacity = n;
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		count = 0;
	}

	/* Initialize this array with n elements each assigned the value t */
	array(const value_type &t, int n = 1)
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
	private:
		friend class array<value_type>;
		friend class const_iterator;
		array<value_type> *arr;
		value_type *loc;
	public:
		typedef array<value_type> container;
		typedef value_type type;
		iterator()
		{
			arr = NULL;
			loc = NULL;
		}

		iterator(array<value_type> *arr, int offset)
		{
			this->arr = arr;
			if (offset < 0)
				this->loc = arr->data + arr->count + offset;
			else
				this->loc = arr->data + offset;
		}

		~iterator() {}

		value_type &operator*()
		{
			return *loc;
		}
		value_type *operator->()
		{
			return loc;
		}

		value_type *pointer()
		{
			return loc;
		}

		value_type &value()
		{
			return *loc;
		}

		iterator &operator++(int)
		{
			loc++;
			return *this;
		}

		iterator &operator--(int)
		{
			loc--;
			return *this;
		}

		iterator &operator++()
		{
			++loc;
			return *this;
		}

		iterator &operator--()
		{
			--loc;
			return *this;
		}

		iterator &operator+=(int n)
		{
			loc += n;
			return *this;
		}

		iterator &operator-=(int n)
		{
			loc -= n;
			return *this;
		}

		iterator operator+(int n) const
		{
			iterator result;
			result.arr = arr;
			result.loc = loc + n;
			return result;
		}

		iterator operator-(int n) const
		{
			iterator result;
			result.arr = arr;
			result.loc = loc - n;
			return result;
		}

		iterator &operator=(iterator i)
		{
			arr = i.arr;
			loc = i.loc;
			return *this;
		}

		bool operator==(iterator i) const
		{
			return loc == i.loc;
		}

		bool operator!=(iterator i) const
		{
			return loc != i.loc;
		}

		int operator-(iterator i) const
		{
			return loc - i.loc;
		}

		bool operator==(const_iterator i) const
		{
			return loc == i.loc;
		}

		bool operator!=(const_iterator i) const
		{
			return loc != i.loc;
		}

		int operator-(const_iterator i) const
		{
			return loc - i.loc;
		}

		template <class iterator_type>
		void swap(iterator_type i)
		{
			value_type temp;
			memcpy(&temp, loc, sizeof(value_type));
			memcpy(loc, i.pointer(), sizeof(value_type));
			memcpy(i.pointer(), &temp, sizeof(value_type));
		}

		/* Erase all elements in the range [this, this+n) */
		void drop(int n = 1)
		{
			int offset = loc - arr->data;
			if (n > 0)
			{
				n = min(offset + n, arr->count) - offset;
				for (value_type *i = loc; i < loc+n; i++)
					i->~value_type();
				memmove(loc, loc+n, (arr->count-offset-n)*sizeof(value_type));
				arr->count -= n;
			}
			else if (n < 0)
			{
				n = max(n, -offset);
				for (value_type *i = loc+n; i < loc; i++)
					i->~value_type();
				memmove(loc+n, loc, (arr->count-offset)*sizeof(value_type));
				arr->count += n;
				loc += n;
			}
		}


		/* Erase all elements in the range [this, this+n) */
		array<value_type> pop(int n = 1)
		{
			array<value_type> result;

			int offset = loc - arr->data;
			if (n > 0)
			{
				n = min(offset + n, arr->count) - offset;
				result.reserve(n);
				memcpy(result.data, loc, n*sizeof(value_type));
				result.count = n;
				memmove(loc, loc+n, (arr->count-offset-n)*sizeof(value_type));
				arr->count -= n;
			}
			else if (n < 0)
			{
				n = max(n, -offset);
				result.reserve(-n);
				memcpy(result.data, loc+n, -n*sizeof(value_type));
				result.count = -n;
				memmove(loc+n, loc, (arr->count-offset)*sizeof(value_type));
				arr->count += n;
				loc += n;
			}

			return result;
		}

		void push(value_type v, int n = 1)
		{
			int offset = loc - arr->data;
			if (arr->count > 0 && arr->count+n <= arr->capacity)
				memmove(loc+n, loc, (arr->count-offset)*sizeof(value_type));
			else if (arr->count+n > arr->capacity)
			{
				arr->capacity = arr->count + n + log2i(arr->count + n);
				value_type *newdata = (value_type*)malloc(sizeof(value_type)*arr->capacity);

				if (arr->data != NULL)
				{
					memcpy(newdata, arr->data, offset*sizeof(value_type));
					memcpy(newdata+offset+n, loc, (arr->count-offset)*sizeof(value_type));
					free(arr->data);
				}
				arr->data = newdata;
				loc = arr->data + offset;
			}

			arr->count += n;
			for (int i = 0; i < n; i++)
			{
				new (loc) value_type(v);
				loc++;
			}
		}

		template <class container>
		void push(const container &c)
		{
			int n = c.size();
			int offset = loc - arr->data;
			if (arr->count > 0 && arr->count + n <= arr->capacity)
				memmove(loc+n, loc, (arr->count-offset)*sizeof(value_type));
			else if (arr->count + n > arr->capacity)
			{
				arr->capacity = arr->count + n + log2i(arr->count + n);
				value_type *newdata = (value_type*)malloc(sizeof(value_type)*arr->capacity);

				if (arr->data != NULL)
				{
					memcpy(newdata, arr->data, offset*sizeof(value_type));
					memcpy(newdata+offset+n, loc, (arr->count-offset)*sizeof(value_type));
					free(arr->data);
				}
				arr->data = newdata;
				loc = arr->data + offset;
			}

			arr->count += n;
			value_type *j = loc;
			for (typename container::const_iterator i = c.begin(); i != c.end(); i++, j++)
				new (j) value_type(*i);
			loc += n;
		}
	
		void chop(bool forward = true)
		{
			if (forward)
			{
				for (value_type *ptr = loc; ptr < arr->data+arr->count; ptr++)
					ptr->~value_type();
				arr->count = loc - arr->data;
			}
			else
			{
				for (value_type *ptr = arr->data; ptr < loc; ptr++)
					ptr->~value_type();
				arr->count -= loc - arr->data;
			}
		}
	};

	struct const_iterator
	{
	private:
		friend class array<value_type>;
		friend class iterator;
		const array<value_type> *arr;
		const value_type *loc;
	public:
		typedef const array<value_type> container;
		typedef value_type type;
		const_iterator()
		{
			arr = NULL;
			loc = NULL;
		}

		const_iterator(const array<value_type> *arr, int offset)
		{
			this->arr = arr;
			if (offset < 0)
				this->loc = arr->data + arr->count + offset;
			else
				this->loc = arr->data + offset;
		}

		~const_iterator() {}

		const value_type &operator*()
		{
			return *loc;
		}
		const value_type *operator->()
		{
			return loc;
		}

		const value_type *pointer()
		{
			return loc;
		}

		const value_type &value()
		{
			return *loc;
		}

		const_iterator &operator++(int)
		{
			loc++;
			return *this;
		}

		const_iterator &operator--(int)
		{
			loc--;
			return *this;
		}

		const_iterator &operator++()
		{
			++loc;
			return *this;
		}

		const_iterator &operator--()
		{
			--loc;
			return *this;
		}

		const_iterator &operator+=(int n)
		{
			loc += n;
			return *this;
		}

		const_iterator &operator-=(int n)
		{
			loc -= n;
			return *this;
		}

		const_iterator operator+(int n) const
		{
			const_iterator result;
			result.arr = arr;
			result.loc = loc + n;
			return result;
		}

		const_iterator operator-(int n) const
		{
			const_iterator result;
			result.arr = arr;
			result.loc = loc - n;
			return result;
		}

		const_iterator &operator=(const_iterator i)
		{
			arr = i.arr;
			loc = i.loc;
			return *this;
		}

		bool operator==(const_iterator i) const
		{
			return loc == i.loc;
		}

		bool operator!=(const_iterator i) const
		{
			return loc != i.loc;
		}

		int operator-(const_iterator i) const
		{
			return loc - i.loc;
		}

		const_iterator &operator=(iterator i)
		{
			arr = i.arr;
			loc = i.loc;
			return *this;
		}

		bool operator==(iterator i) const
		{
			return loc == i.loc;
		}

		bool operator!=(iterator i) const
		{
			return loc != i.loc;
		}

		int operator-(iterator i) const
		{
			return loc - i.loc;
		}
	};

	int size() const
	{
		return count;
	}

	iterator at(int i)
	{
		return iterator(this, i);
	}

	const_iterator at(int i) const
	{
		return const_iterator(this, i);
	}

	value_type &get(int i) const
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
		return *data;
	}

	value_type &back() const
	{
		return *(data + count-1);
	}

	iterator begin()
	{
		return iterator(this, 0);
	}

	iterator end()
	{
		return iterator(this, count);
	}

	iterator rbegin()
	{
		return iterator(this, -1);
	}

	iterator rend()
	{
		return iterator(this, -count-1);
	}

	const_iterator begin() const
	{
		return const_iterator(this, 0);
	}

	const_iterator end() const
	{
		return const_iterator(this, count);
	}

	const_iterator rbegin() const
	{
		return const_iterator(this, -1);
	}

	const_iterator rend() const
	{
		return const_iterator(this, -count-1);
	}

	slice<iterator> bound()
	{
		return slice<iterator>(begin(), rbegin());
	}

	slice<const_iterator> bound() const
	{
		return slice<const_iterator>(begin(), rbegin());
	}

	template <class iterator2>
	void push_back(const slice<iterator2> &c)
	{
		end().push(c);
	}

	template <class iterator2>
	void push_front(const slice<iterator2> &c)
	{
		begin().push(c);
	}

	void push_back(value_type v, int n = 1)
	{
		end().push(v, n);
	}

	void push_front(value_type v, int n = 1)
	{
		begin().push(v, n);
	}

	array<value_type> pop_back(unsigned int n = 1)
	{
		return end().pop(-n);
	}

	array<value_type> pop_front(unsigned int n = 1)
	{
		return begin().pop(n);
	}

	void drop_back(unsigned int n = 1)
	{
		return end().drop(-n);
	}

	void drop_front(unsigned int n = 1)
	{
		return begin().drop(n);
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

