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
	struct node
	{
		node()
		{
			next = this;
			prev = this;
		}
	
		virtual ~node()
		{
		}
	
		node *next;
		node *prev;
	};

	struct item : node
	{
		item()
		{
		}

		item(const value_type &d)
		{
			data = d;
		}

		~item()
		{
		}

		value_type data;
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

	list(const value_type &t, int n = 1)
	{
		left.next = &right;
		right.prev = &left;
		count = 0;
		end().push(t, n);
	}

	~list()
	{
		clear();
	}

	node left;
	node right;
	int count;

	struct iterator;
	struct const_iterator;

	struct iterator
	{
	private:
		friend class list<value_type>;
		friend class const_iterator;
		list<value_type> *lst;
		node *loc;
	public:
		typedef list<value_type> container;
		typedef value_type type;

		iterator()
		{
			lst = NULL;
			loc = NULL;
		}

		iterator(list<value_type> *l, node *n)
		{
			lst = l;
			loc = n;
		}

		iterator(const iterator &i)
		{
			lst = i.lst;
			loc = i.loc;
		}

		~iterator() {}

		value_type &operator*()
		{
			return ((item*)loc)->data;
		}
		value_type *operator->()
		{
			return &((item*)loc)->data;
		}

		value_type *pointer()
		{
			return &((item*)loc)->data;
		}

		value_type &value()
		{
			return ((item*)loc)->data;
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
			for (int i = 0; i < n && loc != &lst->right; i++)
				loc = loc->next;

			return *this;
		}

		iterator &operator-=(int n)
		{
			for (int i = 0; i < n && loc != &lst->left; i++)
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
			lst = i.lst;
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
			while (i.loc != loc && i.loc != &i.lst->right)
			{
				count++;
				i.loc = i.loc->next;
			}

			while (i.loc != loc && i.loc != &i.lst->left)
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
			while (i.loc != loc && i.loc != &i.lst->right)
			{
				count++;
				i.loc = i.loc->next;
			}

			while (i.loc != loc && i.loc != &i.lst->left)
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
			memcpy(&temp, &((item*)loc)->data, sizeof(value_type));
			memcpy(&((item*)loc)->data, &((item*)i.loc)->data, sizeof(value_type));
			memcpy(&((item*)i.loc)->data, &temp, sizeof(value_type));
		}

		list<value_type> pop(int n = 1)
		{
			list<value_type> result;
			node *start = loc;
			for (int i = 0; i < n && loc != &lst->right; i++)
				loc = loc->next;
			for (int i = 0; i > n && start != &lst->left && start != lst->left.next; i--)
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
					lst->count -= n;
				else
					lst->count += n;
			}

			return result;
		}

		void drop(int n = 1)
		{
			if (n > 0)
			{
				node* start = loc->prev;
				
				for (int i = 0; i < n && loc != &lst->right; i++)
				{
					node *temp = loc->next;
					delete loc;
					loc = temp;
				}
					
				start->next = loc;
				loc->prev = start;
				lst->count -= n;
			}
			else if (n < 0)
			{
				node *start = loc->prev;
				
				for (int i = 0; i > n && start != &lst->left; i--)
				{
					node *temp = start->prev;
					delete start;
					start = temp;
				}
				
				start->next = loc;
				loc->prev = start;
				lst->count += n;
			}
		}

		void push(value_type v, int n = 1)
		{
			node *start = loc->prev;
			for (int i = 0; i < n; i++)
			{
				start->next = new item(v);
				start->next->prev = start;
				start = start->next;
			}

			start->next = loc;
			loc->prev = start;
			lst->count += n;
		}

		template <class container>
		void push(const container &c)
		{
			for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
				push(*i);
		}

		void chop(bool forward = true)
		{
			if (forward)
			{
				node *ptr = loc;
				loc = ptr->pev;
				while (ptr != &lst->right)
				{
					node *temp = ptr->next;
					delete ptr;
					ptr = temp;
					lst->count--;
				}
				loc->next = &lst->right;
				lst->right->prev = loc;
			}
			else
			{
				node *ptr = lst->left.next;
				while (ptr != loc)
				{
					node *temp = ptr->next;
					delete ptr;
					ptr = temp;
					lst->count--;
				}
				lst->left.next = loc;
				loc->prev = &lst->left;
			}
		}
	};

	struct const_iterator
	{
	private:
		friend class list<value_type>;
		friend class iterator;
		const list<value_type> *lst;
		const node *loc;
	public:
		typedef const list<value_type> container;
		typedef value_type type;

		const_iterator()
		{
			lst = NULL;
			loc = NULL;
		}

		const_iterator(const list *l)
		{
			lst = l;
			loc = &l->left;
		}

		const_iterator(const list *l, const node *n)
		{
			lst = l;
			loc = n;
		}

		const_iterator(const const_iterator &i)
		{
			lst = i.lst;
			loc = i.loc;
		}

		~const_iterator() {}

		const value_type &operator*()
		{
			return ((const item*)loc)->data;
		}
		const value_type *operator->()
		{
			return &((const item*)loc)->data;
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
			lst = i.lst;
			loc = i.loc;
			return *this;
		}

		bool operator==(const_iterator i) const
		{
			return lst == i.lst && loc == i.loc;
		}

		bool operator!=(const_iterator i) const
		{
			return lst != i.lst || loc != i.loc;
		}

		int operator-(const_iterator i) const
		{
			int count = 0;
			for (const_iterator j = i; j.loc != loc && j.loc != &j.lst->right; j++)
				count++;
			return count;
		}

		const_iterator &operator=(iterator i)
		{
			lst = i.lst;
			loc = i.loc;
			return *this;
		}

		bool operator==(iterator i) const
		{
			return lst == i.lst && loc == i.loc;
		}

		bool operator!=(iterator i) const
		{
			return lst != i.lst || loc != i.loc;
		}

		int operator-(iterator i) const
		{
			int count = 0;
			for (const_iterator j = i; j.loc != loc && j.loc != &j.lst->right; j++)
				count++;
			return count;
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
		return ((item*)(begin() + i))->data;
	}

	value_type &operator[](int i) const
	{
		return ((item*)(begin() + i))->data;
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

	slice<iterator> bound()
	{
		return slice<iterator>(begin(), rbegin());
	}

	slice<const_iterator> bound() const
	{
		return slice<const_iterator>(begin(), rbegin());
	}

	void push_back(value_type t)
	{
		end().push(t);
	}
	
	void push_front(value_type t)
	{
		begin().push(t);
	}

	template <class container>
	void merge_back(container &c)
	{
		end().merge(c);
	}

	template <class container>
	void merge_front(container &c)
	{
		begin().merge(c);
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
		node *curr = left.next, *prev;
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

	list<value_type> &operator=(const list<value_type> &c)
	{
		clear();

		typename list<value_type>::const_iterator i;
		for (i = c.begin(); i != c.end(); i++)
			push_back(*i);
		return *this;
	}
};

}

