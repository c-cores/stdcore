/*
 * list.h
 *
 *  Created on: Feb 4, 2014
 *      Author: nbingham
 */

#pragma once

#include <std/range.h>
#include <std/slice.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

namespace core
{

struct list_end_item
{
	list_end_item()
	{
		next = this;
		prev = this;
	}

	virtual ~list_end_item()
	{
	}

	list_end_item *next;
	list_end_item *prev;
};

template <typename value_type>
struct list_item : list_end_item
{
	list_item()
	{
	}

	list_item(const value_type &value)
	{
		this->value = value;
	}

	~list_item()
	{
	}

	value_type value;
};

template <typename value_type>
struct list;

template <typename value_type>
struct list_const_iterator;

template <typename value_type>
struct list_iterator
{
	friend class list<value_type>;
	friend class list_const_iterator<value_type>;
	typedef value_type type;
	
	list_end_item *loc;

	list_iterator(list_end_item *loc)
	{
		this->loc = loc;
	}
	
	list_iterator()
	{
		loc = NULL;
	}

	list_iterator(const list_iterator<value_type> &copy)
	{
		loc = copy.loc;
	}

	~list_iterator() {}

	operator bool() const
	{
		return loc != NULL and loc->next != loc and loc->prev != loc;
	}

	value_type &operator*() const
	{
		return ((list_item<value_type>*)loc)->value;
	}
	value_type *operator->() const
	{
		return &((list_item<value_type>*)loc)->value;
	}

	value_type *ptr() const
	{
		return &((list_item<value_type>*)loc)->value;
	}

	value_type &get() const
	{
		return ((list_item<value_type>*)loc)->value;
	}

	int idx() const
	{
		int count = -1;
		for (list_end_item *i = loc; i->prev != i; i = i->prev)
			count++;
		return count;
	}

	list_iterator<value_type> operator++(int)
	{
		list_iterator<value_type> result = *this;
		loc = loc->next;
		return result;
	}

	list_iterator<value_type> operator--(int)
	{
		list_iterator<value_type> result = *this;
		loc = loc->prev;
		return result;
	}

	list_iterator<value_type> &operator++()
	{
		loc = loc->next;
		return *this;
	}

	list_iterator<value_type> &operator--()
	{
		loc = loc->prev;
		return *this;
	}

	list_iterator<value_type> &operator+=(int n)
	{
		while (n > 0 and loc->next != loc)
		{
			loc = loc->next;
			n--;
		}

		while (n < 0 and loc->prev != loc)
		{
			loc = loc->prev;
			n++;
		}

		return *this;
	}

	list_iterator<value_type> &operator-=(int n)
	{
		while (n < 0 and loc->next != loc)
		{
			loc = loc->next;
			n++;
		}

		while (n > 0 and loc->prev != loc)
		{
			loc = loc->prev;
			n--;
		}

		return *this;
	}

	list_iterator<value_type> operator+(int n) const
	{
		list_iterator<value_type> result(*this);
		result += n;
		return result;
	}

	list_iterator<value_type> operator-(int n) const
	{
		list_iterator<value_type> result(*this);
		result -= n;
		return result;
	}

	bool operator==(list_iterator<value_type> i) const
	{
		return loc == i.loc or (!i and !*this);
	}

	bool operator!=(list_iterator<value_type> i) const
	{
		return loc != i.loc and (i or *this);
	}

	int operator-(list_iterator<value_type> i) const
	{
		int c0 = 0, c1 = 0;
		list_iterator<value_type> j = i;
		while (i.loc != loc and j.loc != loc)
		{
			j.loc = j.loc->next;
			c1++;
			i.loc = i.loc->prev;
			c0--;
		}

		if (i.loc == loc)
			return c0;
		else if (j.loc == loc)
			return c1;
		else
			return c1 - c0;
	}

	bool operator==(list_const_iterator<value_type> i) const
	{
		return loc == i.loc;
	}

	bool operator!=(list_const_iterator<value_type> i) const
	{
		return loc != i.loc;
	}

