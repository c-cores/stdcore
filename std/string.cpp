#include <std/string.h>
#include <std/fill.h>

namespace core
{

string::string()
{
}

string::string(const char *cstr) : array<char>(wrapstr(cstr))
{
}

string::string(const char *cstr, int n) : array<char>(wrapstr(cstr, n))
{
}

string::string(char cstr) : array<char>(cstr)
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
	array<char>::operator=(wrapstr(str));
	return *this;
}

string &string::operator=(char *str)
{
	array<char>::operator=(wrapstr(str));
	return *this;
}

string &string::operator+=(const char *str)
{
	array<char>::append_back(wrapstr(str));
	return *this;
}

string &string::operator+=(char *str)
{
	array<char>::append_back(wrapstr(str));
	return *this;
}

string &string::operator+=(const string &str)
{
	array<char>::append_back(str);
	return *this;
}

string string::escaped()
{
	string result;
	result.reserve(size());
	for (iterator i = begin(); i != end(); i++)
	{
		char c = *i;
		switch (c)
		{
		case '\?': result.append_back(wrapstr("\\?")); break;
		case '\\': result.append_back(wrapstr("\\\\")); break;
		case '\a': result.append_back(wrapstr("\\a")); break;
		case '\b': result.append_back(wrapstr("\\b")); break;
		case '\f': result.append_back(wrapstr("\\f")); break;
		case '\n': result.append_back(wrapstr("\\n")); break;
		case '\r': result.append_back(wrapstr("\\r")); break;
		case '\t': result.append_back(wrapstr("\\t")); break;
		case '\v': result.append_back(wrapstr("\\v")); break;
		case '\0': result.append_back(wrapstr("\\0")); break;
		default: result.push_back(c); break;
		}
	}
	return result;
}

string string::unescaped()
{
	string result;
	result.reserve(size());
	bool escaped = false;
	for (iterator i = begin(); i != end(); i++)
	{
		char c = *i;
		if (escaped)
		{
			switch (c)
			{
			case '?': result.push_back('?'); break;
			case '\\': result.push_back('\\'); break;
			case 'a': result.push_back('\a'); break;
			case 'b': result.push_back('\b'); break;
			case 'f': result.push_back('\f'); break;
			case 'n': result.push_back('\n'); break;
			case 'r': result.push_back('\r'); break;
			case 't': result.push_back('\t'); break;
			case 'v': result.push_back('\v'); break;
			case '0': result.push_back('\0'); break;
			default: result.push_back(c); break;
			}
			escaped = false;
		}
		else if (c == '\\')
			escaped = true;
		else
			result.push_back(c);
	}
	return result;
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
	result.append_back(wrapstr(s2, n));
	return result;
}

string operator+(const string &s1, char *s2)
{
	string result;
	int n = strlen(s2);
	result.reserve(s1.size() + n);
	result.append_back(s1);
	result.append_back(wrapstr(s2, n));
	return result;
}

string operator+(const string &s1, char s2)
{
	string result;
	result.reserve(s1.size() + 1);
	result.append_back(s1);
	result.push_back(s2);
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
	s1.append_back(wrapstr(v, 4+(1-s2)));
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
	s1.reserve(s1.size() + 12);
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
	s1.reserve(s1.size() + 12);
	s1.alloc_back_unsafe(itoa((unsigned int)s2, s1.data + s1.size()));
	return s1;
}

string &operator<<(string &s1, unsigned long long s2)
{
	s1.reserve(s1.size() + 21);
	s1.alloc_back_unsafe(itoa(s2, s1.data + s1.size()));
	return s1;
}

string &operator<<(string &s1, options<int> s2)
{
	switch (s2.radix)
	{
	case 2:
		s1.reserve(s1.size() + 33);
		s1.alloc_back_unsafe(itob(*s2.value, s1.data+s1.size()));
		break;
	case 16:
		s1.reserve(s1.size() + 9);
		s1.alloc_back_unsafe(itox(*s2.value, s1.data+s1.size()));
		break;
	default:
		s1.reserve(s1.size() + 12);
		s1.alloc_back_unsafe(itoa(*s2.value, s1.data+s1.size()));
	}

	return s1;
}

