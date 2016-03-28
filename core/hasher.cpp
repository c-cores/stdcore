/*
 * hasher.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: nbingham
 */

#include "hasher.h"

hasher::hasher()
{

}

hasher::~hasher()
{

}

uint32_t hasher::get()
{
	uint32_t len = data.size();
	const char* ptr = data.data();
	uint32_t hash = len, tmp;
	int rem;

	if (len <= 0 || ptr == NULL)
		return 0;

	rem = len & 3;
	len >>= 2;

	/* Main loop */
	for (;len > 0; len--)
	{
		hash  += (*((const uint16_t *) (ptr)));
		tmp    = ((*((const uint16_t *) (ptr+2))) << 11) ^ hash;
		hash   = (hash << 16) ^ tmp;
		ptr  += 2*sizeof (uint16_t);
		hash  += hash >> 11;
	}

	/* Handle end cases */
	switch (rem)
	{
		case 3: hash += (*((const uint16_t *) (ptr)));
				hash ^= hash << 16;
				hash ^= ((signed char)ptr[sizeof (uint16_t)]) << 18;
				hash += hash >> 11;
				break;
		case 2: hash += (*((const uint16_t *) (ptr)));
				hash ^= hash << 11;
				hash += hash >> 17;
				break;
		case 1: hash += (signed char)*ptr;
				hash ^= hash << 10;
				hash += hash >> 1;
	}

	/* Force "avalanching" of final 127 bits */
	hash ^= hash << 3;
	hash += hash >> 5;
	hash ^= hash << 4;
	hash += hash >> 17;
	hash ^= hash << 25;
	hash += hash >> 6;

	data.clear();
	return hash;
}

void put(hasher &h, char v)
{
	h.data.reserve(h.data.size() + sizeof(char));
	h.data.push_back(v);
}

void put(hasher &h, unsigned char v)
{
	h.data.reserve(h.data.size() + sizeof(unsigned char));
	for (int i = 0; i < (int)sizeof(unsigned char); i++)
		h.data.push_back(*(((const char*)&v)+i));
}

void put(hasher &h, short v)
{
	h.data.reserve(h.data.size() + sizeof(short));
	for (int i = 0; i < (int)sizeof(short); i++)
		h.data.push_back(*(((const char*)&v)+i));
}

void put(hasher &h, unsigned short v)
{
	h.data.reserve(h.data.size() + sizeof(unsigned short));
	for (int i = 0; i < (int)sizeof(unsigned short); i++)
		h.data.push_back(*(((const char*)&v)+i));
}

void put(hasher &h, int v)
{
	h.data.reserve(h.data.size() + sizeof(int));
	for (int i = 0; i < (int)sizeof(int); i++)
		h.data.push_back(*(((const char*)&v)+i));
}

void put(hasher &h, unsigned int v)
{
	h.data.reserve(h.data.size() + sizeof(unsigned int));
	for (int i = 0; i < (int)sizeof(unsigned int); i++)
		h.data.push_back(*(((const char*)&v)+i));
}

void put(hasher &h, long v)
{
	h.data.reserve(h.data.size() + sizeof(long));
	for (int i = 0; i < (int)sizeof(long); i++)
		h.data.push_back(*(((const char*)&v)+i));
}

void put(hasher &h, unsigned long v)
{
	h.data.reserve(h.data.size() + sizeof(unsigned long));
	for (int i = 0; i < (int)sizeof(unsigned long); i++)
		h.data.push_back(*(((const char*)&v)+i));
}

void put(hasher &h, long long v)
{
	h.data.reserve(h.data.size() + sizeof(long long));
	for (int i = 0; i < (int)sizeof(long long); i++)
		h.data.push_back(*(((const char*)&v)+i));
}

void put(hasher &h, unsigned long long v)
{
	h.data.reserve(h.data.size() + sizeof(unsigned long long));
	for (int i = 0; i < (int)sizeof(unsigned long long); i++)
		h.data.push_back(*(((const char*)&v)+i));
}

void put(hasher &h, bool v)
{
	h.data.reserve(h.data.size() + sizeof(bool));
	for (int i = 0; i < (int)sizeof(bool); i++)
		h.data.push_back(*(((const char*)&v)+i));
}

void put(hasher &h, float v)
{
	h.data.reserve(h.data.size() + sizeof(float));
	for (int i = 0; i < (int)sizeof(float); i++)
		h.data.push_back(*(((const char*)&v)+i));
}

void put(hasher &h, double v)
{
	h.data.reserve(h.data.size() + sizeof(double));
	for (int i = 0; i < (int)sizeof(double); i++)
		h.data.push_back(*(((const char*)&v)+i));
}

void put(hasher &h, string v)
{
	h.data.reserve(h.data.size() + v.size());
	for (string::iterator i = v.begin(); i != v.end(); i++)
		h.data.push_back(*i);
}


