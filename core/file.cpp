/*
 * file.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include "file.h"
#include "string.h"
#include <stdarg.h>
#include <stdint.h>

namespace core
{

file::file()
{
	ptr = NULL;
}

file::file(FILE *ptr)
{
	this->ptr = ptr;
}

file::~file()
{
	if (ptr != NULL)
		fclose(ptr);
	ptr = NULL;
}

file::operator bool()
{
	return !feof(ptr);
}

int file::size()
{
	int curpos = ftell(ptr);
	fseek(ptr, 0, SEEK_END);
	int result = ftell(ptr);
	fseek(ptr, curpos, SEEK_SET);
	return result;
}

bool file::open(const char *filename, const char *options)
{
	ptr = fopen(filename, options);
	return (ptr != NULL);
}

void file::close()
{
	fclose(ptr);
}

void file::flush()
{
	fflush(ptr);
}

int file::read(char *str, int n)
{
	int result = (int)fread(str, 1, n-1, ptr);
	str[result] = '\0';
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

void file::write(char *str)
{
	fputs(str, ptr);
}

void file::write(char *str, int n)
{
	fwrite(str, 1, n, ptr);
}

void file::write(const array<char> &data)
{
	fwrite(data.data, 1, data.size(), ptr);
}

void file::moveto(int location)
{
	if (location > 0)
		fseek(ptr, location, SEEK_SET);
	else if (location < 0)
		fseek(ptr, location, SEEK_END);
}

void file::move(int distance)
{
	fseek(ptr, distance, SEEK_CUR);
}

int file::where()
{
	return ftell(ptr);
}

}
