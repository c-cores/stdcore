/*
 * hash_set.h
 *
 *  Created on: Jun 20, 2015
 *      Author: nbingham
 */

#pragma once

#include <std/array.h>
#include <std/list.h>
#include <std/bits.h>
#include <std/pair.h>
#include <std/search.h>

namespace core
{

uint32_t murmur3_32(const char *key, int len, uint32_t seed);

template <class key_type, uint32_t (*hash_func)(const char *,int,uint32_t)>
struct hash_set;

template <class key_type, uint32_t (*hash_func)(const char *,int,uint32_t)>
struct hash_set_const_iterator;

template <class key_type, uint32_t (*hash_func)(const char *,int,uint32_t) = murmur3_32>
struct hash_set_iterator
{
	friend class hash_set<key_type, hash_func>;
	friend class hash_set_const_iterator<key_type, hash_func>;
	hash_set<key_type, hash_func> *root;
	typename list<pair<uint32_t, key_type> >::iterator ref;
	typedef key_type type;
	
	hash_set_iterator(hash_set<key_type, hash_func> *root, typename list<pair<uint32_t, key_type> >::iterator ref)
	{
		this->root = root;
		this->ref = ref;
	}

	hash_set_iterator()
	{
		root = NULL;
	}

	hash_set_iterator(const hash_set_iterator<key_type, hash_func> &copy)
	{
		root = copy.root;
		ref = copy.ref;
	}

	~hash_set_iterator() {}

	operator bool() const
	{
		return root != NULL && ref;
	}

	key_type &operator*() const
	{
		return ref->second;
	}
	key_type *operator->() const
	{
		return &ref->second;
	}

	key_type *ptr() const
	{
		return &ref->second;
	}

	key_type &get() const
	{
		return ref->second;
	}

	int idx() const
	{
		return ref.idx();
	}

	uint32_t hash() const
	{
		return ref->first;
	}

	int bucket() const
	{
		return hash() >> root->shift;
	}

	hash_set_iterator<key_type, hash_func> operator++(int)
	{
		return hash_set_iterator<key_type, hash_func>(root, ref++);
	}

	hash_set_iterator<key_type, hash_func> operator--(int)
	{
		return hash_set_iterator<key_type, hash_func>(root, ref--);
	}

	hash_set_iterator<key_type, hash_func> &operator++()
	{
		++ref;
		return *this;
	}

	hash_set_iterator<key_type, hash_func> &operator--()
	{
		--ref;
		return *this;
	}

	hash_set_iterator<key_type, hash_func> &operator+=(int n)
	{
		ref += n;
		return *this;
	}

	hash_set_iterator<key_type, hash_func> &operator-=(int n)
	{
		ref -= n;
		return *this;
	}

	hash_set_iterator<key_type, hash_func> operator+(int n) const
	{
		return hash_set_iterator<key_type, hash_func>(root, ref+n);
	}

	hash_set_iterator<key_type, hash_func> operator-(int n) const
	{
		return hash_set_iterator<key_type, hash_func>(root, ref-n);
	}

	bool operator==(hash_set_iterator<key_type, hash_func> i) const
	{
		return ref == i.ref;
	}

	bool operator!=(hash_set_iterator<key_type, hash_func> i) const
	{
		return ref != i.ref;
	}

	bool operator==(hash_set_const_iterator<key_type, hash_func> i) const
	{
		return ref == i.ref;
	}

	bool operator!=(hash_set_const_iterator<key_type, hash_func> i) const
	{
		return ref != i.ref;
	}

	int operator-(hash_set_iterator<key_type, hash_func> i) const
	{
		return ref - i.ref;
	}

	int operator-(hash_set_const_iterator<key_type, hash_func> i) const
	{
		return ref - i.ref;
	}

