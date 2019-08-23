/*
 * map.h
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#pragma once

#include <std/list.h>
#include <std/implier.h>
#include <std/sort.h>

namespace core
{

template <class ktype, class vtype>
struct map : list<implier<ktype, vtype> >
{
	map()
	{

	}

	~map()
	{

	}

	using typename list<implier<ktype, vtype> >::type;
	using typename list<implier<ktype, vtype> >::iterator;
	using typename list<implier<ktype, vtype> >::const_iterator;
	using list<implier<ktype, vtype> >::begin;
	using list<implier<ktype, vtype> >::end;
	using list<implier<ktype, vtype> >::rbegin;
	using list<implier<ktype, vtype> >::rend;
	using list<implier<ktype, vtype> >::sub;

	iterator insert(implier<ktype, vtype> entry)
	{
		iterator pos = lower_bound(*this, entry);
		pos.push(entry);
		return (pos-1);
	}

	iterator insert(const ktype &key, const vtype &value)
	{
		iterator pos = lower_bound(*this, key);
		pos.push(implier<ktype, vtype>(key, value));
		return (pos-1);
	}

	iterator find(const ktype &key)
	{
		iterator pos = lower_bound(*this, key);
		if (pos != end() && pos->key == key)
			return pos;
		else
			return end();
	}

	iterator at(const ktype &key, const vtype &value = vtype())
	{
		iterator pos = lower_bound(*this, key);
		if (pos == end() || pos->key != key) {
			pos.push(implier<ktype, vtype>(key, value));
			return pos-1;
		} else
			return pos;
	}

	vtype &operator[](ktype key)
	{
		return at(key)->value;
	}

	void update(const ktype &key, const vtype &value, vtype (*U)(vtype, vtype))
	{
		iterator pos = lower_bound(*this, key);
		if (pos == end() || pos->key != key) {
			pos.push(implier<ktype, vtype>(key, value));
		} else {
			pos->value = U(pos->value, value);
		}
	}
};

}

