/*
 * sparse_range.h
 *
 *  Created on: May 29, 2016
 *      Author: nbingham
 */

#pragma once

#include <memory.h>
#include <std/container.h>

namespace core
{

template <class value_type, class step_type = value_type>
struct sparse_range
{
	typedef value_type type;
	struct const_iterator;

	value_type start;
	value_type finish;
	step_type step;

	struct const_iterator
	{
	protected:
		friend class sparse_range<value_type, step_type>;

		const sparse_range<value_type, step_type> *root;
		value_type value;

		const_iterator(const sparse_range<value_type, step_type> *root, value_type value)
		{
			this->root = root;
			this->value = value;
		}
	public:
		typedef value_type type;

		const_iterator()
		{
			this->root = NULL;
		}

		~const_iterator()
		{

		}

		operator bool() const
		{
			return root != NULL && ((value >= root->start && value < root->finish) ||
									(value <= root->start && value > root->finish));
		}

		value_type operator*() const
		{
			return value;
		}

		const value_type *operator->() const
		{
			return &value;
		}

		const value_type *ptr() const
		{
			return &value;
		}

		value_type get() const
		{
			return value;
		}
		
		const_iterator &ref()
		{
			return *this;
		}

		const const_iterator &ref() const
		{
			return *this;
		}

		int idx() const
		{
			return (value - root->start)/root->step;
		}

		const_iterator operator++(int)
		{
			const_iterator result = *this;
			value += root->step;
			return result;
		}

		const_iterator operator--(int)
		{
			const_iterator result = *this;
			value -= root->step;
			return result;
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

		slice<range<const_iterator> > sub(int length)
		{
			if (length < 0)
				return range<const_iterator>(*this+length, *this);
			else
				return range<const_iterator>(*this, *this+length);
		}

		sparse_range<value_type, step_type> subcpy(int length)
		{
			if (length < 0)
				return sparse_range<value_type, step_type>(value + root->step*length, value, root->step);
			else
				return sparse_range<value_type, step_type>(value, value + root->step*length, root->step);
		}

		slice<range<const_iterator> > sub()
		{
			return range<const_iterator>(*this, root->end());
		}

		sparse_range<value_type, step_type> subcpy()
		{
			return sparse_range<value_type, step_type>(value, root->finish, root->step);
		}
	};

	typedef const_iterator iterator;

	sparse_range(value_type start, value_type finish)
	{
		this->start = start;
		this->finish = finish;
		this->step = (step_type)1;
	}

	sparse_range(value_type start, value_type finish, step_type step)
	{
		this->start = start;
		this->finish = finish;
		this->step = step;
	}

	template <class value_type2, class step_type2>
	sparse_range(const sparse_range<value_type2, step_type2> &a)
	{
		this->start = a.start;
		this->finish = a.finish;
		this->step = a.step;
	}

	template <class value_type2>
	sparse_range(const range<value_type2> &a)
	{
		this->start = a.start;
		this->finish = a.finish;
		this->step = (step_type)1;
	}

	sparse_range(const_iterator start, const_iterator finish)
	{
		this->start = *start;
		this->finish = *finish;
		this->step = start.root->step;
	}

	template <class value_type2, class step_type2>
	sparse_range(typename range<value_type2>::const_iterator start, typename range<value_type2>::const_iterator finish)
	{
		this->start = *start;
		this->finish = *finish;
		this->step = (step_type)1;
	}

	virtual ~sparse_range()
	{

	}

	// Utility

