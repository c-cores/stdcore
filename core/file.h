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

#ifndef file_h
#define file_h

namespace core
{

struct file
{
	template <class value_type>
	struct hex
	{
		hex(value_type value){ this->value = value; }
		~hex(){}

		value_type value;
	};

	template <class value_type>
	struct hex<array<value_type> >
	{
		hex(const array<value_type> &value){ this->value = &value; }
		~hex(){}

		const array<value_type> *value;
	};

	template <class value_type>
	struct hex<list<value_type> >
	{
		hex(const list<value_type> &value){ this->value = &value; }
		~hex(){}

		const list<value_type> *value;
	};

	template <class key_value, class value_type>
	struct hex<map<key_value, value_type> >
	{
		hex(const map<key_value, value_type> &value){ this->value = &value; }
		~hex(){}

		const map<key_value, value_type> *value;
	};

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
file::hex<value_type> to_hex(value_type v)
{
	return file::hex<value_type>(v);
}

template <class value_type>
file::hex<array<value_type> > to_hex(array<value_type> &v)
{
	return file::hex<array<value_type> >(v);
}

template <class value_type>
file::hex<list<value_type> > to_hex(list<value_type> &v)
{
	return file::hex<list<value_type> >(v);
}

template <class key_value, class value_type>
file::hex<map<key_value, value_type> > to_hex(map<key_value, value_type> &v)
{
	return file::hex<map<key_value, value_type> >(v);
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

file &operator<<(file &fout, file::hex<const char *> str);
file &operator<<(file &fout, file::hex<char *> str);
file &operator<<(file &fout, file::hex<string> str);
file &operator<<(file &fout, file::hex<char> i);
file &operator<<(file &fout, file::hex<unsigned char> i);
file &operator<<(file &fout, file::hex<bool> i);
file &operator<<(file &fout, file::hex<int> i);
file &operator<<(file &fout, file::hex<short> i);
file &operator<<(file &fout, file::hex<long> i);
file &operator<<(file &fout, file::hex<unsigned int> i);
file &operator<<(file &fout, file::hex<unsigned short> i);
file &operator<<(file &fout, file::hex<unsigned long> i);
file &operator<<(file &fout, file::hex<float> i);
file &operator<<(file &fout, file::hex<double> i);

template <class value_type>
file &operator<<(file &f, const array<value_type> &c)
{
	f << "{";
	for (typename array<value_type>::const_iterator i = c.begin(); i != c.end(); i++)
	{
		if (i != c.begin())
			f << ", ";
		f << *i;
	}
	f << "}";
	return f;
}

template <class value_type>
file &operator<<(file &f, const list<value_type> &c)
{
	f << "{";
	for (typename list<value_type>::const_iterator i = c.begin(); i != c.end(); i++)
	{
		if (i != c.begin())
			f << ", ";
		f << *i;
	}
	f << "}";
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
	f << "(" << p.first << ", " << p.second << ")";
	return f;
}

template <class value_type>
file &operator<<(file &f, const file::hex<array<value_type> > &c)
{
	f << "{";
	for (typename array<value_type>::const_iterator i = c.value->begin(); i != c.value->end(); i++)
	{
		if (i != c.value->begin())
			f << ", ";
		f << to_hex(*i);
	}
	f << "}";
	return f;
}

template <class value_type>
file &operator<<(file &f, const file::hex<list<value_type> > &c)
{
	f << "{";
	for (typename list<value_type>::const_iterator i = c.value->begin(); i != c.value->end(); i++)
	{
		if (i != c.value->begin())
			f << ", ";
		f << to_hex(*i);
	}
	f << "}";
	return f;
}

template <class key_type, class value_type>
file &operator<<(file &f, const file::hex<implier<key_type, value_type> > &c)
{
	f << to_hex(c.key) << " -> " << to_hex(c.value);
	return f;
}

template <class type1, class type2>
file &operator<<(file &f, const file::hex<pair<type1, type2> > &p)
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
