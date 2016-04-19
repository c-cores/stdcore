/*
 * hash_map.h
 *
 *  Created on: Jun 20, 2015
 *      Author: nbingham
 */

#pragma once

#include "hash_set.h"
#include "implier.h"

namespace core
{

template <class key_type, class value_type, class hasher>
struct hash_map : hash_set<implier<key_type, value_type>, hasher>
{
	typedef hash_set<implier<key_type, value_type>, hasher> super;
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

	iterator insert(const key_type &key, const value_type &value)
	{
		return super::insert(implier<key_type, value_type>(key, value));
	}

	iterator find(const key_type &key)
	{
		return super::find(implier<key_type, value_type>(key, value_type()));
	}

	bool contains(const key_type &key)
	{
		return find(key) != end();
	}
};

}
