/*
 * compare.h
 *
 *  Created on: Sep 16, 2016
 *      Author: nbingham
 */

#include <core/array.h>
#include <core/list.h>
#include <core/fill.h>
#include <core/sparse_range.h>

#pragma once

namespace core
{

template<class value_type>
bool operator==(array<value_type> a0, list<value_type> a1)
{
	return equal_to(a0, a1);
}

template<class value_type>
bool operator!=(array<value_type> a0, list<value_type> a1)
{
	return !equal_to(a0, a1);
}

template<class value_type>
bool operator<(array<value_type> a0, list<value_type> a1)
{
	return less_than(a0, a1);
}

template<class value_type>
bool operator>(array<value_type> a0, list<value_type> a1)
{
	return greater_than(a0, a1);
}

template<class value_type>
bool operator<=(array<value_type> a0, list<value_type> a1)
{
	return !greater_than(a0, a1);
}

template<class value_type>
bool operator>=(array<value_type> a0, list<value_type> a1)
{
	return !less_than(a0, a1);
}


template<class value_type>
bool operator==(list<value_type> a0, array<value_type> a1)
{
	return equal_to(a0, a1);
}

template<class value_type>
bool operator!=(list<value_type> a0, array<value_type> a1)
{
	return !equal_to(a0, a1);
}

template<class value_type>
bool operator<(list<value_type> a0, array<value_type> a1)
{
	return less_than(a0, a1);
}

template<class value_type>
bool operator>(list<value_type> a0, array<value_type> a1)
{
	return greater_than(a0, a1);
}

template<class value_type>
bool operator<=(list<value_type> a0, array<value_type> a1)
{
	return !greater_than(a0, a1);
}

template<class value_type>
bool operator>=(list<value_type> a0, array<value_type> a1)
{
	return !less_than(a0, a1);
}

template<class value_type>
bool operator==(array<value_type> a0, fill<value_type> a1)
{
	return equal_to(a0, a1);
}

template<class value_type>
bool operator!=(array<value_type> a0, fill<value_type> a1)
{
	return !equal_to(a0, a1);
}

template<class value_type>
bool operator<(array<value_type> a0, fill<value_type> a1)
{
	return less_than(a0, a1);
}

template<class value_type>
bool operator>(array<value_type> a0, fill<value_type> a1)
{
	return greater_than(a0, a1);
}

template<class value_type>
bool operator<=(array<value_type> a0, fill<value_type> a1)
{
	return !greater_than(a0, a1);
}

template<class value_type>
bool operator>=(array<value_type> a0, fill<value_type> a1)
{
	return !less_than(a0, a1);
}


template<class value_type>
bool operator==(fill<value_type> a0, array<value_type> a1)
{
	return equal_to(a0, a1);
}

template<class value_type>
bool operator!=(fill<value_type> a0, array<value_type> a1)
{
	return !equal_to(a0, a1);
}

template<class value_type>
bool operator<(fill<value_type> a0, array<value_type> a1)
{
	return less_than(a0, a1);
}

template<class value_type>
bool operator>(fill<value_type> a0, array<value_type> a1)
{
	return greater_than(a0, a1);
}

template<class value_type>
bool operator<=(fill<value_type> a0, array<value_type> a1)
{
	return !greater_than(a0, a1);
}

template<class value_type>
bool operator>=(fill<value_type> a0, array<value_type> a1)
{
	return !less_than(a0, a1);
}

template<class value_type>
bool operator==(fill<value_type> a0, list<value_type> a1)
{
	return equal_to(a0, a1);
}

template<class value_type>
bool operator!=(fill<value_type> a0, list<value_type> a1)
{
	return !equal_to(a0, a1);
}

template<class value_type>
bool operator<(fill<value_type> a0, list<value_type> a1)
{
	return less_than(a0, a1);
}

template<class value_type>
bool operator>(fill<value_type> a0, list<value_type> a1)
{
	return greater_than(a0, a1);
}

template<class value_type>
bool operator<=(fill<value_type> a0, list<value_type> a1)
{
	return !greater_than(a0, a1);
}

template<class value_type>
bool operator>=(fill<value_type> a0, list<value_type> a1)
{
	return !less_than(a0, a1);
}


template<class value_type>
bool operator==(list<value_type> a0, fill<value_type> a1)
{
	return equal_to(a0, a1);
}

template<class value_type>
bool operator!=(list<value_type> a0, fill<value_type> a1)
{
	return !equal_to(a0, a1);
}

template<class value_type>
bool operator<(list<value_type> a0, fill<value_type> a1)
{
	return less_than(a0, a1);
}

template<class value_type>
bool operator>(list<value_type> a0, fill<value_type> a1)
{
	return greater_than(a0, a1);
}

template<class value_type>
bool operator<=(list<value_type> a0, fill<value_type> a1)
{
	return !greater_than(a0, a1);
}

template<class value_type>
bool operator>=(list<value_type> a0, fill<value_type> a1)
{
	return !less_than(a0, a1);
}

template <class value_type, class step_type>
bool operator==(sparse_range<value_type, step_type> s1, array<value_type> s2)
{
	return equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator!=(sparse_range<value_type, step_type> s1, array<value_type> s2)
{
	return !equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator<(sparse_range<value_type, step_type> s1, array<value_type> s2)
{
	return less_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>(sparse_range<value_type, step_type> s1, array<value_type> s2)
{
	return greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator<=(sparse_range<value_type, step_type> s1, array<value_type> s2)
{
	return !greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>=(sparse_range<value_type, step_type> s1, array<value_type> s2)
{
	return !less_than(s1, s2);
}

template <class value_type, class step_type>
bool operator==(array<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator!=(array<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return !equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator<(array<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return less_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>(array<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator<=(array<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return !greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>=(array<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return !less_than(s1, s2);
}


template <class value_type, class step_type>
bool operator==(sparse_range<value_type, step_type> s1, list<value_type> s2)
{
	return equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator!=(sparse_range<value_type, step_type> s1, list<value_type> s2)
{
	return !equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator<(sparse_range<value_type, step_type> s1, list<value_type> s2)
{
	return less_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>(sparse_range<value_type, step_type> s1, list<value_type> s2)
{
	return greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator<=(sparse_range<value_type, step_type> s1, list<value_type> s2)
{
	return !greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>=(sparse_range<value_type, step_type> s1, list<value_type> s2)
{
	return !less_than(s1, s2);
}

template <class value_type, class step_type>
bool operator==(list<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator!=(list<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return !equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator<(list<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return less_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>(list<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator<=(list<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return !greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>=(list<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return !less_than(s1, s2);
}


template <class value_type, class step_type>
bool operator==(sparse_range<value_type, step_type> s1, fill<value_type> s2)
{
	return equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator!=(sparse_range<value_type, step_type> s1, fill<value_type> s2)
{
	return !equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator<(sparse_range<value_type, step_type> s1, fill<value_type> s2)
{
	return less_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>(sparse_range<value_type, step_type> s1, fill<value_type> s2)
{
	return greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator<=(sparse_range<value_type, step_type> s1, fill<value_type> s2)
{
	return !greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>=(sparse_range<value_type, step_type> s1, fill<value_type> s2)
{
	return !less_than(s1, s2);
}

template <class value_type, class step_type>
bool operator==(fill<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator!=(fill<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return !equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator<(fill<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return less_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>(fill<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator<=(fill<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return !greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>=(fill<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return !less_than(s1, s2);
}

}
