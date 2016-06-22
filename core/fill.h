/*
 * fill.h
 *
 *  Created on: May 29, 2016
 *      Author: nbingham
 */

#pragma once

#include <memory.h>

namespace core
{

template <class value_type>
struct fill
{
	typedef value_type type;

	fill(int count, value_type value)
	{
		this->count = count;
		this->value = value;
	}

	virtual ~fill()
	{

	}

	int count;
	value_type value;

	struct const_iterator
	{
	protected:
		friend class fill<value_type>;

		const fill<value_type> *rng;
		int index;

		const_iterator(const fill<value_type> *rng, int index)
		{
			this->rng = rng;
			this->index = index;
		}
	public:
		const_iterator()
		{
			this->rng = NULL;
			this->index = 0;
		}

		~const_iterator()
		{

		}

		value_type operator*()
		{
			return rng->value;
		}

		value_type get()
		{
			return rng->value;
		}

		const_iterator &operator++(int)
		{
			index++;
			return *this;
		}

		const_iterator &operator--(int)
		{
			index--;
			return *this;
		}

		const_iterator &operator++()
		{
			index++;
			return *this;
		}

		const_iterator &operator--()
		{
			index--;
			return *this;
		}

		const_iterator &operator+=(int n)
		{
			index += n;
			return *this;
		}

		const_iterator &operator-=(int n)
		{
			index -= n;
			return *this;
		}

		const_iterator operator+(int n) const
		{
			const_iterator result;
			result.rng = rng;
			result.index = index + n;
			return result;
		}

		const_iterator operator-(int n) const
		{
			const_iterator result;
			result.rng = rng;
			result.index = index - n;
			return result;
		}

		bool operator==(const_iterator i) const
		{
			return index == i.index;
		}

		bool operator!=(const_iterator i) const
		{
			return index != i.index;
		}

		int operator-(const_iterator i) const
		{
			return index - i.index;
		}

		slice<const fill<value_type> > sub(int n)
		{
			const_iterator right = *this + n;
			if (right.index > rng->count-1)
				right.index = rng->count-1;

			return slice<const fill<value_type> >(*this, right);
		}

		fill<value_type> subcpy(int n)
		{
			return fill<value_type>(sub(n));
		}
	};

	typedef const_iterator iterator;

	int size() const
	{
		return count;
	}

	const_iterator at(int i) const
	{
		if (i < 0)
			i += size();

		return const_iterator(this, i);
	}

	value_type get(int i) const
	{
		return value;
	}

	value_type operator[](int i) const
	{
		return value;
	}

	value_type front() const
	{
		return value;
	}

	value_type back() const
	{
		return value;
	}

	const_iterator begin() const
	{
		return const_iterator(this, 0);
	}

	const_iterator end() const
	{
		return const_iterator(this, count);
	}

	const_iterator rbegin() const
	{
		return const_iterator(this, count-1);
	}

	const_iterator rend() const
	{
		return const_iterator(this, -1);
	}

	slice<const fill<value_type> > sub(int start, int finish = -1)
	{
		if (start < 0)
			start += count;

		if (finish < 0)
			finish += count;
		else
			finish--;

		return slice<fill<value_type> >(iterator(this, start), iterator(this, finish));
	}

	slice<const fill<value_type> > sub(int start, int finish = -1) const
	{
		if (start < 0)
			start += count;

		if (finish < 0)
			finish += count;
		else
			finish--;

		return slice<const fill<value_type> >(const_iterator(this, start), const_iterator(this, finish));
	}

	fill<value_type> subcpy(int start, int end = -1) const
	{
		return fill<value_type>(sub(start, end));
	}

	static slice<const fill<value_type> > sub(const_iterator start, const_iterator end)
	{
		return slice<const fill<value_type> >(start, end);
	}

	static fill<value_type> subcpy(const_iterator start, const_iterator end)
	{
		return fill<value_type>(sub(start, end));
	}

	slice<fill<value_type> > ref()
	{
		return slice<fill<value_type> >(begin(), rbegin());
	}

	slice<const fill<value_type> > ref() const
	{
		return slice<const fill<value_type> >(begin(), rbegin());
	}

	void swap(fill<value_type> &rng)
	{
		int tmp_count = count;
		value_type tmp_value = value;
		count = rng.count;
		value = rng.value;
		rng.count = tmp_count;
		rng.value = tmp_value;
	}

	fill<value_type> &operator=(const fill<value_type> &rng)
	{
		count = rng.count;
		value = rng.value;
		return *this;
	}
};

}
