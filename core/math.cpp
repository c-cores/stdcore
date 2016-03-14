/*
 * math.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: nbingham
 */

#include "math.h"

namespace core
{

uint32_t count_1bits(uint32_t x)
{
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x0000003F;
}

uint32_t count_0bits(uint32_t x)
{
	x = x - ((x >> 1) & 0x55555555);
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
	x = x + (x >> 8);
	x = x + (x >> 16);
    return 32 - (x & 0x0000003F);
}

int log2i(uint64_t value)
{
  static const uint64_t t[6] = {
    0xFFFFFFFF00000000ull,
    0x00000000FFFF0000ull,
    0x000000000000FF00ull,
    0x00000000000000F0ull,
    0x000000000000000Cull,
    0x0000000000000002ull
  };

  int y = (((value & (value - 1)) == 0) ? 0 : 1);
  int j = 32;
  int i;

  for (i = 0; i < 6; i++) {
    int k = (((value & t[i]) == 0) ? 0 : j);
    y += k;
    value >>= k;
    j >>= 1;
  }

  return y;
}

bool is_even(int i)
{
	return ((i & 0xFFFFFFFE) == (unsigned int)i);
}

bool is_odd(int i)
{
	return ((i & 0xFFFFFFFE) != (unsigned int)i);
}

uint32_t hash(const char *ptr, int len)
{
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

}
