#include <core/string.h>
#include <core/fill.h>

namespace core
{

string::string()
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
	array<char>::append_back(slice<const char*>(str, str + strlen(str)-1));
	return *this;
}

string &string::operator+=(char *str)
{
	array<char>::append_back(slice<const char*>(str, str + strlen(str)-1));
	return *this;
}

string &string::operator+=(const string &str)
{
	array<char>::append_back(str);
	return *this;
}

char *string::c_str()
{
	reserve(size()+1);
	get(size()) = '\0';
	return data;
}

string operator+(const string &s1, const string &s2)
{
	string result;
	result.reserve(s1.size() + s2.size());
	result.append_back(s1);
	result.append_back(s2);
	return result;
}

string operator+(const string &s1, const char *s2)
{
	string result;
	int n = strlen(s2);
	result.reserve(s1.size() + n);
	result.append_back(s1);
	result.append_back(slice<const char*>(s2, s2 + n-1));
	return result;
}

string operator+(const string &s1, char *s2)
{
	string result;
	int n = strlen(s2);
	result.reserve(s1.size() + n);
	result.append_back(s1);
	result.append_back(slice<const char*>(s2, s2 + n-1));
	return result;
}

string &operator<<(string &s1, const string &s2)
{
	s1.append_back(s2);
	return s1;
}

string &operator<<(string &s1, char s2)
{
	s1.push_back(s2);
	return s1;
}

string &operator<<(string &s1, bool s2)
{
	const char *v = s2 ? "true" : "false";
	s1.append_back(slice<const char*>(v, v+3+(1-s2)));
	return s1;
}

string &operator<<(string &s1, int s2)
{
	s1.reserve(s1.size() + 12);
	s1.alloc_back_unsafe(itoa(s2, s1.data+s1.size()));
	return s1;
}

string &operator<<(string &s1, short s2)
{
	s1.reserve(s1.size() + 7);
	s1.alloc_back_unsafe(itoa((int)s2, s1.data + s1.size()));
	return s1;
}

string &operator<<(string &s1, long s2)
{
	s1.reserve(s1.size() + 21);
	s1.alloc_back_unsafe(itoa((int)s2, s1.data + s1.size()));
	return s1;
}

string &operator<<(string &s1, long long s2)
{
	s1.reserve(s1.size() + 21);
	s1.alloc_back_unsafe(itoa(s2, s1.data + s1.size()));
	return s1;
}

string &operator<<(string &s1, unsigned char s2)
{
	s1.reserve(s1.size() + 5);
	s1.alloc_back_unsafe(itoa((unsigned int)s2, s1.data + s1.size()));
	return s1;
}

string &operator<<(string &s1, unsigned int s2)
{
	s1.reserve(s1.size() + 12);
	s1.alloc_back_unsafe(itoa(s2, s1.data + s1.size()));
	return s1;
}

string &operator<<(string &s1, unsigned short s2)
{
	s1.reserve(s1.size() + 7);
	s1.alloc_back_unsafe(itoa((unsigned int)s2, s1.data + s1.size()));
	return s1;
}

string &operator<<(string &s1, unsigned long s2)
{
	s1.reserve(s1.size() + 21);
	s1.alloc_back_unsafe(itoa((unsigned int)s2, s1.data + s1.size()));
	return s1;
}

string &operator<<(string &s1, unsigned long long s2)
{
	s1.reserve(s1.size() + 21);
	s1.alloc_back_unsafe(itoa(s2, s1.data + s1.size()));
	return s1;
}

string &operator<<(string &s1, float s2)
{
	s1.reserve(s1.size() + 32);
	s1.alloc_back_unsafe(ftoa(s2, s1.data + s1.size()));
	return s1;
}

string &operator<<(string &s1, double s2)
{
	s1.reserve(s1.size() + 32);
	s1.alloc_back_unsafe(ftoa(s2, s1.data + s1.size()));
	return s1;
}

string &operator<<(string &s1, const char *s2)
{
	s1.append_back(slice<const char*>(s2, s2 + strlen(s2)-1));
	return s1;
}

string &operator<<(string &s1, char *s2)
{
	s1.append_back(slice<char*>(s2, s2 + strlen(s2)-1));
	return s1;
}