	void drop(int n = 1)
	{
		if (ref.loc != NULL) {
			if (n > 0)
			{
				hash_set_iterator<key_type, hash_func> start = *this-1;
				list_item<pair<uint32_t, key_type> > *temp;
				
				for (int i = 0; i < n and ref.loc->next != ref.loc; i++)
				{
					int bx = bucket();
					if (root->buckets[bx].loc == ref.loc)
						root->buckets[bx]++;
					
					for (int b = bx+1; b < root->buckets.size() and root->buckets[b].loc == ref.loc; b++) {
						root->buckets[b]++;
					}
					
					for (int b = bx-1; b >= 0 and root->buckets[b].loc == ref.loc; b--) {
						root->buckets[b]++;
					}

					temp = (list_item<pair<uint32_t, key_type> >*)ref.loc;
					ref.loc = ref.loc->next;
					delete temp;
					root->count--;
				}
					
				start.ref.loc->next = ref.loc;
				ref.loc->prev = start.ref.loc;
			}
			else if (n < 0)
			{
				hash_set_iterator<key_type, hash_func> start = *this-1;
				list_item<pair<uint32_t, key_type> > *temp;
				
				for (int i = 0; i > n and start.ref.loc->prev != start.ref.loc; i--)
				{
					int bx = start.bucket();
					if (root->buckets[bx].loc == start.ref.loc)
						root->buckets[bx]--;
						
					for (int b = bx+1; b < root->buckets.size() and root->buckets[b].loc == start.ref.loc; b++)
						root->buckets[b]--;
					
					for (int b = bx-1; b >= 0 and root->buckets[b].loc == start.ref.loc; b--)
						root->buckets[b]--;

					temp = (list_item<pair<uint32_t, key_type> >*)start.ref.loc;
					start.ref.loc = start.ref.loc->prev;
					delete temp;
					root->count--;
				}
				
				start.ref.loc->next = ref.loc;
				ref.loc->prev = start.ref.loc;
			}
		}
	}

	hash_set_iterator<key_type, hash_func> &operator=(hash_set_iterator<key_type, hash_func> i)
	{
		root = i.root;
		ref = i.ref;
		return *this;
	}
};

template <class key_type, uint32_t (*hash_func)(const char *,int,uint32_t) = murmur3_32>
struct hash_set_const_iterator
{
	friend class hash_set<key_type, hash_func>;
	friend class hash_set_iterator<key_type, hash_func>;
	typedef key_type type;

	const hash_set<key_type, hash_func> *root;
	typename list<pair<uint32_t, key_type> >::const_iterator ref;

	hash_set_const_iterator(const hash_set<key_type, hash_func> *root, typename list<pair<uint32_t, key_type> >::const_iterator ref)
	{
		this->root = root;
		this->ref = ref;
	}

	hash_set_const_iterator()
	{
		root = NULL;
	}

	hash_set_const_iterator(const hash_set_iterator<key_type, hash_func> &i)
	{
		root = i.root;
		ref = i.ref;
	}

	hash_set_const_iterator(const hash_set_const_iterator<key_type, hash_func> &i)
	{
		root = i.root;
		ref = i.ref;
	}

	~hash_set_const_iterator() {}

	operator bool() const
	{
		return root != NULL && ref;
	}

	const key_type &operator*() const
	{
		return ref->second;
	}

	const key_type *operator->() const
	{
		return &ref->second;
	}

	const key_type &get() const
	{
		return ref->second;
	}

	const key_type *ptr() const
	{
		return &ref->second;
	}

	int idx() const
	{
		return ref.idx();
	}

	uint32_t hash() const
	{
		return ref->first;
	}

	int bucket() const
	{
		return hash() >> root->shift;
	}

	hash_set_const_iterator<key_type, hash_func> operator++(int)
	{
		return hash_set_const_iterator<key_type, hash_func>(root, ref++);
	}

	hash_set_const_iterator<key_type, hash_func> operator--(int)
	{
		return hash_set_const_iterator<key_type, hash_func>(root, ref--);
	}

	hash_set_const_iterator<key_type, hash_func> &operator++()
	{
		++ref;
		return *this;
	}

	hash_set_const_iterator<key_type, hash_func> &operator--()
	{
		--ref;
		return *this;
	}

	hash_set_const_iterator<key_type, hash_func> &operator+=(int n)
	{
		ref += n;
		return *this;
	}

	hash_set_const_iterator<key_type, hash_func> &operator-=(int n)
	{
		ref -= n;
		return *this;
	}

