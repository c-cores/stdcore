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
	typedef value_type type;

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
		capacity = (1 << (log2i(count)+1));
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		value_type *ptr = data;
		for (typename container::const_iterator i = a.begin(); i != a.end(); i++, ptr++)
			new (ptr) value_type(*i);
	}

	array(const array<value_type> &a)
	{
		count = a.size();
		capacity = a.capacity;
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		value_type *ptr = data;
		for (const_iterator i = a.begin(); i != a.end(); i++, ptr++)
			new (ptr) value_type(*i);
	}

	/* Initialize this array with n elements each assigned the value t */
	array(int n, const value_type &t)
	{
		capacity = (1 << (log2i(count)+1));
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		for (count = 0; count < n; count++)
			new (data+count) value_type(t);
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
	protected:
		friend class array<value_type>;
		friend class const_iterator;
		array<value_type> *arr;
		value_type *loc;
	public:
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

		value_type *ptr()
		{
			return loc;
		}

		value_type &get()
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
			memcpy(loc, i.ptr(), sizeof(value_type));
			memcpy(i.ptr(), &temp, sizeof(value_type));
		}

		void alloc(unsigned int n = 1)
		{
			int offset = loc - arr->data;
			if (arr->count > 0 && arr->count+(int)n <= arr->capacity)
				memmove(loc+n, loc, (arr->count-offset)*sizeof(value_type));
			else if (arr->count+(int)n > arr->capacity)
			{
				arr->capacity = (1 << (log2i(arr->count + n)+1));
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
		}

		/* Erase all elements in the range [this, this+n) */
		void drop(int n = 1)
		{
			int offset = loc - arr->data;
			if (n < 0)
			{
				n = min(-n, offset);
				loc -= n;
				offset -= n;
			}

			n = min(offset + n, arr->count) - offset;
			for (value_type *i = loc; i < loc+n; i++)
				i->~value_type();
			memmove(loc, loc+n, (arr->count-offset-n)*sizeof(value_type));
			arr->count -= n;
		}


		/* Erase all elements in the range [this, this+n) */
		array<value_type> pop(int n = 1)
		{
			array<value_type> result;

			int offset = loc - arr->data;
			if (n < 0)
			{
				n = min(-n, offset);
				loc -= n;
				offset -= n;
			}

			n = min(offset + n, arr->count) - offset;
			result.reserve(n);
			memcpy(result.data, loc, n*sizeof(value_type));
			result.count = n;
			memmove(loc, loc+n, (arr->count-offset-n)*sizeof(value_type));
			arr->count -= n;

			return result;
		}

		void push(value_type v)
		{
			alloc(1);
			new (loc) value_type(v);
			loc++;
		}


		void push(int n, value_type v)
		{
			alloc(n);
			for (int i = 0; i < n; i++, loc++)
				new (loc) value_type(v);
		}

		template <class container>
		void append(const container &c)
		{
			int n = c.size();
			alloc(n);
		
			typename container::const_iterator i = c.begin();
			while (i != c.end())
			{
				new (loc) value_type(*i);
				i++;
				loc++;
			}
		}

		slice<array<value_type> > sub(int n = -1)
		{
			iterator right;
			if (n < 0)
				right = arr->end()+n;
			else
				right = *this+n-1;
			return slice<array<value_type> >(*this, right);
		}

		void replace(int n, int m, value_type v)
		{
			int offset = loc - arr->data;
			if (n < 0)
			{
				n = min(-n, offset);
				loc -= n;
				offset -= n;
			}

			n = min(offset + n, arr->count) - offset;
			while (n > 0 && m > 0)
			{
				*loc = v;
				loc++;
				m--;
				n--;
			}

			if (m == 0 && n > 0)
			{
				for (value_type *i = loc; i < loc+n; i++)
					i->~value_type();
				memmove(loc, loc+n, (arr->count-offset-n)*sizeof(value_type));
				arr->count -= n;
			}
			else
			{
				alloc(m);
				while (m > 0)
				{
					new (loc) value_type(v);
					loc++;
					m--;
				}
			}

		}

		template <class container>
		void replace(int n, const container &c)
		{
			int offset = loc - arr->data;
			if (n < 0)
			{
				n = min(-n, offset);
				loc -= n;
				offset -= n;
			}

			n = min(offset + n, arr->count) - offset;
			typename container::const_iterator j = c.begin();
			while (n > 0 && j != c.end())
			{
				*loc = *j;
				loc++;
				j++;
				n--;
			}

			if (j == c.end() && n > 0)
			{
				for (value_type *i = loc; i < loc+n; i++)
					i->~value_type();
				memmove(loc, loc+n, (arr->count-offset-n)*sizeof(value_type));
				arr->count -= n;
			}
			else
			{
				alloc(c.end()-j);
				while (j != c.end())
				{
					new (loc) value_type(*j);
					loc++;
					j++;
				}
			}
		}
	};

	struct const_iterator
	{
	protected:
		friend class array<value_type>;
		friend class iterator;
		const array<value_type> *arr;
		const value_type *loc;
	public:
		const_iterator()
		{
			arr = NULL;
			loc = NULL;
		}

		const_iterator(iterator copy)
		{
			arr = copy.arr;
			loc = copy.loc;
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

		const value_type *ptr()
		{
			return loc;
		}

		const value_type &get()
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

		slice<const array<value_type> > sub(int n = -1) const
		{
			const_iterator right;
			if (n < 0)
				right = arr->end()+n;
			else
				right = *this+n-1;
			return slice<const array<value_type> >(*this, right);
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

	value_type *ptr(int i) const
	{
		return data+i;
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

	slice<array<value_type> > sub(int left, int right = -1)
	{
		return slice<array<value_type> >(iterator(this, left), iterator(this, right));
	}

	slice<const array<value_type> > sub(int left, int right = -1) const
	{
		return slice<const array<value_type> >(const_iterator(this, left), const_iterator(this, right));
	}

	static slice<array<value_type> > sub(iterator left, iterator right)
	{
		return slice<array<value_type> >(left, right);
	}

	static slice<const array<value_type> > sub(const_iterator left, const_iterator right)
	{
		return slice<const array<value_type> >(left, right);
	}

	slice<array<value_type> > ref()
	{
		return slice<array<value_type> >(begin(), rbegin());
	}

	slice<const array<value_type> > ref() const
	{
		return slice<const array<value_type> >(begin(), rbegin());
	}

	void push_back(int n, value_type v)
	{
		end().push(n, v);
	}

	void push_front(int n, value_type v)
	{
		begin().push(n, v);
	}

	void push_back(value_type v)
	{
		end().push(v);
	}

	void push_front(value_type v)
	{
		begin().push(v);
	}

	template <class container>
	void append_back(const container &c)
	{
		end().append(c);
	}

	template <class container>
	void append_front(const container &c)
	{
		begin().append(c);
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

	void alloc_back(unsigned int n = 1)
	{
		end().alloc(n);
	}

	void alloc_front(unsigned int n = 1)
	{
		begin().alloc(n);
	}

	/**
	 * \fn void array<value_type>::reserve(int n)
	 * \brief Increase the capacity of the array to at least n possible elements.
	 */
	void reserve(int n)
	{
		if (n > capacity)
		{
			capacity = (1 << (log2i(n)+1));
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
		reserve(count + n);
	}

	/**
	 * \fn void array<value_type>::clear()
	 * \brief Erase all elements from the array.
	 */
	void clear()
	{
		for (int i = 0; i < count; i++)
			data[i].~value_type();
		count = 0;
	}

	void release()
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

	template <class container>
	array<value_type> &operator=(const container &c)
	{
		for (int i = 0; i < count; i++)
			data[i].~value_type();

		count = c.size();
		if (count > capacity)
		{
			if (data != NULL)
				free(data);

			capacity = (1 << (log2i(count)+1));
			data = (value_type*)malloc(sizeof(value_type)*capacity);
		}

		typename container::const_iterator i = c.begin();
		iterator j = begin();
		while (i != c.end() && j != end())
		{
			new (j.ptr()) value_type(*i);
			i++;
			j++;
		}

		return *this;
	}

	array<value_type> &operator=(const array<value_type> &c)
	{
		for (int i = 0; i < count; i++)
			data[i].~value_type();

		count = c.size();
		if (count > capacity)
		{
			if (data != NULL)
				free(data);

			capacity = (1 << (log2i(count)+1));
			data = (value_type*)malloc(sizeof(value_type)*capacity);
		}

		const_iterator i = c.begin();
		iterator j = begin();
		while (i != c.end() && j != end())
		{
			new (j.ptr()) value_type(*i);
			i++;
			j++;
		}

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

template <class value_type>
array<value_type> &operator<<(array<value_type> &a1, const array<value_type> &a2)
{
	a1.push_back(a2);
}

template <class value_type>
array<value_type> &operator<<(array<value_type> &a1, const value_type &a2)
{
	a1.push_back(a2);
}

}

