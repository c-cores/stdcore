/*
 * hash_table.h
 *
 *  Created on: Jun 20, 2015
 *      Author: nbingham
 */

#pragma once

#include "hasher.h"

template <class value_type, int num_buckets>
struct hash_table
{
	hash_table() : capacity(num_buckets)
	{
		count = 0;
	}

	~hash_table() {}

	const int capacity;
	vector<value_type> buckets[num_buckets];
	int count;

	int size()
	{
		return count;
	}

	bool insert(const value_type &value, typename vector<value_type>::iterator *loc = NULL)
	{
		int bucket = hasher(value).get()%num_buckets;
		typename vector<value_type>::iterator result = lower_bound(buckets[bucket].begin(), buckets[bucket].end(), value);
		if (result == buckets[bucket].end() || *result != value)
		{
			result = buckets[bucket].insert(result, value);
			count++;
			if (loc != NULL)
				*loc = result;

			return true;
		}

		if (loc != NULL)
			*loc = result;

		return false;
	}

	bool contains(const value_type &value, typename vector<value_type>::iterator *loc = NULL)
	{
		int bucket = hasher(value).get()%num_buckets;
		typename vector<value_type>::iterator result = lower_bound(buckets[bucket].begin(), buckets[bucket].end(), value);
		if (loc != NULL)
			*loc = result;

		return (result != buckets[bucket].end() && *result == value);
	}

	void erase(const value_type &value)
	{
		int bucket = hasher(value).get()%num_buckets;
		typename vector<value_type>::iterator result = lower_bound(buckets[bucket].begin(), buckets[bucket].end(), value);
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

	void merge(const hash_table<value_type, num_buckets> &m)
	{
		for (int i = 0; i < num_buckets; i++)
		{
			int s = (int)buckets[i].size();
			buckets[i].insert(buckets[i].end(), m.buckets[i].begin(), m.buckets[i].end());
			inplace_merge(buckets[i].begin(), buckets[i].begin() + s, buckets[i].end());
		}
		count += m.count;
	}

	value_type &operator[](int index)
	{
		int i = 0;
		for (; i < num_buckets && buckets[i].size() <= index; i++)
			index -= buckets[i].size();
		return buckets[i][index];
	}

	hash_table<value_type, num_buckets> &operator=(const hash_table<value_type, num_buckets> &copy)
	{
		for (int i = 0; i < num_buckets; i++)
			buckets[i] = copy.buckets[i];
		count = copy.count;
		return *this;
	}

};