	int operator-(list_const_iterator<value_type> i) const
	{
		int c0 = 0, c1 = 0;
		list_const_iterator<value_type> j = i;
		while (i.loc != loc and j.loc != loc)
		{
			j.loc = j.loc->next;
			c1++;
			i.loc = i.loc->prev;
			c0--;
		}

		if (i.loc == loc)
			return c0;
		else if (j.loc == loc)
			return c1;
		else
			return c1 - c0;
	}

	core::slice<range<list_iterator<value_type> > > sub(int length) const
	{
		if (length < 0)
			return range<list_iterator<value_type> >(*this+length, *this);
		else
			return range<list_iterator<value_type> >(*this, *this+length);
	}

	list<value_type> subcpy(int length) const
	{
		if (length < 0)
			return list<value_type>(*this+length, *this);
		else
			return list<value_type>(*this, *this+length);
	}

	core::slice<range<list_iterator<value_type> > > sub() const
	{
		return range<list_iterator<value_type> >(*this, list_iterator<value_type>());
	}

	list<value_type> subcpy() const
	{
		return list<value_type>(*this, list_iterator<value_type>());
	}

	void drop(int n = 1)
	{
		if (n > 0)
		{
			list_end_item* start = loc->prev;
			
			for (int i = 0; i < n and loc->next != loc; i++)
			{
				list_end_item *temp = loc->next;
				delete loc;
				loc = temp;
			}
				
			start->next = loc;
			loc->prev = start;
		}
		else if (n < 0)
		{
			list_end_item *start = loc->prev;
			
			for (int i = 0; i > n and start->prev != start; i--)
			{
				list_end_item *temp = start->prev;
				delete start;
				start = temp;
			}
			
			start->next = loc;
			loc->prev = start;
		}
	}

	list<value_type> pop(int n = 1)
	{
		list<value_type> result;
		list_end_item *start = loc;
		for (int i = 0; i < n and loc->next != loc; i++)
			loc = loc->next;
		for (int i = 0; i > n and start->prev != start and start->prev->prev != start->prev; i--)
			start = start->prev;

		if (start != loc)
		{
			result.left->next = start;
			result.right->prev = loc->prev;
			start->prev->next = loc;
			loc->prev = start->prev;
			result.left->next->prev = result.left;
			result.right->prev->next = result.right;
		}

		return result;
	}

	void push(value_type v) const
	{
		list_end_item *start = loc->prev;
		start->next = new list_item<value_type>(v);
		start->next->prev = start;
		start = start->next;
		start->next = loc;
		loc->prev = start;
	}

	template <class container>
	void append(const container &c) const
	{
		list_end_item *start = loc->prev;
		for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
		{
			start->next = new list_item<value_type>(*i);
			start->next->prev = start;
			start = start->next;
		}

		start->next = loc;
		loc->prev = start;
	}

	void replace(int n, value_type v)
	{
		if (n < 0)
		{
			*this += n;
			n = -n;
		}

		if (loc->next == loc)
		{
			push(v);
			loc = loc->next;
		}
		else
		{
			((list_item<value_type>*)loc)->value = v;
			loc = loc->next;
			drop(n-1);
		}
	}
	
	template <class container>
	void replace(int n, const container &c)
	{
		if (n < 0)
		{
			*this += n;
			n = -n;
		}

		typename container::const_iterator j = c.begin();
		while (n > 0 and j and loc->next != loc)
		{
			((list_item<value_type>*)loc)->value = *j;
			loc = loc->next;
			n--;
			j++;
		}

		if (j)
			append(j.sub());
		else if (n > 0)
			drop(n);
	}

	template <class iterator_type>
	void swap(iterator_type i) const
	{
		value_type temp;
		memcpy(&temp, &((list_item<value_type>*)loc)->value, sizeof(value_type));
		memcpy(&((list_item<value_type>*)loc)->value, &((list_item<value_type>*)i.loc)->value, sizeof(value_type));
		memcpy(&((list_item<value_type>*)i.loc)->value, &temp, sizeof(value_type));
	}

	void swap(list_iterator<value_type> &i)
	{
		list_end_item *next1 = loc->next;
		list_end_item *prev1 = loc->prev;
		list_end_item *next2 = i.loc->next;
		list_end_item *prev2 = i.loc->prev;
		next1->prev = i.loc;
		prev1->next = i.loc;
		next2->prev = loc;
		prev2->next = loc;
		loc->next = next2;
		loc->prev = prev2;
		i.loc->next = next1;
		i.loc->prev = prev1;

		next1 = loc;
		loc = i.loc;
		i.loc = next1;
	}

