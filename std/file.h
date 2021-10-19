/*
 * file.h
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#pragma once

#include <stdint.h>
#include <std/array.h>

namespace core
{

struct file
{
	file();
	file(int desc);
	file(const file &copy);
	file(const char *filename, unsigned char mode = rw, unsigned char owner = rw, unsigned char group = r, unsigned char user = r);
	file(array<char> filename, unsigned char mode = rw, unsigned char owner = rw, unsigned char group = r, unsigned char user = r);
	~file();

	enum {
		r = 0x01, // read
		w = 0x02, // write
		x = 0x04, // execute
		rw = 0x03,
		rx = 0x05,
		wx = 0x06,
		rwx = 0x07,
		replace = 0x8, // replace with empty file
		exists = 0x10, // fail if file doesn't exist
		not_exists = 0x20 // fail if file exists
	};

	int desc;
	intptr_t index;

	operator bool() const;

	bool open(const char *filename, unsigned char mode = rw, unsigned char owner = rw, unsigned char group = r, unsigned char user = r);
	bool open(array<char>, unsigned char mode = rw, unsigned char owner = rw, unsigned char group = r, unsigned char user = r);
	bool close();

	intptr_t size();

	intptr_t set(intptr_t offset);
	intptr_t mov(intptr_t offset);

	intptr_t read(intptr_t length, char *str);
	intptr_t read(intptr_t length, array<char> &str);
	array<char> read(intptr_t length);

	intptr_t write(intptr_t length, const char *str);
	intptr_t write(const array<char> &str);

	intptr_t read_to(const char *delimiters, array<char> &str);
};

}

