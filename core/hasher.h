/*
 * hasher.h
 *
 *  Created on: Jun 20, 2015
 *      Author: nbingham
 */

#pragma once

#include "array.h"

struct hasher
{
	hasher();
	
	template <class type>
	hasher(type v)
	{
		put(*this, v);
	}

	template <class type>
	hasher(const type *v, int n)
	{
		put(*this, v, n);
	}

	~hasher();

	array<char> data;

	uint32_t get();
};

void put(hasher &h, char v);
void put(hasher &h, unsigned char v);
void put(hasher &h, short v);
void put(hasher &h, unsigned short v);
void put(hasher &h, int v);
void put(hasher &h, unsigned int v);
void put(hasher &h, long v);
void put(hasher &h, unsigned long v);
void put(hasher &h, long long v);
void put(hasher &h, unsigned long long v);
void put(hasher &h, bool v);
void put(hasher &h, float v);
void put(hasher &h, double v);
void put(hasher &h, string v);

template <class type>
void put(hasher &h, type *v, int n = 1)
{
	for (int i = 0; i < n; i++)
		put(h, *(v+i));
}

template <class type0, class type1>
void put(hasher &h, const pair<type0, type1> &v)
{
	put(h, v.first);
	put(h, v.second);
}

template <class type>
void put(hasher &h, const vector<type> &v)
{
	for (typename vector<type>::const_iterator i = v.begin(); i != v.end(); i++)
		put(h, *i);
}

template <class type>
void put(hasher &h, const list<type> &v)
{
	for (typename vector<type>::const_iterator i = v.begin(); i != v.end(); i++)
		put(h, *i);
}

template <class key_type, class value_type>
void put(hasher &h, const map<key_type, value_type> &v)
{
	for (typename map<key_type, value_type>::const_iterator i = v->begin(); i != v->end(); i++)
		put(h, *i);
}

