/*
 * hash_map.h
 *
 *  Created on: Jun 20, 2015
 *      Author: nbingham
 */

#pragma once

#include "hasher.h"
#include "map.h"

template <class key_type, class value_type, int num_buckets>
struct hash_map
{
	hash_map() : capacity(num_buckets)
	{
		count = 0;
	}

	~hash_map() {}

	const int capacity;
	map<key_type, value_type> buckets[num_buckets];
	int count;

	int size()
	{
		return count;
	}

	bool insert(const key_type &key, const value_type &value, typename map<key_type, value_type>::iterator* loc = NULL)
	{
		int bucket = hasher(key).get()%num_buckets;
		pair<typename map<key_type, value_type>::iterator, bool> result = buckets[bucket].insert(pair<key_type, value_type>(key, value));
		if (loc != NULL)
			*loc = result.first;
		count++;
		return result.second;
	}

	bool find(const key_type &key, typename map<key_type, value_type>::iterator* loc = NULL)
	{
		int bucket = hasher(key).get()%num_buckets;
		typename map<key_type, value_type>::iterator result = buckets[bucket].find(key);
		if (loc != NULL)
			*loc = result;
		return (result != buckets[bucket].end());
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

	hash_map<key_type, value_type, num_buckets> &operator=(const hash_map<key_type, value_type, num_buckets> &copy)
	{
		for (int i = 0; i < num_buckets; i++)
			buckets[i] = copy.buckets[i];
		count = copy.count;
		return *this;
	}
};

