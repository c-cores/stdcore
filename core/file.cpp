/*
 * file.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include "file.h"
#include <stdarg.h>

namespace core
{

file cout(stdout);
file cin(stdin);
file cerr(stderr);
string endl("\n");

file::file()
{
	ptr = NULL;
}

file::file(FILE *f)
{
	ptr = f;
}

file::file(string filename, string options)
{
	ptr = fopen(filename.c_str(), options.c_str());
}

file::~file()
{
	fclose(ptr);
	ptr = NULL;
}

int file::size()
{
	int curpos = ftell(ptr);
	fseek(ptr, 0, SEEK_END);
	int result = ftell(ptr);
	fseek(ptr, curpos, SEEK_SET);
	return result;
}

bool file::eof()
{
	return (bool)feof(ptr);
}

bool file::is_open()
{
	return (ptr != NULL);
}

bool file::open(string filename, string options)
{
	ptr = fopen(filename.c_str(), options.c_str());
	return (ptr != NULL);
}

void file::close()
{
	fclose(ptr);
	ptr = NULL;
}

char file::get()
{
	return fgetc(ptr);
}

string file::read(int n)
{
	string result(n, '\0');
	result.resize(fread(result.c_str(), 1, n, ptr));
	return result;
}

void file::read(char *s, int n)
{
	fread(s, 1, n, ptr);
}

void file::read(unsigned char *s, int n)
{
	fread(s, 1, n, ptr);
}

string file::read_word()
{
	string result(16);
	char c;
	while ((c = fgetc(ptr)) != ' ' && c != '\t' && c != '\n' && c != '\0')
		result.push_back(c);
	return result;
}

string file::read_line()
{
	string result(256);
	fgets(result.c_str(), 256, ptr);
	return result;
}

string file::read_file()
{
	fseek(ptr, 0, SEEK_END);
	int s = ftell(ptr);
	fseek(ptr, 0, SEEK_SET);
	string result(s, '\0');
	result.resize(fread(result.c_str(), 1, s, ptr));
	return result;
}

void file::write(string str)
{
	fputs(str.c_str(), ptr);
}

void file::writef(string format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(ptr, format.c_str(), args);
	va_end(args);
}

void file::insert(string str)
{

}

void file::moveto(int location)
{
	if (location > 0)
		fseek(ptr, location, SEEK_SET);
	else if (location < 0)
		fseek(ptr, location, SEEK_END);
}


void file::move(int distance)
{
	fseek(ptr, distance, SEEK_CUR);
}


int file::where()
{
	return ftell(ptr);
}

void file::flush()
{
	fflush(ptr);
}

file &file::operator=(file f)
{
	ptr = f.ptr;
	return *this;
}

file::operator string()
{
	return read_file();
}

file &operator<<(file &fout, const char *str)
{
	fputs(str, fout.ptr);
	return fout;
}

file &operator<<(file &fout, char *str)
{
	fputs(str, fout.ptr);
	return fout;
}

file &operator<<(file &fout, string str)
{
	fputs(str.c_str(), fout.ptr);
	return fout;
}

file &operator<<(file &fout, char i)
{
	fputc(i, fout.ptr);
	return fout;
}

file &operator<<(file &fout, unsigned char i)
{
	fputc(i, fout.ptr);
	return fout;
}

file &operator<<(file &fout, bool i)
{
	fputs(i ? "true" : "false", fout.ptr);
	return fout;
}

file &operator<<(file &fout, int i)
{
	fprintf(fout.ptr, "%d", i);
	return fout;
}

file &operator<<(file &fout, short i)
{
	fprintf(fout.ptr, "%hd", i);
	return fout;
}

file &operator<<(file &fout, long i)
{
	fprintf(fout.ptr, "%ld", i);
	return fout;
}

file &operator<<(file &fout, unsigned int i)
{
	fprintf(fout.ptr, "%u", i);
	return fout;
}

file &operator<<(file &fout, unsigned short i)
{
	fprintf(fout.ptr, "%hu", i);
	return fout;
}

file &operator<<(file &fout, unsigned long i)
{
	fprintf(fout.ptr, "%lu", i);
	return fout;
}

file &operator<<(file &fout, float i)
{
	fprintf(fout.ptr, "%f", i);
	return fout;
}

file &operator<<(file &fout, double i)
{
	fprintf(fout.ptr, "%f", i);
	return fout;
}

file &operator<<(file &fout, file::hex<const char *> str)
{
	while (*str.value != '\0')
		fprintf(fout.ptr, "%02X ", *str.value++);
	return fout;
}

file &operator<<(file &fout, file::hex<char *> str)
{
	while (*str.value != '\0')
		fprintf(fout.ptr, "%02X ", *str.value++);
	return fout;
}

file &operator<<(file &fout, file::hex<string> str)
{
	for (int i = 0; i < str.value.size(); i++)
		fprintf(fout.ptr, "%02X ", str.value[i]);
	return fout;
}

file &operator<<(file &fout, file::hex<char> i)
{
	fprintf(fout.ptr, "%02X", i.value);
	return fout;
}

file &operator<<(file &fout, file::hex<unsigned char> i)
{
	fprintf(fout.ptr, "%02X", i.value);
	return fout;
}

file &operator<<(file &fout, file::hex<bool> i)
{
	fprintf(fout.ptr, "%01X", i.value);
	return fout;
}

file &operator<<(file &fout, file::hex<int> i)
{
	fprintf(fout.ptr, "%08X", i.value);
	return fout;
}

file &operator<<(file &fout, file::hex<short> i)
{
	fprintf(fout.ptr, "%04hX", i.value);
	return fout;
}

file &operator<<(file &fout, file::hex<long> i)
{
	fprintf(fout.ptr, "%08lX", i.value);
	return fout;
}

file &operator<<(file &fout, file::hex<unsigned int> i)
{
	fprintf(fout.ptr, "%08X", i.value);
	return fout;
}

file &operator<<(file &fout, file::hex<unsigned short> i)
{
	fprintf(fout.ptr, "%04hX", i.value);
	return fout;
}

file &operator<<(file &fout, file::hex<unsigned long> i)
{
	fprintf(fout.ptr, "%08lX", i.value);
	return fout;
}

file &operator<<(file &fout, file::hex<float> i)
{
	fprintf(fout.ptr, "%08X", *(int*)(&i.value));
	return fout;
}

file &operator<<(file &fout, file::hex<double> i)
{
	fprintf(fout.ptr, "%08X%08X", *(int*)((&i.value) + 1), *(int*)(&i.value));
	return fout;
}

}
