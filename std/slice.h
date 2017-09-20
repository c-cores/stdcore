/*
 * slice.h
 *
 *  Created on: Oct 13, 2014
 *      Author: nbingham
 */

#pragma once

#include <std/range.h>

namespace core
{

template <class container_type>
struct elem_type
{
	typedef typename container_type::type type;
};

template <class value>
struct elem_type<value*>
{
	typedef value type;
};

template <class container_type>
struct slice;

template <typename container_type>
struct slice_const_iterator;

template <typename container_type>
struct slice_iterator
{
	typedef typename container_type::iterator iterator_type;
	typedef typename container_type::const_iterator const_iterator_type;

	typedef typename elem_type<typename iterator_type::type>::type type;
	
	iterator_type ref;

	slice_iterator() {}
	slice_iterator(const iterator_type &copy) : ref(copy) {}
	~slice_iterator() {}

	operator bool() const
	{
		return (bool)ref && (bool)*ref;
	}

	operator typename iterator_type::type() const
	{
		return *ref;
	}

	type &operator*()
	{
		return **ref;
	}

	type *operator->()
	{
		return &(**ref);
	}

	type *ptr()
	{
		return &(**ref);
	}

	type &get()
	{
		return **ref;
	}

	int idx() const
	{
		return ref.idx();
	}

	slice_iterator<container_type> operator++(int)
	{
		return ref++;
	}

	slice_iterator<container_type> operator--(int)
	{
		return ref--;
	}

	slice_iterator<container_type> &operator++()
	{
		++ref;
		return *this;
	}

	slice_iterator<container_type> &operator--()
	{
		--ref;
		return *this;
	}

	slice_iterator<container_type> &operator+=(int n)
	{
		ref += n;
		return *this;
	}

	slice_iterator<container_type> &operator-=(int n)
	{
		ref -= n;
		return *this;
	}

	slice_iterator<container_type> operator+(int n) const
	{
		return ref + n;
	}

	slice_iterator<container_type> operator-(int n) const
	{
		return ref - n;
	}

	bool operator==(slice_iterator<container_type> i) const
	{
		return ref == i.ref;
	}

	bool operator!=(slice_iterator<container_type> i) const
	{
		return ref != i.ref;
	}

	bool operator==(slice_const_iterator<container_type> i) const
	{
		return ref == i.ref;
	}

	bool operator!=(slice_const_iterator<container_type> i) const
	{
		return ref != i.ref;
	}

	int operator-(slice_iterator<container_type> i) const
	{
		return ref - i.ref;
	}

	int operator-(slice_const_iterator<container_type> i) const
	{
		return ref - i.ref;
	}

	slice<container_type> sub(int length)
	{
		return ref.subcpy(length);
	}

	slice<container_type> subcpy(int length)
	{
		return ref.subcpy(length);
	}

	slice<container_type> sub()
	{
		return ref.subcpy();
	}

	slice<container_type> subcpy()
	{
		return ref.subcpy();
	}

	void swap(slice_iterator<container_type> i)
	{
		ref.get().swap(i.ref.get());
	}

	void swap(slice_const_iterator<container_type> i)
	{
		ref.get().swap(i.ref.get());
	}

	slice_iterator<container_type> &operator=(slice_iterator<container_type> i)
	{
		ref = i.ref;
		return *this;
	}
};

template <typename container_type>
struct slice_const_iterator
{
	typedef typename container_type::iterator iterator_type;
	typedef typename container_type::const_iterator const_iterator_type;

	typedef typename elem_type<typename iterator_type::type>::type type;
	
	const_iterator_type ref;

	slice_const_iterator() {}
	slice_const_iterator(const const_iterator_type &copy) : ref(copy) {}
	~slice_const_iterator() {}

	operator bool() const
	{
		return (bool)ref && (bool)*ref;
	}

	operator typename const_iterator_type::type() const
	{
		return *ref;
	}

	type operator*()
	{
		return **ref;
	}

	type *operator->()
	{
		return &(**ref);
	}

	type *ptr()
	{
		return &(**ref);
	}

	type &get()
	{
		return **ref;
	}

	int idx() const
	{
		return ref.idx();
	}

	slice_const_iterator<container_type> operator++(int)
	{
		return ref++;
	}

	slice_const_iterator<container_type> operator--(int)
	{
		return ref--;
	}

	slice_const_iterator<container_type> &operator++()
	{
		++ref;
		return *this;
	}

	slice_const_iterator<container_type> &operator--()
	{
		++ref;
		return *this;
	}

	slice_const_iterator<container_type> &operator+=(int n)
	{
		ref += n;
		return *this;
	}

	slice_const_iterator<container_type> &operator-=(int n)
	{
		ref -= n;
		return *this;
	}

	slice_const_iterator<container_type> operator+(int n) const
	{
		return ref + n;
	}

	slice_const_iterator<container_type> operator-(int n) const
	{
		return ref - n;
	}

	bool operator==(slice_iterator<container_type> i) const
	{
		return ref == i.ref;
	}

	bool operator!=(slice_iterator<container_type> i) const
	{
		return ref != i.ref;
	}

	bool operator==(slice_const_iterator<container_type> i) const
	{
		return ref == i.ref;
	}

	bool operator!=(slice_const_iterator<container_type> i) const
	{
		return ref != i.ref;
	}

	int operator-(slice_iterator<container_type> i) const
	{
		return ref - i.ref;
	}