string format_string(const string &str, const char *esc)
{
	string result;
	result.reserve(str.size()*2+2);
	result.push_back('\"');
	for (string::const_iterator i = str.begin(); i != str.end(); i++)
	{
		bool do_esc = (*i == '\\');
		for (const char *p = esc; !do_esc && *p != '\0'; p++)
			do_esc = (*i == *p);

		if (do_esc)
			result.push_back('\\');

		result.push_back(*i);
	}
	result.push_back('\"');
	return result;
}

template <>
string &operator<<(string &s1, const parsable<string> &p)
{
	s1 << format_string(*p.obj, "\"");
	return s1;
}

bool operator==(string s1, string s2)
{
	return (compare(s1, s2) == 0);
}

bool operator!=(string s1, string s2)
{
	return (compare(s1, s2) != 0);
}

bool operator<(string s1, string s2)
{
	return (compare(s1, s2) < 0);
}

bool operator>(string s1, string s2)
{
	return (compare(s1, s2) > 0);
}

bool operator<=(string s1, string s2)
{
	return (compare(s1, s2) <= 0);
}

bool operator>=(string s1, string s2)
{
	return (compare(s1, s2) >= 0);
}

bool operator==(string s1, const char* s2)
{
	return (compare(s1, slice<const char*>(s2, s2+strlen(s2))) == 0);
}

bool operator!=(string s1, const char* s2)
{
	return (compare(s1, slice<const char*>(s2, s2+strlen(s2))) != 0);
}

bool operator<(string s1, const char* s2)
{
	return (compare(s1, slice<const char*>(s2, s2+strlen(s2))) < 0);
}

bool operator>(string s1, const char* s2)
{
	return (compare(s1, slice<const char*>(s2, s2+strlen(s2))) > 0);
}

bool operator<=(string s1, const char* s2)
{
	return (compare(s1, slice<const char*>(s2, s2+strlen(s2))) <= 0);
}

bool operator>=(string s1, const char* s2)
{
	return (compare(s1, slice<const char*>(s2, s2+strlen(s2))) >= 0);
}

bool operator==(const char* s1, string s2)
{
	return (compare(slice<const char*>(s1, s1+strlen(s1)), s2) == 0);
}

bool operator!=(const char* s1, string s2)
{
	return (compare(slice<const char*>(s1, s1+strlen(s1)), s2) != 0);
}

bool operator<(const char* s1, string s2)
{
	return (compare(slice<const char*>(s1, s1+strlen(s1)), s2) < 0);
}

bool operator>(const char* s1, string s2)
{
	return (compare(slice<const char*>(s1, s1+strlen(s1)), s2) > 0);
}

bool operator<=(const char* s1, string s2)
{
	return (compare(slice<const char*>(s1, s1+strlen(s1)), s2) <= 0);
}

