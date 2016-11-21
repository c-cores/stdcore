/*
 * file.h
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include <std/search.h>
#include <std/array.h>

#include <stdlib.h>
#include <stdio.h>

#ifndef file_h
#define file_h

namespace core
{

struct file
{
	file();
	file(const char *filename, const char *options);
	file(FILE *ptr);
	~file();

	FILE *ptr;

	operator bool();
	int size();
	bool open(const char *filename, const char *options);
	void close();
	void flush();

	int read(char *str, int n);
	int read(char *str, int n, const char *delimiter);
	int read(char *str, int n, const array<char> &delimiter);
	array<char> read(int n = -1);
	array<char> read(const char *delimiter);
	array<char> read(const array<char> &delimiter);
	char get();

	void write(const char *str);
	void write(const char *str, int n);
	void write(const array<char> &data);

	void moveto(int location);
	void move(int distance);
	int where();
};

inline file::file()
{
	ptr = NULL;
}

inline file::file(const char *filename, const char *options)
{
	ptr = fopen(filename, options);
}

inline file::file(FILE *ptr)
{
	this->ptr = ptr;
}

inline file::~file()
{
	if (ptr != NULL)
		fclose(ptr);
	ptr = NULL;
}

inline file::operator bool()
{
	return ptr != NULL && !feof(ptr);
}

inline bool file::open(const char *filename, const char *options)
{
	ptr = fopen(filename, options);
	return (ptr != NULL);
}

inline void file::close()
{
	fclose(ptr);
}

inline void file::flush()
{
	fflush(ptr);
}

inline int file::read(char *str, int n)
{
	int result = (int)fread(str, 1, n-1, ptr);
	str[result] = '\0';
	return result;
}

inline char file::get()
{
	return fgetc(ptr);
}

inline void file::write(const char *str)
{
	fputs(str, ptr);
}

inline void file::write(const char *str, int n)
{
	fwrite(str, 1, n, ptr);
}

inline void file::write(const array<char> &data)
{
	fwrite(data.data, 1, data.size(), ptr);
}

inline void file::moveto(int location)
{
	if (location > 0)
		fseek(ptr, location, SEEK_SET);
	else if (location < 0)
		fseek(ptr, location, SEEK_END);
}

inline void file::move(int distance)
{
	fseek(ptr, distance, SEEK_CUR);
}

inline int file::where()
{
	return ftell(ptr);
}

}

#endif
