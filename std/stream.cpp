/*
 * stream.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include <std/stream.h>

namespace core
{

flush_t::flush_t(const char *end)
{
	this->end = end;
}

flush_t::~flush_t()
{
}

}
