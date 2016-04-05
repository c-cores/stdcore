/*
 * file.h
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "list.h"
#include "map.h"
#include "pair.h"
#include "string.h"
#include "base.h"

#ifndef file_h
#define file_h

namespace core
{

struct file
{
	file();
	file(FILE *f);
	file(string filename, string options);
	~file();

	FILE *ptr;

	int size();
	bool eof();
	bool is_open();

	bool open(string filename, string options);
	void close();
	char get();
	string read(int n);
	int read(char *s, int n);
	int read(unsigned char *s, int n);
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

template <class value_type>
hex<value_type> to_hex(value_type v)
{
	return hex<value_type>(v);
}

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

file &operator<<(file &fout, hex<const char *> str);
file &operator<<(file &fout, hex<char *> str);
file &operator<<(file &fout, hex<string> str);
file &operator<<(file &fout, hex<char> i);
file &operator<<(file &fout, hex<unsigned char> i);
file &operator<<(file &fout, hex<bool> i);
file &operator<<(file &fout, hex<int> i);
file &operator<<(file &fout, hex<short> i);
file &operator<<(file &fout, hex<long> i);
file &operator<<(file &fout, hex<unsigned int> i);
file &operator<<(file &fout, hex<unsigned short> i);
file &operator<<(file &fout, hex<unsigned long> i);
file &operator<<(file &fout, hex<float> i);
file &operator<<(file &fout, hex<double> i);

template <class container>
file &operator<<(file &f, const container &c)
{
	f << "[";
	for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
	{
		if (i != c.begin())
			f << " ";
		f << *i;
	}
	f << "]";
	return f;
}

template <class key_type, class value_type>
file &operator<<(file &f, const implier<key_type, value_type> &c)
{
	f << c.key << " -> " << c.value;
	return f;
}

template <class type1, class type2>
file &operator<<(file &f, const pair<type1, type2> &p)
{
	f << "(" << p.first << " " << p.second << ")";
	return f;
}

template <class container>
file &operator<<(file &f, const hex<container> &c)
{
	f << "[";
	for (typename container::const_iterator i = c.value.begin(); i != c.value.end(); i++)
	{
		if (i != c.value.begin())
			f << " ";
		f << to_hex(*i);
	}
	f << "}";
	return f;
}

template <class key_type, class value_type>
file &operator<<(file &f, const hex<implier<key_type, value_type> > &c)
{
	f << to_hex(c.key) << " -> " << to_hex(c.value);
	return f;
}

template <class type1, class type2>
file &operator<<(file &f, const hex<pair<type1, type2> > &p)
{
	f << "(" << to_hex(p.first) << ", " << to_hex(p.second) << ")";
	return f;
}

extern file cout;
extern file cin;
extern file cerr;
extern string endl;

}

#endif