	list_iterator<value_type> &operator=(list_iterator<value_type> i)
	{
		loc = i.loc;
		return *this;
	}
};

template <typename value_type>
struct list_const_iterator
{
protected:
	friend class list<value_type>;
	friend class list_iterator<value_type>;
	const list_end_item *loc;

	list_const_iterator(const list_end_item *n)
	{
		loc = n;
	}
public:
	typedef value_type type;

	list_const_iterator()
	{
		loc = NULL;
	}

	list_const_iterator(const list<value_type> *l)
	{
		loc = l->left;
	}

	list_const_iterator(const list_iterator<value_type> &i)
	{
		loc = i.loc;
	}

	list_const_iterator(const list_const_iterator<value_type> &i)
	{
		loc = i.loc;
	}

	~list_const_iterator() {}

	operator bool() const
	{
		return loc != NULL and loc->next != loc and loc->prev != loc;
	}

	const value_type &operator*() const
	{
		return ((list_item<value_type>*)loc)->value;
	}

	const value_type *operator->() const
	{
		return &((list_item<value_type>*)loc)->value;
	}

	const value_type &get() const
	{
		return ((list_item<value_type>*)loc)->value;
	}

	const value_type *ptr() const
	{
		return &((list_item<value_type>*)loc)->value;
	}

	list_const_iterator<value_type> &ref()
	{
		return *this;
	}

	const list_const_iterator<value_type> &ref() const
	{
		return *this;
	}

	int idx() const
	{
		int count = -1;
		for (list_end_item *i = loc; i->prev != i; i = i->prev)
			count++;
		return count;
	}

	list_const_iterator<value_type> operator++(int)
	{
		list_const_iterator<value_type> result = *this;
		loc = loc->next;
		return result;
	}

	list_const_iterator<value_type> operator--(int)
	{
		list_const_iterator<value_type> result = *this;
		loc = loc->prev;
		return result;
	}

	list_const_iterator<value_type> &operator++()
	{
		loc = loc->next;
		return *this;
	}

	list_const_iterator<value_type> &operator--()
	{
		loc = loc->prev;
		return *this;
	}

	list_const_iterator<value_type> &operator+=(int n)
	{
		while (n > 0 and loc->next != loc)
		{
			loc = loc->next;
			n--;
		}

		while (n < 0 and loc->prev != loc)
		{
			loc = loc->prev;
			n++;
		}

		return *this;
	}

	list_const_iterator<value_type> &operator-=(int n)
	{
		while (n < 0 and loc->next != loc)
		{
			loc = loc->next;
			n++;
		}

		while (n > 0 and loc->prev != loc)
		{
			loc = loc->prev;
			n--;
		}

		return *this;
	}

	list_const_iterator<value_type> operator+(int n) const
	{
		list_const_iterator<value_type> result(*this);
		result += n;
		return result;
	}

	list_const_iterator<value_type> operator-(int n) const
	{
		list_const_iterator<value_type> result(*this);
		result -= n;
		return result;
	}

	bool operator==(list_const_iterator<value_type> i) const
	{
		return loc == i.loc or (!i and !*this);
	}

	bool operator!=(list_const_iterator<value_type> i) const
	{
		return loc != i.loc and (i or *this);
	}

	bool operator==(list_iterator<value_type> i) const
	{
		return loc == i.loc or (!i and !*this);
	}

	bool operator!=(list_iterator<value_type> i) const
	{
		return loc != i.loc and (i or *this);
	}

	int operator-(list_const_iterator<value_type> i) const
	{
		int c0 = 0, c1 = 0;
		list_const_iterator<value_type> j = i;
		while (i.loc != loc and j.loc != loc)
		{
			j.loc = j.loc->next;
			c1++;
			i.loc = i.loc->prev;
			c0--;
		}

		if (i.loc == loc)
			return c0;
		else if (j.loc == loc)
			return c1;
		else
			return c1 - c0;
	}

