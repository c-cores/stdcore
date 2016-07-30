/*
 * array.h
 *
 *  Created on: Feb 4, 2014
 *      Author: nbingham
 */

#pragma once

#include <core/slice.h>
#include <core/math.h>

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <csignal>
#include <new>

namespace core
{

// A dynamically allocated array structure
template <class value_type>
struct array
{
	typedef value_type type;
	struct const_iterator;

	value_type *data;	// pointer to first object
	int count;			// number of stored objects
	int capacity;		// number of allocated spaces

	struct iterator
	{
	protected:
		friend class array<value_type>;
		friend class const_iterator;

		array<value_type> *root;
		value_type *loc;

		iterator(array<value_type> *root, value_type *loc)
		{
			this->root = root;
			this->loc = loc;
		}
	public:
		typedef value_type type;

		iterator()
		{
			this->root = NULL;
			this->loc = NULL;
		}

		~iterator() {}

		operator bool() const
		{
			return root != NULL && loc >= root->data && loc < root->data+root->count;
		}

		value_type &operator*() const
		{
			return *loc;
		}
		value_type *operator->() const
		{
			return loc;
		}

		value_type *ptr() const
		{
			return loc;
		}

		value_type &get() const
		{
			return *loc;
		}

		int idx() const
		{
			return loc - root->data;
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
			result.root = root;
			result.loc = loc + n;
			return result;
		}

		iterator operator-(int n) const
		{
			iterator result;
			result.root = root;
			result.loc = loc - n;
			return result;
		}

