/*
  * string.h
 *
 *  Created on: Feb 4, 2014
 *      Author: nbingham
 */

#include "array.h"

#ifndef string_h
#define string_h

namespace core
{

struct string : array<char>
{
	string();
	string(char i);
	string(bool b);
	string(int i);
	string(short i);
	string(long i);
	string(unsigned char c);
	string(unsigned int i);
	string(unsigned short i);
	string(unsigned long i);
	string(float f);
	string(double d);
	string(int num, char t);
	string(const char *str);
	string(const string &str);
	~string();

	using typename array<char>::iterator;
	using typename array<char>::const_iterator;

	void resize(int n, char c = '\0');

	bool to_bool();
	long to_long(int base = 10);
	double to_double();

	int length();
	int find(string str, int pos = 0);
	int find(const char *str, int pos = 0);
	int find_l0(string str, string del, int pos = 0);
	int find_l0(const char *str, const char *del, int pos = 0);
	int rfind(const char *str, int pos = -1);
	int rfind(string str, int pos = -1);
	int rfind_l0(string str, string del, int pos = 0);
	int rfind_l0(const char *str, const char *del, int pos = 0);
	int find_first_of(const char *str, int pos = 0);
	int find_first_of(string str, int pos = 0);
	int find_last_of(const char *str, int pos = -1);
	int find_last_of(string str, int pos = -1);
	int find_first_not_of(const char *str, int pos = 0);
	int find_first_not_of(string str, int pos = 0);
	int find_last_not_of(const char *str, int pos = -1);
	int find_last_not_of(string str, int pos = -1);
	int find_first_of_l0(const char *str, const char *del, int pos = 0);
	int find_first_of_l0(string str, string del, int pos = 0);
	int find_last_of_l0(const char *str, const char *del, int pos = -1);
	int find_last_of_l0(string str, string del, int pos = -1);
	int find_first_not_of_l0(const char *str, const char *del, int pos = 0);
	int find_first_not_of_l0(string str, string del, int pos = 0);
	int find_last_not_of_l0(const char *str, const char *del, int pos = -1);
	int find_last_not_of_l0(string str, string del, int pos = -1);
	void insert(int pos, const char *str);
	void insert(int pos, string str);
	string &replace(int s, int e, const char *r);
	string &replace(int s, int e, string r);
	string &replace(const char *s, const char *r);
	string &replace(string s, string r);
	string &rreplace(const char *s, const char *r);
	string &rreplace(string s, string r);
	string substr(int s, int e);
	string substr(int s);
	int compare(const char *str);
	int compare(string str);

	string &toupper(int i);
	string &toupper();
	string &tolower(int i);
	string &tolower();

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

bool operator==(string s1, string s2);
bool operator!=(string s1, string s2);
bool operator<(string s1, string s2);
bool operator>(string s1, string s2);
bool operator<=(string s1, string s2);
bool operator>=(string s1, string s2);
bool operator==(string s1, const char *s2);
bool operator==(const char *s1, string s2);
bool operator!=(string s1, const char *s2);
bool operator!=(const char *s1, string s2);
bool operator<(string s1, const char *s2);
bool operator<(const char *s1, string s2);
bool operator>(string s1, const char *s2);
bool operator>(const char *s1, string s2);
bool operator<=(string s1, const char *s2);
bool operator<=(const char *s1, string s2);
bool operator>=(string s1, const char *s2);
bool operator>=(const char *s1, string s2);

bool is_alpha(char c);
bool is_numeric(char c);
bool is_symbol(char c);
bool is_whitespace(char c);

}

#endif
