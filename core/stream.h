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

}

