#include "string.h"

namespace core
{

string::string()
{
}

string::string(int n, char c) : array<char>(n, c)
{
}

string::string(const char *str) : array<char>(slice<const char*>(str, str + strlen(str)-1))
{
}
	
string::string(const string &str) : array<char>(str)
{
}
	
string::~string()
{
}

string &string::operator=(const char *str)
{
	array<char>::operator=(slice<const char*>(str, str + strlen(str)-1));
	return *this;
}

string &string::operator=(char *str)
{
	array<char>::operator=(slice<char*>(str, str + strlen(str)-1));
	return *this;
}

string &string::operator+=(const char *str)
{
	array<char>::push_back(slice<const char *>(str, str + strlen(str)-1));
	return *this;
}

string &string::operator+=(char *str)
{
	array<char>::push_back(slice<const char *>(str, str + strlen(str)-1));
	return *this;
}

string &string::operator+=(string str)
{
	array<char>::push_back(str.sub(0));
	return *this;
}

char *string::c_str()
{
	reserve(size()+1);
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
	string result;
	int n = strlen(s2);
	result.reserve(s1.size() + n);
	result.push_back(s1);
	result.push_back(slice<const char*>(s2, s2 + n-1));
	return result;
}

string operator+(string s1, char *s2)
{
	string result;
	int n = strlen(s2);
	result.reserve(s1.size() + n);
	result.push_back(s1);
	result.push_back(slice<const char*>(s2, s2 + n-1));
	return result;
}

string &operator<<(string &s1, string s2)
{
	s1.push_back(s2);
	return s1;
}

string &operator<<(string &s1, char s2)
{
	s1.push_back(s2);
	return s1;
}

string &operator<<(string &s1, bool s2)
{
	if (s2)
	{
		const char *v = "true";
		s1.push_back(slice<const char *>(v, v+3));
	}
	else
	{
		const char *v = "false";
		s1.push_back(slice<const char *>(v, v+4));
	}

	return s1;
}

string &operator<<(string &s1, int s2)
{
	s1.reserve(s1.size() + 12);
	s1.alloc_back(snprintf(s1.data+s1.size(), 12, "%d", s2));
	return s1;
}

string &operator<<(string &s1, short s2)
{
	s1.reserve(s1.size() + 7);
	snprintf(s1.data + s1.size(), 7, "%hd", s2);
	return s1;
}

string &operator<<(string &s1, long s2)
{
	s1.reserve(s1.size() + 21);
	snprintf(s1.data + s1.size(), 21, "%ld", s2);
	return s1;
}

string &operator<<(string &s1, long long s2)
{
	s1.reserve(s1.size() + 21);
	snprintf(s1.data + s1.size(), 21, "%lld", s2);
	return s1;
}

string &operator<<(string &s1, unsigned char s2)
{
	s1.reserve(s1.size() + 5);
	snprintf(s1.data + s1.size(), 5, "%hu", s2);
	return s1;
}

string &operator<<(string &s1, unsigned int s2)
{
	s1.reserve(s1.size() + 12);
	snprintf(s1.data + s1.size(), 12, "%u", s2);
	return s1;
}

string &operator<<(string &s1, unsigned short s2)
{
	s1.reserve(s1.size() + 7);
	snprintf(s1.data + s1.size(), 7, "%hu", s2);
	return s1;
}

string &operator<<(string &s1, unsigned long s2)
{
	s1.reserve(s1.size() + 21);
	snprintf(s1.data + s1.size(), 21, "%lu", s2);
	return s1;
}

string &operator<<(string &s1, unsigned long long s2)
{
	s1.reserve(s1.size() + 21);
	snprintf(s1.data + s1.size(), 21, "%llu", s2);
	return s1;
}

string &operator<<(string &s1, float s2)
{
	s1.reserve(s1.size() + 32);
	snprintf(s1.data + s1.size(), 32, "%f", s2);
	return s1;
}

string &operator<<(string &s1, double s2)
{
	s1.reserve(s1.size() + 32);
	snprintf(s1.data + s1.size(), 32, "%f", s2);
	return s1;
}

string &operator<<(string &s1, const char *s2)
{
	s1.push_back(slice<const char *>(s2, s2 + strlen(s2)-1));
	return s1;
}

string &operator<<(string &s1, char *s2)
{
	s1.push_back(slice<char *>(s2, s2 + strlen(s2)-1));
	return s1;
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