	hash_set_const_iterator<key_type, hash_func> operator+(int n) const
	{
		return hash_set_const_iterator<key_type, hash_func>(root, ref + n);
	}

	hash_set_const_iterator<key_type, hash_func> operator-(int n) const
	{
		return hash_set_const_iterator<key_type, hash_func>(root, ref - n);
	}

	bool operator==(hash_set_const_iterator<key_type, hash_func> i) const
	{
		return ref == i.ref;
	}

	bool operator!=(hash_set_const_iterator<key_type, hash_func> i) const
	{
		return ref != i.ref;
	}

	bool operator==(hash_set_iterator<key_type, hash_func> i) const
	{
		return ref == i.ref;
	}

	bool operator!=(hash_set_iterator<key_type, hash_func> i) const
	{
		return ref != i.ref;
	}

	int operator-(hash_set_const_iterator<key_type, hash_func> i) const
	{
		return ref - i.ref;
	}

	int operator-(hash_set_iterator<key_type, hash_func> i) const
	{
		return ref - i.ref;
	}

	hash_set_const_iterator<key_type, hash_func> &operator=(hash_set_const_iterator<key_type, hash_func> i)
	{
		root = i.root;
		ref = i.ref;
		return *this;
	}

	hash_set_const_iterator<key_type, hash_func> &operator=(hash_set_iterator<key_type, hash_func> i)
	{
		root = i.root;
		ref = i.ref;
		return *this;
	}
};

template <class key_type, uint32_t (*hash_func)(const char *,int,uint32_t) = murmur3_32>
struct hash_set : container<key_type, hash_set_iterator<key_type, hash_func>, hash_set_const_iterator<key_type, hash_func> >
{
	friend class hash_set_iterator<key_type, hash_func>;
	friend class hash_set_const_iterator<key_type, hash_func>;

	typedef container<key_type, hash_set_iterator<key_type, hash_func>, hash_set_const_iterator<key_type, hash_func> > super;
	using typename super::type;
	using typename super::iterator;
	using typename super::const_iterator;

	typedef typename list<pair<uint32_t, key_type> >::iterator item_iterator;
	typedef typename list<pair<uint32_t, key_type> >::const_iterator item_const_iterator;

	list<pair<uint32_t, key_type> > items;
	array<item_iterator> buckets;
	uint32_t salt;
	int shift;
	int count;

	hash_set()
	{
		buckets.resize(17, items.end());
		shift = 28;
		salt = rand();
		count = 0;
	}

	~hash_set()
	{
	}

	int size() const
	{
		return count;
	}

	iterator begin()
	{
		return iterator(this, items.begin());
	}

	iterator end()
	{
		return iterator(this, items.end());
	}

	iterator rbegin()
	{
		return iterator(this, items.rbegin());
	}

	iterator rend()
	{
		return iterator(this, items.rend());
	}

	const_iterator begin() const
	{
		return const_iterator(this, items.begin());
	}

	const_iterator end() const
	{
		return const_iterator(this, items.end());
	}

	const_iterator rbegin() const
	{
		return const_iterator(this, items.rbegin());
	}

	const_iterator rend() const
	{
		return const_iterator(this, items.rend());
	}

	iterator at(int i)
	{
		return begin() + i;
	}

	const_iterator at(int i) const
	{
		return begin() + i;
	}

	key_type &front() const
	{
		return *begin();
	}

	key_type &back() const
	{
		return *rbegin();
	}

	key_type &get(int i) const
	{
		return items.get(i).second;
	}

	key_type *ptr(int i) const
	{
		return &items.get(i).second;
	}

	key_type &operator[](int i) const
	{
		return items.get(i).second;
	}

	void rebucket()
	{
		shift--;

		int old_size = buckets.size()-1;
		buckets.resize(old_size*2+1, items.end());
		for (int i = old_size-1; i > 0; i--)
			buckets[i*2] = buckets[i];
		for (int i = 0; i < buckets.size()-1; i+=2)
		{
			uint32_t start = (i+1) << shift;
			if (buckets[i]) {
				buckets[i+1] = lower_bound(buckets[i], buckets[i+2], pair<uint32_t, key_type>(start, key_type()));
			} else {
				buckets[i+1] = buckets[i];
			}
		
			/*item_iterator j = buckets[i];
			while (j and j != buckets[i+2] and j->first < start) {
				j++;
			}
			buckets[i+1] = j;*/
		}
	}

