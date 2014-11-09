/*
 * big.h
 * Blaze Game Engine v0.11
 *
 * Created by Ned Bingham on June 10, 2011.
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

#include <gmp.h>

#ifndef big_h
#define big_h

namespace core
{

struct Float
{
	Float();
	~Float();

	template <class t>
	Float(t f)
	{
		mpf_init_set_d(value, (double)f);
	}

	template <class t>
	Float(t f, unsigned long prec)
	{
		mpf_init2(value, prec);
		mpf_set_d(value, (double)f);
	}

	mpf_t value;

	template <class t>
	inline operator t()
	{
		return ((t)mpf_get_d(value));
	}

	inline operator __mpf_struct*()
	{
		return value;
	}

	unsigned long int size();
	unsigned long int prec();
	void set_prec(unsigned long int p);

	Float &operator=(Float f);

	template <class t>
	Float &operator=(t f)
	{
		mpf_set_d(value, (double)f);
		return *this;
	}

	Float &operator+=(Float f);
	Float &operator-=(Float f);
	Float &operator*=(Float f);
	Float &operator/=(Float f);

	Float &operator+=(float f);
	Float &operator-=(float f);
	Float &operator*=(float f);
	Float &operator/=(float f);

	Float &operator+=(double f);
	Float &operator-=(double f);
	Float &operator*=(double f);
	Float &operator/=(double f);
};

Float operator-(Float f);

Float operator+(Float f1, Float f2);
Float operator+(Float f1, float f2);
Float operator+(float f1, Float f2);
Float operator+(Float f1, double f2);
Float operator+(double f1, Float f2);

Float operator-(Float f1, Float f2);
Float operator-(Float f1, float f2);
Float operator-(float f1, Float f2);
Float operator-(Float f1, double f2);
Float operator-(double f1, Float f2);

Float operator*(Float f1, Float f2);
Float operator*(Float f1, float f2);
Float operator*(float f1, Float f2);
Float operator*(Float f1, double f2);
Float operator*(double f1, Float f2);

Float operator/(Float f1, Float f2);
Float operator/(Float f1, float f2);
Float operator/(float f1, Float f2);
Float operator/(Float f1, double f2);
Float operator/(double f1, Float f2);

bool operator==(Float f1, Float f2);
bool operator==(Float f1, float f2);
bool operator==(float f1, Float f2);
bool operator==(Float f1, double f2);
bool operator==(double f1, Float f2);

bool operator!=(Float f1, Float f2);
bool operator!=(Float f1, float f2);
bool operator!=(float f1, Float f2);
bool operator!=(Float f1, double f2);
bool operator!=(double f1, Float f2);

bool operator>(Float f1, Float f2);
bool operator>(Float f1, float f2);
bool operator>(float f1, Float f2);
bool operator>(Float f1, double f2);
bool operator>(double f1, Float f2);

bool operator<(Float f1, Float f2);
bool operator<(Float f1, float f2);
bool operator<(float f1, Float f2);
bool operator<(Float f1, double f2);
bool operator<(double f1, Float f2);

bool operator>=(Float f1, Float f2);
bool operator>=(Float f1, float f2);
bool operator>=(float f1, Float f2);
bool operator>=(Float f1, double f2);
bool operator>=(double f1, Float f2);

bool operator<=(Float f1, Float f2);
bool operator<=(Float f1, float f2);
bool operator<=(float f1, Float f2);
bool operator<=(Float f1, double f2);
bool operator<=(double f1, Float f2);


Float sqrt(Float f);
Float pow(Float f, unsigned long int p);
Float abs(Float f);

struct Int
{
	Int();
	~Int();

	template <class t>
	Int(t f)
	{
		mpz_init_set_si(value, (signed long int)f);
	}

	template <class t>
	Int(t f, unsigned long prec)
	{
		mpz_init2(value, prec);
		mpz_set_si(value, (signed long int)f);
	}

	mpz_t value;

	template <class t>
	inline operator t()
	{
		return ((t)mpz_get_si(value));
	}

	inline operator __mpz_struct*()
	{
		return value;
	}

	unsigned long int size();
	unsigned long int prec();
	void set_prec(unsigned long int p);

	Int &operator=(Int f);
	Int &operator=(signed long int f);

	Int &operator+=(Int f);
	Int &operator-=(Int f);
	Int &operator*=(Int f);
	Int &operator/=(Int f);
	Int &operator%=(Int f);
	Int &operator&=(Int f);
	Int &operator|=(Int f);
	Int &operator^=(Int f);
	Int &operator<<=(Int f);
	Int &operator>>=(Int f);

	Int &operator+=(signed long int f);
	Int &operator-=(signed long int f);
	Int &operator*=(signed long int f);
	Int &operator/=(signed long int f);
	Int &operator%=(unsigned long int f);
	Int &operator&=(unsigned long int f);
	Int &operator|=(unsigned long int f);
	Int &operator^=(unsigned long int f);
	Int &operator<<=(unsigned long int f);
	Int &operator>>=(unsigned long int f);
};

Int operator-(Int f);

Int operator+(Int f1, Int f2);
Int operator+(Int f1, signed long int f2);
Int operator+(signed long int f1, Int f2);

Int operator-(Int f1, Int f2);
Int operator-(Int f1, signed long int f2);
Int operator-(signed long int f1, Int f2);

Int operator*(Int f1, Int f2);
Int operator*(Int f1, signed long int f2);
Int operator*(signed long int f1, Int f2);

Int operator/(Int f1, Int f2);
Int operator/(Int f1, signed long int f2);
Int operator/(signed long int f1, Int f2);

Int operator%(Int f1, Int f2);
Int operator%(Int f1, unsigned long int f2);
Int operator%(unsigned long int f1, Int f2);

bool operator==(Int f1, Int f2);
bool operator==(Int f1, signed long int f2);
bool operator==(signed long int f1, Int f2);

bool operator!=(Int f1, Int f2);
bool operator!=(Int f1, signed long int f2);
bool operator!=(signed long int f1, Int f2);

bool operator>(Int f1, Int f2);
bool operator>(Int f1, signed long int f2);
bool operator>(signed long int f1, Int f2);

bool operator<(Int f1, Int f2);
bool operator<(Int f1, signed long int f2);
bool operator<(signed long int f1, Int f2);

bool operator>=(Int f1, Int f2);
bool operator>=(Int f1, signed long int f2);
bool operator>=(signed long int f1, Int f2);

bool operator<=(Int f1, Int f2);
bool operator<=(Int f1, signed long int f2);
bool operator<=(signed long int f1, Int f2);

Int operator&(Int f1, Int f2);
Int operator&(Int f1, unsigned long int f2);
Int operator&(unsigned long int f1, Int f2);

Int operator|(Int f1, Int f2);
Int operator|(Int f1, unsigned long int f2);
Int operator|(unsigned long int f1, Int f2);

Int operator^(Int f1, Int f2);
Int operator^(Int f1, unsigned long int f2);
Int operator^(unsigned long int f1, Int f2);

Int operator<<(Int f1, Int f2);
Int operator<<(Int f1, unsigned long int  f2);
Int operator<<(unsigned long int f1, Int f2);

Int operator>>(Int f1, Int f2);
Int operator>>(Int f1, unsigned long int  f2);
Int operator>>(unsigned long int f1, Int f2);

Int abs(Int f);
Int pow(Int f, unsigned long int p);
Int sqrt(Int f);
Int root(Int f, unsigned long int r);

}

#endif
