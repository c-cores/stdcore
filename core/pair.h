/*
 * pair.h
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include "file.h"

#ifndef pair_h
#define pair_h

namespace core
{

template <class type1, class type2>
struct pair
{
	pair() : first(), second()
	{

	}

	pair(type1 f, type2 s) : first(f), second(s)
	{
	}

	~pair()
	{

	}

	type1 first;
	type2 second;
};

template <class type1, class type2>
file &operator<<(file &f, const pair<type1, type2> &p)
{
	f << "(" << p.first << ", " << p.second << ")";
	return f;
}

template <class type1, class type2>
bool operator==(pair<type1, type2> p1, pair<type1, type2> p2)
{
	return p1.first == p2.first && p1.second == p2.second;
}

template <class type1, class type2>
bool operator!=(pair<type1, type2> p1, pair<type1, type2> p2)
{
	return p1.first != p2.first || p1.second != p2.second;
}

template <class type1, class type2>
bool operator<(pair<type1, type2> p1, pair<type1, type2> p2)
{
	return p1.first < p2.first || (p1.first == p2.first && p1.second < p2.second);
}

template <class type1, class type2>
bool operator>(pair<type1, type2> p1, pair<type1, type2> p2)
{
	return p1.first > p2.first || (p1.first == p2.first && p1.second > p2.second);
}

template <class type1, class type2>
bool operator<=(pair<type1, type2> p1, pair<type1, type2> p2)
{
	return p1.first < p2.first || (p1.first == p2.first && p1.second <= p2.second);
}

template <class type1, class type2>
bool operator>=(pair<type1, type2> p1, pair<type1, type2> p2)
{
	return p1.first > p2.first || (p1.first == p2.first && p1.second >= p2.second);
}

}

#endif
