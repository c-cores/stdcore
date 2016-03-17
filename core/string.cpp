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

string::string(char t, int n) : array<char>(t, n)
{
	
}

string::string(const char *str) : array<char>(slice<const char*>(str, strlen(str)))
{
}

string::~string()
{
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
	at(pos).push(slice<const char*>(str, strlen(str)));
}

void string::insert(int pos, string str)
{
	at(pos).push(str);
}

string &string::replace(int s, int e, const char *r)
{
	at(s).replace(e-s, slice<const char*>(r, strlen(r)));
	return *this;
}

string &string::replace(int s, int e, string r)
{
	at(s).replace(e-s, r);
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
	return string(sub(s, e));
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
	array<char>::operator=(slice<const char *>(str, strlen(str)));
	return *this;
}

string &string::operator=(char *str)
{
	array<char>::operator=(slice<char*>(str, strlen(str)));
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
	array<char>::push_back(str);
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
	result.reserve(s1.size() + s2.size());
	result.push_back(s1);
	result.push_back(s2);
	return result;
}

string operator+(string s1, const char *s2)
{
	int s2s = strlen(s2);
	string result;
	result.reserve(s1.size() + s2s);
	result.push_back(s1);
	result.push_back(slice<const char*>(s2, s2+s2s));
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


string to_string(char i)
{
	char str[5];
	snprintf(str, 5, "%hd", i);
	return string(slice<char*>(str, 5));
}

string to_string(bool b)
{
	return string(b ? slice<const char*>("true", 4) : slice<const char*>("false", 5));
}

string to_string(int i)
{
	char str[12];
	snprintf(str, 12, "%d", i);
	return string(slice<char*>(str, 12));
}

string to_string(short i)
{
	char str[7];
	snprintf(str, 7, "%hd", i);
	return string(slice<char*>(str, 7));
}

string to_string(long i)
{
	char str[21];
	snprintf(str, 21, "%ld", i);
	return string(slice<char*>(str, 21));
}

string to_string(unsigned char i)
{
	char str[5];
	snprintf(str, 5, "%hu", i);
	return string(slice<char*>(str, 5));
}

string to_string(unsigned int i)
{
	char str[12];
	snprintf(str, 12, "%u", i);
	return string(slice<char*>(str, 12));
}

string to_string(unsigned short i)
{
	char str[7];
	snprintf(str, 7, "%hu", i);
	return string(slice<char*>(str, 7));
}

string to_string(unsigned long i)
{
	char str[21];
	snprintf(str, 21, "%lu", i);
	return string(slice<char*>(str, 7));
}

string to_string(float f)
{
	char str[32];
	snprintf(str, 32, "%f", f);
	return string(slice<char*>(str, 32));
}

string to_string(double d)
{
	char str[32];
	snprintf(str, 32, "%f", d);
	return string(slice<char*>(str, 32));
}

bool to_bool(string s)
{
	return (s.compare("true") == 0 || s.compare("1") == 0);
}

long to_long(string s, int base)
{
	return strtol(s.c_str(), NULL, base);
}

double to_double(string s)
{
	return strtod(s.c_str(), NULL);
}

}
