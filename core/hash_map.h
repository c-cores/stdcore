/*
 * hash_map.h
 *
 *  Created on: Jun 20, 2015
 *      Author: nbingham
 */

#pragma once

#include "list.h"
#include "implier.h"
#include "pair.h"

namespace core
{

template <class key_type, class value_type, class hasher>
struct hash_map : list<implier<pair<uint32_t, key_type>, value_type> >
{
	typedef implier<pair<uint32_t, key_type>, value_type> implier
	typedef list<implier> super;
	
	hash_map()
	{
		// start out with 16 buckets
		buckets.push_back(16, begin());
		shift = 28;
	}

	~hash_map() {}

	using typename super::type;
	using typename super::iterator;
	using typename super::const_iterator;

	array<iterator> buckets;
	uint32_t shift;

	using super::size;
	using super::begin;
	using super::end;
	using super::rbegin;
	using super::rend;
	using super::sub;

	iterator insert(const key_type &key, const value_type &value, )
	{
		uint32_t hash = hasher(key);
		uint32_t bucket = hash >> shift;
		implier data(key, value, hash);
		iterator pos = search_tree(sub(buckets.at(bucket), buckets.at(bucket+1)-1), data);
		pos.push(data);
		return pos-1;
	}

	iterator find(const key_type &key)
	{
		uint32_t hash = hasher(key);
		uint32_t bucket = hash >> shift;
		iterator pos = search_tree(slice<iterator, type>(buckets.at(bucket), buckets.at(bucket+1)-1), pair<uint32_t, key_type>(hash, key));
		return pos-1;
	}

	void erase(key_type key)
	{
		int bucket = hasher(key).get()%num_buckets;
		typename map<key_type, value_type>::iterator result = buckets[bucket].find(key);
		if (result != buckets[bucket].end())
			buckets[bucket].erase(result);
	}

	int max_bucket_size()
	{
		int max_size = 0;
		for (int i = 0; i < num_buckets; i++)
			if ((int)buckets[i].size() > max_size)
				max_size = buckets[i].size();
		return max_size;
	}

	
};

}
