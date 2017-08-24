/*
 * ascii_stream.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include <std/ascii_stream.h>

namespace core
{

void ascii_stream::open(const char *filename)
{
	ptr = fopen(filename, "w");
}

void ascii_stream::close()
{
	flush(__FILE__, __LINE__);
	if (ptr != NULL)
		fclose(ptr);
	ptr = NULL;
	count = 0;
}

void ascii_stream::flush(const char *path, int line)
{
	if (ptr != NULL && store.size() > 0)
	{
		if (debug)
			fprintf(ptr, "%s:%d: ", path, line);
		if (msg != NULL && strlen(msg) > 0)
			fprintf(ptr, "%s: ", msg);

		fwrite(store.data, 1, store.size(), ptr);
		fputs(end, ptr);
	}
	else
		fputs(end, ptr);

	if (ptr != NULL)
		fflush(ptr);
	store.clear();
	count++;
}

template <>
ascii_stream &operator<<(ascii_stream &s1, stream_flush s2)
{
	s1.flush(s2.path, s2.line);
	return s1;
}

ascii_stream cout(stdout, "\n", NULL, false);
ascii_stream cprog(stdout, "\r", NULL, false);
ascii_stream cnote(stdout, "\n", "note", false);
ascii_stream cwarn(stderr, "\n", "warning", false);
ascii_stream cerr(stderr, "\n", "error", false);
ascii_stream cfate(stderr, "\n", "fatal", true);

}
