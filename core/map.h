/*
 * map.h
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include "list.h"
#include "implier.h"
#include "algorithm.h"

#ifndef map_h
#define map_h

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
	using list<implier<ktype, vtype> >::bound;

	iterator find(ktype key)
	{
		iterator pos = search_tree(*this, implier<ktype, vtype>(key, vtype()));
		if (pos != end() && pos->key == key)
			return pos;
		else
			return end();
	}

	iterator insert(ktype key, vtype value)
	{
		iterator pos = search_tree(*this, implier<ktype, vtype>(key, vtype()));
		pos.push(implier<ktype, vtype>(key, value));
		return (pos-1);
	}

	vtype &operator[](ktype key)
	{
		iterator pos = search_tree(*this, implier<ktype, vtype>(key, vtype()));
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

#endif
