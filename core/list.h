/*
 * list.h
 *
 *  Created on: Feb 4, 2014
 *      Author: nbingham
 */

#pragma once

#include <core/slice.h>
#include <core/range.h>

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

	list()
	{
		left.next = &right;
		right.prev = &left;
	}

	template <class container>
	list(const container &c)
	{
		left.next = &right;
		right.prev = &left;
		for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
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

	list(const list<value_type> &c)
	{
		left.next = &right;
		right.prev = &left;
		for (const_iterator i = c.begin(); i != c.end(); i++)
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

	end_item left;
	end_item right;

	struct iterator;
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

		int idx()
		{
			int count = 0;
			for (end_item *i = &root->left; i != loc; i = i->next)
				count++;
			return count;
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

		slice<range<iterator, int> > sub(int n)
		{
			iterator l = n < 0 ? *this + n : *this;
			iterator r = n < 0 ? *this : *this + n;
			return range<iterator, int>(l, r);
		}

		list<value_type> subcpy(int n)
		{
			return list<value_type>(sub(n));
		}

		slice<range<iterator, int> > sub()
		{
			return range<iterator, int>(*this, root->end());
		}

		list<value_type> subcpy()
		{
			return list<value_type>(sub());
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

		void push(value_type v)
		{
			end_item *start = loc->prev;
			start->next = new item(v);
			start->next->prev = start;
			start = start->next;
			start->next = loc;
			loc->prev = start;
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
		}

		void replace(int n, value_type v)
		{
			if (n > 0)
			{
				*(*this) = v;
				(*this+1).pop(n-1);
			}
			else if (n < 0)
			{
				*(*this-1) = v;
				(*this-1).pop(n+1);
			}
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
				i.append(j.sub());
			else if (j != c.end())
				(i+1).append(j.sub());
			else if (k < n)
				i.pop(n-k);
		}

		template <class iterator_type>
		void swap(iterator_type i)
		{
			value_type temp;
			memcpy(&temp, &((item*)loc)->value, sizeof(value_type));
			memcpy(&((item*)loc)->value, &((item*)i.loc)->value, sizeof(value_type));
			memcpy(&((item*)i.loc)->value, &temp, sizeof(value_type));
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

		int idx()
		{
			int count = 0;
			for (end_item *i = &root->left; i != loc; i = i->next)
				count++;
			return count;
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

		slice<range<const_iterator, int> > sub(int n)
		{
			const_iterator l = n < 0 ? *this + n : *this;
			const_iterator r = n < 0 ? *this : *this + n;
			return range<const_iterator, int>(l, r);
		}

		list<value_type> subcpy(int n)
		{
			return list<value_type>(sub(n));
		}

		slice<range<const_iterator, int> > sub()
		{
			return range<const_iterator, int>(*this, root->end());
		}

		list<value_type> subcpy()
		{
			return list<value_type>(sub());
		}
	};

	int size() const
	{
		return end() - begin();
	}

	iterator at(int i)
	{
		if (i < 0)
			return end() + i;
		else
			return begin() + i;
	}

	const_iterator at(int i) const
	{
		if (i < 0)
			return end() + i;
		else
			return begin() + i;
	}

	value_type &get(int i)
	{
		if (i < 0)
			return (end() + i).get();
		else
			return (begin() + i).get();
	}

	const value_type &get(int i) const
	{
		if (i < 0)
			return (end() + i).get();
		else
			return (begin() + i).get();
	}

	value_type *ptr(int i)
	{
		if (i < 0)
			return (end() + i).ptr();
		else
			return (begin() + i).ptr();
	}

	const value_type *ptr(int i) const
	{
		if (i < 0)
			return (end() + i).ptr();
		else
			return (begin() + i).ptr();
	}

	value_type &operator[](int i)
	{
		return get(i);
	}

	const value_type &operator[](int i) const
	{
		return get(i);
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

	slice<range<iterator, int> > sub(int start, int end)
	{
		iterator l = start < 0 ? this->end()+start : this->begin()+start;
		iterator r = end < 0 ? this->end()+end : this->begin()+end;
		return range<iterator, int>(l, r);
	}

	slice<range<iterator, int> > sub(int start)
	{
		iterator l = start < 0 ? end()+start : begin()+start;
		return range<iterator, int>(l, end());
	}

	slice<range<const_iterator, int> > sub(int start, int end) const
	{
		const_iterator l = start < 0 ? this->end()+start : this->begin()+start;
		const_iterator r = end < 0 ? this->end()+end : this->begin()+end;
		return range<const_iterator, int>(l, r);
	}

	slice<range<const_iterator, int> > sub(int start) const
	{
		const_iterator l = start < 0 ? end()+start : begin()+start;
		return range<const_iterator, int>(l, end());
	}

	list<value_type> subcpy(int start, int end) const
	{
		return list<value_type>(sub(start, end));
	}

	list<value_type> subcpy(int start) const
	{
		return list<value_type>(sub(start));
	}

	static slice<range<iterator, int> > sub(iterator left, iterator right)
	{
		return range<iterator, int>(left, right);
	}

	static slice<range<const_iterator, int> > sub(const_iterator left, const_iterator right)
	{
		return range<const_iterator, int>(left, right);
	}

	static list<value_type> subcpy(iterator left, iterator right)
	{
		return list<value_type>(sub(left, right));
	}

	static list<value_type> subcpy(const_iterator left, const_iterator right)
	{
		return list<value_type>(sub(left, right));
	}

	slice<range<iterator, int> > sub()
	{
		return range<iterator, int>(begin(), end());
	}

	slice<range<const_iterator, int> > sub() const
	{
		return range<const_iterator, int>(begin(), end());
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

	list<value_type> drop(int start, int end)
	{
		iterator l = start < 0 ? this->end()+start : this->begin()+start;
		iterator r = end < 0 ? this->end()+end : this->begin()+end;
		return pop(l, r);
	}

	void drop_front(unsigned int n = 1)
	{
		drop(begin(), begin()+n);
	}

	void drop_back(unsigned int n = 1)
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

	list<value_type> pop_back(unsigned int n = 1)
	{
		return pop(end()-n, end());
	}

	list<value_type> pop_front(unsigned int n = 1)
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

protected:
	end_item* get_item(iterator i)
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
list<value_type> operator<<(list<value_type> os, const value_type &v)
{
	os.push_back(v);
	return os;
}

template<class value_type>
bool operator==(list<value_type> a0, list<value_type> a1)
{
	return (compare(a0, a1) == 0);
}

template<class value_type>
bool operator!=(list<value_type> a0, list<value_type> a1)
{
	return (compare(a0, a1) != 0);
}

template <class value_type, class container>
list<value_type> operator<<(list<value_type> os, const container &c)
{
	os.append_back(c);
	return os;
}

template<class value_type>
bool operator<(list<value_type> a0, list<value_type> a1)
{
	return (compare(a0, a1) < 0);
}

template<class value_type>
bool operator>(list<value_type> a0, list<value_type> a1)
{
	return (compare(a0, a1) > 0);
}

template<class value_type>
bool operator<=(list<value_type> a0, list<value_type> a1)
{
	return (compare(a0, a1) <= 0);
}

template<class value_type>
bool operator>=(list<value_type> a0, list<value_type> a1)
{
	return (compare(a0, a1) >= 0);
}

}