	uint32_t hash_it(key_type key) const
	{
		bits h;
		hash_data(h, key);
		return hash_func((const char*)h.data, h.size(), salt);
	}

	item_iterator position(key_type key, uint32_t *hashptr = NULL)
	{
		uint32_t hash = hash_it(key);
		int bucket = (int)(hash >> shift);

		if (hashptr != NULL)
			*hashptr = hash;

		if (buckets[bucket])
			return lower_bound(buckets[bucket], buckets[bucket+1], pair<uint32_t, key_type>(hash, key));
		else
			return items.end();
	}

	item_const_iterator position(key_type key, uint32_t *hashptr = NULL) const
	{
		uint32_t hash = hash_it(key);
		int bucket = (int)(hash >> shift);

		if (hashptr != NULL)
			*hashptr = hash;

		if (buckets[bucket])
			return lower_bound(buckets[bucket], buckets[bucket+1], pair<uint32_t, key_type>(hash, key));
		else
			return items.end();
	}

	iterator insert_at(item_iterator pos, key_type key, uint32_t *hashptr = NULL)
	{
		uint32_t hash = hashptr == NULL ? hash_it(key) : *hashptr;
		int bucket = (int)(hash >> shift);

		pair<uint32_t, key_type> search(hash, key);

		if (pos and pos->second == key)
			return iterator(this, pos);
		else
		{
			pos.push(search);
			item_iterator result = pos-1;

			for (int i = bucket; i >= 0 && buckets[i] == pos; i--)
				buckets[i] = result;

			count++;
			if (count > buckets.size()-1) {
				rebucket();
			}
			return iterator(this, result);
		}
	}

	iterator insert(key_type key)
	{
		uint32_t hash = hash_it(key);
		int bucket = (int)(hash >> shift);

		pair<uint32_t, key_type> search(hash, key);
		item_iterator pos;
		if (buckets[bucket])
			pos = lower_bound(buckets[bucket], buckets[bucket+1], search);
		else
			pos = items.end();

		if (pos and pos->second == key) {
			return iterator(this, pos);
		} else {
			pos.push(search);
			item_iterator result = pos-1;

			for (int i = bucket; i >= 0 && buckets[i] == pos; i--)
				buckets[i] = result;

			count++;
			if (count > buckets.size()-1) {
				rebucket();
			}
			return iterator(this, result);
		}
	}

	iterator insert_duplicate(key_type key)
	{
		uint32_t hash = hash_it(key);
		int bucket = (int)(hash >> shift);
		
		pair<uint32_t, key_type> search(hash, key);
		item_iterator pos;
		if (buckets[bucket])
			pos = lower_bound(buckets[bucket], buckets[bucket+1], search);
		else
			pos = items.end();

		pos.push(search);
		item_iterator result = pos-1;

		for (int i = bucket; i >= 0 && buckets[i] == pos; i--)
			buckets[i] = result;

		count++;
		if (count > buckets.size()-1)
			rebucket();
		return iterator(this, result);
	}

	iterator find(key_type key)
	{
		item_iterator pos = position(key);
		if (pos and pos->second == key)
			return iterator(this, pos);
		else
			return end();
	}

	const_iterator find(key_type key) const
	{
		item_const_iterator pos = position(key);
		if (pos and pos->second == key)
			return const_iterator(this, pos);
		else
			return end();
	}

	int count_all(key_type key)
	{
		int result = 0;
		iterator start = find(key);
		while (start != end() && *start == key)
		{
			result++;
			start++;
		}

		return result;
	}

	bool contains(key_type key) const
	{
		item_const_iterator pos = position(key);
		return (pos && pos->second == key);
	}

	void clear()
	{
		items.clear();
		buckets.clear();
		shift = 28;
		count = 0;
		
		buckets.resize(17, items.end());
	}
};

}