	int operator-(list_iterator<value_type> i) const
	{
		int c0 = 0, c1 = 0;
		list_const_iterator<value_type> j = i;
		while (i.loc != loc and j.loc != loc)
		{
			j.loc = j.loc->next;
			c1++;
			i.loc = i.loc->prev;
			c0--;
		}

		if (i.loc == loc)
			return c0;
		else if (j.loc == loc)
			return c1;
		else
			return c1 - c0;
	}

	core::slice<range<list_const_iterator<value_type> > > sub(int length) const
	{
		if (length < 0)
			return range<list_const_iterator<value_type> >(*this+length, *this);
		else
			return range<list_const_iterator<value_type> >(*this, *this+length);
	}

	list<value_type> subcpy(int length) const
	{
		if (length < 0)
			return list<value_type>(*this+length, *this);
		else
			return list<value_type>(*this, *this+length);
	}

	core::slice<range<list_const_iterator<value_type> > > sub() const
	{
		return range<list_const_iterator<value_type> >(*this, list_const_iterator<value_type>());
	}

	list<value_type> subcpy() const
	{
		return list<value_type>(*this, list_const_iterator<value_type>());
	}

	list_const_iterator<value_type> &operator=(list_const_iterator<value_type> i)
	{
		loc = i.loc;
		return *this;
	}

	list_const_iterator<value_type> &operator=(list_iterator<value_type> i)
	{
		loc = i.loc;
		return *this;
	}
};

template <class value_type>
struct list : container<value_type, list_iterator<value_type>, list_const_iterator<value_type> >
{
	typedef container<value_type, list_iterator<value_type>, list_const_iterator<value_type> > super;

	using typename super::type;
	using typename super::iterator;
	using typename super::const_iterator;

	typedef list_end_item end_item;
	typedef list_item<value_type> item;

	end_item *left;
	end_item *right;

	list()
	{
		left = new end_item();
		right = new end_item();
		left->next = right;
		right->prev = left;
	}

	list(const value_type &c)
	{
		left = new end_item();
		right = new end_item();
		left->next = right;
		right->prev = left;
		end().push(c);
	}

	template <class container>
	list(const container &c)
	{
		left = new end_item();
		right = new end_item();
		left->next = right;
		right->prev = left;
		for (typename container::const_iterator i = c.begin(); i; i++)
			end().push(*i);
	}

	list(const list<value_type> &c)
	{
		left = new end_item();
		right = new end_item();
		left->next = right;
		right->prev = left;
		for (const_iterator i = c.begin(); i; i++)
			end().push(*i);
	}

	list(iterator left, iterator right)
	{
		left = new end_item();
		right = new end_item();
		this->left->next = this->right;
		this->right->prev = this->left;
		for (iterator i = left; i != right; i++)
			end().push(*i);
	}

	list(const_iterator left, const_iterator right)
	{
		left = new end_item();
		right = new end_item();
		this->left->next = this->right;
		this->right->prev = this->left;
		for (const_iterator i = left; i != right; i++)
			end().push(*i);
	}

	// Initialize this list as a copy of some other container
	template <class container>
	list(typename container::iterator left, typename container::iterator right)
	{
		left = new end_item();
		right = new end_item();
		this->left->next = this->right;
		this->right->prev = this->left;
		for (typename container::iterator i = left; i != right; i++)
			end().push(*i);
	}

	// Initialize this list as a copy of some other container
	template <class container>
	list(typename container::const_iterator left, typename container::const_iterator right)
	{
		left = new end_item();
		right = new end_item();
		this->left->next = this->right;
		this->right->prev = this->left;
		for (typename container::const_iterator i = left; i != right; i++)
			end().push(*i);
	}

	virtual ~list()
	{
		clear();
		delete left;
		left = NULL;
		delete right;
		right = NULL;
	}

	int size() const
	{
		return end() - begin();
	}

	iterator begin()
	{
		return iterator(left->next);
	}

	iterator end()
	{
		return iterator(right);
	}

	iterator rbegin()
	{
		return iterator(right->prev);
	}

	iterator rend()
	{
		return iterator(left);
	}

	const_iterator begin() const
	{
		return const_iterator(left->next);
	}

