/*
 * math.cpp
 *
 *  Created on: Sep 25, 2014
 *      Author: nbingham
 */

#include "math.h"

namespace core
{

unsigned int count_1bits(unsigned int x)
{
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x0000003F;
}

unsigned int count_0bits(unsigned int x)
{
	x = x - ((x >> 1) & 0x55555555);
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
	x = x + (x >> 8);
	x = x + (x >> 16);
    return 32 - (x & 0x0000003F);
}

int log2i(unsigned long long value)
{
  static const unsigned long long t[6] = {
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

}
