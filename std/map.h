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


	iterator insert(ktype key, vtype value)
	{
		iterator pos = lower_bound(*this, key);
		pos.push(implier<ktype, vtype>(key, value));
		return (pos-1);
	}

	iterator find(ktype key)
	{
		iterator pos = lower_bound(*this, key);
		if (pos != end() && pos->key == key)
			return pos;
		else
			return end();
	}

	vtype &operator[](ktype key)
	{
		iterator pos = lower_bound(*this, key);
		if (pos != end() && pos->key == key)
			return pos->value;
		else
		{
			pos.push(implier<ktype, vtype>(key, vtype()));
			return (pos-1)->value;
		}
	}
};

}