	const_iterator end() const
	{
		return const_iterator(right);
	}

	const_iterator rbegin() const
	{
		return const_iterator(right->prev);
	}

	const_iterator rend() const
	{
		return const_iterator(left);
	}

	iterator at(int i)
	{
		return i < 0 ? end()+i : begin()+i;
	}

	const_iterator at(int i) const
	{
		return i < 0 ? end()+i : begin()+i;
	}

	value_type &front()
	{
		return *begin();
	}

	const value_type &front() const
	{
		return *begin();
	}

	value_type &back()
	{
		return *rbegin();
	}

	const value_type &back() const
	{
		return *rbegin();
	}

	value_type &get(int i)
	{
		return i < 0 ? (end()+i).get() : (begin()+i).get();
	}

	const value_type &get(int i) const
	{
		return i < 0 ? (end()+i).get() : (begin()+i).get();
	}

	value_type *ptr(int i)
	{
		return i < 0 ? (end()+i).ptr() : (begin()+i).ptr();
	}

	const value_type *ptr(int i) const
	{
		return i < 0 ? (end()+i).ptr() : (begin()+i).ptr();
	}

	value_type &operator[](int i)
	{
		return i < 0 ? (end()+i).get() : (begin()+i).get();
	}

	const value_type &operator[](int i) const
	{
		return i < 0 ? (end()+i).get() : (begin()+i).get();
	}

	list<int> idx()
	{
		list<int> result;
		for (iterator i = begin(); i != end(); i++)
			result.push_back(i->idx());
		return result;
	}

	core::slice<range<iterator> > sub(int start, int end)
	{
		return range<iterator>(at(start), at(end));
	}

	list<value_type> subcpy(int start, int end)
	{
		return list<value_type>(at(start), at(end));
	}

	core::slice<range<iterator> > sub(int start)
	{
		return range<iterator>(at(start), this->end());
	}

	list<value_type> subcpy(int start)
	{
		return list<value_type>(at(start), this->end());
	}

	core::slice<range<iterator> > sub()
	{
		return range<iterator>(begin(), end());
	}

	list<value_type> subcpy()
	{
		return *this;
	}

	core::slice<range<const_iterator> > sub(int start, int end) const
	{
		return range<const_iterator>(at(start), at(end));
	}

	list<value_type> subcpy(int start, int end) const
	{
		return list<value_type>(at(start), at(end));
	}

	core::slice<range<const_iterator> > sub(int start) const
	{
		return range<const_iterator>(at(start), this->end());
	}

	list<value_type> subcpy(int start) const
	{
		return list<value_type>(at(start), this->end());
	}

	core::slice<range<const_iterator> > sub() const
	{
		return range<const_iterator>(begin(), end());
	}

	list<value_type> subcpy() const
	{
		return list<value_type>(begin(), end());
	}

	template <class container>
	list<typename container::iterator> sample(container &c)
	{
		list<typename container::iterator> result;
		for (iterator i = begin(); i != end(); i++)
			result.push_back(c.at(*i));
		return result;
	}

	template <class container>
	list<typename container::const_iterator> sample(const container &c)
	{
		list<typename container::const_iterator> result;
		for (iterator i = begin(); i != end(); i++)
			result.push_back(c.at(*i));
		return result;
	}

	static void drop(iterator start, iterator end)
	{
		list<value_type> result;
		result.left->next = start.loc;
		result.right->prev = end.loc->prev;
		start.loc->prev->next = end.loc;
		end.loc->prev = start.loc->prev;
		result.left->next->prev = result.left;
		result.right->prev->next = result.right;
		result.release();
	}

	void drop(int start, int end)
	{
		iterator l = start < 0 ? this->end()+start : this->begin()+start;
		iterator r = end < 0 ? this->end()+end : this->begin()+end;
		drop(l, r);
	}

	void drop_front(int n = 1)
	{
		drop(begin(), begin()+n);
	}

	void drop_back(int n = 1)
	{
		drop(end()-n, end());
	}

	static list<value_type> pop(iterator start, iterator end)
	{
		list<value_type> result;
		result.left->next = start.loc;
		result.right->prev = end.loc->prev;
		start.loc->prev->next = end.loc;
		end.loc->prev = start.loc->prev;
		result.left->next->prev = result.left;
		result.right->prev->next = result.right;

		return result;
	}

