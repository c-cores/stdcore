/*
 * stream.h
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#pragma once

#include <std/file.h>

namespace core
{

struct flush_t
{
	flush_t(const char *end = NULL);
	~flush_t();
	
	const char *end;
};

template <typename stream_type>
struct stream : file
{
	stream()
	{
	}

	stream(int desc) : file(desc)
	{
	}

	stream(const char *name, unsigned char mode = file::rw, unsigned char owner = file::rw, unsigned char group = file::r, unsigned char user = file::r) : file(name, mode, owner, group, user)
	{
	}

	stream(array<char> name, unsigned char mode = file::rw, unsigned char owner = file::rw, unsigned char group = file::r, unsigned char user = file::r) : file(name, mode, owner, group, user)
	{
	}

	~stream()
	{
	}

	stream_type cache;
};

template <typename stream_type, typename value_type>
stream<stream_type> &operator<<(stream<stream_type> &str, value_type value)
{
	str.cache << value;
	return str;
}

template <typename stream_type>
stream<stream_type> &operator<<(stream<stream_type> &str, flush_t end)
{
	if (end.end != NULL)
		str << end.end;
	str.write(str.cache);
	str.cache.clear();
	return str;
}

template <typename stream_type, typename value_type>
stream<stream_type> &operator>>(stream<stream_type> &str, value_type value)
{
	str.cache >> value;
	return str;
}

}

