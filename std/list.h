/*
 * list.h
 *
 *  Created on: Feb 4, 2014
 *      Author: nbingham
 */

#pragma once

#include <std/slice.h>

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

namespace core
{

template <class value_type>
struct list
{
	typedef value_type type;

	struct end_item
	{
		end_item()
		{
			next = this;
			prev = this;
		}
	
		virtual ~end_item()
		{
		}
	
		end_item *next;
		end_item *prev;
	};

	struct item : end_item
	{
		item()
		{
		}

		item(const value_type &value)
		{
			this->value = value;
		}

		~item()
		{
		}

		value_type value;
	};

	end_item left;
	end_item right;

	struct const_iterator;

	struct iterator
	{
	protected:
		friend class list<value_type>;
		friend class const_iterator;
		list<value_type> *root;
		end_item *loc;

		iterator(list<value_type> *root, end_item *loc)
		{
			this->root = root;
			this->loc = loc;
		}
	public:
		typedef value_type type;

		iterator()
		{
			root = NULL;
			loc = NULL;
		}

		iterator(const iterator &copy)
		{
			root = copy.root;
			loc = copy.loc;
		}

		~iterator() {}

		operator bool() const
		{
			return root != NULL && loc != &root->left && loc != &root->right;
		}

		value_type &operator*() const
		{
			return ((item*)loc)->value;
		}
		value_type *operator->() const
		{
			return &((item*)loc)->value;
		}

		value_type *ptr() const
		{
			return &((item*)loc)->value;
		}

		value_type &get() const
		{
			return ((item*)loc)->value;
		}

		iterator &ref()
		{
			return *this;
		}

		const iterator &ref() const
		{
			return *this;
		}

		int idx() const
		{
			int count = 0;
			for (end_item *i = root->left.next; i != loc && i != &root->right; i = i->next)
				count++;
			return count;
		}

		iterator operator++(int)
		{
			iterator result = *this;
			loc = loc->next;
			return result;
		}

		iterator operator--(int)
		{
			iterator result = *this;
			loc = loc->prev;
			return result;
		}

		iterator &operator++()
		{
			loc = loc->next;
			return *this;
		}

		iterator &operator--()
		{
			loc = loc->prev;
			return *this;
		}

		iterator &operator+=(int n)
		{
			while (n > 0 && loc != &root->right)
			{
				loc = loc->next;
				n--;
			}

			while (n < 0 && loc != &root->left)
			{
				loc = loc->prev;
				n++;
			}

			return *this;
		}

		iterator &operator-=(int n)
		{
			while (n < 0 && loc != &root->right)
			{
				loc = loc->next;
				n++;
			}

			while (n > 0 && loc != &root->left)
			{
				loc = loc->prev;
				n--;
			}

			return *this;
		}

		iterator operator+(int n) const
		{
			iterator result(*this);
			result += n;
			return result;
		}