	list<value_type> pop(int start, int end)
	{
		iterator l = start < 0 ? this->end()+start : this->begin()+start;
		iterator r = end < 0 ? this->end()+end : this->begin()+end;
		return pop(l, r);
	}

	list<value_type> pop_back(int n = 1)
	{
		return pop(end()-n, end());
	}

	list<value_type> pop_front(int n = 1)
	{
		return pop(begin(), begin()+n);
	}

	void push_back(const value_type &value)
	{
		end().push(value);
	}
	
	void push_front(const value_type &value)
	{
		begin().push(value);
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

	static void replace(iterator start, iterator end, value_type v)
	{
		if (start != end)
		{
			start.get() = v;
			start++;
			drop(start, end);
		}
		else
			start.push(v);
	}

	template <class container>
	static void replace(iterator start, iterator end, const container &c)
	{
		typename container::const_iterator i = c.begin();
		while (start != end and i)
		{
			start.get() = *i;
			start++;
			i++;
		}

		if (start != end)
			drop(start, end);
		else if (i)
			start.append(i.sub());
	}

	void replace(int start, int end, value_type v)
	{
		replace(at(start), at(end), v);
	}
	
	template <class container>
	void replace(int start, int end, const container &c)
	{
		replace(at(start), at(end), c);
	}

	void replace_back(int n, const value_type &v)
	{
		replace(at(-n), end(), v);
	}

	template <class container>
	void replace_back(int n, const container &c)
	{
		replace(at(-n), end(), c);
	}

	void replace_front(int n, const value_type &v)
	{
		replace(begin(), at(n), v);
	}

	template <class container>
	void replace_front(int n, const container &c)
	{
		replace(begin(), at(n), c);
	}

	void swap(list<value_type> &lst)
	{
		end_item* tmp_left = left->next;
		end_item* tmp_right = right->prev;

		left->next = lst.left->next;
		left->prev = left;
		left->next->prev = left;
		right->prev = lst.right->prev;
		right->next = right;
		right->prev->next = right;

		lst.left->next = tmp_left;
		lst.left->prev = lst.left;
		lst.left->next->prev = lst.left;
		lst.right->prev = tmp_right;
		lst.right->next = lst.right;
		lst.right->prev->next = lst.right;
	}

	void resize(int n, const value_type &v = value_type())
	{
		iterator i = begin();
		while (i != end() and n > 0)
		{
			i++;
			n--;
		}

		if (i != end())
			drop(i, end());

		while (n > 0)
		{
			push_back(v);
			n--;
		}
	}

	void clear()
	{
		end_item *curr = left->next, *prev;
		while (curr != right)
		{
			prev = curr;
			curr = curr->next;
			delete prev;
		}
		left->next = right;
		right->prev = left;
	}

	void release()
	{
		end_item *curr = left->next, *prev;
		while (curr != right)
		{
			prev = curr;
			curr = curr->next;
			delete prev;
		}
		left->next = right;
		right->prev = left;
	}

	template <class container>
	list<value_type> &operator=(const container &c)
	{
		clear();
		append_back(c);
		return *this;
	}

	list<value_type> &operator=(const list<value_type> &c)
	{
		clear();
		append_back(c);
		return *this;
	}
};

template <class value_type>
list<value_type> &operator<<(list<value_type> &os, const value_type &v)
{
	os.push_back(v);
	return os;
}

template <class value_type, class container>
list<value_type> &operator<<(list<value_type> &os, const container &c)
{
	os.append_back(c);
	return os;
}

template <class value_type>
list<value_type> operator+(list<value_type> os, const value_type &v)
{
	os.push_back(v);
	return os;
}

template <class value_type, class container>
list<value_type> operator+(list<value_type> os, const container &c)
{
	os.append_back(c);
	return os;
}

template <typename value_type>
list<value_type> list_t(int n, ...)
{
	list<value_type> result;
	va_list args;
	va_start(args, n);
	for (int i = 0; i < n; i++)
		result.push_back(va_arg(args, value_type));
	va_end(args);

	return result;
}

}

