#pragma once

#include <std/array.h>
#include <std/pair.h>
#include <std/implier.h>

namespace core
{

struct string : array<char>
{
	string();
	
	template <class container>
	string(const container &str) : array<char>(str)
	{
	}

	string(const iterator &left, const iterator &right) : array<char>(left, right)
	{
	}

	string(const string &str);
	
	string(const char *str);
	string(const char *str, int n);
	string(char str);

	~string();

	using array<char>::size;

	using array<char>::operator=;
	string &operator=(const char *str);
	string &operator=(char *str);
	
	string &operator+=(const char *str);
	string &operator+=(char *str);
	string &operator+=(const string &str);

	string escaped();
	string unescaped();

	char *c_str();
};

template <class value_type>
struct options
{
	options(const value_type &value, int radix)
	{
		this->value = &value;
		this->radix = radix;
	}

	~options() {}

	const value_type *value;
	int radix;
};

template <class value_type>
options<value_type> to_hex(const value_type &value)
{
	return options<value_type>(value, 16);
}

template <class value_type>
options<value_type> to_bin(const value_type &value)
{
	return options<value_type>(value, 2);
}

string operator+(const string &s1, const string &s2);
string operator+(const string &s1, const char *s2);
string operator+(const string &s1, char *s2);
string operator+(const string &s1, char s2);

string &operator<<(string &s1, char s2);
string &operator<<(string &s1, bool s2);
string &operator<<(string &s1, int s2);
string &operator<<(string &s1, short s2);
string &operator<<(string &s1, long s2);
string &operator<<(string &s1, long long s2);
string &operator<<(string &s1, unsigned char s2);
string &operator<<(string &s1, unsigned int s2);
string &operator<<(string &s1, unsigned short s2);
string &operator<<(string &s1, unsigned long s2);
string &operator<<(string &s1, unsigned long long s2);
string &operator<<(string &s1, options<int> s2);
string &operator<<(string &s1, options<short> s2);
string &operator<<(string &s1, options<long> s2);
string &operator<<(string &s1, options<long long> s2);
string &operator<<(string &s1, options<unsigned char> s2);
string &operator<<(string &s1, options<unsigned int> s2);
string &operator<<(string &s1, options<unsigned short> s2);
string &operator<<(string &s1, options<unsigned long> s2);
string &operator<<(string &s1, options<unsigned long long> s2);
string &operator<<(string &s1, float s2);
string &operator<<(string &s1, double s2);
string &operator<<(string &s1, const string &s2);
string &operator<<(string &s1, const char *s2);
string &operator<<(string &s1, char *s2);

string format_string(const string &str, const char *esc);

template <class type>
struct parsable
{
	parsable(const type *val) : obj(val) {}
	~parsable() {}

	const type *obj;
};

template <class container>
string &operator<<(string &s1, const container &v)
{
	s1 << '{';
	for (typename container::const_iterator i = v.begin(); i; i++)
	{
		if (i != v.begin())
			s1 << ", ";
		s1 << parsable<typename container::type>(i.ptr());
	}
	s1 << '}';
	return s1;
}

template <class container>
string &operator<<(string &s1, const options<container> &v)
{
	s1 << '{';
	for (typename container::const_iterator i = v.value->begin(); i; i++)
	{
		if (i != v.value->begin())
			s1 << ", ";
		s1 << options<parsable<typename container::type> >(parsable<typename container::type>(i.ptr()), v.radix);
	}
	s1 << '}';
	return s1;
}

template <class type>
string &operator<<(string &s1, const parsable<type> &p)
{
	s1 << *p.obj;
	return s1;
}

template <class type>
string &operator<<(string &s1, const options<parsable<type> > &p)
{
	s1 << options<type>(*p.value->obj, p.radix);
	return s1;
}

template <>
string &operator<<(string &s1, const parsable<string> &p);

template <>
string &operator<<(string &s1, const options<parsable<string> > &p);

template <class type0, class type1>
string &operator<<(string &s1, const pair<type0, type1> &v)
{
	return s1 << '(' << parsable<type0>(&v.first) << ", " << parsable<type1>(&v.second) << ')';
}

template <class type0, class type1>
string &operator<<(string &s1, const implier<type0, type1> &v)
{
	return s1 << parsable<type0>(&v.key) << ": " << parsable<type1>(&v.value);
}

template <class type0, class type1>
string &operator<<(string &s1, const options<pair<type0, type1> > &v)
{
	return s1 << '(' << options<parsable<type0> >(parsable<type0>(&v.value->first), v.radix) << ", " << options<parsable<type1> >(parsable<type1>(&v.value->second), v.radix) << ')';
}

template <class type0, class type1>
string &operator<<(string &s1, const options<implier<type0, type1> > &v)
{
	return s1 << options<parsable<type0> >(parsable<type0>(&v.value->key), v.radix) << ": " << options<parsable<type1> >(parsable<type1>(&v.value->value), v.radix);
}


bool operator==(string s1, string s2);
bool operator!=(string s1, string s2);
bool operator<(string s1, string s2);
bool operator>(string s1, string s2);
bool operator<=(string s1, string s2);
bool operator>=(string s1, string s2);
bool operator==(string s1, const char* s2);
bool operator!=(string s1, const char* s2);
bool operator<(string s1, const char* s2);
bool operator>(string s1, const char* s2);
bool operator<=(string s1, const char* s2);
bool operator>=(string s1, const char* s2);
bool operator==(const char* s1, string s2);
bool operator!=(const char* s1, string s2);
bool operator<(const char* s1, string s2);
bool operator>(const char* s1, string s2);
bool operator<=(const char* s1, string s2);
bool operator>=(const char* s1, string s2);

bool is_alpha(char c);
bool is_numeric(char c);
bool is_symbol(char c);
bool is_whitespace(char c);

int edit_distance(const string &s1, const string &s2);
int get_column(const string &line, int index, int tab_width);
string get_column_ptr(const string &line, int index);
string line_wrap(const string &line, int length);

int itoa(int value, char *str);
int itoa(unsigned int value, char *str);
int itoa(long long value, char *str);
int itoa(unsigned long long value, char *str);
int itob(unsigned int value, char *str);
int itox(unsigned int value, char *str);

int ftoa(float value, char *str);
int ftoa(double value, char *str);

slice<range<const char*> > wrapstr(const char *cstr);
slice<range<char*> > wrapstr(char *cstr);
slice<range<const char*> > wrapstr(const char *cstr, int n);
slice<range<char*> > wrapstr(char *cstr, int n);

}
