/*
 * math.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: nbingham
 */

#include <core/math.h>

namespace core
{

uint32_t count_ones(uint32_t x)
{
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x0000003F;
}

uint32_t count_zeros(uint32_t x)
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

/**
 * copied from wikipedia
 * https://en.wikipedia.org/wiki/MurmurHash
 *
 * under the creative commons license
 * http://creativecommons.org/licenses/by-sa/3.0/
 */
#define ROT32(x, y) ((x << y) | (x >> (32 - y))) // avoid effort
uint32_t murmur3_32(const char *key, int len, uint32_t seed) {
	static const uint32_t c1 = 0xcc9e2d51;
	static const uint32_t c2 = 0x1b873593;
	static const uint32_t r1 = 15;
	static const uint32_t r2 = 13;
	static const uint32_t m = 5;
	static const uint32_t n = 0xe6546b64;

	uint32_t hash = seed;

	const int nblocks = len / 4;
	const uint32_t *blocks = (const uint32_t *) key;
	int i;
	uint32_t k;
	for (i = 0; i < nblocks; i++) {
		k = blocks[i];
		k *= c1;
		k = ROT32(k, r1);
		k *= c2;

		hash ^= k;
		hash = ROT32(hash, r2) * m + n;
	}

	const uint8_t *tail = (const uint8_t *) (key + nblocks * 4);
	uint32_t k1 = 0;

	switch (len & 3) {
	case 3:
		k1 ^= tail[2] << 16;
	case 2:
		k1 ^= tail[1] << 8;
	case 1:
		k1 ^= tail[0];

		k1 *= c1;
		k1 = ROT32(k1, r1);
		k1 *= c2;
		hash ^= k1;
	}

	hash ^= len;
	hash ^= (hash >> 16);
	hash *= 0x85ebca6b;
	hash ^= (hash >> 13);
	hash *= 0xc2b2ae35;
	hash ^= (hash >> 16);

	return hash;
}

/* copied from azillionmonkeys
 * http://www.azillionmonkeys.com/qed/hash.html
 *
 * under the lgpl 2.1 license
 * http://www.gnu.org/licenses/lgpl-2.1.txt
 */
uint32_t superfasthash(const char *key, int len, uint32_t seed)
{
	uint32_t hash = seed, tmp;
	int rem;

	if (len <= 0 || key == NULL)
		return 0;

	rem = len & 3;
	len >>= 2;

	/* Main loop */
	for (;len > 0; len--)
	{
		hash  += (*((const uint16_t *) (key)));
		tmp    = ((*((const uint16_t *) (key+2))) << 11) ^ hash;
		hash   = (hash << 16) ^ tmp;
		key  += 2*sizeof (uint16_t);
		hash  += hash >> 11;
	}

	/* Handle end cases */
	switch (rem)
	{
		case 3: hash += (*((const uint16_t *) (key)));
				hash ^= hash << 16;
				hash ^= ((signed char)key[sizeof (uint16_t)]) << 18;
				hash += hash >> 11;
				break;
		case 2: hash += (*((const uint16_t *) (key)));
				hash ^= hash << 11;
				hash += hash >> 17;
				break;
		case 1: hash += (signed char)*key;
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
