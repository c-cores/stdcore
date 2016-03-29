/*
 * bits.h
 *
 *  Created on: Jun 20, 2015
 *      Author: nbingham
 */

#pragma once

#include "array.h"

struct bits : array<unsigned char>
{
	bits();
	~bits();

	using typename array<unsigned char>::type;
	using typename array<unsigned char>::iterator;
	using typename array<unsigned char>::const_iterator;
	
	using array<char>::begin;
	using array<char>::end;
	using array<char>::rbegin;
	using array<char>::rend;
	using array<char>::sub;
	using array<char>::size;

	using array<char>::operator=;

	uint32_t hash();
};

bits &operator<<(bits &str, char v);
bits &operator<<(bits &str, short v);
bits &operator<<(bits &str, int v);
bits &operator<<(bits &str, long v);
bits &operator<<(bits &str, long long v);
bits &operator<<(bits &str, unsigned char v);
bits &operator<<(bits &str, unsigned short v);
bits &operator<<(bits &str, unsigned int v);
bits &operator<<(bits &str, unsigned long v);
bits &operator<<(bits &str, unsigned long long v);
bits &operator<<(bits &str, bool v);
bits &operator<<(bits &str, float v);
bits &operator<<(bits &str, double v);
bits &operator<<(bits &str, string v);
bits &operator<<(bits &str, const char *v);
bits &operator<<(bits &str, char *v);

template <class type0, class type1>
bits &operator<<(bits &str, const pair<type0, type1> &v)
{
	return str << v.first << v.second;
}

template <class type>
bits &operator<<(bits &str, const array<type> &v)
{
	for (typename array<type>::const_iterator i = v.begin(); i != v.end(); i++)
		str << *i;
	return str;
}

template <class type>
bits &operator<<(bits &str, const list<type> &v)
{
	for (typename array<type>::const_iterator i = v.begin(); i != v.end(); i++)
		str << *i;
	return str;
}

template <class key_type, class value_type>
bits &operator<<(bits &str, const map<key_type, value_type> &v)
{
	for (typename map<key_type, value_type>::const_iterator i = v->begin(); i != v->end(); i++)
		str << *i;
	return str;
}