string &operator<<(string &s1, options<short> s2)
{
	switch (s2.radix)
	{
	case 2:
		s1.reserve(s1.size() + 17);
		s1.alloc_back_unsafe(itob(*s2.value, s1.data+s1.size()));
		break;
	case 16:
		s1.reserve(s1.size() + 5);
		s1.alloc_back_unsafe(itox(*s2.value, s1.data+s1.size()));
		break;
	default:
		s1.reserve(s1.size() + 7);
		s1.alloc_back_unsafe(itoa(*s2.value, s1.data+s1.size()));
	}

	return s1;
}

string &operator<<(string &s1, options<long> s2)
{
	switch (s2.radix)
	{
	case 2:
		s1.reserve(s1.size() + 33);
		s1.alloc_back_unsafe(itob(*s2.value, s1.data+s1.size()));
		break;
	case 16:
		s1.reserve(s1.size() + 9);
		s1.alloc_back_unsafe(itox(*s2.value, s1.data+s1.size()));
		break;
	default:
		s1.reserve(s1.size() + 12);
		s1.alloc_back_unsafe(itoa((int)*s2.value, s1.data+s1.size()));
	}

	return s1;
}

string &operator<<(string &s1, options<long long> s2)
{
	switch (s2.radix)
	{
	case 2:
		s1.reserve(s1.size() + 65);
		s1.alloc_back_unsafe(itob(*s2.value, s1.data+s1.size()));
		break;
	case 16:
		s1.reserve(s1.size() + 17);
		s1.alloc_back_unsafe(itox(*s2.value, s1.data+s1.size()));
		break;
	default:
		s1.reserve(s1.size() + 21);
		s1.alloc_back_unsafe(itoa(*s2.value, s1.data+s1.size()));
	}

	return s1;
}

string &operator<<(string &s1, options<unsigned char> s2)
{
	switch (s2.radix)
	{
	case 2:
		s1.reserve(s1.size() + 9);
		s1.alloc_back_unsafe(itob(*s2.value, s1.data+s1.size()));
		break;
	case 16:
		s1.reserve(s1.size() + 3);
		s1.alloc_back_unsafe(itox(*s2.value, s1.data+s1.size()));
		break;
	default:
		s1.reserve(s1.size() + 5);
		s1.alloc_back_unsafe(itoa(*s2.value, s1.data+s1.size()));
	}
	return s1;
}

string &operator<<(string &s1, options<unsigned int> s2)
{
	switch (s2.radix)
	{
	case 2:
		s1.reserve(s1.size() + 32);
		s1.alloc_back_unsafe(itob(*s2.value, s1.data+s1.size()));
		break;
	case 16:
		s1.reserve(s1.size() + 8);
		s1.alloc_back_unsafe(itox(*s2.value, s1.data+s1.size()));
		break;
	default:
		s1.reserve(s1.size() + 12);
		s1.alloc_back_unsafe(itoa(*s2.value, s1.data+s1.size()));
	}
	return s1;
}

string &operator<<(string &s1, options<unsigned short> s2)
{
	switch (s2.radix)
	{
	case 2:
		s1.reserve(s1.size() + 16);
		s1.alloc_back_unsafe(itob(*s2.value, s1.data+s1.size()));
		break;
	case 16:
		s1.reserve(s1.size() + 4);
		s1.alloc_back_unsafe(itox(*s2.value, s1.data+s1.size()));
		break;
	default:
		s1.reserve(s1.size() + 7);
		s1.alloc_back_unsafe(itoa(*s2.value, s1.data+s1.size()));
	}
	return s1;
}

string &operator<<(string &s1, options<unsigned long> s2)
{
	switch (s2.radix)
	{
	case 2:
		s1.reserve(s1.size() + 32);
		s1.alloc_back_unsafe(itob(*s2.value, s1.data+s1.size()));
		break;
	case 16:
		s1.reserve(s1.size() + 8);
		s1.alloc_back_unsafe(itox(*s2.value, s1.data+s1.size()));
		break;
	default:
		s1.reserve(s1.size() + 12);
		s1.alloc_back_unsafe(itoa((unsigned int)*s2.value, s1.data+s1.size()));
	}
	return s1;
}

string &operator<<(string &s1, options<unsigned long long> s2)
{
	switch (s2.radix)
	{
	case 2:
		s1.reserve(s1.size() + 64);
		s1.alloc_back_unsafe(itob(*s2.value, s1.data+s1.size()));
		break;
	case 16:
		s1.reserve(s1.size() + 16);
		s1.alloc_back_unsafe(itox(*s2.value, s1.data+s1.size()));
		break;
	default:
		s1.reserve(s1.size() + 21);
		s1.alloc_back_unsafe(itoa(*s2.value, s1.data+s1.size()));
	}
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
	s1.append_back(wrapstr(s2));
	return s1;
}

