/*
 * hash_map.h
 *
 *  Created on: Jun 20, 2015
 *      Author: nbingham
 */

#pragma once

#include <core/hash_set.h>
#include <core/implier.h>

namespace core
{

template <class key_type, class value_type, uint32_t (*hash_func)(const char *,int,uint32_t) = murmur3_32>
struct hash_map : hash_set<implier<key_type, value_type>, hash_func>
{
	typedef hash_set<implier<key_type, value_type>, hash_func> super;
	using typename super::type;
	using typename super::iterator;
	using typename super::const_iterator;
	using super::size;
	using super::begin;
	using super::end;
	using super::rbegin;
	using super::rend;
	using super::insert;
	using super::find;
	using super::contains;
	
	hash_map()
	{
	}

	~hash_map() {}

	value_type &operator[](const key_type &key)
	{
		iterator result = find(key);
		return result->value;
	}

	iterator insert(const key_type &key, const value_type &value)
	{
		return super::insert(implier<key_type, value_type>(key, value));
	}

	iterator find(const key_type &key)
	{
		return super::find(implier<key_type, value_type>(key, value_type()));
	}

	const_iterator find(const key_type &key) const
	{
		return super::find(implier<key_type, value_type>(key, value_type()));
	}

	bool contains(const key_type &key) const
	{
		return find(key) != end();
	}
};

}