bool operator>=(const char* s1, string s2)
{
	return (compare(slice<const char*>(s1, s1+strlen(s1)), s2) >= 0);
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

int edit_distance(const string &s1, const string &s2)
{
	array<int> col;
	array<int> prev_col;

	col.append_back(fill<int>(s2.size()+1, 0));
	prev_col.reserve(s2.size()+1);
	for (int i = 0; i < s2.size()+1; i++)
		prev_col.push_back_unsafe(i);

	for (int i = 0; i < s1.size(); i++)
	{
		col[0] = i+1;

		for (int j = 0; j < s2.size(); j++)
			col[j+1] = min(min(prev_col[1 + j] + 1, col[j] + 1), prev_col[j] + (s1[i] == s2[j] ? 0 : 1));

		col.swap(prev_col);
	}

	return prev_col.back();
}

int get_column(const string &line, int index, int tab_width)
{
	int count = 0;
	for (int i = 0; i < line.size() && i < index; i++)
		count += (line[i] == '\t');

	return index + count*(tab_width-1);
}

string get_column_ptr(const string &line, int index)
{
	string result;
	result.reserve(index);
	for (int i = 0; i < line.size() && i < index; i++)
		result.push_back_unsafe(line[i] == '\t' ? '\t' : ' ');
	return result;
}

string line_wrap(const string &line, int length)
{
	string result;
	result.reserve(line.size() + line.size()/length);
	for (string::const_iterator i = line.begin(); i != line.end(); i += length)
	{
		result.append_back_unsafe(i.sub(length));
		result.push_back_unsafe('\n');
	}
	return result;
}

int itoa(int value, char *str)
{
	if (value < 0)
	{
		*str = '-';
		return itoa((unsigned int)-value, str+1)+1;
	}
	else
		return itoa((unsigned int)value, str);
}

int itoa(unsigned int value, char *str)
{
	char *end = str-1;	
	if (value == 0)
		*++end = '0';
	else do
	{
		char digit = value%10;
		value /= 10;
		*++end = '0' + digit;
	} while (value > 0);

	*(end+1) = '\0';
	int size = end-str+1;

	do
	{
		char temp = *end;
		*end = *str;
		*str = temp;
	} while (--end >= ++str);

	return size;
}

int itoa(long long value, char *str)
{
	if (value < 0)
	{
		*str = '-';
		return itoa((unsigned long long)-value, str+1)+1;
	}
	else
		return itoa((unsigned long long)value, str);
}

int itoa(unsigned long long value, char *str)
{
	char *end = str-1;	
	if (value == 0)
		*++end = '0';
	else do
	{
		char digit = value%10;
		value /= 10;
		*++end = '0' + digit;
	} while (value > 0);

	*(end+1) = '\0';
	int size = end-str+1;

	do
	{
		char temp = *end;
		*end = *str;
		*str = temp;
	} while (--end >= ++str);

	return size;
}

int itob(unsigned int value, char *str)
{
	char *end = str-1;
	while (value != 0)
	{
		*++end = '0' + (value & 1);
		value >>= 1;
	}

	*(end+1) = '\0';
	int size = end-str+1;

	do
	{
		char temp = *end;
		*end = *str;
		*str = temp;
	} while (--end >= ++str);

	return size;
}

int itox(unsigned int value, char *str)
{
	char *end = str-1;
	while (value != 0)
	{
		int digit = value%16;
		value /= 16;

		*++end = digit < 10 ? '0' + digit : 'a' + digit-10;
	}

	*(end+1) = '\0';
	int size = end-str+1;

	do
	{
		char temp = *end;
		*end = *str;
		*str = temp;
	} while (--end >= ++str);

	return size;
}

int ftoa(float value, char *str)
{
	char *end = str-1;
	switch (fpclassify(value))
	{
	case FP_INFINITE:
		if (signbit(value))
			*++end = '-';
		*++end = 'i';
		*++end = 'n';
		*++end = 'f';
		*++end = '\0';
		return end-str;
	case FP_NAN:
		*++end = 'N';
		*++end = 'a';
		*++end = 'N';
		*++end = '\0';
		return end-str;
	case FP_ZERO:
		*++end = '0';
		*++end = '\0';
		return 1;
	default:
		if (signbit(value))
		{
			*++end = '-';
			value = -value;
		}

		int exp = (int)log10f(value);
		float sig = value/pow(10.0f, (float)exp);
	
		int digit = (sig+1e-2f);
		sig = (sig - (float)digit)*10.0f;
		*++end = '0' + digit;
		
		if (end - str < 8 && sig > 1e-2f)
		{
			*++end = '.';
			do
			{
				digit = (sig+1e-2f);
				sig = (sig - (float)digit)*10.0f;
				*++end = '0' + digit;
			} while (end-str < 8 && sig > 1e-2f);
		}
	
		if (exp != 0)
		{
			*++end = 'e';
			end += itoa(exp, ++end);
		}
		else
			*++end = '\0';

		return end - str;
	}
}

int ftoa(double value, char *str)
{
	char *end = str-1;
	switch (fpclassify(value))
	{
	case FP_INFINITE:
		if (signbit(value))
			*++end = '-';
		*++end = 'i';
		*++end = 'n';
		*++end = 'f';
		*++end = '\0';
		return end-str;
	case FP_NAN:
		*++end = 'N';
		*++end = 'a';
		*++end = 'N';
		*++end = '\0';
		return end-str;
	case FP_ZERO:
		*++end = '0';
		*++end = '\0';
		return 1;
	default:
		if (signbit(value))
		{
			*++end = '-';
			value = -value;
		}

		int exp = (int)log10f(value);
		double sig = value/pow(10.0, (double)exp);
	
		int digit = (sig+1e-2);
		sig = (sig - (double)digit)*10.0;
		*++end = '0' + digit;
		
		if (end - str < 8 && sig > 1e-2)
		{
			*++end = '.';
			do
			{
				digit = (sig+1e-2);
				sig = (sig - (double)digit)*10.0;
				*++end = '0' + digit;
			} while (end-str < 8 && sig > 1e-2);
		}
	
		if (exp != 0)
		{
			*++end = 'e';
			end += itoa(exp, ++end);
		}
		else
			*++end = '\0';

		return end - str;
	}
}

}