string &operator<<(string &s1, char *s2)
{
	s1.append_back(wrapstr(s2));
	return s1;
}

string format_string(const string &str, const char *esc)
{
	string result;
	result.reserve(str.size()*2+2);
	result.push_back('\"');
	for (string::const_iterator i = str.begin(); i; i++)
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

template <>
string &operator<<(string &s1, const options<parsable<string> > &p)
{
	s1 << format_string(*p.value->obj, "\"");
	return s1;
}

bool operator==(string s1, string s2)
{
	return equal_to(s1, s2);
}

bool operator!=(string s1, string s2)
{
	return !equal_to(s1, s2);
}

bool operator<(string s1, string s2)
{
	return less_than(s1, s2);
}

bool operator>(string s1, string s2)
{
	return greater_than(s1, s2);
}

bool operator<=(string s1, string s2)
{
	return !greater_than(s1, s2);
}

bool operator>=(string s1, string s2)
{
	return !less_than(s1, s2);
}

bool operator==(string s1, const char* s2)
{
	return equal_to(s1, wrapstr(s2));
}

bool operator!=(string s1, const char* s2)
{
	return !equal_to(s1, wrapstr(s2));
}

bool operator<(string s1, const char* s2)
{
	return less_than(s1, wrapstr(s2));
}

bool operator>(string s1, const char* s2)
{
	return greater_than(s1, wrapstr(s2));
}

bool operator<=(string s1, const char* s2)
{
	return !greater_than(s1, wrapstr(s2));
}

bool operator>=(string s1, const char* s2)
{
	return !less_than(s1, wrapstr(s2));
}

bool operator==(const char* s1, string s2)
{
	return equal_to(wrapstr(s1), s2);
}

bool operator!=(const char* s1, string s2)
{
	return !equal_to(wrapstr(s1), s2);
}

bool operator<(const char* s1, string s2)
{
	return less_than(wrapstr(s1), s2);
}

bool operator>(const char* s1, string s2)
{
	return greater_than(wrapstr(s1), s2);
}

bool operator<=(const char* s1, string s2)
{
	return !greater_than(wrapstr(s1), s2);
}

bool operator>=(const char* s1, string s2)
{
	return !less_than(wrapstr(s1), s2);
}

template<class container>
bool operator==(string a0, slice<container> a1)
{
	return equal_to(a0, a1);
}

template<class container>
bool operator!=(string a0, slice<container> a1)
{
	return !equal_to(a0, a1);
}

template<class container>
bool operator<(string a0, slice<container> a1)
{
	return less_than(a0, a1);
}

template<class container>
bool operator>(string a0, slice<container> a1)
{
	return greater_than(a0, a1);
}

template<class container>
bool operator<=(string a0, slice<container> a1)
{
	return !greater_than(a0, a1);
}

template<class container>
bool operator>=(string a0, slice<container> a1)
{
	return !less_than(a0, a1);
}


template<class container>
bool operator==(slice<container> a0, string a1)
{
	return equal_to(a0, a1);
}

template<class container>
bool operator!=(slice<container> a0, string a1)
{
	return !equal_to(a0, a1);
}

template<class container>
bool operator<(slice<container> a0, string a1)
{
	return less_than(a0, a1);
}

template<class container>
bool operator>(slice<container> a0, string a1)
{
	return greater_than(a0, a1);
}

template<class container>
bool operator<=(slice<container> a0, string a1)
{
	return !greater_than(a0, a1);
}

template<class container>
bool operator>=(slice<container> a0, string a1)
{
	return !less_than(a0, a1);
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
	for (string::const_iterator i = line.begin(); i; i += length)
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

slice<range<const char*> > wrapstr(const char *cstr)
{
	return slice<range<const char*> >(range<const char*>(cstr, cstr+strlen(cstr)));
}

slice<range<char*> > wrapstr(char *cstr)
{
	return slice<range<char*> >(range<char*>(cstr, cstr+strlen(cstr)));
}

slice<range<const char*> > wrapstr(const char *cstr, int n)
{
	return slice<range<const char*> >(range<const char*>(cstr, cstr+n));
}

slice<range<char*> > wrapstr(char *cstr, int n)
{
	return slice<range<char*> >(range<char*>(cstr, cstr+n));
}

}
