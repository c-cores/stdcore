#pragma once

#include "array.h"
#include "pair.h"
#include "implier.h"

namespace core
{

struct string : array<char>
{
	string();
	string(int n, char c);
	string(const char *str);
	
	template <class container>
	string(const container &str) : array<char>(str)
	{
	}

	string(const string &str);
	
	~string();

	using array<char>::operator=;
	string &operator=(const char *str);
	string &operator=(char *str);
	
	string &operator+=(const char *str);
	string &operator+=(char *str);
	string &operator+=(string str);

	char *c_str();
};

string operator+(string s1, string s2);
string operator+(string s1, const char *s2);
string operator+(string s1, char *s2);

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
string &operator<<(string &s1, string s2);
string &operator<<(string &s1, const char *s2);
string &operator<<(string &s1, char *s2);

template <class container>
string &operator<<(string &s1, const container &v)
{
	s1.push_back('[');
	for (typename container::const_iterator i = v.begin(); i != v.end(); i++)
	{
		if (i != v.begin())
			s1.push_back(' ');
		s1 << *i;
	}
	s1.push_back(']');
	return s1;
}

template <class type0, class type1>
string &operator<<(string &s1, const pair<type0, type1> &v)
{
	s1.push_back('(');
	s1 << v.first;
	s1.push_back(' ');
	s1 << v.second;
	s1.push_back(')');
	return s1;
}

template <class type0, class type1>
string &operator<<(string &s1, const implier<type0, type1> &v)
{
	s1.push_back('(');
	s1 << v.first;
	s1 += " -> ";
	s1 << v.second;
	s1.push_back(')');
	return s1;
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

}
