/*
 * file.h
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "string.h"

#ifndef file_h
#define file_h

namespace core
{

struct file
{
private:
	FILE *ptr;

public:
	file();
	file(FILE *f);
	file(string filename, string options);
	~file();

	int size();
	bool eof();
	bool is_open();

	bool open(string filename, string options);
	void close();
	char get();
	string read(int n);
	void read(char *s, int n);
	void read(unsigned char *s, int n);
	string read_word();
	string read_line();
	string read_file();
	void write(string str);
	void writef(string format, ...);
	void insert(string str);
	void moveto(int location);
	void move(int distance);
	int where();
	void flush();

	file &operator=(file f);
	operator string();
};

file &operator<<(file &fout, const char *str);
file &operator<<(file &fout, char *str);
file &operator<<(file &fout, string str);
file &operator<<(file &fout, char i);
file &operator<<(file &fout, unsigned char i);
file &operator<<(file &fout, bool i);
file &operator<<(file &fout, int i);
file &operator<<(file &fout, short i);
file &operator<<(file &fout, long i);
file &operator<<(file &fout, unsigned int i);
file &operator<<(file &fout, unsigned short i);
file &operator<<(file &fout, unsigned long i);
file &operator<<(file &fout, float i);
file &operator<<(file &fout, double i);

template <class container>
file &operator<<(file &f, const container &c)
{
	boundary<typename container::const_iterator> b = c.bound();
	f << "{";
	for (typename container::const_iterator i = b.left; i != b.right+1; i++)
	{
		if (i != b.left)
			f << ", ";
		f << *i;
	}
	f << "}";
	return f;
}

extern file cout;
extern file cin;
extern file cerr;
extern string endl;

}

#endif