		iterator operator-(int n) const
		{
			iterator result(*this);
			result -= n;
			return result;
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
			int c0 = 0, c1 = 0;
			iterator j = i;
			while (i.loc != loc && j.loc != loc)
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
			int c0 = 0, c1 = 0;
			const_iterator j = i;
			while (i.loc != loc && j.loc != loc)
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

		core::slice<range<iterator> > sub(int length) const
		{
			if (length < 0)
				return range<iterator>(*this+length, *this);
			else
				return range<iterator>(*this, *this+length);
		}

		list<value_type> subcpy(int length) const
		{
			if (length < 0)
				return range<iterator>(*this+length, *this).deref();
			else
				return range<iterator>(*this, *this+length).deref();
		}

		core::slice<range<iterator> > sub() const
		{
			return range<iterator>(*this, root->end());
		}

		list<value_type> subcpy() const
		{
			return range<iterator>(*this, root->end()).deref();
		}

		void drop(int n = 1)
		{
			if (n > 0)
			{
				end_item* start = loc->prev;
				
				for (int i = 0; i < n && loc != &root->right; i++)
				{
					end_item *temp = loc->next;
					delete loc;
					loc = temp;
				}
					
				start->next = loc;
				loc->prev = start;
			}
			else if (n < 0)
			{
				end_item *start = loc->prev;
				
				for (int i = 0; i > n && start != &root->left; i--)
				{
					end_item *temp = start->prev;
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
			end_item *start = loc;
			for (int i = 0; i < n && loc != &root->right; i++)
				loc = loc->next;
			for (int i = 0; i > n && start != &root->left && start != root->left.next; i--)
				start = start->prev;

			if (start != loc)
			{
				result.left.next = start;
				result.right.prev = loc->prev;
				start->prev->next = loc;
				loc->prev = start->prev;
				result.left.next->prev = &result.left;
				result.right.prev->next = &result.right;
			}

			return result;
		}

		void push(value_type v) const
		{
			end_item *start = loc->prev;
			start->next = new item(v);
			start->next->prev = start;
			start = start->next;
			start->next = loc;
			loc->prev = start;
		}

		template <class container>
		void append(const container &c) const
		{
			end_item *start = loc->prev;
			for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
			{
				start->next = new item(*i);
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

			if (loc == &root->right)
			{
				push(v);
				loc = loc->next;
			}
			else
			{
				((item*)loc)->value = v;
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
			while (n > 0 && j && loc != &root->right)
			{
				((item*)loc)->value = *j;
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
			memcpy(&temp, &((item*)loc)->value, sizeof(value_type));
			memcpy(&((item*)loc)->value, &((item*)i.loc)->value, sizeof(value_type));
			memcpy(&((item*)i.loc)->value, &temp, sizeof(value_type));
		}

		void swap(iterator &i)
		{
			end_item *next1 = loc->next;
			end_item *prev1 = loc->prev;
			end_item *next2 = i.loc->next;
			end_item *prev2 = i.loc->prev;
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

		iterator &operator=(iterator i)
		{
			root = i.root;
			loc = i.loc;
			return *this;
		}
	};

	struct const_iterator
	{
	protected:
		friend class list<value_type>;
		friend class iterator;
		const list<value_type> *root;
		const end_item *loc;

		const_iterator(const list<value_type> *l, const end_item *n)
		{
			root = l;
			loc = n;
		}
	public:
		typedef value_type type;

		const_iterator()
		{
			root = NULL;
			loc = NULL;
		}

		const_iterator(const list<value_type> *l)
		{
			root = l;
			loc = &l->left;
		}

		const_iterator(const iterator &i)
		{
			root = i.root;
			loc = i.loc;
		}

		const_iterator(const const_iterator &i)
		{
			root = i.root;
			loc = i.loc;
		}

		~const_iterator() {}

		operator bool() const
		{
			return root != NULL && loc != &root->left && loc != &root->right;
		}

		const value_type &operator*() const
		{
			return ((item*)loc)->value;
		}

		const value_type *operator->() const
		{
			return &((item*)loc)->value;
		}

		const value_type &get() const
		{
			return ((item*)loc)->value;
		}

		const value_type *ptr() const
		{
			return &((item*)loc)->value;
		}

		const_iterator &ref()
		{
			return *this;
		}

		const const_iterator &ref() const
		{
			return *this;
		}

		int idx() const
		{
			int count = 0;
			for (end_item *i = root->left.next; i != loc && i != &root->right; i = i->next)
				count++;
			return count;
		}

		const_iterator operator++(int)
		{
			const_iterator result = *this;
			loc = loc->next;
			return result;
		}

		const_iterator operator--(int)
		{
			const_iterator result = *this;
			loc = loc->prev;
			return result;
		}

		const_iterator &operator++()
		{
			loc = loc->next;
			return *this;
		}

		const_iterator &operator--()
		{
			loc = loc->prev;
			return *this;
		}

		const_iterator &operator+=(int n)
		{
			while (n > 0 && loc != &root->right)
			{
				loc = loc->next;
				n--;
			}

			while (n < 0 && loc != &root->left)
			{
				loc = loc->prev;
				n++;
			}

			return *this;
		}

		const_iterator &operator-=(int n)
		{
			while (n < 0 && loc != &root->right)
			{
				loc = loc->next;
				n++;
			}

			while (n > 0 && loc != &root->left)
			{
				loc = loc->prev;
				n--;
			}

			return *this;
		}

		const_iterator operator+(int n) const
		{
			const_iterator result(*this);
			result += n;
			return result;
		}

		const_iterator operator-(int n) const
		{
			const_iterator result(*this);
			result -= n;
			return result;
		}

		bool operator==(const_iterator i) const
		{
			return root == i.root && loc == i.loc;
		}

		bool operator!=(const_iterator i) const
		{
			return root != i.root || loc != i.loc;
		}

		bool operator==(iterator i) const
		{
			return root == i.root && loc == i.loc;
		}

		bool operator!=(iterator i) const
		{
			return root != i.root || loc != i.loc;
		}

		int operator-(const_iterator i) const
		{
			int c0 = 0, c1 = 0;
			const_iterator j = i;
			while (i.loc != loc && j.loc != loc)
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

		int operator-(iterator i) const
		{
			int c0 = 0, c1 = 0;
			const_iterator j = i;
			while (i.loc != loc && j.loc != loc)
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

		core::slice<range<const_iterator> > sub(int length) const
		{
			if (length < 0)
				return range<const_iterator>(*this+length, *this);
			else
				return range<const_iterator>(*this, *this+length);
		}

		list<value_type> subcpy(int length) const
		{
			if (length < 0)
				return range<const_iterator>(*this+length, *this).deref();
			else
				return range<const_iterator>(*this, *this+length).deref();
		}

		core::slice<range<const_iterator> > sub() const
		{
			return range<const_iterator>(*this, root->end());
		}

		list<value_type> subcpy() const
		{
			return range<const_iterator>(*this, root->end()).deref();
		}

		const_iterator &operator=(const_iterator i)
		{
			root = i.root;
			loc = i.loc;
			return *this;
		}

		const_iterator &operator=(iterator i)
		{
			root = i.root;
			loc = i.loc;
			return *this;
		}
	};

	list()
	{
		left.next = &right;
		right.prev = &left;
	}

	list(const value_type &c)
	{
		left.next = &right;
		right.prev = &left;
		end().push(c);
	}

	template <class container>
	list(const container &c)
	{
		left.next = &right;
		right.prev = &left;
		for (typename container::const_iterator i = c.begin(); i; i++)
			end().push(*i);
	}

	list(const list<value_type> &c)
	{
		left.next = &right;
		right.prev = &left;
		for (const_iterator i = c.begin(); i; i++)
			end().push(*i);
	}

	list(iterator left, iterator right)
	{
		this->left.next = &this->right;
		this->right.prev = &this->left;
		for (iterator i = left; i != right; i++)
			end().push(*i);
	}

	list(const_iterator left, const_iterator right)
	{
		this->left.next = &this->right;
		this->right.prev = &this->left;
		for (const_iterator i = left; i != right; i++)
			end().push(*i);
	}

	// Initialize this list as a copy of some other container
	template <class container>
	list(typename container::iterator left, typename container::iterator right)
	{
		this->left.next = &this->right;
		this->right.prev = &this->left;
		for (typename container::iterator i = left; i != right; i++)
			end().push(*i);
	}

	// Initialize this list as a copy of some other container
	template <class container>
	list(typename container::const_iterator left, typename container::const_iterator right)
	{
		this->left.next = &this->right;
		this->right.prev = &this->left;
		for (typename container::const_iterator i = left; i != right; i++)
			end().push(*i);
	}

	static list<value_type> values(int n, ...)
	{
		list<value_type> result;
		va_list args;
		va_start(args, n);
		for (int i = 0; i < n; i++)
			result.push_back(va_arg(args, value_type));
		va_end(args);

		return result;
	}

	virtual ~list()
	{
		clear();
	}

	int size() const
	{
		return end() - begin();
	}

	iterator begin()
	{
		return iterator(this, left.next);
	}

	iterator end()
	{
		return iterator(this, &right);
	}

	iterator rbegin()
	{
		return iterator(this, right.prev);
	}

	iterator rend()
	{
		return iterator(this, &left);
	}

	const_iterator begin() const
	{
		return const_iterator(this, left.next);
	}

	const_iterator end() const
	{
		return const_iterator(this, &right);
	}

	const_iterator rbegin() const
	{
		return const_iterator(this, right.prev);
	}

	const_iterator rend() const
	{
		return const_iterator(this, &left);
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

	core::slice<list<value_type> > deref()
	{
		return *this;
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
		return range<iterator>(at(start), at(end)).deref();
	}

	core::slice<range<iterator> > sub(int start)
	{
		return range<iterator>(at(start), this->end());
	}

	list<value_type> subcpy(int start)
	{
		return range<iterator>(at(start), this->end()).deref();
	}

	core::slice<range<iterator> > sub()
	{
		return range<iterator>(begin(), end());
	}

	list<value_type> subcpy()
	{
		return range<iterator>(begin(), end()).deref();
	}

	core::slice<range<const_iterator> > sub(int start, int end) const
	{
		return range<const_iterator>(at(start), at(end));
	}

	list<value_type> subcpy(int start, int end) const
	{
		return range<const_iterator>(at(start), at(end)).deref();
	}

	core::slice<range<const_iterator> > sub(int start) const
	{
		return range<const_iterator>(at(start), this->end());
	}

	list<value_type> subcpy(int start) const
	{
		return range<const_iterator>(at(start), this->end()).deref();
	}

	core::slice<range<const_iterator> > sub() const
	{
		return range<const_iterator>(begin(), end());
	}

	list<value_type> subcpy() const
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
		result.left.next = start.loc;
		result.right.prev = end.loc->prev;
		start.loc->prev->next = end.loc;
		end.loc->prev = start.loc->prev;
		result.left.next->prev = &result.left;
		result.right.prev->next = &result.right;
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
		result.left.next = start.loc;
		result.right.prev = end.loc->prev;
		start.loc->prev->next = end.loc;
		end.loc->prev = start.loc->prev;
		result.left.next->prev = &result.left;
		result.right.prev->next = &result.right;

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
		while (start != end && i)
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
		end_item* tmp_left = left.next;
		end_item* tmp_right = right.prev;

		left.next = lst.left.next;
		left.prev = &left;
		left.next->prev = &left;
		right.prev = lst.right.prev;
		right.next = &right;
		right.prev->next = &right;

		lst.left.next = tmp_left;
		lst.left.prev = &lst.left;
		lst.left.next->prev = &lst.left;
		lst.right.prev = tmp_right;
		lst.right.next = &lst.right;
		lst.right.prev->next = &lst.right;
	}

	void resize(int n, const value_type &v = value_type())
	{
		iterator i = begin();
		while (i != end() && n > 0)
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
		end_item *curr = left.next, *prev;
		while (curr != &right)
		{
			prev = curr;
			curr = curr->next;
			delete prev;
		}
		left.next = &right;
		right.prev = &left;
	}

	void release()
	{
		end_item *curr = left.next, *prev;
		while (curr != &right)
		{
			prev = curr;
			curr = curr->next;
			delete prev;
		}
		left.next = &right;
		right.prev = &left;
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

protected:
	end_item* get_item(iterator i) const
	{
		return i.loc;
	}

	end_item* get_item(const_iterator i) const
	{
		return i.loc;
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

template<class value_type>
bool operator==(list<value_type> a0, list<value_type> a1)
{
	return equal_to(a0, a1);
}

template<class value_type>
bool operator!=(list<value_type> a0, list<value_type> a1)
{
	return !equal_to(a0, a1);
}

template<class value_type>
bool operator<(list<value_type> a0, list<value_type> a1)
{
	return less_than(a0, a1);
}

template<class value_type>
bool operator>(list<value_type> a0, list<value_type> a1)
{
	return greater_than(a0, a1);
}

template<class value_type>
bool operator<=(list<value_type> a0, list<value_type> a1)
{
	return !greater_than(a0, a1);
}

template<class value_type>
bool operator>=(list<value_type> a0, list<value_type> a1)
{
	return !less_than(a0, a1);
}

template<class value_type, class container>
bool operator==(list<value_type> a0, slice<container> a1)
{
	return equal_to(a0, a1);
}

template<class value_type, class container>
bool operator!=(list<value_type> a0, slice<container> a1)
{
	return !equal_to(a0, a1);
}

template<class value_type, class container>
bool operator<(list<value_type> a0, slice<container> a1)
{
	return less_than(a0, a1);
}

template<class value_type, class container>
bool operator>(list<value_type> a0, slice<container> a1)
{
	return greater_than(a0, a1);
}

template<class value_type, class container>
bool operator<=(list<value_type> a0, slice<container> a1)
{
	return !greater_than(a0, a1);
}

template<class value_type, class container>
bool operator>=(list<value_type> a0, slice<container> a1)
{
	return !less_than(a0, a1);
}


template<class container, class value_type>
bool operator==(slice<container> a0, list<value_type> a1)
{
	return equal_to(a0, a1);
}

template<class container, class value_type>
bool operator!=(slice<container> a0, list<value_type> a1)
{
	return !equal_to(a0, a1);
}

template<class container, class value_type>
bool operator<(slice<container> a0, list<value_type> a1)
{
	return less_than(a0, a1);
}

template<class container, class value_type>
bool operator>(slice<container> a0, list<value_type> a1)
{
	return greater_than(a0, a1);
}

template<class container, class value_type>
bool operator<=(slice<container> a0, list<value_type> a1)
{
	return !greater_than(a0, a1);
}

template<class container, class value_type>
bool operator>=(slice<container> a0, list<value_type> a1)
{
	return !less_than(a0, a1);
}

template<class value_type>
bool operator==(list<value_type> a0, range<value_type> a1)
{
	return equal_to(a0, a1);
}

template<class value_type>
bool operator!=(list<value_type> a0, range<value_type> a1)
{
	return !equal_to(a0, a1);
}

template<class value_type>
bool operator<(list<value_type> a0, range<value_type> a1)
{
	return less_than(a0, a1);
}

template<class value_type>
bool operator>(list<value_type> a0, range<value_type> a1)
{
	return greater_than(a0, a1);
}

template<class value_type>
bool operator<=(list<value_type> a0, range<value_type> a1)
{
	return !greater_than(a0, a1);
}

template<class value_type>
bool operator>=(list<value_type> a0, range<value_type> a1)
{
	return !less_than(a0, a1);
}


template<class value_type>
bool operator==(range<value_type> a0, list<value_type> a1)
{
	return equal_to(a0, a1);
}

template<class value_type>
bool operator!=(range<value_type> a0, list<value_type> a1)
{
	return !equal_to(a0, a1);
}

template<class value_type>
bool operator<(range<value_type> a0, list<value_type> a1)
{
	return less_than(a0, a1);
}

template<class value_type>
bool operator>(range<value_type> a0, list<value_type> a1)
{
	return greater_than(a0, a1);
}

template<class value_type>
bool operator<=(range<value_type> a0, list<value_type> a1)
{
	return !greater_than(a0, a1);
}

template<class value_type>
bool operator>=(range<value_type> a0, list<value_type> a1)
{
	return !less_than(a0, a1);
}

}

