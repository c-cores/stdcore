/*
 * bits.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: nbingham
 */

#include "bits.h"

bits::bits()
{

}

bits::~bits()
{

}

// http://www.azillionmonkeys.com/qed/hash.html
uint32_t bits::hash()
{
	uint32_t len = size();
	const char* ptr = data();
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
	return hash;
}

bits &operator<<(bits &str, char v)
{
	str.push_back(v);
	return bits;
}

bits &operator<<(bits &str, unsigned char v)
{
	str.push_back(v);
	return bits;
}

bits &operator<<(bits &str, short v)
{
	str.reserve(str.size() + sizeof(short));
	memcpy(str.data + str.size(), &v, sizeof(short));
	str.alloc_back(sizeof(short));
	return bits;
}

bits &operator<<(bits &str, unsigned short v)
{
	str.reserve(str.size() + sizeof(unsigned short));
	memcpy(str.data + str.size(), &v, sizeof(unsigned short));
	str.alloc_back(sizeof(unsigned short));
	return bits;
}

bits &operator<<(bits &str, int v)
{
	str.reserve(str.size() + sizeof(int));
	memcpy(str.data + str.size(), &v, sizeof(int));
	str.alloc_back(sizeof(int));
	return bits;
}

bits &operator<<(bits &str, unsigned int v)
{
	str.reserve(str.size() + sizeof(unsigned int));
	memcpy(str.data + str.size(), &v, sizeof(unsigned int));
	str.alloc_back(sizeof(unsigned int));
	return bits;
}

bits &operator<<(bits &str, long v)
{
	str.reserve(str.size() + sizeof(long));
	memcpy(str.data + str.size(), &v, sizeof(long));
	str.alloc_back(sizeof(long));
	return bits;
}

bits &operator<<(bits &str, unsigned long v)
{
	str.reserve(str.size() + sizeof(unsigned long));
	memcpy(str.data + str.size(), &v, sizeof(unsigned long));
	str.alloc_back(sizeof(unsigned long));
	return bits;
}

bits &operator<<(bits &str, long long v)
{
	str.reserve(str.size() + sizeof(long long));
	memcpy(str.data + str.size(), &v, sizeof(long long));
	str.alloc_back(sizeof(long long));
	return bits;
}

bits &operator<<(bits &str, unsigned long long v)
{
	str.reserve(str.size() + sizeof(unsigned long long));
	memcpy(str.data + str.size(), &v, sizeof(unsigned long long));
	str.alloc_back(sizeof(unsigned long long));
	return bits;
}

bits &operator<<(bits &str, bool v)
{
	str.reserve(str.size() + sizeof(bool));
	memcpy(str.data + str.size(), &v, sizeof(bool));
	str.alloc_back(sizeof(bool));
	return bits;
}

bits &operator<<(bits &str, float v)
{
	str.reserve(str.size() + sizeof(float));
	memcpy(str.data + str.size(), &v, sizeof(float));
	str.alloc_back(sizeof(float));
	return bits;
}

bits &operator<<(bits &str, double v)
{
	str.reserve(str.size() + sizeof(double));
	memcpy(str.data + str.size(), &v, sizeof(double));
	str.alloc_back(sizeof(double));
	return bits;
}

bits &operator<<(bits &str, string v)
{
	str.reserve(str.size() + v.size());
	memcpy(str.data + str.size(), v.data, v.size());
	str.alloc_back(v.size());
	return bits;
}

bits &operator<<(bits &str, const char *v)
{
	int n = strlen(v);
	str.reserve(str.size() + n);
	memcpy(str.data + str.size(), v, n);
	str.alloc_back(n);
	return bits;
}

bits &operator<<(bits &str, char *v)
{
	int n = strlen(v);
	str.reserve(str.size() + n);
	memcpy(str.data + str.size(), v, n);
	str.alloc_back(n);
	return bits;
}



