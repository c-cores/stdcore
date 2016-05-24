/*
 * hash_set.h
 *
 *  Created on: Jun 20, 2015
 *      Author: nbingham
 */

#pragma once

#include <core/array.h>
#include <core/list.h>
#include <core/pair.h>
#include <core/search.h>

namespace core
{

template <class key_type, class hasher>
struct hash_set : list<pair<int, key_type> >
{
	typedef list<pair<int, key_type> > super;
	typedef key_type type;
	using super::size;
	using super::left;
	using super::right;
	using super::count;
	using typename super::end_item;
	using typename super::item;

	struct iterator;
	struct const_iterator;

	struct iterator
	{
	protected:
		friend class hash_set<key_type, hasher>;
		friend class const_iterator;
		hash_set<key_type, hasher> *root;
		end_item *loc;
	public:
		iterator()
		{
			root = NULL;
			loc = NULL;
		}

		iterator(hash_set<key_type, hasher> *root, end_item *loc)
		{
			this->root = root;
			this->loc = loc;
		}

		iterator(hash_set<key_type, hasher> *root, int n)
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

		key_type &operator*()
		{
			return ((item*)loc)->value.second;
		}
		key_type *operator->()
		{
			return &((item*)loc)->value.second;
		}

		key_type *ptr()
		{
			return &((item*)loc)->value.second;
		}

		key_type &get()
		{
			return ((item*)loc)->value.second;
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
	};

	struct const_iterator
	{
	protected:
		friend class hash_set<key_type, hasher>;
		friend class iterator;
		const hash_set<key_type, hasher> *root;
		const end_item *loc;
	public:
		const_iterator()
		{
			root = NULL;
			loc = NULL;
		}

		const_iterator(const hash_set<key_type, hasher> *l)
		{
			root = l;
			loc = &l->left;
		}

		const_iterator(const hash_set<key_type, hasher> *l, const end_item *n)
		{
			root = l;
			loc = n;
		}

		const_iterator(hash_set<key_type, hasher> *l, int n)
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

		const key_type &operator*()
		{
			return ((const item*)loc)->value.second;
		}

		const key_type *operator->()
		{
			return &((const item*)loc)->value.second;
		}

		const key_type &get()
		{
			return ((const item*)loc)->value.second;
		}

		const key_type *ptr()
		{
			return &((const item*)loc)->value.second;
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
	};

	hash_set()
	{
		buckets.push_back(17, super::begin());
		shift = 28;
		salt = rand()*(0xFFFFFFFF/RAND_MAX);
	}

	~hash_set()
	{
	}

	array<typename super::iterator> buckets;
	uint32_t salt;
	int shift;

	iterator at(int i)
	{
		return begin() + i;
	}

	const_iterator at(int i) const
	{
		return begin() + i;
	}

	key_type &get(int i) const
	{
		return ((item*)(begin() + i))->value.second;
	}

	key_type *ptr(int i) const
	{
		return (begin() + i).ptr();
	}

	key_type &operator[](int i) const
	{
		return ((item*)(begin() + i))->value.second;
	}

	key_type &front() const
	{
		return *begin();
	}

	key_type &back() const
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

	iterator insert(const key_type &key)
	{
		hasher h;
		h << key;
		uint32_t hash = h.hash() + salt;
		int bucket = (int)(hash >> shift);

		typename super::iterator pos = super::end();
		pair<int, key_type> search(hash, key);
		if (buckets[bucket] != super::end())
			pos = search_tree(super::sub(buckets[bucket], buckets[bucket+1]-1), search);

		pos.push(search);
		typename super::iterator result = pos-1;

		for (int i = bucket; i >= 0 && buckets[i] == pos; i--)
			buckets[i] = result;

		if (size() > buckets.size()-1)
		{
			shift--;

			int old_size = buckets.size()-1;
			buckets.push_back(buckets.size()-1, super::end());
			for (int i = old_size-1; i > 0; i--)
				buckets[i*2] = buckets[i];
			for (int i = 0; i < buckets.size()-1; i+=2)
			{
				int boundary = (i+1) << shift;
				typename super::iterator j = buckets[i];
				while (j != buckets[i+2] && j->first < boundary)
					j++;
				buckets[i+1] = j;
			}
		}

		return iterator(this, super::get_item(result));
	}

	iterator find(const key_type &key)
	{
		hasher h;
		h << key;
		uint32_t hash = h.hash() + salt;
		int bucket = (int)(hash >> shift);

		if (buckets[bucket] != super::end())
		{
			pair<int, key_type> search(hash, key);
			typename super::iterator pos = search_tree(super::sub(buckets[bucket], buckets[bucket+1]-1), search);
			if (*pos != search)
				return end();
			else
				return iterator(this, super::get_item(pos));
		}
		else
			return end();
	}

	bool contains(const key_type &key)
	{
		return find(key) != end();
	}
};

}
