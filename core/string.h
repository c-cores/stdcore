#pragma once

#include "array.h"

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

	using typename array<char>::type;
	using typename array<char>::iterator;
	using typename array<char>::const_iterator;

	using array<char>::begin;
	using array<char>::end;
	using array<char>::rbegin;
	using array<char>::rend;
	using array<char>::sub;
	using array<char>::size;

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

bool is_alpha(char c);
bool is_numeric(char c);
bool is_symbol(char c);
bool is_whitespace(char c);

}
