/*
 * hash_map.h
 *
 *  Created on: Jun 20, 2015
 *      Author: nbingham
 */

#pragma once

#include <std/hash_set.h>
#include <std/implier.h>

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
	using super::contains;
	using super::position;
	using super::insert_at;
	
	hash_map()
	{
	}

	~hash_map() {}

	iterator insert(key_type key, value_type value = value_type())
	{
		return super::insert(implier<key_type, value_type>(key, value));
	}

	iterator insert_duplicate(key_type key, value_type value = value_type())
	{
		return super::insert_duplicate(implier<key_type, value_type>(key, value));
	}

	iterator find(key_type key)
	{
		return super::find(implier<key_type, value_type>(key, value_type()));
	}

	const_iterator find(key_type key) const
	{
		return super::find(implier<key_type, value_type>(key, value_type()));
	}

	bool contains(key_type key) const
	{
		return contains(implier<key_type, value_type>(key, value_type()));
	}

	value_type &operator[](key_type key)
	{
		iterator result = insert(key);
		return result->value;
	}

	void update(const key_type &key, const value_type &value, value_type (*U)(value_type, value_type))
	{
		iterator pos = insert(key);
		pos->value = U(pos->value, value);
	}
};

}
