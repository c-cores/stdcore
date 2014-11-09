/*
 * ref.h
 * Blaze Game Engine v0.11
 *
 * Created by Ned Bingham on June 10, 2012.
 * Modified by Ned Bingham on June 10, 2012.
 * Copyright 2011 Sol Union. All rights reserved.
 *
 * Blaze Game Engine v0.11 is free software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * Blaze Game Engine v0.11 is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Blaze Game Engine v0.11.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "memory.h"

#ifndef ref_h
#define ref_h

namespace core
{

template <class t>
struct ref
{
	ref()
	{
		value = NULL;
	}
	ref(t &v)
	{
		value = &v;
	}
	ref(t *v)
	{
		value = v;
	}
	~ref()
	{
		value = NULL;
	}

	t *value;

	template <class t2>
	inline operator t2()
	{
		if (value != NULL)
			return ((t2)*value);
		else
			return (t2)0;
	}

	ref<t> &operator=(ref<t> r)
	{
		if (value != NULL && r.value != NULL)
			*value = *r.value;
		else
			value = r.value;
		return *this;
	}

	template <class t2>
	ref<t> &operator=(t2 r)
	{
		if (value != NULL)
			*value = r;
		return *this;
	}

	template <class t2>
	ref<t> &operator+=(t2 r)
	{
		*this = *this + r;
		return *this;
	}

	template <class t2>
	ref<t> &operator-=(t2 r)
	{
		*this = *this - r;
		return *this;
	}

	template <class t2>
	ref<t> &operator*=(t2 r)
	{
		*this = *this * r;
		return *this;
	}

	template <class t2>
	ref<t> &operator/=(t2 r)
	{
		*this = *this / r;
		return *this;
	}

	template <class t2>
	ref<t> &operator%=(t2 r)
	{
		*this = *this % r;
		return *this;
	}

	template <class t2>
	ref<t> &operator&=(t2 r)
	{
		*this = *this & r;
		return *this;
	}

	template <class t2>
	ref<t> &operator|=(t2 r)
	{
		*this = *this | r;
		return *this;
	}

	template <class t2>
	ref<t> &operator^=(t2 r)
	{
		*this = *this ^ r;
		return *this;
	}

	template <class t2>
	ref<t> &operator<<=(t2 r)
	{
		*this = *this << r;
		return *this;
	}

	template <class t2>
	ref<t> &operator>>=(t2 r)
	{
		*this = *this >> r;
		return *this;
	}
};

template <class t>
inline t operator-(ref<t> r)
{
	return -*r.value;
}

template <class t>
inline t operator+(ref<t> r1, ref<t> r2)
{
	return (*r1.value + *r2.value);
}

template <class t>
inline t operator+(ref<t> r1, t r2)
{
	return (*r1.value + r2);
}

template <class t>
inline t operator+(t r1, ref<t> r2)
{
	return (r1 + *r2.value);
}

template <class t>
inline t operator-(ref<t> r1, ref<t> r2)
{
	return (*r1.value - *r2.value);
}

template <class t>
inline t operator-(ref<t> r1, t r2)
{
	return (*r1.value - r2);
}

template <class t>
inline t operator-(t r1, ref<t> r2)
{
	return (r1 - *r2.value);
}

template <class t>
inline t operator*(ref<t> r1, ref<t> r2)
{
	return (*r1.value * *r2.value);
}

template <class t>
inline t operator*(ref<t> r1, t r2)
{
	return (*r1.value * r2);
}

template <class t>
inline t operator*(t r1, ref<t> r2)
{
	return (r1 * *r2.value);
}

template <class t>
inline t operator/(ref<t> r1, ref<t> r2)
{
	return (*r1.value / *r2.value);
}

template <class t>
inline t operator/(ref<t> r1, t r2)
{
	return (*r1.value / r2);
}

template <class t>
inline t operator/(t r1, ref<t> r2)
{
	return (r1 / *r2.value);
}

template <class t>
inline t operator%(ref<t> r1, ref<t> r2)
{
	return (*r1.value % *r2.value);
}

template <class t>
inline t operator%(ref<t> r1, t r2)
{
	return (*r1.value % r2);
}

template <class t>
inline t operator%(t r1, ref<t> r2)
{
	return (r1 % *r2.value);
}

template <class t>
inline bool operator==(ref<t> r1, ref<t> r2)
{
	return (*r1.value == *r2.value);
}

template <class t>
inline bool operator==(ref<t> r1, t r2)
{
	return (*r1.value == r2);
}

template <class t>
inline bool operator==(t r1, ref<t> r2)
{
	return (r1 == *r2.value);
}

template <class t>
inline bool operator!=(ref<t> r1, ref<t> r2)
{
	return (*r1.value != *r2.value);
}

template <class t>
inline bool operator!=(ref<t> r1, t r2)
{
	return (*r1.value != r2);
}

template <class t>
inline bool operator!=(t r1, ref<t> r2)
{
	return (r1 != *r2.value);
}

template <class t>
inline bool operator>(ref<t> r1, ref<t> r2)
{
	return (*r1.value > *r2.value);
}

template <class t>
inline bool operator>(ref<t> r1, t r2)
{
	return (*r1.value > r2);
}

template <class t>
inline bool operator>(t r1, ref<t> r2)
{
	return (r1 > *r2.value);
}

template <class t>
inline bool operator<(ref<t> r1, ref<t> r2)
{
	return (*r1.value < *r2.value);
}

template <class t>
inline bool operator<(ref<t> r1, t r2)
{
	return (*r1.value < r2);
}

template <class t>
inline bool operator<(t r1, ref<t> r2)
{
	return (r1 < *r2.value);
}

template <class t>
inline bool operator>=(ref<t> r1, ref<t> r2)
{
	return (*r1.value >= *r2.value);
}

template <class t>
inline bool operator>=(ref<t> r1, t r2)
{
	return (*r1.value >= r2);
}

template <class t>
inline bool operator>=(t r1, ref<t> r2)
{
	return (r1 >= *r2.value);
}

template <class t>
inline bool operator<=(ref<t> r1, ref<t> r2)
{
	return (*r1.value <= *r2.value);
}

template <class t>
inline bool operator<=(ref<t> r1, t r2)
{
	return (*r1.value <= r2);
}

template <class t>
inline bool operator<=(t r1, ref<t> r2)
{
	return (r1 <= *r2.value);
}

template <class t>
inline bool operator&(ref<t> r1, ref<t> r2)
{
	return (*r1.value & *r2.value);
}

template <class t>
inline bool operator&(ref<t> r1, t r2)
{
	return (*r1.value & r2);
}

template <class t>
inline bool operator&(t r1, ref<t> r2)
{
	return (r1 & *r2.value);
}

template <class t>
inline bool operator|(ref<t> r1, ref<t> r2)
{
	return (*r1.value | *r2.value);
}

template <class t>
inline bool operator|(ref<t> r1, t r2)
{
	return (*r1.value | r2);
}

template <class t>
inline bool operator|(t r1, ref<t> r2)
{
	return (r1 | *r2.value);
}

template <class t>
inline bool operator^(ref<t> r1, ref<t> r2)
{
	return (*r1.value ^ *r2.value);
}

template <class t>
inline bool operator^(ref<t> r1, t r2)
{
	return (*r1.value ^ r2);
}

template <class t>
inline bool operator^(t r1, ref<t> r2)
{
	return (r1 ^ *r2.value);
}

template <class t>
inline bool operator<<(ref<t> r1, ref<t> r2)
{
	return (*r1.value << *r2.value);
}

template <class t>
inline bool operator<<(ref<t> r1, t r2)
{
	return (*r1.value << r2);
}

template <class t>
inline bool operator<<(t r1, ref<t> r2)
{
	return (r1 << *r2.value);
}

template <class t>
inline bool operator>>(ref<t> r1, ref<t> r2)
{
	return (*r1.value >> *r2.value);
}

template <class t>
inline bool operator>>(ref<t> r1, t r2)
{
	return (*r1.value >> r2);
}

template <class t>
inline bool operator>>(t r1, ref<t> r2)
{
	return (r1 >> *r2.value);
}

}

#endif
