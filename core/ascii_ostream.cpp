/*
 * ascii_ostream.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include "ascii_ostream.h"

namespace core
{

template <>
ascii_ostream &operator<<(ascii_ostream &s1, stream_flush s2)
{
	if (s1.debug)
		fprintf(s1.ptr, "%s:%d: ", s2.path, s2.line);
	if (s1.msg != NULL)
		fprintf(s1.ptr, "%s: ", s1.msg);
	fwrite(s1.store.data, 1, s1.store.size(), s1.ptr);
	fputs(s1.end, s1.ptr);
	fflush(s1.ptr);
	s1.store.clear();
	s1.count++;
	return s1;
}

ascii_ostream cout(stdout, "\n", NULL, false);
ascii_ostream cprog(stdout, "\r", NULL, false);
ascii_ostream cnote(stdout, "\n", "note", false);
ascii_ostream cwarn(stderr, "\n", "warning", false);
ascii_ostream cerr(stderr, "\n", "error", false);
ascii_ostream cfate(stderr, "\n", "fatal", true);

}
