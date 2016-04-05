/*
 * map.h
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#pragma once

#include "list.h"
#include "implier.h"
#include "search.h"

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
	using list<implier<ktype, vtype> >::ref;

	iterator find(ktype key)
	{
		iterator pos = search_tree(ref(), key);
		if (pos != end() && pos->key == key)
			return pos;
		else
			return end();
	}

	iterator insert(ktype key, vtype value)
	{
		iterator pos = search_tree(ref(), key);
		pos.push(implier<ktype, vtype>(key, value));
		return (pos-1);
	}

	vtype &operator[](ktype key)
	{
		iterator pos = search_tree(ref(), key);
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