	int size() const
	{
		return (finish - start)/step;
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
	
	const_iterator at(int i) const
	{
		if (i < 0)
			i += size();

		return const_iterator(this, start + step*i);
	}

	// Accessors

	value_type front() const
	{
		return start;
	}

	value_type back() const
	{
		return finish-step;
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

	// Slicing

	core::slice<sparse_range<value_type, step_type> > deref()
	{
		return *this;
	}

	sparse_range<int, step_type> idx()
	{
		return sparse_range<int, step_type>(start.idx(), finish.idx(), step);
	}

	core::slice<range<iterator> > sub(int start, int end)
	{
		return range<iterator>(at(start), at(end));
	}

	sparse_range<value_type, step_type> subcpy(int start, int end)
	{
		int count = size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return sparse_range<value_type, step_type>(this->start + this->step*start, this->start + this->step*end, this->step);
	}

	core::slice<range<iterator> > sub(int start)
	{
		return range<iterator>(at(start), this->end());
	}

	sparse_range<value_type, step_type> subcpy(int start)
	{
		int count = size();
		start = start < 0 ? count + start : start;
		return sparse_range<value_type, step_type>(this->start + this->step*start, this->finish, this->step);
	}

	core::slice<range<iterator> > sub()
	{
		return range<iterator>(begin(), end());
	}

	sparse_range<value_type, step_type> subcpy()
	{
		int count = size();
		return sparse_range<value_type, step_type>(start, finish, step);
	}

	core::slice<range<const_iterator> > sub(int start, int end) const
	{
		return range<const_iterator>(at(start), at(end));
	}

	sparse_range<value_type, step_type> subcpy(int start, int end) const
	{
		int count = size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return sparse_range<value_type, step_type>(this->start + this->step*start, this->start + this->step*end, this->step);
	}

	core::slice<range<const_iterator> > sub(int start) const
	{
		return range<const_iterator>(at(start), this->end());
	}

	sparse_range<value_type, step_type> subcpy(int start) const
	{
		int count = size();
		start = start < 0 ? count + start : start;
		return sparse_range<value_type, step_type>(this->start + this->step*start, this->finish, this->step);
	}

	core::slice<range<const_iterator> > sub() const
	{
		return range<const_iterator>(begin(), end());
	}

	sparse_range<value_type, step_type> subcpy() const
	{
		return sparse_range<value_type, step_type>(start, finish, step);
	}

	static core::slice<range<const_iterator> > sub(const_iterator start, const_iterator end)
	{
		return range<const_iterator>(start, end).deref();
	}

	template <class container>
	sparse_range<typename container::iterator, step_type> sample(container &c)
	{
		return sparse_range<typename container::iterator, step_type>(c.at(start), c.at(finish), step);
	}

	template <class container>
	sparse_range<typename container::const_iterator, step_type> sample(const container &c)
	{
		return sparse_range<typename container::iterator, step_type>(c.at(start), c.at(finish), step);
	}

	// Modifiers

	void swap(sparse_range<value_type, step_type> &root)
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

	sparse_range<value_type, step_type> &operator=(const sparse_range<value_type, step_type> &root)
	{
		start = root.start;
		finish = root.finish;
		step = root.step;
		return *this;
	}
};

typedef sparse_range<int, int> sparse_rangei;
typedef sparse_range<float, float> sparse_rangef;

template <class value_type1, class step_type1, class value_type2, class step_type2>
bool operator==(sparse_range<value_type1, step_type1> s1, sparse_range<value_type2, step_type2> s2)
{
	return (s1.start == s2.start && s1.finish == s2.finish && s1.step == s2.step);
}

template <class value_type1, class step_type1, class value_type2, class step_type2>
bool operator!=(sparse_range<value_type1, step_type1> s1, sparse_range<value_type2, step_type2> s2)
{
	return (s1.start != s2.start || s1.finish != s2.finish || s1.step != s2.step);
}

template <class value_type1, class step_type1, class value_type2, class step_type2>
bool operator<(sparse_range<value_type1, step_type1> s1, sparse_range<value_type2, step_type2> s2)
{
	return (s1.start < s2.start || (s1.start == s2.start &&
		   (s1.step < s2.step   || (s1.step == s2.step   &&
		    s1.finish < s2.finish))));
}

template <class value_type1, class step_type1, class value_type2, class step_type2>
bool operator>(sparse_range<value_type1, step_type1> s1, sparse_range<value_type2, step_type2> s2)
{
	return (s1.start > s2.start || (s1.start == s2.start &&
		   (s1.step > s2.step   || (s1.step == s2.step   &&
			s1.finish > s2.finish))));
}

template <class value_type1, class step_type1, class value_type2, class step_type2>
bool operator<=(sparse_range<value_type1, step_type1> s1, sparse_range<value_type2, step_type2> s2)
{
	return (s1.start < s2.start || (s1.start == s2.start &&
		   (s1.step < s2.step   || (s1.step == s2.step   &&
			s1.finish <= s2.finish))));
}

template <class value_type1, class step_type1, class value_type2, class step_type2>
bool operator>=(sparse_range<value_type1, step_type1> s1, sparse_range<value_type2, step_type2> s2)
{
	return (s1.start > s2.start || (s1.start == s2.start &&
		   (s1.step > s2.step   || (s1.step == s2.step   &&
			s1.finish >= s2.finish))));
}

template <class value_type1, class step_type1, class container2>
bool operator==(sparse_range<value_type1, step_type1> s1, slice<container2> s2)
{
	return equal_to(s1, s2);
}

template <class value_type1, class step_type1, class container2>
bool operator!=(sparse_range<value_type1, step_type1> s1, slice<container2> s2)
{
	return !equal_to(s1, s2);
}

template <class value_type1, class step_type1, class container2>
bool operator<(sparse_range<value_type1, step_type1> s1, slice<container2> s2)
{
	return less_than(s1, s2);
}

template <class value_type1, class step_type1, class container2>
bool operator>(sparse_range<value_type1, step_type1> s1, slice<container2> s2)
{
	return greater_than(s1, s2);
}

template <class value_type1, class step_type1, class container2>
bool operator<=(sparse_range<value_type1, step_type1> s1, slice<container2> s2)
{
	return !greater_than(s1, s2);
}

template <class value_type1, class step_type1, class container2>
bool operator>=(sparse_range<value_type1, step_type1> s1, slice<container2> s2)
{
	return !less_than(s1, s2);
}

template <class container1, class value_type2, class step_type2>
bool operator==(slice<container1> s1, sparse_range<value_type2, step_type2> s2)
{
	return equal_to(s1, s2);
}

template <class container1, class value_type2, class step_type2>
bool operator!=(slice<container1> s1, sparse_range<value_type2, step_type2> s2)
{
	return !equal_to(s1, s2);
}

template <class container1, class value_type2, class step_type2>
bool operator<(slice<container1> s1, sparse_range<value_type2, step_type2> s2)
{
	return less_than(s1, s2);
}

template <class container1, class value_type2, class step_type2>
bool operator>(slice<container1> s1, sparse_range<value_type2, step_type2> s2)
{
	return greater_than(s1, s2);
}

template <class container1, class value_type2, class step_type2>
bool operator<=(slice<container1> s1, sparse_range<value_type2, step_type2> s2)
{
	return !greater_than(s1, s2);
}

template <class container1, class value_type2, class step_type2>
bool operator>=(slice<container1> s1, sparse_range<value_type2, step_type2> s2)
{
	return !less_than(s1, s2);
}

template <class value_type, class step_type>
bool operator==(sparse_range<value_type, step_type> s1, range<value_type> s2)
{
	return equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator!=(sparse_range<value_type, step_type> s1, range<value_type> s2)
{
	return !equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator<(sparse_range<value_type, step_type> s1, range<value_type> s2)
{
	return less_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>(sparse_range<value_type, step_type> s1, range<value_type> s2)
{
	return greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator<=(sparse_range<value_type, step_type> s1, range<value_type> s2)
{
	return !greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>=(sparse_range<value_type, step_type> s1, range<value_type> s2)
{
	return !less_than(s1, s2);
}

template <class value_type, class step_type>
bool operator==(range<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator!=(range<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return !equal_to(s1, s2);
}

template <class value_type, class step_type>
bool operator<(range<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return less_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>(range<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator<=(range<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return !greater_than(s1, s2);
}

template <class value_type, class step_type>
bool operator>=(range<value_type> s1, sparse_range<value_type, step_type> s2)
{
	return !less_than(s1, s2);
}

}
