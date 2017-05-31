/*
 * stream.h
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#pragma once

namespace core
{

struct stream_flush
{
	stream_flush(const char *txt, const char *path, int line)
	{
		this->txt = txt;
		this->path = path;
		this->line = line;
	}

	~stream_flush() {}

	const char *txt;
	const char *path;
	int line;
};

#define endl stream_flush("\n", __FILE__, __LINE__)

template <typename store_type>
struct ostream
{
	ostream()
	{
		file = NULL;
	}

	ostream(const char *filename)
	{
		open(filename);
	}

	ostream(FILE *ptr)
	{
		file = ptr;
	}

	~ostream()
	{
		close();
	}

	FILE *file;
	store_type store;

	bool open(const char *filename)
	{
		if (file == NULL)
		{
			file = fopen(filename, "w");
			return (file != NULL);
		}
		else
		{
#ifdef DEBUG
			printf("error: failed to open \"%s\", stream already open.\n", filename);
#endif
			return false;
		}
	}

	void close()
	{
		flush();
		if (file != NULL)
			fclose(file);
		file = NULL;
	}

	void flush()
	{
		if (file != NULL)
		{
			if (store.size() > 0)
				fwrite(store.data, 1, store.size(), file);

			fflush(file);
		}
		store.clear();
	}
};

template <typename store_type, typename type>
ostream<store_type> &operator<<(ostream<store_type> &s1, type s2)
{
	s1.store << s2;
	return s1;
}

template <typename store_type>
ostream<store_type> &operator<<(ostream<store_type> &s1, stream_flush s2)
{
	if (s2.txt != NULL)
		s1.store << s2.txt;
	s1.flush();
	return s1;
}

}

