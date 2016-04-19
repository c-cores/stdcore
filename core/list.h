/*
 * list.h
 *
 *  Created on: Feb 4, 2014
 *      Author: nbingham
 */

#pragma once

#include "slice.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef NULL
#define NULL 0
#endif

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

	list()
	{
		left.next = &right;
		right.prev = &left;
		count = 0;
	}

	template <class container>
	list(const container &c)
	{
		left.next = &right;
		right.prev = &left;
		count = 0;
		for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
			end().push(*i);
	}

	list(const list<value_type> &c)
	{
		left.next = &right;
		right.prev = &left;
		count = 0;
		for (const_iterator i = c.begin(); i != c.end(); i++)
			end().push(*i);
	}

	list(int n, const value_type &t)
	{
		left.next = &right;
		right.prev = &left;
		count = 0;
		end().push(n, t);
	}

	~list()
	{
		clear();
	}

	end_item left;
	end_item right;
	int count;

	struct iterator;
	struct const_iterator;

	struct iterator
	{
	protected:
		friend class list<value_type>;
		friend class const_iterator;
		list<value_type> *root;
		end_item *loc;
	public:
		iterator()
		{
			root = NULL;
			loc = NULL;
		}

		iterator(list<value_type> *root, end_item *loc)
		{
			this->root = root;
			this->loc = loc;
		}

		iterator(list<value_type> *root, int n)
		{
			this->root = root;
			if (n > 0)
			{
				loc = root->left.next;
				while (n > 0)
				{
					loc = loc->next;
					n--;
				}
			}
			else
			{
				loc = &root->right;
				while (n < 0)
				{
					loc = loc->prev;
					n++;
				}
			}
		}

		iterator(const iterator &copy)
		{
			root = copy.root;
			loc = copy.loc;
		}

		~iterator() {}

		operator bool()
		{
			return loc != &root->left && loc != &root->right;
		}

		value_type &operator*()
		{
			return ((item*)loc)->value;
		}
		value_type *operator->()
		{
			return &((item*)loc)->value;
		}

		value_type *ptr()
		{
			return &((item*)loc)->value;
		}

		value_type &get()
		{
			return ((item*)loc)->value;
		}

		iterator &operator++(int)
		{
			loc = loc->next;
			return *this;
		}

		iterator &operator--(int)
		{
			loc = loc->prev;
			return *this;
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
			for (int i = 0; i < n && loc != &root->right; i++)
				loc = loc->next;

			return *this;
		}

		iterator &operator-=(int n)
		{
			for (int i = 0; i < n && loc != &root->left; i++)
				loc = loc->prev;

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

		int operator-(iterator i) const
		{
			int count = 0;
			while (i.loc != loc && i.loc != &i.root->right)
			{
				count++;
				i.loc = i.loc->next;
			}

			while (i.loc != loc && i.loc != &i.root->left)
			{
				count--;
				i.loc = i.loc->prev;
			}

			return count;
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
			int count = 0;
			while (i.loc != loc && i.loc != &i.root->right)
			{
				count++;
				i.loc = i.loc->next;
			}

			while (i.loc != loc && i.loc != &i.root->left)
			{
				count--;
				i.loc = i.loc->prev;
			}

			return count;
		}

		template <class iterator_type>
		void swap(iterator_type i)
		{
			value_type temp;
			memcpy(&temp, &((item*)loc)->value, sizeof(value_type));
			memcpy(&((item*)loc)->value, &((item*)i.loc)->value, sizeof(value_type));
			memcpy(&((item*)i.loc)->value, &temp, sizeof(value_type));
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
				if (n > 0)
					root->count -= n;
				else
					root->count += n;
			}

			return result;
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
				root->count -= n;
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
				root->count += n;
			}
		}

		void push(value_type v)
		{
			end_item *start = loc->prev;
			start->next = new item(v);
			start->next->prev = start;
			start = start->next;
			start->next = loc;
			loc->prev = start;
			root->count++;
		}

		void push(int n, value_type v)
		{
			end_item *start = loc->prev;
			for (int i = 0; i < n; i++)
			{
				start->next = new item(v);
				start->next->prev = start;
				start = start->next;
			}

			start->next = loc;
			loc->prev = start;
			root->count += n;
		}

		template <class container>
		void append(const container &c)
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
			root->count += c.size();
		}

		slice<list<value_type> > sub(int n = -1)
		{
			iterator right;
			if (n < 0)
				right = root->end()+n;
			else
				right = *this+n-1;
			return slice<list<value_type> >(*this, right);
		}

		list<value_type> subcpy(int n = -1)
		{
			return list<value_type>(sub(n));
		}

		void replace(int n, int m, value_type v)
		{
			int j = 0;
			iterator i = *this;
			while (i != root->end() && j < n && j < m)
			{
				*i = v;
				i++;
				j++;
			}

			if (i == root->end() && j < m)
				i.push(m-j, v);
			else if (j < m)
				(i+1).push(m-j, v);
			else if (j < n)
				i.pop(n-j);
		}
		
		template <class container>
		void replace(int n, const container &c)
		{
			typename container::const_iterator j = c.begin();
			int k = 0;
			iterator i = *this;
			while (i != root->end() && k < n && j != c.end())
			{
				*i = *j;
				i++;
				j++;
				k++;
			}

			if (i == root->end() && j != c.end())
				i.push(j.sub());
			else if (j != c.end())
				(i+1).push(j.sub());	
			else if (k < n)
				i.pop(n-k);
		}

	};

	struct const_iterator
	{
	protected:
		friend class list<value_type>;
		friend class iterator;
		const list<value_type> *root;
		const end_item *loc;
	public:
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

		const_iterator(const list<value_type> *l, const end_item *n)
		{
			root = l;
			loc = n;
		}

		const_iterator(list<value_type> *l, int n)
		{
			root = l;
			if (n > 0)
			{
				loc = root->left.next;
				while (n > 0)
				{
					loc = loc->next;
					n--;
				}
			}
			else
			{
				loc = &root->right;
				while (n < 0)
				{
					loc = loc->prev;
					n++;
				}
			}
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

		operator bool()
		{
			return loc != &root->left && loc != &root->right;
		}

		const value_type &operator*()
		{
			return ((const item*)loc)->value;
		}

		const value_type *operator->()
		{
			return &((const item*)loc)->value;
		}

		const value_type &get()
		{
			return ((const item*)loc)->value;
		}

		const value_type *ptr()
		{
			return &((const item*)loc)->value;
		}

		const_iterator &operator++(int)
		{
			loc = loc->next;
			return *this;
		}

		const_iterator &operator--(int)
		{
			loc = loc->prev;
			return *this;
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
			for (int i = 0; i < n; i++)
				(*this)++;

			return *this;
		}

		const_iterator &operator-=(int n)
		{
			for (int i = 0; i < n; i++)
				(*this)--;

			return *this;
		}

		const_iterator operator+(int n) const
		{
			const_iterator result(*this);
			for (int i = 0; i < n; i++)
				result++;

			return result;
		}

		const_iterator operator-(int n) const
		{
			const_iterator result(*this);
			for (int i = 0; i < n; i++)
				result--;

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
			return root == i.root && loc == i.loc;
		}

		bool operator!=(const_iterator i) const
		{
			return root != i.root || loc != i.loc;
		}

		int operator-(const_iterator i) const
		{
			int count = 0;
			for (const_iterator j = i; j.loc != loc && j.loc != &j.root->right; j++)
				count++;
			return count;
		}

		const_iterator &operator=(iterator i)
		{
			root = i.root;
			loc = i.loc;
			return *this;
		}

		bool operator==(iterator i) const
		{
			return root == i.root && loc == i.loc;
		}

		bool operator!=(iterator i) const
		{
			return root != i.root || loc != i.loc;
		}

		int operator-(iterator i) const
		{
			int count = 0;
			for (const_iterator j = i; j.loc != loc && j.loc != &j.root->right; j++)
				count++;
			return count;
		}

		slice<const list<value_type> > sub(int n = -1)
		{
			const_iterator right;
			if (n < 0)
				right = root->end()+n;
			else
				right = *this+n-1;
			return slice<const list<value_type> >(*this, right);
		}

		list<value_type> subcpy(int n = -1)
		{
			return list<value_type>(sub(n));
		}
	};

	int size() const
	{
		return count;
	}

	iterator at(int i)
	{
		return begin() + i;
	}

	const_iterator at(int i) const
	{
		return begin() + i;
	}

	value_type &get(int i) const
	{
		return ((item*)(begin() + i))->value;
	}

	value_type *ptr(int i) const
	{
		return (begin() + i).ptr();
	}

	value_type &operator[](int i) const
	{
		return ((item*)(begin() + i))->value;
	}

	value_type &front() const
	{
		return *begin();
	}

	value_type &back() const
	{
		return *rbegin();
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

	slice<list<value_type> > sub(int left, int right = -1)
	{
		return slice<list<value_type> >(iterator(this, left), iterator(this, right));
	}

	slice<const list<value_type> > sub(int left, int right = -1) const
	{
		return slice<const list<value_type> >(const_iterator(this, left), const_iterator(this, right));
	}

	list<value_type> subcpy(int left, int right = -1) const
	{
		return list<value_type>(sub(left, right));
	}

	static slice<list<value_type> > sub(iterator left, iterator right)
	{
		return slice<list<value_type> >(left, right);
	}

	static slice<const list<value_type> > sub(const_iterator left, const_iterator right)
	{
		return slice<const list<value_type> >(left, right);
	}

	static list<value_type> subcpy(iterator left, iterator right)
	{
		return list<value_type>(sub(left, right));
	}

	static list<value_type> subcpy(const_iterator left, const_iterator right)
	{
		return list<value_type>(sub(left, right));
	}

	slice<list<value_type> > ref()
	{
		return slice<list<value_type> >(begin(), rbegin());
	}

	slice<const list<value_type> > ref() const
	{
		return slice<const list<value_type> >(begin(), rbegin());
	}

	void push_back(const value_type &value)
	{
		end().push(value);
	}
	
	void push_front(const value_type &value)
	{
		begin().push(value);
	}

	void push_back(int num, const value_type &value)
	{
		end().push(num, value);
	}
	
	void push_front(int num, const value_type &value)
	{
		begin().push(num, value);
	}


	template <class container>
	void append_back(container &c)
	{
		end().append(c);
	}

	template <class container>
	void append_front(container &c)
	{
		begin().append(c);
	}

	list<value_type> pop_back(unsigned int n = 1)
	{
		return end().pop(-n);
	}

	list<value_type> pop_front(unsigned int n = 1)
	{
		return begin().pop(n);
	}

	void drop_front(unsigned int n = 1)
	{
		begin().drop(n);
	}

	void drop_back(unsigned int n = 1)
	{
		end().drop(-n);
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
		count = 0;
	}

	template <class container>
	list<value_type> &operator=(const container &c)
	{
		clear();
		for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
			push_back(*i);
		return *this;
	}

	list<value_type> &operator=(const list<value_type> &c)
	{
		clear();
		for (const_iterator i = c.begin(); i != c.end(); i++)
			push_back(*i);
		return *this;
	}

protected:
	end_item* get_item(iterator i)
	{
		return i.loc;
	}
};

}

