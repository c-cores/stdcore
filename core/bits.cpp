/*
 * bits.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: nbingham
 */

#include <core/bits.h>

namespace core
{

bits::bits()
{

}

bits::~bits()
{

}

bits &operator<<(bits &str, char v)
{
	str.push_back((unsigned char)v);
	return str;
}

bits &operator<<(bits &str, unsigned char v)
{
	str.push_back(v);
	return str;
}

bits &operator<<(bits &str, short v)
{
	str.reserve(str.size() + sizeof(short));
	memcpy(str.data + str.size(), &v, sizeof(short));
	str.alloc_back(sizeof(short));
	return str;
}

bits &operator<<(bits &str, unsigned short v)
{
	str.reserve(str.size() + sizeof(unsigned short));
	memcpy(str.data + str.size(), &v, sizeof(unsigned short));
	str.alloc_back(sizeof(unsigned short));
	return str;
}

bits &operator<<(bits &str, int v)
{
	str.reserve(str.size() + sizeof(int));
	memcpy(str.data + str.size(), &v, sizeof(int));
	str.alloc_back(sizeof(int));
	return str;
}

bits &operator<<(bits &str, unsigned int v)
{
	str.reserve(str.size() + sizeof(unsigned int));
	memcpy(str.data + str.size(), &v, sizeof(unsigned int));
	str.alloc_back(sizeof(unsigned int));
	return str;
}

bits &operator<<(bits &str, long v)
{
	str.reserve(str.size() + sizeof(long));
	memcpy(str.data + str.size(), &v, sizeof(long));
	str.alloc_back(sizeof(long));
	return str;
}

bits &operator<<(bits &str, unsigned long v)
{
	str.reserve(str.size() + sizeof(unsigned long));
	memcpy(str.data + str.size(), &v, sizeof(unsigned long));
	str.alloc_back(sizeof(unsigned long));
	return str;
}

bits &operator<<(bits &str, long long v)
{
	str.reserve(str.size() + sizeof(long long));
	memcpy(str.data + str.size(), &v, sizeof(long long));
	str.alloc_back(sizeof(long long));
	return str;
}

bits &operator<<(bits &str, unsigned long long v)
{
	str.reserve(str.size() + sizeof(unsigned long long));
	memcpy(str.data + str.size(), &v, sizeof(unsigned long long));
	str.alloc_back(sizeof(unsigned long long));
	return str;
}

bits &operator<<(bits &str, bool v)
{
	str.reserve(str.size() + sizeof(bool));
	memcpy(str.data + str.size(), &v, sizeof(bool));
	str.alloc_back(sizeof(bool));
	return str;
}

bits &operator<<(bits &str, float v)
{
	str.reserve(str.size() + sizeof(float));
	memcpy(str.data + str.size(), &v, sizeof(float));
	str.alloc_back(sizeof(float));
	return str;
}

bits &operator<<(bits &str, double v)
{
	str.reserve(str.size() + sizeof(double));
	memcpy(str.data + str.size(), &v, sizeof(double));
	str.alloc_back(sizeof(double));
	return str;
}

bits &operator<<(bits &str, const char *v)
{
	int n = strlen(v);
	str.reserve(str.size() + n);
	memcpy(str.data + str.size(), v, n);
	str.alloc_back(n);
	return str;
}

bits &operator<<(bits &str, char *v)
{
	int n = strlen(v);
	str.reserve(str.size() + n);
	memcpy(str.data + str.size(), v, n);
	str.alloc_back(n);
	return str;
}

}
