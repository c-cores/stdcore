/*
 * array.h
 *
 *  Created on: Feb 4, 2014
 *      Author: nbingham
 */

#include "memory.h"
#include "slice.h"
#include "math.h"
#include <csignal>
#include "stdio.h"
#include "stdlib.h"

#ifndef array_h
#define array_h

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
		data = new value_type[capacity];
		for (count = 0; count < a.count; count++)
			data[count] = a.data[count];
	}

	/* Initialize this array with n spaces reserved */
	array(int n)
	{
		capacity = n;
		data = new value_type[capacity];
		count = 0;
	}

	/* Initialize this array with n elements each assigned the value t */
	array(int n, const value_type &t)
	{
		capacity = n + log2i(n);
		data = new value_type[capacity];
		for (count = 0; count < n; count++)
			data[count] = t;
	}

	~array()
	{
		if (data != NULL)
			delete [] data;
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
			if (arr->count < arr->capacity)
				for (int i = arr->count; i > offset+1; i--)
					memcpy(arr->data + i, arr->data + (i-1), sizeof(value_type));
			else
			{
				arr->capacity = arr->count + 1 + log2i(arr->count + 1);
				value_type *newdata = new value_type[arr->capacity];
				memcpy(newdata, arr->data, (offset+1)*sizeof(value_type));
				memcpy(newdata+(offset+2), arr->data+(offset+1), (arr->count - (offset+1)));

				if (arr->data != NULL)
					free(arr->data);
				arr->data = newdata;
			}

			arr->count++;
			arr->data[offset+1] = v;
		}

		template <class container>
		void merge(const container &c)
		{
			slice<typename container::const_iterator> b = c.bound();
			int n = (b.right+1) - b.left;
			if (arr->count + n <= arr->capacity)
				for (int i = arr->count + n - 1; i > offset+1; i--)
					memcpy(arr->data + i, arr->data + (i-n), sizeof(value_type));
			else
			{
				arr->capacity = arr->count + n + log2i(arr->count + n);
				value_type *newdata = new value_type[arr->capacity];
				memcpy(newdata, arr->data, (offset+1)*sizeof(value_type));
				memcpy(newdata+(offset+1+n), arr->data+(offset+1), (arr->count - (offset+1))*sizeof(value_type));

				if (arr->data != NULL)
					free(arr->data);
				arr->data = newdata;
			}

			arr->count += n;
			int j = offset+1;
			for (typename container::const_iterator i = b.left; i != b.right+1; i++, j++)
				arr->data[j] = *i;
		}

		/* Erase all elements in the range [this, this+n) */
		void pop(int n = 1)
		{
			n = (min(offset + n, arr->count) - offset);
			arr->count -= n;
			memcpy(arr->data+offset, arr->data+offset+n, (arr->count-offset)*sizeof(value_type));
		}

		/* Erase all elements in the range [this, last) */
		void pop(iterator last)
		{
			int n = last.offset - offset;
			arr->count -= n;
			memcpy(arr->data+offset, arr->data+offset+n, (arr->count-offset)*sizeof(value_type));
			last.offset = offset;
		}

		void rpush(value_type v)
		{
			if (arr->count < arr->capacity)
				for (int i = arr->count; i > offset; i--)
					memcpy(arr->data+i, arr->data+i-1, sizeof(value_type));
			else
			{
				arr->capacity = arr->count + 1 + log2i(arr->count + 1);
				value_type *newdata = new value_type[arr->capacity];
				memcpy(newdata, arr->data, offset*sizeof(value_type));
				memcpy(newdata+offset+1, arr->data+offset, (arr->count-offset)*sizeof(value_type));

				if (arr->data != NULL)
					delete [] arr->data;
				arr->data = newdata;
			}

			arr->count++;
			arr->data[offset] = v;
			offset++;
		}

		template <class container>
		void rmerge(const container &c)
		{
			slice<typename container::const_iterator> b = c.bound();
			int n = (b.right+1) - b.left;
			if (arr->count + n <= arr->capacity)
				for (int i = arr->count + n - 1; i > offset; i--)
					memcpy(arr->data+i, arr->data+i-n, sizeof(value_type));
			else
			{
				arr->capacity = arr->count + n + log2i(arr->count + n);
				value_type *newdata = new value_type[arr->capacity];
				memcpy(newdata, arr->data, offset*sizeof(value_type));
				memcpy(newdata+offset+n, arr->data+offset, (arr->count-offset)*sizeof(value_type));

				if (arr->data != NULL)
					delete [] arr->data;
				arr->data = newdata;
			}

			arr->count += n;
			int j = offset;
			for (typename container::const_iterator i = b.left; i != b.right+1; i++, j++)
				arr->data[j] = *i;
			offset += n;
		}

		/* Erase all elements in the range (this - n, this] */
		void rpop(int n = 1)
		{
			n = min(n, offset+1);
			arr->count -= n;
			memcpy(arr->data+offset-n+1, arr->data+offset+1, (arr->count-offset+n-1)*sizeof(value_type));
			offset -= n - 1;
		}

		/* Erase all elements in the range (last, this] */
		void rpop(iterator last)
		{
			int n = offset - last.offset;
			arr->count -= n;
			memcpy(arr->data+last.offset+1, arr->data+last.offset+1+n, (arr->count-last.offset-1)*sizeof(value_type));
			offset -= n;
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

	void pop_back(int n = 1)
	{
		rbegin().rpop(n);
	}

	void pop_front(int n = 1)
	{
		begin().pop(n);
	}

	void pop(int i, int n = 1)
	{
		(begin() + i).pop(n);
	}

	void rpop(int i, int n = 1)
	{
		(begin() + i).rpop(n);
	}

	/**
	 * \fn void array<value_type>::reserve(int n)
	 * \brief Increase the capacity of the array to at least n possible elements.
	 */
	void resize(int n)
	{
		if (n > capacity)
		{
			capacity = n + log2i(n);
			value_type *newdata = new value_type[capacity];
			memcpy(newdata, data, count*sizeof(value_type));

			if (data != NULL)
				delete [] data;
			data = newdata;

			count = n;
		}
	}

	/**
	 * \fn void array<value_type>::reserve(int n)
	 * \brief Increase the capacity of the array to at least count + n possible elements.
	 */
	void extend(int n)
	{
		n = count + n;
		if (n > capacity)
		{
			capacity = n + log2i(n);
			value_type *newdata = new value_type[capacity];
			memcpy(newdata, data, count*sizeof(value_type));

			if (data != NULL)
				delete [] data;
			data = newdata;

			count = n;
		}
	}

	/**
	 * \fn void array<value_type>::reserve(int n)
	 * \brief Increase the capacity of the array to at least n possible elements.
	 */
	void reserve(int n)
	{
		if (n > capacity)
		{
			capacity = n;
			value_type *newdata = new value_type[capacity];
			memcpy(newdata, data, count*sizeof(value_type));

			if (data != NULL)
				delete [] data;
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
		if (n > capacity)
		{
			capacity = n;
			value_type *newdata = new value_type[capacity];
			memcpy(newdata, data, count*sizeof(value_type));

			if (data != NULL)
				delete [] data;
			data = newdata;
		}
	}

	/**
	 * \fn void array<value_type>::clear()
	 * \brief Erase all elements from the array.
	 */
	void clear()
	{
		if (data != NULL)
			delete [] data;
		data = NULL;
		capacity = 0;
		count = 0;
	}

	array<value_type> &operator=(const array<value_type> &c)
	{
		if (c.count > capacity)
		{
			if (data != NULL)
				delete [] data;

			capacity = c.count + log2i(c.count);
			data = new value_type[capacity];
		}

		for (count = 0; count < c.count; count++)
			data[count] = c.data[count];

		return *this;
	}
};

}

#endif
