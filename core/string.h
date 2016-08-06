#pragma once

#include <core/array.h>
#include <core/pair.h>
#include <core/implier.h>
#include <core/slice.h>

namespace core
{

struct string : array<char>
{
	string();
	string(const char *str);
	
	template <class container>
	string(const container &str) : array<char>(str)
	{
	}

	string(const string &str);
	
	~string();

	using array<char>::size;

	using array<char>::operator=;
	string &operator=(const char *str);
	string &operator=(char *str);
	
	string &operator+=(const char *str);
	string &operator+=(char *str);
	string &operator+=(const string &str);

	char *c_str();
};

string operator+(const string &s1, const string &s2);
string operator+(const string &s1, const char *s2);
string operator+(const string &s1, char *s2);

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

template <class type>
string &operator<<(string &s1, const parsable<type> &p)
{
	s1 << *p.obj;
	return s1;
}

template <>
string &operator<<(string &s1, const parsable<string> &p);

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
