/*
 * file.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include <std/file.h>

#include <unistd.h>
#include <fcntl.h>

namespace core
{

file::file()
{
	desc = -1;
}

file::file(int desc)
{
	this->desc = desc;
	index = -1;
}

file::file(const file &copy)
{
	desc = ::dup(copy.desc);
	index = copy.index;
}

file::file(const char *filename, unsigned char mode, unsigned char owner, unsigned char group, unsigned char user)
{
	desc = -1;
	open(filename, mode, owner, group, user);
}

file::file(array<char> filename, unsigned char mode, unsigned char owner, unsigned char group, unsigned char user)
{
	desc = -1;
	open(filename, mode, owner, group, user);
}

file::~file()
{
	close();
}

file::operator bool() const
{
	return desc >= 0;
}

bool file::open(const char *filename, unsigned char mode, unsigned char owner, unsigned char group, unsigned char user)
{
	if (desc >= 0)
		return false;

	int oflags = O_CREAT;
	int rights = 0;
	index = 0;

	if ((mode & rw) == rw)
		oflags |= O_RDWR;
	else if (mode & r)
		oflags |= O_RDONLY;
	else if (mode & w)
		oflags |= O_WRONLY;

	if (mode & replace)
		oflags |= O_TRUNC;

	if (mode & exists)
		oflags &= ~O_CREAT;
	else if (mode & not_exists)
		oflags |= O_EXCL;
	
	if (owner & r)
		rights |= S_IRUSR;
	if (owner & w)
		rights |= S_IWUSR;
	if (owner & x)
		rights |= S_IXUSR;

	if (group & r)
		rights |= S_IRGRP;
	if (group & w)
		rights |= S_IWGRP;
	if (group & x)
		rights |= S_IXGRP;

	if (user & r)
		rights |= S_IROTH;
	if (user & w)
		rights |= S_IWOTH;
	if (user & x)
		rights |= S_IXOTH;

	desc = ::open(filename, oflags, rights);
	return desc >= 0;
}

bool file::open(array<char> filename, unsigned char mode, unsigned char owner, unsigned char group, unsigned char user)
{
	if (filename[-1] != '\0')
		filename.push_back('\0');
	return open(filename.data, mode, owner, group, user);
}

bool file::close()
{
	if (desc >= 3)
		return ::close(desc) == 0;
	else
		return true;
}

intptr_t file::size()
{
	intptr_t result = ::lseek(desc, 0, SEEK_END);
	::lseek(desc, index, SEEK_SET);
	return result;
}

intptr_t file::set(intptr_t offset)
{
	if (offset >= 0)
		index = ::lseek(desc, offset, SEEK_SET);
	else
		index = ::lseek(desc, offset, SEEK_END);
	return index;
}

intptr_t file::mov(intptr_t offset)
{
	index = ::lseek(desc, offset, SEEK_CUR);
	return index;
}

intptr_t file::read(intptr_t length, char *str)
{
	intptr_t result = ::read(desc, str, length);
	index += result;
	return result;
}

intptr_t file::read(intptr_t length, array<char> &str)
{
	str.reserve(length);
	str.count = ::read(desc, str.data, length);
	index += str.count;
	return str.count;
}

array<char> file::read(intptr_t length)
{
	array<char> result;
	result.reserve(length);
	result.count = ::read(desc, result.data, length);
	index += result.count;
	return result;
}

intptr_t file::write(intptr_t length, const char *str)
{
	intptr_t result = ::write(desc, str, length);
	index += result;
	return result;
}

intptr_t file::write(const array<char> &str)
{
	intptr_t result = ::write(desc, str.data, str.count);
	index += result;
	return result;
}

}