	int operator-(slice_const_iterator<container_type> i) const
	{
		return ref - i.ref;
	}

	slice<container_type> sub(int length)
	{
		return ref.subcpy(length);
	}

	slice<container_type> subcpy(int length)
	{
		return ref.subcpy(length);
	}

	slice<container_type> sub()
	{
		return ref.subcpy();
	}

	slice<container_type> subcpy()
	{
		return ref.subcpy();
	}

	slice_const_iterator<container_type> &operator=(slice_const_iterator<container_type> i)
	{
		ref = i.ref;
		return *this;
	}
};

template <class container_type>
struct slice : container<typename elem_type<typename elem_type<container_type>::type>::type, slice_iterator<container_type>, slice_const_iterator<container_type> >
{
	typedef typename elem_type<container_type>::type index_type;
	typedef container<typename elem_type<index_type>::type, slice_iterator<container_type>, slice_const_iterator<container_type> > super;
	
	using typename super::type;
	using typename super::iterator;
	using typename super::const_iterator;

	container_type ref;

	slice() {}
	slice(const_iterator left, const_iterator right) : ref(left.ref, right.ref) {}
	slice(iterator left, iterator right) : ref(left.ref, right.ref) {}

	template <class container_type2>
	slice(const container_type2 &copy) : ref(copy) {}

	~slice() {}

	int size() const
	{
		return ref.size();
	}

	iterator begin()
	{
		return iterator(ref.begin());
	}

	iterator end()
	{
		return iterator(ref.end());
	}

	iterator rbegin()
	{
		return iterator(ref.rbegin());
	}

	iterator rend()
	{
		return iterator(ref.rend());
	}

	const_iterator begin() const
	{
		return const_iterator(ref.begin());
	}

	const_iterator end() const
	{
		return const_iterator(ref.end());
	}

	const_iterator rbegin() const
	{
		return const_iterator(ref.rbegin());
	}

	const_iterator rend() const
	{
		return const_iterator(ref.rend());
	}

	iterator at(int i)
	{
		return iterator(ref.at(i));
	}

	const_iterator at(int i) const
	{
		return const_iterator(ref.at(i));
	}

	type &front()
	{
		return ref.front().get();
	}

	type &back()
	{
		return ref.back().get();
	}

	const type front() const
	{
		return ref.front().get();
	}

	const type back() const
	{
		return ref.back().get();
	}

	type &get(int i)
	{
		return ref.get(i).get();
	}

	type *ptr(int i)
	{
		return ref.get(i).ptr();
	}

	const type &get(int i) const
	{
		return ref.get(i).get();
	}

	const type *ptr(int i) const
	{
		return ref.get(i).ptr();
	}

	type &operator[](int i)
	{
		return ref.get(i).get();
	}

	const type &operator[](int i) const
	{
		return ref.get(i).get();
	}

	core::slice<container_type> sub(int start, int end) const
	{
		typename container_type::const_iterator first = start < 0 ? ref.end() + start : ref.begin() + start;
		typename container_type::const_iterator last = end < 0 ? ref.end() + end : ref.begin() + end;
		return container_type(first, last);
	}

	core::slice<container_type> subcpy(int start, int end) const
	{
		typename container_type::const_iterator first = start < 0 ? ref.end() + start : ref.begin() + start;
		typename container_type::const_iterator last = end < 0 ? ref.end() + end : ref.begin() + end;
		return container_type(first, last);
	}

	core::slice<container_type> sub(int start) const
	{
		typename container_type::const_iterator first = start < 0 ? ref.end() + start : ref.begin() + start;
		return container_type(first, ref.end());
	}

	core::slice<container_type> subcpy(int start) const
	{
		typename container_type::const_iterator first = start < 0 ? ref.end() + start : ref.begin() + start;
		return container_type(first, ref.end());
	}

	core::slice<container_type> sub() const
	{
		return container_type(ref.begin(), ref.end());
	}

	core::slice<container_type> subcpy() const
	{
		return container_type(ref.begin(), ref.end());
	}
};

template <typename iterator_type>
slice<range<iterator_type> > slice_t(iterator_type start, iterator_type end)
{
	return range<iterator_type>(start, end);
}

template <typename iterator_type>
slice<range<iterator_type> > slice_t(slice_iterator<range<iterator_type> > start, slice_iterator<range<iterator_type> > end)
{
	return range<iterator_type>(start.ref.get(), end.ref.get());
}

template <typename container_type>
slice<container_type> deref(const container_type &c)
{
	return c;
}

template <typename container_type>
slice<container_type> deref(const range<slice_iterator<container_type> > &c)
{
	return container_type(c.begin()->ref, c.end()->ref);
}

template <typename container_type>
container_type &ref(slice<container_type> &c)
{
	return c;
}

template <typename container_type>
container_type ref(const slice<container_type> &c)
{
	return c;
}

template <typename container_type>
typename container_type::iterator &ref(typename slice<container_type>::iterator &i)
{
	return i;
}

template <typename container_type>
typename container_type::iterator ref(const typename slice<container_type>::iterator &i)
{
	return i;
}

template <typename container_type>
typename container_type::const_iterator &ref(typename slice<container_type>::const_iterator &i)
{
	return i;
}

template <typename container_type>
typename container_type::const_iterator ref(const typename slice<container_type>::const_iterator &i)
{
	return i;
}

}

