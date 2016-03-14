/*
 * string.cpp
 *
 *  Created on: Feb 4, 2014
 *      Author: nbingham
 */

#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

namespace core
{

string::string()
{

}

string::string(char i)
{
	array<char>::reserve(5);
	array<char>::resize(snprintf(data, 5, "%hd", i));
}

string::string(bool b)
{
	if (b)
	{
		array<char>::resize(4);
		get(0) = 't';
		get(1) = 'r';
		get(2) = 'u';
		get(3) = 'e';
	}
	else
	{
		array<char>::resize(5);
		get(0) = 'f';
		get(1) = 'a';
		get(2) = 'l';
		get(3) = 's';
		get(4) = 'e';
	}
}

string::string(int i)
{
	array<char>::reserve(12);
	array<char>::resize(snprintf(data, 12, "%d", i));
}

string::string(short i)
{
	array<char>::reserve(7);
	array<char>::resize(snprintf(data, 7, "%hd", i));
}

string::string(long i)
{
	array<char>::reserve(21);
	array<char>::resize(snprintf(data, 21, "%ld", i));
}

string::string(unsigned char i)
{
	array<char>::reserve(5);
	array<char>::resize(snprintf(data, 5, "%hu", i));
}

string::string(unsigned int i)
{
	array<char>::reserve(12);
	array<char>::resize(snprintf(data, 12, "%u", i));
}

string::string(unsigned short i)
{
	array<char>::reserve(7);
	array<char>::resize(snprintf(data, 7, "%hu", i));
}

string::string(unsigned long i)
{
	array<char>::reserve(21);
	array<char>::resize(snprintf(data, 21, "%lu", i));
}

string::string(float f)
{
	array<char>::reserve(32);
	array<char>::resize(snprintf(data, 32, "%f", f));
}

string::string(double d)
{
	array<char>::reserve(32);
	array<char>::resize(snprintf(data, 32, "%f", d));
}

string::string(int num, char t) : array<char>(num, t)
{

}

string::string(const char *str)
{
	array<char>::resize(strlen(str));
	memcpy(data, str, size()*sizeof(char));
}

string::string(const string &str) : array<char>(str)
{
}

string::~string()
{
}

void string::resize(int n, char c)
{
	int s = size();
	array<char>::resize(n);
	for (int i = s; i < size(); i++)
		get(i) = c;
}

bool string::to_bool()
{
	if (compare("true") == 0 || compare("1") == 0)
		return true;
	else
		return false;
}

long string::to_long(int base)
{
	return strtol(data, NULL, base);
}

double string::to_double()
{
	return strtod(data, NULL);
}

int string::length()
{
	return size();
}

int string::find(const char *str, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	for (int i = pos; i < size(); i++)
	{
		int j;
		for (j = 0; i + j < size() && str[j] != '\0' && get(i+j) == str[j]; j++);

		if (str[j] == '\0')
			return i;
	}
	return -1;
}

int string::find(string str, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	for (int i = pos; i < size(); i++)
	{
		int j;
		for (j = 0; i + j < size() && j < str.size() && get(i+j) == str[j]; j++);

		if (j >= str.size())
			return i;
	}
	return -1;
}

int string::find_l0(string str, string del, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	string stack;
	for (int i = pos; i < size(); i++)
	{
		bool found = false;
		if (stack.size() > 0 && get(i) == stack.back())
		{
			stack.drop_back();
			found = true;
		}

		if (!found && stack.size() == 0)
		{
			int j;
			for (j = 0; i + j < size() && j < str.size() && get(i+j) == str[j]; j++);

			if (j >= str.size())
				return i;
		}

		for (int j = 0; !found && j < del.size(); j+=2)
			if (get(i) == del[j])
			{
				stack.push_back(del[j+1]);
				found = true;
			}
	}

	return -1;
}

int string::find_l0(const char *str, const char *del, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	string stack;
	for (int i = pos; i < size(); i++)
	{
		bool found = false;
		if (stack.size() > 0 && get(i) == stack.back())
		{
			stack.drop_back();
			found = true;
		}

		if (!found && stack.size() == 0)
		{
			int j;
			for (j = 0; i + j < size() && str[j] != '\0' && get(i+j) == str[j]; j++);

			if (str[j] == '\0')
				return i;
		}

		for (int j = 0; !found && del[j] != '\0'; j+=2)
			if (get(i) == del[j])
			{
				stack.push_back(del[j+1]);
				found = true;
			}
	}

	return -1;
}

int string::rfind(const char *str, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	for (int i = pos; i >= 0; i--)
	{
		int j;
		for (j = i; j < size() && str[j-i] != '\0' && get(j) == str[j-i]; j++);

		if (str[j-i] == '\0')
			return i;
	}
	return -1;
}

int string::rfind(string str, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	for (int i = pos; i >= 0; i--)
	{
		int j;
		for (j = i; j < size() && j-i < str.size() && get(j) == str[j-i]; j++);

		if (j-i >= str.size())
			return i;
	}
	return -1;
}

int string::rfind_l0(string str, string del, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	string stack;
	for (int i = pos; i >= 0; i--)
	{
		bool found = false;
		if (stack.size() > 0 && get(i) == stack.back())
		{
			stack.drop_back();
			found = true;
		}

		if (!found && stack.size() == 0)
		{
			int j;
			for (j = 0; i + j < size() && j < str.size() && get(i+j) == str[j]; j++);

			if (j >= str.size())
				return i;
		}

		for (int j = 1; !found && j-1 < del.size(); j+=2)
			if (get(i) == del[j])
			{
				stack.push_back(del[j-1]);
				found = true;
			}
	}

	return -1;
}

int string::rfind_l0(const char *str, const char *del, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	string stack;
	for (int i = pos; i >= 0; i--)
	{
		bool found = false;
		if (stack.size() > 0 && get(i) == stack.back())
		{
			stack.drop_back();
			found = true;
		}

		if (!found && stack.size() == 0)
		{
			int j;
			for (j = 0; i + j < size() && str[j] != '\0' && get(i+j) == str[j]; j++);

			if (str[j] == '\0')
				return i;
		}

		for (int j = 1; !found && del[j-1] != '\0'; j+=2)
			if (get(i) == del[j])
			{
				stack.push_back(del[j-1]);
				found = true;
			}
	}

	return -1;
}

int string::find_first_of(const char *str, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	for (int i = pos; i < size(); i++)
		for (int j = 0; str[j] != '\0'; j++)
			if (get(i) == str[j])
				return i;

	return -1;
}

int string::find_first_of(string str, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	for (int i = pos; i < size(); i++)
		for (int j = 0; j < str.size(); j++)
			if (get(i) == str[j])
				return i;

	return -1;
}

int string::find_last_of(const char *str, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	for (int i = pos; i >= 0; i--)
		for (int j = 0; str[j] != '\0'; j++)
			if (get(i) == str[j])
				return i;

	return -1;
}

int string::find_last_of(string str, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	for (int i = pos; i >= 0; i--)
		for (int j = 0; j < str.size(); j++)
			if (get(i) == str[j])
				return i;

	return -1;
}

int string::find_first_not_of(const char *str, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	for (int i = pos; i < size(); i++)
	{
		bool found = false;
		for (int j = 0; !found && str[j] != '\0'; j++)
			if (get(i) == str[j])
				found = true;

		if (!found)
			return i;
	}

	return -1;
}

int string::find_first_not_of(string str, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	for (int i = pos; i < size(); i++)
	{
		bool found = false;
		for (int j = 0; !found && j < str.size(); j++)
			if (get(i) == str[j])
				found = true;

		if (!found)
			return i;
	}

	return -1;
}

int string::find_last_not_of(const char *str, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	for (int i = pos; i >= 0; i--)
	{
		bool found = false;
		for (int j = 0; !found && str[j] != '\0'; j++)
			if (get(i) == str[j])
				found = true;

		if (!found)
			return i;
	}

	return -1;
}

int string::find_last_not_of(string str, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	for (int i = pos; i >= 0; i--)
	{
		bool found = false;
		for (int j = 0; !found && j < str.size(); j++)
			if (get(i) == str[j])
				found = true;

		if (!found)
			return i;
	}

	return -1;
}

int string::find_first_of_l0(const char *str, const char *del, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	string stack;
	for (int i = pos; i < size(); i++)
	{
		bool found = false;
		if (stack.size() > 0 && get(i) == stack.back())
		{
			stack.drop_back();
			found = true;
		}

		if (!found && stack.size() == 0)
			for (int j = 0; str[j] != '\0'; j++)
				if (get(i) == str[j])
					return i;

		for (int j = 0; !found && del[j] != '\0'; j+=2)
			if (get(i) == del[j])
			{
				stack.push_back(del[j+1]);
				found = true;
			}
	}

	return -1;
}

int string::find_first_of_l0(string str, string del, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	string stack;
	for (int i = pos; i < size(); i++)
	{
		bool found = false;
		if (stack.size() > 0 && get(i) == stack.back())
		{
			stack.drop_back();
			found = true;
		}

		if (!found && stack.size() == 0)
			for (int j = 0; j < str.size(); j++)
				if (get(i) == str[j])
					return i;

		for (int j = 0; !found && j < del.size(); j+=2)
			if (get(i) == del[j])
			{
				stack.push_back(del[j+1]);
				found = true;
			}
	}

	return -1;
}

int string::find_last_of_l0(const char *str, const char *del, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	string stack;
	for (int i = pos; i >= 0; i--)
	{
		bool found = false;
		if (stack.size() > 0 && get(i) == stack.back())
		{
			stack.drop_back();
			found = true;
		}

		if (!found && stack.size() == 0)
			for (int j = 0; str[j] != '\0'; j++)
				if (get(i) == str[j])
					return i;

		for (int j = 1; !found && del[j-1] != '\0'; j+=2)
			if (get(i) == del[j])
			{
				stack.push_back(del[j-1]);
				found = true;
			}
	}

	return -1;
}

int string::find_last_of_l0(string str, string del, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	string stack;
	for (int i = pos; i >= 0; i--)
	{
		bool found = false;
		if (stack.size() > 0 && get(i) == stack.back())
		{
			stack.drop_back();
			found = true;
		}

		if (!found && stack.size() == 0)
			for (int j = 0; j < str.size(); j++)
				if (get(i) == str[j])
					return i;

		for (int j = 1; !found && j < del.size(); j+=2)
			if (get(i) == del[j])
			{
				stack.push_back(del[j-1]);
				found = true;
			}
	}

	return -1;
}

int string::find_first_not_of_l0(const char *str, const char *del, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	string stack;
	for (int i = pos; i < size(); i++)
	{
		bool found = false;
		if (stack.size() > 0 && get(i) == stack.back())
		{
			stack.drop_back();
			found = true;
		}

		if (!found && stack.size() == 0)
		{
			bool subfound = false;
			for (int j = 0; !subfound && str[j] != '\0'; j++)
				if (get(i) == str[j])
					subfound = true;

			if (!subfound)
				return i;
		}

		for (int j = 0; !found && del[j] != '\0'; j+=2)
			if (get(i) == del[j])
			{
				stack.push_back(del[j+1]);
				found = true;
			}
	}

	return -1;
}

int string::find_first_not_of_l0(string str, string del, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	string stack;
	for (int i = pos; i < size(); i++)
	{
		bool found = false;
		if (stack.size() > 0 && get(i) == stack.back())
		{
			stack.drop_back();
			found = true;
		}

		if (!found && stack.size() == 0)
		{
			bool subfound = false;
			for (int j = 0; !subfound && j < str.size(); j++)
				if (get(i) == str[j])
					subfound = true;

			if (!subfound)
				return i;
		}

		for (int j = 0; !found && j < del.size(); j+=2)
			if (get(i) == del[j])
			{
				stack.push_back(del[j+1]);
				found = true;
			}
	}

	return -1;
}

int string::find_last_not_of_l0(const char *str, const char *del, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	string stack;
	for (int i = pos; i >= 0; i--)
	{
		bool found = false;
		if (stack.size() > 0 && get(i) == stack.back())
		{
			stack.drop_back();
			found = true;
		}

		if (!found && stack.size() == 0)
		{
			bool subfound = false;
			for (int j = 0; !subfound && str[j] != '\0'; j++)
				if (get(i) == str[j])
					subfound = true;

			if (!subfound)
				return i;
		}

		for (int j = 1; !found && del[j-1] != '\0'; j+=2)
			if (get(i) == del[j])
			{
				stack.push_back(del[j-1]);
				found = true;
			}
	}

	return -1;
}

int string::find_last_not_of_l0(string str, string del, int pos)
{
	while (size() > 0 && pos < 0)
		pos += size();

	string stack;
	for (int i = pos; i >= 0; i--)
	{
		bool found = false;
		if (stack.size() > 0 && get(i) == stack.back())
		{
			stack.drop_back();
			found = true;
		}

		if (!found && stack.size() == 0)
		{
			bool subfound = false;
			for (int j = 0; !subfound && j < str.size(); j++)
				if (get(i) == str[j])
					subfound = true;

			if (!subfound)
				return i;
		}

		for (int j = 1; !found && j < del.size(); j+=2)
			if (get(i) == del[j])
			{
				stack.push_back(del[j-1]);
				found = true;
			}
	}

	return -1;
}

void string::insert(int pos, const char *str)
{
	while (size() > 0 && pos < 0)
		pos += size();

	int s = strlen(str);
	array<char>::resize(s + size());
	for (int i = size() - 1; i >= pos + s; i--)
		get(i) = get(i - s);
	for (int i = 0; str[i] != '\0'; i++)
		get(i + pos) = str[i];
}

void string::insert(int pos, string str)
{
	while (size() > 0 && pos < 0)
		pos += size();

	array<char>::resize(str.size() + size());
	for (int i = size() - 1; i >= pos + str.size(); i--)
		get(i) = get(i - str.size());
	for (int i = 0; str[i] != '\0'; i++)
		get(i + pos) = str[i];
}

string &string::replace(int s, int e, const char *r)
{
	while (size() > 0 && s < 0)
		s += size();
	while (size() > 0 && e < 0)
		e += size();

	int rs = strlen(r);
	if (rs > e-s)
	{
		array<char>::resize(size() + rs - (e - s));
		for (int i = size()-1; i >= rs + s; i--)
			get(i) = get(i - rs + e - s);
	}
	else if (rs < e-s)
	{
		for (int i = rs + s; i < size(); i++)
			get(i) = get(i + e - s - rs);
		array<char>::resize(size() + rs - (e - s));
	}

	for (int i = 0; r[i] != '\0'; i++)
		get(i + s) = r[i];

	return *this;
}

string &string::replace(int s, int e, string r)
{
	while (size() > 0 && s < 0)
		s += size();
	while (size() > 0 && e < 0)
		e += size();

	array<char>::resize(size() + r.size() - (e - s));
	if (r.size() > e-s)
	{
		array<char>::resize(size() + r.size() - (e - s));
		for (int i = size()-1; i >= r.size() + s; i--)
			get(i) = get(i - r.size() + e - s);
	}
	else if (r.size() < e-s)
	{
		for (int i = r.size() + s; i < size(); i++)
			get(i) = get(i + e - s - r.size());
		array<char>::resize(size() + r.size() - (e - s));
	}

	for (int i = 0; i < r.size(); i++)
		get(i + s) = r[i];

	return *this;
}

string &string::replace(const char *s, const char *r)
{
	int i = 0;
	int ss = strlen(s);
	int rs = strlen(r);
	while ((i = find(s, i)) != -1)
	{
		replace(i, i+ss, r);
		i += rs+1;
	}

	return *this;
}

string &string::replace(string s, string r)
{
	int i = 0;
	while ((i = find(s, i)) != -1)
	{
		replace(i, i+s.size(), r);
		i += r.size()+1;
	}

	return *this;
}

string &string::rreplace(const char *s, const char *r)
{
	int i = size()-1;
	int ss = strlen(s);
	int rs = strlen(r);
	while ((i = rfind(s, i)) != -1)
	{
		replace(i, i+ss, r);
		i -= rs+1;
	}

	return *this;
}

string &string::rreplace(string s, string r)
{
	int i = size()-1;
	while ((i = rfind(s, i)) != -1)
	{
		replace(i, i+s.size(), r);
		i -= r.size()+1;
	}

	return *this;
}

string string::substr(int s, int e)
{
	while (size() > 0 && s < 0)
		s += size();
	while (size() > 0 && e < s)
		e += size();

	if (e > size())
		e = size();

	if (s > size())
		return string();
	else
	{
		string result;
		result.resize(e-s);
		for (int i = s; i < e; i++)
			result[i-s] = get(i);
		return result;
	}
}

string string::substr(int s)
{
	while (size() > 0 && s < 0)
		s += size();

	if (s > size())
		return string();
	else
	{
		string result;
		result.resize(size()-s);
		for (int i = s; i < size(); i++)
			result[i-s] = get(i);
		return result;
	}
}

int string::compare(const char *str)
{
	int i = 0;
	for (i = 0; i < size() && str[i] != '\0'; i++)
	{
		if (get(i) < str[i])
			return -1;
		else if (get(i) > str[i])
			return 1;
	}

	if (str[i] != '\0')
		return -1;
	else if (i < size())
		return 1;
	else
		return 0;
}

int string::compare(string a)
{
	int i = 0;
	for (i = 0; i < size() && i < a.size(); i++)
	{
		if (get(i) < a[i])
			return -1;
		else if (get(i) > a[i])
			return 1;
	}

	if (i < a.size())
		return -1;
	else if (i < size())
		return 1;
	else
		return 0;
}

string &string::toupper(int i)
{
	get(i) = ::toupper(get(i));
	return *this;
}

string &string::toupper()
{
	for (int i = 0; i < size(); i++)
		get(i) = ::toupper(get(i));
	return *this;
}

string &string::tolower(int i)
{
	get(i) = ::tolower(get(i));
	return *this;
}

string &string::tolower()
{
	for (int i = 0; i < size(); i++)
		get(i) = ::tolower(get(i));
	return *this;
}

string &string::operator=(const char *str)
{
	array<char>::resize(strlen(str));
	memcpy(data, str, size()*sizeof(char));
	return *this;
}

string &string::operator=(char *str)
{
	array<char>::resize(strlen(str));
	memcpy(data, str, size()*sizeof(char));
	return *this;
}

string &string::operator+=(const char *str)
{
	array<char>::push_back(slice<const char*>(str, str+strlen(str)-1));
	return *this;
}

string &string::operator+=(char *str)
{
	array<char>::push_back(slice<char*>(str, str+strlen(str)-1));
	return *this;
}

string &string::operator+=(string str)
{
	array<char>::push_back(str.bound());
	return *this;
}

char *string::c_str()
{
	reserve(size() + 1);
	get(size()) = '\0';

	return data;
}

string operator+(string s1, string s2)
{
	string result;
	result.array<char>::resize(s1.size() + s2.size());
	memcpy(result.data, s1.data, s1.size()*sizeof(char));
	memcpy(result.data+s1.size(), s2.data, s2.size()*sizeof(char));
	return result;
}

string operator+(string s1, const char *s2)
{
	int s2s = strlen(s2);
	string result;
	result.array<char>::resize(s1.size() + s2s);
	memcpy(result.data, s1.data, s1.size()*sizeof(char));
	memcpy(result.data+s1.size(), s2, s2s*sizeof(char));
	return result;
}

bool operator==(string s1, string s2)
{
	return (s1.compare(s2) == 0);
}

bool operator!=(string s1, string s2)
{
	return (s1.compare(s2) != 0);
}

bool operator<(string s1, string s2)
{
	return (s1.compare(s2) < 0);
}

bool operator>(string s1, string s2)
{
	return (s1.compare(s2) > 0);
}

bool operator<=(string s1, string s2)
{
	return (s1.compare(s2) <= 0);
}

bool operator>=(string s1, string s2)
{
	return (s1.compare(s2) >= 0);
}

bool operator==(string s1, const char *s2)
{
	return (s1.compare(s2) == 0);
}

bool operator==(const char *s1, string s2)
{
	return (s2.compare(s1) == 0);
}

bool operator!=(string s1, const char *s2)
{
	return (s1.compare(s2) != 0);
}

bool operator!=(const char *s1, string s2)
{
	return (s2.compare(s1) != 0);
}

bool operator<(string s1, const char *s2)
{
	return (s1.compare(s2) < 0);
}

bool operator<(const char *s1, string s2)
{
	return (s2.compare(s1) > 0);
}
bool operator>(string s1, const char *s2)
{
	return (s1.compare(s2) > 0);
}

bool operator>(const char *s1, string s2)
{
	return (s2.compare(s1) < 0);
}

bool operator<=(string s1, const char *s2)
{
	return (s1.compare(s2) <= 0);
}

bool operator<=(const char *s1, string s2)
{
	return (s2.compare(s1) >= 0);
}

bool operator>=(string s1, const char *s2)
{
	return (s1.compare(s2) >= 0);
}

bool operator>=(const char *s1, string s2)
{
	return (s2.compare(s1) <= 0);
}

/*Is this character a legal name starter character?
 */
bool is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') );
}

/* Is this character a character that is legal to have
 * in a type name or variable name? a-z A-Z 0-9 _
 */
bool is_numeric(char c)
{
	return (c >= '0' && c <= '9');
}

/* Is this character an operator?
 *
 */
bool is_symbol(char c)
{
	return (c == '!' ||
			c == '\"' ||
			c == '#' ||
			c == '$' ||
			c == '%' ||
			c == '&' ||
			c == '\'' ||
			c == '(' ||
			c == ')' ||
			c == '*' ||
			c == '+' ||
			c == ',' ||
			c == '-' ||
			c == '.' ||
			c == '/' ||
			c == ':' ||
			c == ';' ||
			c == '<' ||
			c == '=' ||
			c == '>' ||
			c == '?' ||
			c == '@' ||
			c == '[' ||
			c == ']' ||
			c == '^' ||
			c == '`' ||
			c == '{' ||
			c == '|' ||
			c == '}' ||
			c == '~');
}

/* Is this character whitespace?
 *
 */
bool is_whitespace(char c)
{
	return (c == ' '  ||
			c == '\t' ||
			c == '\n' ||
			c == '\r');
}

}
