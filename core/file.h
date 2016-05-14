/*
 * file.h
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include <stdlib.h>
#include <stdio.h>
#include "search.h"
#include "array.h"

#ifndef file_h
#define file_h

namespace core
{

struct file
{
	file();
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

	void write(char *str);
	void write(char *str, int n);
	void write(const array<char> &data);

	void moveto(int location);
	void move(int distance);
	int where();
};

}

#endif
