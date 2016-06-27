/*
 * range.h
 *
 *  Created on: May 29, 2016
 *      Author: nbingham
 */

#pragma once

#include <core/slice.h>

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

		const range<value_type> *root;
		value_type value;

		const_iterator(const range<value_type> *root, value_type value)
		{
			this->root = root;
			this->value = value;
		}
	public:
		const_iterator()
		{
			this->root = NULL;
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

		int idx()
		{
			return (value - root->start)/root->step;
		}

		const_iterator &operator++(int)
		{
			value += root->step;
			return *this;
		}

		const_iterator &operator--(int)
		{
			value -= root->step;
			return *this;
		}

		const_iterator &operator++()
		{
			value += root->step;
			return *this;
		}

		const_iterator &operator--()
		{
			value -= root->step;
			return *this;
		}

		const_iterator &operator+=(int n)
		{
			value += root->step*n;
			return *this;
		}

		const_iterator &operator-=(int n)
		{
			value -= root->step*n;
			return *this;
		}

		const_iterator operator+(int n) const
		{
			const_iterator result;
			result.root = root;
			result.value = value + root->step*n;
			return result;
		}

		const_iterator operator-(int n) const
		{
			const_iterator result;
			result.root = root;
			result.value = value - root->step*n;
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
			const_iterator l = n < 0 ? *this+n : *this;
			const_iterator r = n < 0 ? *this : *this + n;

			return slice<const range<value_type> >(l, r);
		}

		range<value_type> subcpy(int n)
		{
			value_type l = n < 0 ? value + n*root->step : value;
			value_type r = n < 0 ? value : value + n*root->step;
			return range<value_type>(l, r, root->step);
		}

		slice<const range<value_type> > sub()
		{
			return slice<const range<value_type> >(*this, root->end());
		}

		range<value_type> subcpy()
		{
			return range<value_type>(value, root->finish, root->step);
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

	slice<const range<value_type> > sub(int start, int end) const
	{
		const_iterator l = start < 0 ? this->end()+start : this->begin()+start;
		const_iterator r = end < 0 ? this->end()+end : this->begin()+end;
		return slice<const range<value_type> >(l, r);
	}

	slice<const range<value_type> > sub(int start) const
	{
		const_iterator l = start < 0 ? this->end()+start : this->begin()+start;
		return slice<const range<value_type> >(l, end());
	}

	range<value_type> subcpy(int start, int end) const
	{
		value_type l = start < 0 ? this->finish + start*this->step : this->start + start*this->step;
		value_type r = end < 0 ? this->finish + end*this->step : this->start + end*this->step;
		return range<value_type>(l, r, this->step);
	}

	range<value_type> subcpy(int start) const
	{
		value_type l = start < 0 ? this->finish + start*this->step : this->start + start*this->step;
		return range<value_type>(l, finish, this->step);
	}

	static slice<const range<value_type> > sub(const_iterator start, const_iterator end)
	{
		return slice<const range<value_type> >(start, end);
	}

	static range<value_type> subcpy(const_iterator start, const_iterator end)
	{
		return range<value_type>(*start, *end, start.root->step);
	}

	slice<const range<value_type> > sub() const
	{
		return slice<const range<value_type> >(begin(), end());
	}

	range<value_type> subcpy() const
	{
		return *this;
	}

	void swap(range<value_type> &root)
	{
		value_type tmp_start = start;
		value_type tmp_finish = finish;
		value_type tmp_step = step;
		start = root.start;
		finish = root.finish;
		step = root.step;
		root.start = tmp_start;
		root.finish = tmp_finish;
		root.step = tmp_step;
	}

	range<value_type> &operator=(const range<value_type> &root)
	{
		start = root.start;
		finish = root.finish;
		step = root.step;
		return *this;
	}
};

template <class value_type1, class value_type2>
bool operator==(range<value_type1> s1, range<value_type2> s2)
{
	return (s1.start == s2.start && s1.finish == s2.finish && s1.step == s2.step);
}

template <class value_type1, class value_type2>
bool operator!=(range<value_type1> s1, range<value_type2> s2)
{
	return (s1.start != s2.start || s1.finish != s2.finish || s1.step != s2.step);
}

template <class value_type1, class value_type2>
bool operator<(range<value_type1> s1, range<value_type2> s2)
{
	return (s1.start < s2.start || (s1.start == s2.start &&
		   (s1.step < s2.step   || (s1.step == s2.step   &&
		    s1.finish < s2.finish))));
}

template <class value_type1, class value_type2>
bool operator>(range<value_type1> s1, range<value_type2> s2)
{
	return (s1.start > s2.start || (s1.start == s2.start &&
		   (s1.step > s2.step   || (s1.step == s2.step   &&
			s1.finish > s2.finish))));
}

template <class value_type1, class value_type2>
bool operator<=(range<value_type1> s1, range<value_type2> s2)
{
	return (s1.start < s2.start || (s1.start == s2.start &&
		   (s1.step < s2.step   || (s1.step == s2.step   &&
			s1.finish <= s2.finish))));
}

template <class value_type1, class value_type2>
bool operator>=(range<value_type1> s1, range<value_type2> s2)
{
	return (s1.start > s2.start || (s1.start == s2.start &&
		   (s1.step > s2.step   || (s1.step == s2.step   &&
			s1.finish >= s2.finish))));
}

template <class value_type1, class container2>
bool operator==(range<value_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) == 0);
}

template <class value_type1, class container2>
bool operator!=(range<value_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) != 0);
}

template <class value_type1, class container2>
bool operator<(range<value_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) < 0);
}

template <class value_type1, class container2>
bool operator>(range<value_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) > 0);
}

template <class value_type1, class container2>
bool operator<=(range<value_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) <= 0);
}

template <class value_type1, class container2>
bool operator>=(range<value_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) >= 0);
}

template <class container1, class value_type2>
bool operator==(slice<container1> s1, range<value_type2> s2)
{
	return (compare(s1, s2) == 0);
}

template <class container1, class value_type2>
bool operator!=(slice<container1> s1, range<value_type2> s2)
{
	return (compare(s1, s2) != 0);
}

template <class container1, class value_type2>
bool operator<(slice<container1> s1, range<value_type2> s2)
{
	return (compare(s1, s2) < 0);
}

template <class container1, class value_type2>
bool operator>(slice<container1> s1, range<value_type2> s2)
{
	return (compare(s1, s2) > 0);
}

template <class container1, class value_type2>
bool operator<=(slice<container1> s1, range<value_type2> s2)
{
	return (compare(s1, s2) <= 0);
}

template <class container1, class value_type2>
bool operator>=(slice<container1> s1, range<value_type2> s2)
{
	return (compare(s1, s2) >= 0);
}

}