		iterator &operator=(iterator i)
		{
			root = i.root;
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

		bool operator <(iterator i) const
		{
			return loc < i.loc;
		}

		bool operator >(iterator i) const
		{
			return loc > i.loc;
		}

		bool operator <=(iterator i) const
		{
			return loc <= i.loc;
		}

		bool operator >=(iterator i) const
		{
			return loc >= i.loc;
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

		bool operator <(const_iterator i) const
		{
			return loc < i.loc;
		}

		bool operator >(const_iterator i) const
		{
			return loc > i.loc;
		}

		bool operator <=(const_iterator i) const
		{
			return loc <= i.loc;
		}

		bool operator >=(const_iterator i) const
		{
			return loc >= i.loc;
		}

		int operator-(const_iterator i) const
		{
			return loc - i.loc;
		}

		void alloc(int n = 1)
		{
			if (n == 0)
				return;

			bool neg = n < 0;
			if (neg)
				n = -n;

			int offset = loc - root->data;
			if (root->count > 0 && root->count+n <= root->capacity)
				memmove(loc+n, loc, (root->count-offset)*sizeof(value_type));
			else if (root->count+n > root->capacity)
			{
				root->capacity = (1 << (log2i(root->count + n)+1));
				value_type *newdata = (value_type*)malloc(sizeof(value_type)*root->capacity);

				if (root->data != NULL)
				{
					memcpy(newdata, root->data, offset*sizeof(value_type));
					memcpy(newdata+offset+n, loc, (root->count-offset)*sizeof(value_type));
					free(root->data);
				}
				root->data = newdata;
				loc = root->data + offset;
			}

			if (neg)
				loc += n;

			root->count += n;
		}

		/* Erase all elements in the range [this, this+n) */
		void drop(int n = 1)
		{
			if (n == 0)
				return;

			bool neg = n < 0;
			if (neg)
			{
				loc += n;
				n = -n;
			}

			int offset = loc - root->data;
			n = min(offset + n, root->count) - offset;
			for (value_type *i = loc; i < loc+n; i++)
				i->~value_type();
			memmove(loc, loc+n, (root->count-offset-n)*sizeof(value_type));

			root->count -= n;
		}


		/* Erase all elements in the range [this, this+n) */
		array<value_type> pop(int n = 1)
		{
			array<value_type> result;

			if (n == 0)
				return result;

			bool neg = n < 0;
			if (neg)
			{
				loc += n;
				n = -n;
			}

			int offset = loc - root->data;
			n = min(offset + n, root->count) - offset;
			result.reserve(n);
			memcpy(result.data, loc, n*sizeof(value_type));
			result.count = n;
			memmove(loc, loc+n, (root->count-offset-n)*sizeof(value_type));
			root->count -= n;

			return result;
		}

		void push(value_type v)
		{
			alloc(1);
			new (loc) value_type(v);
			loc++;
		}

		template <class container>
		void append(const container &c)
		{
			int n = c.size();
			typename container::const_iterator i = c.begin();
			alloc(n);

			for (i = c.begin(); i; i++)
			{
				new (loc) value_type(*i);
				loc++;
			}
		}

		void replace(int n, value_type v)
		{
			bool neg = n < 0;
			if (neg)
			{
				loc += n;
				n = -n;
			}
			else if (n == 0)
				return;

			*loc = v;

			if (n > 1)
			{
				value_type *mid = loc+1;
				value_type *fin = loc+n;
				for (value_type *i = mid; i < fin; i++)
					i->~value_type();
				memmove(mid, fin, (root->count - n)*sizeof(value_type));
				root->count -= n-1;
			}

			if (neg)
				loc++;
		}

		template <class container>
		void replace(int n, const container &c)
		{
			int s = c.size();
			bool neg = n < 0;
			if (neg)
			{
				loc += n;
				n = -n;
			}

			int lower, upper;
			if (n < s)
			{
				lower = n;
				upper = s;
			}
			else
			{
				lower = s;
				upper = n;
			}

			int diff = upper-lower;
			value_type *mid = loc+lower;
			value_type *fin = loc+upper;
			typename container::const_iterator j = c.begin();
			for (value_type *i = loc; i < mid && j; i++, j++)
				*i = *j;

			if (s < n)
			{
				for (value_type *i = mid; i < fin; i++)
					i->~value_type();
				memmove(mid, fin, (root->count - upper)*sizeof(value_type));
				root->count -= diff;

			}
			else if (n < s)
			{
				alloc(diff);
				// mid and fin are no longer valid after alloc
				mid = loc+lower;
				fin = loc+upper;
				for (value_type *i = mid; i < fin && j; i++, j++)
					new (i) value_type(*j);
			}

			if (neg)
				loc += s;
		}

		template <class iterator_type>
		void swap(iterator_type i)
		{
			value_type temp;
			memcpy(&temp, loc, sizeof(value_type));
			memcpy(loc, i.ptr(), sizeof(value_type));
			memcpy(i.ptr(), &temp, sizeof(value_type));
		}

		core::slice<range<iterator> > sub(int length)
		{
			if (length < 0)
				return range<iterator>(*this+length, *this);
			else
				return range<iterator>(*this, *this+length);
		}

		array<value_type> subcpy(int length)
		{
			if (length < 0)
				return array<value_type>(range<iterator>(*this+length, *this).deref());
			else
				return array<value_type>(range<iterator>(*this, *this+length).deref());
		}

		core::slice<range<iterator> > sub()
		{
			return range<iterator>(*this, root->end());
		}

		array<value_type> subcpy()
		{
			return range<iterator>(*this, root->end()).deref();
		}
	};

	struct const_iterator
	{
	protected:
		friend class array<value_type>;
		friend class iterator;
		const array<value_type> *root;
		const value_type *loc;

		const_iterator(const array<value_type> *root, const value_type *loc)
		{
			this->root = root;
			this->loc = loc;
		}
	public:
		typedef value_type type;

		const_iterator()
		{
			root = NULL;
			loc = NULL;
		}

		const_iterator(iterator copy)
		{
			root = copy.root;
			loc = copy.loc;
		}

		~const_iterator() {}

		operator bool() const
		{
			return root != NULL && loc >= root->data && loc < root->data+root->count;
		}

		const value_type &operator*() const
		{
			return *loc;
		}
		const value_type *operator->() const
		{
			return loc;
		}

		const value_type *ptr() const
		{
			return loc;
		}

		const value_type &get() const
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
			result.root = root;
			result.loc = loc + n;
			return result;
		}

		const_iterator operator-(int n) const
		{
			const_iterator result;
			result.root = root;
			result.loc = loc - n;
			return result;
		}

		const_iterator &operator=(const_iterator i)
		{
			root = i.root;
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

		bool operator <(const_iterator i) const
		{
			return loc < i.loc;
		}

		bool operator >(const_iterator i) const
		{
			return loc > i.loc;
		}

		bool operator <=(const_iterator i) const
		{
			return loc <= i.loc;
		}

		bool operator >=(const_iterator i) const
		{
			return loc >= i.loc;
		}

		int operator-(const_iterator i) const
		{
			return loc - i.loc;
		}

		const_iterator &operator=(iterator i)
		{
			root = i.root;
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

		bool operator <(iterator i) const
		{
			return loc < i.loc;
		}

		bool operator >(iterator i) const
		{
			return loc > i.loc;
		}

		bool operator <=(iterator i) const
		{
			return loc <= i.loc;
		}

		bool operator >=(iterator i) const
		{
			return loc >= i.loc;
		}

		int operator-(iterator i) const
		{
			return loc - i.loc;
		}

		core::slice<range<const_iterator> > sub(int length)
		{
			if (length < 0)
				return range<const_iterator>(*this+length, *this);
			else
				return range<const_iterator>(*this, *this+length);
		}

		array<value_type> subcpy(int length)
		{
			if (length < 0)
				return array<value_type>(range<const_iterator>(*this+length, *this).deref());
			else
				return array<value_type>(range<const_iterator>(*this, *this+length).deref());
		}

		core::slice<range<const_iterator> > sub()
		{
			return range<const_iterator>(*this, root->end());
		}

		array<value_type> subcpy()
		{
			return range<const_iterator>(*this, root->end()).deref();
		}
	};

	array()
	{
		data = NULL;
		count = 0;
		capacity = 0;
	}

	// Initialize this array as a copy of some other container
	template <class container>
	array(const container &a)
	{
		count = a.size();
		capacity = (1 << (log2i(count)+1));
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		value_type *ptr = data;
		for (typename container::const_iterator i = a.begin(); i; i++, ptr++)
			new (ptr) value_type(*i);
	}

	// Initialize this array as a copy of some other container
	template <class container>
	array(typename container::const_iterator left, typename container::const_iterator right)
	{
		count = right - left;
		capacity = (1 << (log2i(count)+1));
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		value_type *ptr = data;
		for (typename container::const_iterator i = left; i != right; i++, ptr++)
			new (ptr) value_type(*i);
	}

	array(const_iterator left, const_iterator right)
	{
		count = right - left;
		capacity = (1 << (log2i(count)+1));
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		value_type *ptr = data;
		for (const_iterator i = left; i != right; i++, ptr++)
			new (ptr) value_type(*i);
	}

	// Initialize this array as a copy of some other container
	template <class container>
	array(typename container::iterator left, typename container::iterator right)
	{
		count = right - left;
		capacity = (1 << (log2i(count)+1));
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		value_type *ptr = data;
		for (typename container::iterator i = left; i != right; i++, ptr++)
			new (ptr) value_type(*i);
	}

	array(iterator left, iterator right)
	{
		count = right - left;
		capacity = (1 << (log2i(count)+1));
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		value_type *ptr = data;
		for (iterator i = left; i != right; i++, ptr++)
			new (ptr) value_type(*i);
	}

	// Initialize this array as a copy of another array
	array(const array<value_type> &a)
	{
		count = a.size();
		capacity = a.capacity;
		data = (value_type*)malloc(sizeof(value_type)*capacity);
		value_type *ptr = data;
		for (const_iterator i = a.begin(); i; i++, ptr++)
			new (ptr) value_type(*i);
	}

	static array<value_type> values(int n, ...)
	{
		array<value_type> result;
		result.capacity = (1 << (log2i(n)+1));
		result.data = (value_type*)malloc(sizeof(value_type)*result.capacity);

		va_list args;
		va_start(args, n);
		for (result.count = 0; result.count < n; result.count++)
			new (result.data+result.count) value_type(va_arg(args, value_type));
		va_end(args);

		return result;
	}

	// delete all of the initialized objects in the array
	// and free the memory block allocated for them
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

	int size() const
	{
		return count;
	}

	iterator at(int i)
	{
		return iterator(this, data + (i < 0 ? i+count : i));
	}

	const_iterator at(int i) const
	{
		return const_iterator(this, data + (i < 0 ? i+count : i));
	}

	value_type &get(int i)
	{
		return *(data + (i < 0 ? i+count : i));
	}

	const value_type &get(int i) const
	{
		return *(data + (i < 0 ? i+count : i));
	}

	value_type *ptr(int i)
	{
		return data + (i < 0 ? i+count : i);
	}

	const value_type *ptr(int i) const
	{
		return data + (i < 0 ? i+count : i);
	}

	value_type &operator[](int i)
	{
		return *(data + (i < 0 ? i+count : i));
	}

	const value_type &operator[](int i) const
	{
		return *(data + (i < 0 ? i+count : i));
	}

	value_type &front()
	{
		return *data;
	}

	const value_type &front() const
	{
		return *data;
	}

	value_type &back()
	{
		return *(data + count-1);
	}

	const value_type &back() const
	{
		return *(data + count-1);
	}

	iterator begin()
	{
		return iterator(this, data);
	}

	iterator end()
	{
		return iterator(this, data+count);
	}

	iterator rbegin()
	{
		return iterator(this, data+count-1);
	}

	iterator rend()
	{
		return iterator(this, data-1);
	}

	const_iterator begin() const
	{
		return const_iterator(this, data);
	}

	const_iterator end() const
	{
		return const_iterator(this, data+count);
	}

	const_iterator rbegin() const
	{
		return const_iterator(this, data+count-1);
	}

	const_iterator rend() const
	{
		return const_iterator(this, data-1);
	}

	core::slice<array<value_type> > deref()
	{
		return *this;
	}

	template <class container>
	core::slice<array<typename container::iterator> > slice(container &c)
	{
		array<typename container::iterator> result;
		result.reserve(count);
		for (int i = 0; i < count; i++)
			result.push_back(c.at(data[i]));
		return result;
	}

	template <class container>
	core::slice<array<typename container::const_iterator> > slice(const container &c)
	{
		array<typename container::const_iterator> result;
		result.reserve(count);
		for (int i = 0; i < count; i++)
			result.push_back(c.at(data[i]));
		return result;
	}

	core::slice<range<iterator> > sub(int start, int end)
	{
		return range<iterator>(at(start), at(end));
	}

	array<value_type> subcpy(int start, int end)
	{
		return range<iterator>(at(start), at(end)).deref();
	}

	core::slice<range<iterator> > sub(int start)
	{
		return range<iterator>(at(start), this->end());
	}

	array<value_type> subcpy(int start)
	{
		return range<iterator>(at(start), this->end()).deref();
	}

	core::slice<range<iterator> > sub()
	{
		return range<iterator>(begin(), end());
	}

	array<value_type> subcpy()
	{
		return range<iterator>(begin(), end()).deref();
	}

	core::slice<range<const_iterator> > sub(int start, int end) const
	{
		return range<const_iterator>(at(start), at(end));
	}

	array<value_type> subcpy(int start, int end) const
	{
		return range<const_iterator>(at(start), at(end)).deref();
	}

	core::slice<range<const_iterator> > sub(int start) const
	{
		return range<const_iterator>(at(start), this->end());
	}

	array<value_type> subcpy(int start) const
	{
		return range<const_iterator>(at(start), this->end()).deref();
	}

	core::slice<range<const_iterator> > sub() const
	{
		return range<const_iterator>(begin(), end());
	}

	array<value_type> subcpy() const
	{
		return range<const_iterator>(begin(), end()).deref();
	}

	static core::slice<range<iterator> > sub(iterator start, iterator end)
	{
		return range<iterator>(start, end).deref();
	}

	static core::slice<range<const_iterator> > sub(const_iterator start, const_iterator end)
	{
		return range<const_iterator>(start, end).deref();
	}

	void alloc_back(unsigned int n = 1)
	{
		end().alloc(n);
	}

	void alloc_back_unsafe(unsigned int n = 1)
	{
		count += n;
	}

	void alloc_front(unsigned int n = 1)
	{
		begin().alloc(n);
	}
	
	static void drop(iterator start, iterator end)
	{
		start.root->drop(start.idx(), end.idx());
	}

	void drop(int start, int end)
	{
		if (start < 0)
			start += count;

		if (end < 0)
			end += count;

		int n = end - start;
		for (value_type *i = data+start; i < data+end; i++)
			i->~value_type();
		memmove(data+start, data+end, (count-end)*sizeof(value_type));
		count -= n;
	}

	void drop_back(int n = 1)
	{
		drop(-n, count);
	}

	void drop_front(int n = 1)
	{
		drop(0, n);
	}

	static array<value_type> pop(iterator start, iterator end)
	{
		return start.root->pop(start.idx(), end.idx());
	}

	array<value_type> pop(int start, int end)
	{
		if (start < 0)
			start += count;

		if (end < 0)
			end += count;

		array<value_type> result;

		int n = end - start;
		result.reserve(n);
		memcpy(result.data, data+start, n*sizeof(value_type));
		result.count = n;
		memmove(data+start, data+end, (count-end)*sizeof(value_type));
		count -= n;

		return result;
	}

	array<value_type> pop_back(int n = 1)
	{
		return pop(-n, count);
	}

	array<value_type> pop_front(int n = 1)
	{
		return pop(0, n);
	}

	void push_back(value_type v)
	{
		end().push(v);
	}

	void push_back_unsafe(value_type v)
	{
		new (data+count) value_type(v);
		count++;
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
	void append_back_unsafe(const container &c)
	{
		for (typename container::const_iterator i = c.begin(); i; i++, count++)
			new (data+count) value_type(*i);
	}

	template <class container>
	void append_front(const container &c)
	{
		begin().append(c);
	}

	static void replace(iterator start, iterator end, value_type v)
	{
		start.root->replace(start.idx(), end.idx(), v);
	}

	void replace(int start, int end, value_type v)
	{
		if (start < 0)
			start += count;

		if (end < 0)
			end += count;

		int n = end-start;
		int lower, upper;
		if (n > 1)
		{
			lower = start+1;
			upper = end;
		}
		else
		{
			lower = end;
			upper = start+1;
		}

		int diff = upper-lower;
		value_type *mid = data+lower;
		value_type *i;
		for (i = data+start; i < mid; i++)
			*i = v;

		if (1 < n)
		{
			value_type *fin = data+upper;
			for (; i < fin; i++)
				i->~value_type();
			memmove(mid, fin, (count-upper)*sizeof(value_type));
			count -= diff;
		}
		else if (n < 1)
		{
			at(lower).alloc(diff);
			value_type *fin = data+upper;
			for (i = data+lower; i < fin; i++)
				new (i) value_type(v);
		}
	}

	template <class container>
	static void replace(iterator start, iterator end, const container &c)
	{
		start.root->replace(start.idx(), end.idx(), c);
	}

	template <class container>
	void replace(int start, int end, const container &c)
	{
		int s = c.size();
		if (start < 0)
			start += count;

		if (end < 0)
			end += count;

		int n = end-start;
		int lower, upper;
		if (n > s)
		{
			lower = start+s;
			upper = end;
		}
		else
		{
			lower = end;
			upper = start+s;
		}

		int diff = upper-lower;
		value_type *mid = data+lower;
		value_type *i;
		typename container::const_iterator j = c.begin();
		for (i = data+start; i < mid && j; i++, j++)
			*i = *j;

		if (c.size() < n)
		{
			value_type *fin = data+upper;
			for (; i < fin; i++)
				i->~value_type();
			memmove(mid, fin, (count-upper)*sizeof(value_type));
			count -= diff;
		}
		else if (n < s)
		{
			at(lower).alloc(diff);
			value_type *fin = data+upper;
			for (i = data+lower; i < fin && j; i++, j++)
				new (i) value_type(*j);
		}
	}

	void replace_back(int n, const value_type &v)
	{
		replace(-n, count, v);
	}

	template <class container>
	void replace_back(int n, const container &c)
	{
		replace(-n, count, c);
	}

	void replace_front(int n, const value_type &v)
	{
		replace(0, n, v);
	}

	template <class container>
	void replace_front(int n, const container &c)
	{
		replace(0, n, c);
	}

	void swap(array<value_type> &arr)
	{
		int tmp_capacity = capacity;
		int tmp_count = count;
		value_type* tmp_data = data;
		capacity = arr.capacity;
		count = arr.count;
		data = arr.data;
		arr.capacity = tmp_capacity;
		arr.count = tmp_count;
		arr.data = tmp_data;
	}

	void resize(int n, const value_type &v = value_type())
	{
		if (n > count)
		{
			reserve(n);
			while (count < n)
				push_back_unsafe(v);
		}
		else if (n < count)
			drop_back(count-n);
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
	void extend(int n)
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
		while (i && j != end())
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
		while (i && j)
		{
			new (j.ptr()) value_type(*i);
			i++;
			j++;
		}

		return *this;
	}
};

template <class value_type>
array<value_type> &operator<<(array<value_type> &os, const value_type &v)
{
	os.push_back(v);
	return os;
}

template <class value_type, class container>
array<value_type> &operator<<(array<value_type> &os, const container &c)
{
	os.append_back(c);
	return os;
}

template <class value_type>
array<value_type> operator<<(array<value_type> os, const value_type &v)
{
	os.push_back(v);
	return os;
}

template <class value_type, class container>
array<value_type> operator<<(array<value_type> os, const container &c)
{
	os.append_back(c);
	return os;
}

template<class value_type>
bool operator==(array<value_type> a0, array<value_type> a1)
{
	return (compare(a0, a1) == 0);
}

template<class value_type>
bool operator!=(array<value_type> a0, array<value_type> a1)
{
	return (compare(a0, a1) != 0);
}

template<class value_type>
bool operator<(array<value_type> a0, array<value_type> a1)
{
	return (compare(a0, a1) < 0);
}

template<class value_type>
bool operator>(array<value_type> a0, array<value_type> a1)
{
	return (compare(a0, a1) > 0);
}

template<class value_type>
bool operator<=(array<value_type> a0, array<value_type> a1)
{
	return (compare(a0, a1) <= 0);
}

template<class value_type>
bool operator>=(array<value_type> a0, array<value_type> a1)
{
	return (compare(a0, a1) >= 0);
}

template<class value_type, class container>
bool operator==(array<value_type> a0, slice<container> a1)
{
	return (compare(a0, a1) == 0);
}

template<class value_type, class container>
bool operator!=(array<value_type> a0, slice<container> a1)
{
	return (compare(a0, a1) != 0);
}

template<class value_type, class container>
bool operator<(array<value_type> a0, slice<container> a1)
{
	return (compare(a0, a1) < 0);
}

template<class value_type, class container>
bool operator>(array<value_type> a0, slice<container> a1)
{
	return (compare(a0, a1) > 0);
}

template<class value_type, class container>
bool operator<=(array<value_type> a0, slice<container> a1)
{
	return (compare(a0, a1) <= 0);
}

template<class value_type, class container>
bool operator>=(array<value_type> a0, slice<container> a1)
{
	return (compare(a0, a1) >= 0);
}


template<class container, class value_type>
bool operator==(slice<container> a0, array<value_type> a1)
{
	return (compare(a0, a1) == 0);
}

template<class container, class value_type>
bool operator!=(slice<container> a0, array<value_type> a1)
{
	return (compare(a0, a1) != 0);
}

template<class container, class value_type>
bool operator<(slice<container> a0, array<value_type> a1)
{
	return (compare(a0, a1) < 0);
}

template<class container, class value_type>
bool operator>(slice<container> a0, array<value_type> a1)
{
	return (compare(a0, a1) > 0);
}

template<class container, class value_type>
bool operator<=(slice<container> a0, array<value_type> a1)
{
	return (compare(a0, a1) <= 0);
}

template<class container, class value_type>
bool operator>=(slice<container> a0, array<value_type> a1)
{
	return (compare(a0, a1) >= 0);
}

}

