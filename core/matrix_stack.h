/*
 * matrix_stack.h
 *
 *  Created on: May 24, 2015
 *      Author: nbingham
 */

#include "matrix.h"
#include "array.h"

using namespace core;

#ifndef matrix_stack_h
#define matrix_stack_h

namespace core
{

template <class t, int s>
struct matrix_stack : array<matrix<t, s, s> >
{
	matrix_stack()
	{
		array<matrix<t, s, s> >::push_back(identity<t, s, s>());
		total = identity<t, s, s>();
		updated = true;
	}

	~matrix_stack()
	{

	}

	matrix<t, s, s> total;
	bool updated;

	matrix_stack<t, s> &operator=(matrix<t, s, s> m)
	{
		array<matrix<t, s, s> >::clear();
		array<matrix<t, s, s> >::push_back(m);
		total = m;
		updated = true;
		return *this;
	}

	matrix_stack<t, s> &operator+=(matrix<t, s, s> m)
	{
		updated = false;
		array<matrix<t, s, s> >::back() += m;
		return *this;
	}

	matrix_stack<t, s> &operator-=(matrix<t, s, s> m)
	{
		updated = false;
		array<matrix<t, s, s> >::back() += m;
		return *this;
	}

	matrix_stack<t, s> &operator*=(matrix<t, s, s> m)
	{
		updated = false;
		array<matrix<t, s, s> >::back() *= m;
		return *this;
	}

	matrix_stack<t, s> &operator/=(matrix<t, s, s> m)
	{
		updated = false;
		array<matrix<t, s, s> >::back() /= m;
		return *this;
	}

	matrix_stack<t, s> &operator+=(t v)
	{
		updated = false;
		return (array<matrix<t, s, s> >::back() += v);
	}

	matrix_stack<t, s> &operator-=(t v)
	{
		updated = false;
		array<matrix<t, s, s> >::back() -= v;
		return *this;
	}

	matrix_stack<t, s> &operator*=(t v)
	{
		updated = false;
		array<matrix<t, s, s> >::back() *= v;
		return *this;
	}

	matrix_stack<t, s> &operator/=(t v)
	{
		updated = false;
		array<matrix<t, s, s> >::back() /= v;
		return *this;
	}

	void push()
	{
		array<matrix<t, s, s> >::push_back(identity<t, s, s>());
	}

	void pop()
	{
		updated = false;
		array<matrix<t, s, s> >::pop_back();
	}

	void update()
	{
		total = identity<t, s, s>();
		for (int i = 0; i < array<matrix<t, s, s> >::size(); i++)
			total *= array<matrix<t, s, s> >::at(i);
		updated = true;
	}

	t *data()
	{
		if (!updated)
			update();

		return total.data();
	}

	matrix<t, s, s> value()
	{
		if (!updated)
			update();

		return total;
	}
};

}

#endif
