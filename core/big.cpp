/*
 * big.cpp
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

#include "big.h"
#include "math.h"

namespace core
{

Float::Float()
{
	mpf_init(value);
}

Float::~Float()
{
	mpf_clear(value);
}

unsigned long int Float::size()
{
	return mpf_get_prec(value)/8;
}

unsigned long int Float::prec()
{
	return mpf_get_prec(value);
}

void Float::set_prec(unsigned long int p)
{
	mpf_set_prec(value, p);
}

Float &Float::operator=(Float f)
{
	mpf_set(value, f.value);
	return *this;
}

Float &Float::operator+=(Float f)
{
	mpf_add(value, value, f.value);
	return *this;
}

Float &Float::operator-=(Float f)
{
	mpf_sub(value, value, f.value);
	return *this;
}

Float &Float::operator*=(Float f)
{
	mpf_mul(value, value, f.value);
	return *this;
}

Float &Float::operator/=(Float f)
{
	mpf_div(value, value, f.value);
	return *this;
}

Float &Float::operator+=(float f)
{
	mpf_add(value, value, Float(f).value);
	return *this;
}

Float &Float::operator-=(float f)
{
	mpf_sub(value, value, Float(f).value);
	return *this;
}

Float &Float::operator*=(float f)
{
	mpf_mul(value, value, Float(f).value);
	return *this;
}

Float &Float::operator/=(float f)
{
	mpf_div(value, value, Float(f).value);
	return *this;
}

Float &Float::operator+=(double f)
{
	mpf_add(value, value, Float(f).value);
	return *this;
}

Float &Float::operator-=(double f)
{
	mpf_sub(value, value, Float(f).value);
	return *this;
}

Float &Float::operator*=(double f)
{
	mpf_mul(value, value, Float(f).value);
	return *this;
}

Float &Float::operator/=(double f)
{
	mpf_div(value, value, Float(f).value);
	return *this;
}

Float operator-(Float f)
{
	Float result(0, f.prec());
	mpf_neg(result.value, f.value);
	return result;
}

Float operator+(Float f1, Float f2)
{
	Float result(0, max(f1.prec(), f2.prec()));
	mpf_add(result, f1.value, f2.value);
	return result;
}

Float operator+(Float f1, float f2)
{
	Float result(0, f1.prec());
	mpf_add(result, f1.value, Float(f2).value);
	return result;
}

Float operator+(float f1, Float f2)
{
	Float result(0, f2.prec());
	mpf_add(result, Float(f1).value, f2.value);
	return result;
}

Float operator+(Float f1, double f2)
{
	Float result(0, f1.prec());
	mpf_add(result, f1.value, Float(f2).value);
	return result;
}

Float operator+(double f1, Float f2)
{
	Float result(0, f2.prec());
	mpf_add(result, Float(f1).value, f2.value);
	return result;
}

Float operator-(Float f1, Float f2)
{
	Float result(0, max(f1.prec(), f2.prec()));
	mpf_sub(result, f1.value, f2.value);
	return result;
}

Float operator-(Float f1, float f2)
{
	Float result(0, f1.prec());
	mpf_sub(result, f1.value, Float(f2).value);
	return result;
}

Float operator-(float f1, Float f2)
{
	Float result(0, f2.prec());
	mpf_sub(result, Float(f1).value, f2.value);
	return result;
}

Float operator-(Float f1, double f2)
{
	Float result(0, f1.prec());
	mpf_sub(result, f1.value, Float(f2).value);
	return result;
}

Float operator-(double f1, Float f2)
{
	Float result(0, f2.prec());
	mpf_sub(result, Float(f1).value, f2.value);
	return result;
}

Float operator*(Float f1, Float f2)
{
	Float result(0, max(f1.prec(), f2.prec()));
	mpf_mul(result, f1.value, f2.value);
	return result;
}

Float operator*(Float f1, float f2)
{
	Float result(0, f1.prec());
	mpf_mul(result, f1.value, Float(f2).value);
	return result;
}

Float operator*(float f1, Float f2)
{
	Float result(0, f2.prec());
	mpf_mul(result, Float(f1).value, f2.value);
	return result;
}

Float operator*(Float f1, double f2)
{
	Float result(0, f1.prec());
	mpf_mul(result, f1.value, Float(f2).value);
	return result;
}

Float operator*(double f1, Float f2)
{
	Float result(0, f2.prec());
	mpf_mul(result, Float(f1).value, f2.value);
	return result;
}

Float operator/(Float f1, Float f2)
{
	Float result(0, max(f1.prec(), f2.prec()));
	mpf_div(result, f1.value, f2.value);
	return result;
}

Float operator/(Float f1, float f2)
{
	Float result(0, f1.prec());
	mpf_div(result, f1.value, Float(f2).value);
	return result;
}

Float operator/(float f1, Float f2)
{
	Float result(0, f2.prec());
	mpf_div(result, Float(f1).value, f2.value);
	return result;
}

Float operator/(Float f1, double f2)
{
	Float result(0, f1.prec());
	mpf_div(result, f1.value, Float(f2).value);
	return result;
}

Float operator/(double f1, Float f2)
{
	Float result(0, f2.prec());
	mpf_div(result, Float(f1).value, f2.value);
	return result;
}

bool operator==(Float f1, Float f2)
{
	return (mpf_cmp(f1.value, f2.value) == 0);
}

bool operator==(Float f1, float f2)
{
	return (mpf_cmp_d(f1.value, (double)f2) == 0);
}

bool operator==(float f1, Float f2)
{
	return (mpf_cmp_d(f2.value, (double)f1) == 0);
}

bool operator==(Float f1, double f2)
{
	return (mpf_cmp_d(f1.value, (double)f2) == 0);
}

bool operator==(double f1, Float f2)
{
	return (mpf_cmp_d(f2.value, (double)f1) == 0);
}

bool operator!=(Float f1, Float f2)
{
	return (mpf_cmp(f1.value, f2.value) != 0);
}

bool operator!=(Float f1, float f2)
{
	return (mpf_cmp_d(f1.value, (double)f2) != 0);
}

bool operator!=(float f1, Float f2)
{
	return (mpf_cmp_d(f2.value, (double)f1) != 0);
}

bool operator!=(Float f1, double f2)
{
	return (mpf_cmp_d(f1.value, (double)f2) != 0);
}

bool operator!=(double f1, Float f2)
{
	return (mpf_cmp_d(f2.value, (double)f1) != 0);
}

bool operator>(Float f1, Float f2)
{
	return (mpf_cmp(f1.value, f2.value) > 0);
}

bool operator>(Float f1, float f2)
{
	return (mpf_cmp_d(f1.value, (double)f2) > 0);
}

bool operator>(float f1, Float f2)
{
	return (-mpf_cmp_d(f2.value, (double)f1) > 0);
}

bool operator>(Float f1, double f2)
{
	return (mpf_cmp_d(f1.value, (double)f2) > 0);
}

bool operator>(double f1, Float f2)
{
	return (-mpf_cmp_d(f2.value, (double)f1) > 0);
}

bool operator<(Float f1, Float f2)
{
	return (mpf_cmp(f1.value, f2.value) < 0);
}

bool operator<(Float f1, float f2)
{
	return (mpf_cmp_d(f1.value, (double)f2) < 0);
}

bool operator<(float f1, Float f2)
{
	return (-mpf_cmp_d(f2.value, (double)f1) < 0);
}

bool operator<(Float f1, double f2)
{
	return (mpf_cmp_d(f1.value, (double)f2) < 0);
}

bool operator<(double f1, Float f2)
{
	return (-mpf_cmp_d(f2.value, (double)f1) < 0);
}

bool operator>=(Float f1, Float f2)
{
	return (mpf_cmp(f1.value, f2.value) >= 0);
}

bool operator>=(Float f1, float f2)
{
	return (mpf_cmp_d(f1.value, (double)f2) >= 0);
}

bool operator>=(float f1, Float f2)
{
	return (-mpf_cmp_d(f2.value, (double)f1) >= 0);
}

bool operator>=(Float f1, double f2)
{
	return (mpf_cmp_d(f1.value, (double)f2) >= 0);
}

bool operator>=(double f1, Float f2)
{
	return (-mpf_cmp_d(f2.value, (double)f1) >= 0);
}

bool operator<=(Float f1, Float f2)
{
	return (mpf_cmp(f1.value, f2.value) <= 0);
}

bool operator<=(Float f1, float f2)
{
	return (mpf_cmp_d(f1.value, (double)f2) <= 0);
}

bool operator<=(float f1, Float f2)
{
	return (-mpf_cmp_d(f2.value, (double)f1) <= 0);
}

bool operator<=(Float f1, double f2)
{
	return (mpf_cmp_d(f1.value, (double)f2) <= 0);
}

bool operator<=(double f1, Float f2)
{
	return (-mpf_cmp_d(f2.value, (double)f1) <= 0);
}

Float sqrt(Float f)
{
	Float result(0, f.prec());
	mpf_sqrt(result.value, f.value);
	return result;
}

Float pow(Float f, unsigned long int p)
{
	Float result(0, f.prec());
	mpf_pow_ui(result.value, f.value, p);
	return result;
}

Float abs(Float f)
{
	Float result(0, f.prec());
	mpf_abs(result.value, f.value);
	return result;
}

// Integers

Int::Int()
{
	mpz_init(value);
}

Int::~Int()
{
	mpz_clear(value);
}

unsigned long int Int::size()
{
	return mpz_sizeinbase(value, 2)/8;
}

unsigned long int Int::prec()
{
	return mpz_sizeinbase(value, 2);
}

void Int::set_prec(unsigned long int p)
{
	mpz_realloc2(value, p);
}

Int &Int::operator=(Int f)
{
	mpz_set(value, f.value);
	return *this;
}

Int &Int::operator=(signed long int f)
{
	mpz_set_d(value, f);
	return *this;
}

Int &Int::operator+=(Int f)
{
	mpz_add(value, value, f.value);
	return *this;
}

Int &Int::operator-=(Int f)
{
	mpz_sub(value, value, f.value);
	return *this;
}

Int &Int::operator*=(Int f)
{
	mpz_mul(value, value, f.value);
	return *this;
}

Int &Int::operator/=(Int f)
{
	mpz_div(value, value, f.value);
	return *this;
}

Int &Int::operator%=(Int f)
{
	mpz_mod(value, value, f.value);
	return *this;
}

Int &Int::operator&=(Int f)
{
	mpz_and(value, value, f.value);
	return *this;
}

Int &Int::operator|=(Int f)
{
	mpz_ior(value, value, f.value);
	return *this;
}

Int &Int::operator^=(Int f)
{
	mpz_xor(value, value, f.value);
	return *this;
}

Int &Int::operator<<=(Int f)
{
	mpz_mul_2exp(value, value, (unsigned long int)f);
	return *this;
}

Int &Int::operator>>=(Int f)
{
	mpz_tdiv_q_2exp(value, value, (unsigned long int)f);
	return *this;
}

Int &Int::operator+=(signed long int f)
{
	mpz_add(value, value, Int(f).value);
	return *this;
}

Int &Int::operator-=(signed long int f)
{
	mpz_sub(value, value, Int(f).value);
	return *this;
}

Int &Int::operator*=(signed long int f)
{
	mpz_mul(value, value, Int(f).value);
	return *this;
}

Int &Int::operator/=(signed long int f)
{
	mpz_div(value, value, Int(f).value);
	return *this;
}

Int &Int::operator%=(unsigned long int f)
{
	mpz_mod_ui(value, value, f);
	return *this;
}

Int &Int::operator&=(unsigned long int f)
{
	mpz_and(value, value, Int(f).value);
	return *this;
}

Int &Int::operator|=(unsigned long int f)
{
	mpz_ior(value, value, Int(f).value);
	return *this;
}

Int &Int::operator^=(unsigned long int f)
{
	mpz_xor(value, value, Int(f).value);
	return *this;
}

Int &Int::operator<<=(unsigned long int f)
{
	mpz_mul_2exp(value, value, f);
	return *this;
}

Int &Int::operator>>=(unsigned long int f)
{
	mpz_tdiv_q_2exp(value, value, f);
	return *this;
}

Int operator-(Int f)
{
	Int result(0, f.prec());
	mpz_neg(result.value, f.value);
	return result;
}

Int operator+(Int f1, Int f2)
{
	Int result(0, max(f1.prec(), f2.prec()));
	mpz_add(result, f1.value, f2.value);
	return result;
}

Int operator+(Int f1, signed long int f2)
{
	Int result(0, f1.prec());
	mpz_add(result, f1.value, Int(f2).value);
	return result;
}

Int operator+(signed long int f1, Int f2)
{
	Int result(0, f2.prec());
	mpz_add(result, Int(f1).value, f2.value);
	return result;
}

Int operator-(Int f1, Int f2)
{
	Int result(0, max(f1.prec(), f2.prec()));
	mpz_sub(result, f1.value, f2.value);
	return result;
}

Int operator-(Int f1, signed long int f2)
{
	Int result(0, f1.prec());
	mpz_sub(result, f1.value, Int(f2).value);
	return result;
}

Int operator-(signed long int f1, Int f2)
{
	Int result(0, f2.prec());
	mpz_sub(result, Int(f1).value, f2.value);
	return result;
}

Int operator*(Int f1, Int f2)
{
	Int result(0, max(f1.prec(), f2.prec()));
	mpz_mul(result, f1.value, f2.value);
	return result;
}

Int operator*(Int f1, signed long int f2)
{
	Int result(0, f1.prec());
	mpz_mul(result, f1.value, Int(f2).value);
	return result;
}

Int operator*(signed long int f1, Int f2)
{
	Int result(0, f2.prec());
	mpz_mul(result, Int(f1).value, f2.value);
	return result;
}

Int operator/(Int f1, Int f2)
{
	Int result(0, max(f1.prec(), f2.prec()));
	mpz_div(result, f1.value, f2.value);
	return result;
}

Int operator/(Int f1, signed long int f2)
{
	Int result(0, f1.prec());
	mpz_div(result, f1.value, Int(f2).value);
	return result;
}

Int operator/(signed long int f1, Int f2)
{
	Int result(0, f2.prec());
	mpz_div(result, Int(f1).value, f2.value);
	return result;
}

Int operator%(Int f1, Int f2)
{
	Int result(0, max(f1.prec(), f2.prec()));
	mpz_mod(result.value, f1.value, f2.value);
	return result;
}

Int operator%(Int f1, unsigned long int f2)
{
	Int result(0, f1.prec());
	mpz_mod_ui(result.value, f1.value, f2);
	return result;
}

Int operator%(unsigned long int f1, Int f2)
{
	Int result(0, f2.prec());
	mpz_mod(result.value, Int(f1).value, f2.value);
	return result;
}

bool operator==(Int f1, Int f2)
{
	return (mpz_cmp(f1.value, f2.value) == 0);
}

bool operator==(Int f1, signed long int f2)
{
	return (mpz_cmp(f1.value, Int(f2).value) == 0);
}

bool operator==(signed long int f1, Int f2)
{
	return (mpz_cmp(f2.value, Int(f1).value) == 0);
}

bool operator!=(Int f1, Int f2)
{
	return (mpz_cmp(f1.value, f2.value) != 0);
}

bool operator!=(Int f1, signed long int f2)
{
	return (mpz_cmp(f1.value, Int(f2).value) != 0);
}

bool operator!=(signed long int f1, Int f2)
{
	return (mpz_cmp(f2.value, Int(f1).value) != 0);
}

bool operator>(Int f1, Int f2)
{
	return (mpz_cmp(f1.value, f2.value) > 0);
}

bool operator>(Int f1, signed long int f2)
{
	return (mpz_cmp(f1.value, Int(f2).value) > 0);
}

bool operator>(signed long int f1, Int f2)
{
	return (-mpz_cmp(f2.value, Int(f1).value) > 0);
}

bool operator<(Int f1, Int f2)
{
	return (mpz_cmp(f1.value, f2.value) < 0);
}

bool operator<(Int f1, signed long int f2)
{
	return (mpz_cmp(f1.value, Int(f2).value) < 0);
}

bool operator<(signed long int f1, Int f2)
{
	return (-mpz_cmp(f2.value, Int(f1).value) < 0);
}

bool operator>=(Int f1, Int f2)
{
	return (mpz_cmp(f1.value, f2.value) >= 0);
}

bool operator>=(Int f1, signed long int f2)
{
	return (mpz_cmp(f1.value, Int(f2).value) >= 0);
}

bool operator>=(signed long int f1, Int f2)
{
	return (-mpz_cmp(f2.value, Int(f1).value) >= 0);
}

bool operator<=(Int f1, Int f2)
{
	return (mpz_cmp(f1.value, f2.value) <= 0);
}

bool operator<=(Int f1, signed long int f2)
{
	return (mpz_cmp(f1.value, Int(f2).value) <= 0);
}

bool operator<=(signed long int f1, Int f2)
{
	return (-mpz_cmp(f2.value, Int(f1).value) <= 0);
}

Int operator&(Int f1, Int f2)
{
	Int result(0, max(f1.prec(), f2.prec()));
	mpz_and(result.value, f1.value, f2.value);
	return result;
}

Int operator&(Int f1, signed long int f2)
{
	Int result(0, f1.prec());
	mpz_and(result.value, f1.value, Int(f2).value);
	return result;
}

Int operator&(signed long int  f1, Int f2)
{
	Int result(0, f2.prec());
	mpz_and(result.value, Int(f1).value, f2.value);
	return result;
}


Int operator|(Int f1, Int f2)
{
	Int result(0, max(f1.prec(), f2.prec()));
	mpz_ior(result.value, f1.value, f2.value);
	return result;
}

Int operator|(Int f1, signed long int  f2)
{
	Int result(0, f1.prec());
	mpz_ior(result.value, f1.value, Int(f2).value);
	return result;
}

Int operator|(signed long int  f1, Int f2)
{
	Int result(0, f2.prec());
	mpz_ior(result.value, Int(f1).value, f2.value);
	return result;
}

Int operator^(Int f1, Int f2)
{
	Int result(0, max(f1.prec(), f2.prec()));
	mpz_xor(result.value, f1.value, f2.value);
	return result;
}

Int operator^(Int f1, signed long int  f2)
{
	Int result(0, f1.prec());
	mpz_xor(result.value, f1.value, Int(f2).value);
	return result;
}

Int operator^(signed long int  f1, Int f2)
{
	Int result(0, f2.prec());
	mpz_xor(result.value, Int(f1).value, f2.value);
	return result;
}

Int operator<<(Int f1, Int f2)
{
	Int result(0, f1.prec());
	mpz_mul_2exp(result, f1.value, (unsigned long int)f2);
	return result;
}

Int operator<<(Int f1, unsigned long int f2)
{
	Int result(0, f1.prec());
	mpz_mul_2exp(result, f1.value, f2);
	return result;
}

Int operator<<(unsigned long int f1, Int f2)
{
	Int result(0, sizeof(unsigned long int)*8);
	mpz_mul_2exp(result, Int(f1).value, (unsigned long int)f2);
	return result;
}

Int operator>>(Int f1, Int f2)
{
	Int result(0, f1.prec());
	mpz_tdiv_q_2exp(result, f1.value, (unsigned long int)f2);
	return result;
}

Int operator>>(Int f1, unsigned long int f2)
{
	Int result(0, f1.prec());
	mpz_tdiv_q_2exp(result, f1.value, f2);
	return result;
}

Int operator>>(unsigned long int f1, Int f2)
{
	Int result(0, sizeof(unsigned long int)*8);
	mpz_tdiv_q_2exp(result, Int(f1).value, (unsigned long int)f2);
	return result;
}

Int abs(Int f)
{
	Int result(0, f.prec());
	mpz_abs(result.value, f.value);
	return result;
}

Int pow(Int f, unsigned long int p)
{
	Int result(0, f.prec());
	mpz_pow_ui(result.value, f.value, p);
	return result;
}

Int sqrt(Int f)
{
	Int result(0, f.prec());
	mpz_sqrt(result.value, f.value);
	return result;
}

Int root(Int f, unsigned long int r)
{
	Int result(0, f.prec());
	mpz_root(result.value, f.value, r);
	return result;
}

}