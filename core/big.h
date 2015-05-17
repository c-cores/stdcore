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

#include "array.h"
#include "file.h"

#ifndef big_h
#define big_h

namespace core
{

struct Integer
{
	Integer();
	Integer(int i);
	Integer(unsigned int i);
	Integer(long long i);
	Integer(unsigned long long i);
	Integer(float i);
	Integer(double i);
	~Integer();

	int sign;
	array<int> data;

	operator double();

	template <class t>
	operator t()
	{
		return (t)((double)*this);
	}

	int size();

	Integer &operator=(Integer i);

	Integer &operator+=(Integer i);
	Integer &operator-=(Integer i);
	Integer &operator*=(Integer i);
	Integer &operator/=(Integer i);
	Integer &operator%=(Integer i);
	Integer &operator&=(Integer i);
	Integer &operator|=(Integer i);
	Integer &operator^=(Integer i);
	Integer &operator<<=(Integer i);
	Integer &operator>>=(Integer i);
};

file &operator<<(file &f, Integer i);

Integer operator-(Integer i);

Integer operator+(Integer i1, Integer i2);
Integer operator-(Integer i1, Integer i2);
Integer operator*(Integer i1, Integer i2);
Integer operator/(Integer i1, Integer i2);
Integer operator%(Integer i1, Integer i2);
Integer operator&(Integer i1, Integer i2);
Integer operator|(Integer i1, Integer i2);
Integer operator^(Integer i1, Integer i2);
Integer operator>>(Integer i1, int i2);
Integer operator<<(Integer i1, int i2);

bool operator==(Integer i1, Integer i2);
bool operator!=(Integer i1, Integer i2);
bool operator>(Integer i1, Integer i2);
bool operator<(Integer i1, Integer i2);
bool operator>=(Integer i1, Integer i2);
bool operator<=(Integer i1, Integer i2);

Integer abs(Integer i);
Integer pow(Integer i, int p);
Integer sqrt(Integer i);
Integer root(Integer i, int r);

struct Real
{
	Real();
	Real(int f);
	Real(unsigned int f);
	Real(long long f);
	Real(unsigned long long f);
	Real(float f);
	Real(double f);
	~Real();

	int exp;
	int limit;
	Integer num;

	operator double();

	template <class t>
	operator t()
	{
		return (t)((double)*this);
	}

	void realign();

	Real &operator=(Real f);

	Real &operator=(double f);

	Real &operator+=(Real f);
	Real &operator-=(Real f);
	Real &operator*=(Real f);
	Real &operator/=(Real f);
};

file &operator<< (file &fin, Real f);

Real operator-(Real f);

Real operator+(Real f1, Real f2);
Real operator-(Real f1, Real f2);
Real operator*(Real f1, Real f2);
Real operator/(Real f1, Real f2);

bool operator==(Real f1, Real f2);
bool operator!=(Real f1, Real f2);
bool operator>(Real f1, Real f2);
bool operator<(Real f1, Real f2);
bool operator>=(Real f1, Real f2);
bool operator<=(Real f1, Real f2);

Real abs(Real f);
Real pow(Real f, int p);
Real sqrt(Real f);
Real root(Real f, int r);

}

#endif
