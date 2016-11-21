/*
 * file.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include <std/file.h>
#include <std/string.h>

#include <stdarg.h>
#include <stdint.h>

namespace core
{

int file::size()
{
	int curpos = ftell(ptr);
	fseek(ptr, 0, SEEK_END);
	int result = ftell(ptr);
	fseek(ptr, curpos, SEEK_SET);
	return result;
}

int file::read(char *str, int n, const char *delimiter)
{
	char *result;
	char *end = str+n-1;
	for (result = str; !feof(ptr) && result < end; result++)
	{
		*result = fgetc(ptr);
		for (const char *i = delimiter; *i != '\0'; i++)
			if (*i == *result)
			{
				*++result = '\0';
				return result-str;
			}
	}
	*result = '\0';
	return result-str;
}

int file::read(char *str, int n, const array<char> &delimiter)
{
	char *result;
	char *end = str+n-1;
	for (result = str; !feof(ptr) && result < end; result++)
	{
		*result = fgetc(ptr);
		for (array<char>::const_iterator i = delimiter.begin(); i; i++)
			if (*i == *result)
			{
				*++result = '\0';
				return result-str;
			}
	}
	*result = '\0';
	return result-str;
}

array<char> file::read(int n)
{
	array<char> result;
	if (n < 0)
		n = size();
	result.reserve(n);
	result.alloc_back_unsafe((int)fread(result.data, 1, n, ptr));
	return result;
}

array<char> file::read(const char *delimiter)
{
	array<char> result;
	result.reserve(256);
	while (!feof(ptr))
	{
		result.push_back(fgetc(ptr));
		for (const char *i = delimiter; *i != '\0'; i++)
			if (*i == result.back())
				return result;
	}
	return result;
}

array<char> file::read(const array<char> &delimiter)
{
	array<char> result;
	result.reserve(256);
	while (!feof(ptr))
	{
		result.push_back(fgetc(ptr));
		for (array<char>::const_iterator i = delimiter.begin(); i; i++)
			if (*i == result.back())
				return result;
	}
	return result;
}

}
