/*
 * ascii_ostream.h
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include "string.h"

#pragma once

namespace core
{

struct ascii_ostream
{
	ascii_ostream()
	{
		ptr = NULL;
		msg = NULL;
		end = "\n";
		debug = false;
		count = 0;
	}

	ascii_ostream(const char *filename, const char *end = "\n", const char *msg = NULL, bool debug = false)
	{
		ptr = fopen(filename, "w");
		this->msg = msg;
		this->debug = debug;
		this->end = end;
		count = 0;
	}

	ascii_ostream(FILE *ptr, const char *end = "\n", const char *msg = NULL, bool debug = false)
	{
		this->ptr = ptr;
		this->msg = msg;
		this->debug = debug;
		this->end = end;
		count = 0;
	}

	~ascii_ostream()
	{
		if (ptr != NULL)
			fclose(ptr);
		ptr = NULL;
		count = 0;
	}

	FILE *ptr;
	string store;
	const char *msg;
	bool debug;
	int count;
	const char *end;
};

struct stream_flush
{
	stream_flush(const char *path, int line)
	{
		this->path = path;
		this->line = line;
	}

	~stream_flush() {}

	const char *path;
	int line;
};

#define endl stream_flush(__FILE__, __LINE__)

template <typename type>
inline ascii_ostream &operator<<(ascii_ostream &s1, type s2)
{
	s1.store << s2;
	return s1;
}

template <>
ascii_ostream &operator<<(ascii_ostream &s1, stream_flush s2);

extern ascii_ostream cout;
extern ascii_ostream cprog;
extern ascii_ostream cnote;
extern ascii_ostream cwarn;
extern ascii_ostream cerr;
extern ascii_ostream cfate;

}

