/*
 * range.h
 *
 *  Created on: May 29, 2016
 *      Author: nbingham
 */

#pragma once

#include <memory.h>

namespace core
{

template <class value_type>
struct range
{
	typedef value_type type;

	range(value_type start, value_type finish)
	{
		this->start = start;
		this->finish = finish;
		this->step = (value_type)(start > finish ? -1 : 1);
	}

	range(value_type start, value_type finish, value_type step)
	{
		this->start = start;
		this->finish = finish;
		this->step = step;
	}

	virtual ~range()
	{

	}

	value_type start;
	value_type finish;
	value_type step;

	struct const_iterator
	{
	protected:
		friend class range<value_type>;

		const range<value_type> *rng;
		value_type value;

		const_iterator(const range<value_type> *rng, value_type value)
		{
			this->rng = rng;
			this->value = value;
		}
	public:
		const_iterator()
		{
			this->rng = NULL;
			this->value = 0;
		}

		~const_iterator()
		{

		}

		value_type operator*()
		{
			return value;
		}

		value_type get()
		{
			return value;
		}

		const_iterator &operator++(int)
		{
			value += rng->step;
			return *this;
		}

		const_iterator &operator--(int)
		{
			value -= rng->step;
			return *this;
		}

		const_iterator &operator++()
		{
			value += rng->step;
			return *this;
		}

		const_iterator &operator--()
		{
			value -= rng->step;
			return *this;
		}

		const_iterator &operator+=(int n)
		{
			value += rng->step*n;
			return *this;
		}

		const_iterator &operator-=(int n)
		{
			value -= rng->step*n;
			return *this;
		}

		const_iterator operator+(int n) const
		{
			const_iterator result;
			result.rng = rng;
			result.value = value + rng->step*n;
			return result;
		}

		const_iterator operator-(int n) const
		{
			const_iterator result;
			result.rng = rng;
			result.value = value - rng->step*n;
			return result;
		}

		bool operator==(const_iterator i) const
		{
			return value == i.value;
		}

		bool operator!=(const_iterator i) const
		{
			return value != i.value;
		}

		int operator-(const_iterator i) const
		{
			return value - i.value;
		}

		slice<const range<value_type> > sub(int n)
		{
			const_iterator right = *this + n;
			if (right.value > rng->finish-rng->step)
				right.value = rng->finish-rng->step;

			return slice<const range<value_type> >(*this, right);
		}

		range<value_type> subcpy(int n)
		{
			return range<value_type>(sub(n));
		}
	};

	typedef const_iterator iterator;

	int size() const
	{
		return (finish - start)/step;
	}

	const_iterator at(int i) const
	{
		if (i < 0)
			i += size();

		return const_iterator(this, start + step*i);
	}

	value_type get(int i) const
	{
		if (i < 0)
			i += size();
		return start + step*i;
	}

	value_type operator[](int i) const
	{
		if (i < 0)
			i += size();
		return start + step*i;
	}

	value_type front() const
	{
		return start;
	}

	value_type back() const
	{
		return finish-step;
	}

	const_iterator begin() const
	{
		return const_iterator(this, start);
	}

	const_iterator end() const
	{
		return const_iterator(this, finish);
	}

	const_iterator rbegin() const
	{
		return const_iterator(this, finish-step);
	}

	const_iterator rend() const
	{
		return const_iterator(this, start-step);
	}

	slice<const range<value_type> > sub(int start, int finish = -1)
	{
		if (start < 0)
			start = this->finish + start*step;
		else
			start = this->start + start*step;

		if (finish < 0)
			finish = this->finish + finish*step;
		else
			finish = this->start + (finish-1)*step;

		return slice<range<value_type> >(iterator(this, start), iterator(this, finish));
	}

	slice<const range<value_type> > sub(int start, int finish = -1) const
	{
		if (start < 0)
			start = this->finish + start*step;
		else
			start = this->start + start*step;

		if (finish < 0)
			finish = this->finish + finish*step;
		else
			finish = this->start + (finish-1)*step;

		return slice<const range<value_type> >(const_iterator(this, start), const_iterator(this, finish));
	}

	range<value_type> subcpy(int start, int end = -1) const
	{
		return range<value_type>(sub(start, end));
	}

	static slice<const range<value_type> > sub(const_iterator start, const_iterator end)
	{
		return slice<const range<value_type> >(start, end);
	}

	static range<value_type> subcpy(const_iterator start, const_iterator end)
	{
		return range<value_type>(sub(start, end));
	}

	slice<range<value_type> > ref()
	{
		return slice<range<value_type> >(begin(), rbegin());
	}

	slice<const range<value_type> > ref() const
	{
		return slice<const range<value_type> >(begin(), rbegin());
	}

	void swap(range<value_type> &rng)
	{
		value_type tmp_start = start;
		value_type tmp_finish = finish;
		value_type tmp_step = step;
		start = rng.start;
		finish = rng.finish;
		step = rng.step;
		rng.start = tmp_start;
		rng.finish = tmp_finish;
		rng.step = tmp_step;
	}

	range<value_type> &operator=(const range<value_type> &rng)
	{
		start = rng.start;
		finish = rng.finish;
		step = rng.step;
		return *this;
	}
};

}
