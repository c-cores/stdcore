/*
 * fill.h
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
struct fill
{
	typedef value_type type;
	struct const_iterator;

	fill(int count, value_type value)
	{
		this->count = count;
		this->value = value;
	}

	fill(const_iterator left, const_iterator right)
	{
		this->count = right - left;
		this->value = left.root->value;
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

		const fill<value_type> *root;
		int index;

		const_iterator(const fill<value_type> *root, int index)
		{
			this->root = root;
			this->index = index;
		}
	public:
		typedef value_type type;

		const_iterator()
		{
			this->root = NULL;
			this->index = 0;
		}

		~const_iterator()
		{

		}

		operator bool() const
		{
			return root != NULL && index >= 0 && index < root->count;
		}

		value_type operator*()
		{
			return root->value;
		}

		value_type get()
		{
			return root->value;
		}

		int idx()
		{
			return index;
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
			result.root = root;
			result.index = index + n;
			return result;
		}

		const_iterator operator-(int n) const
		{
			const_iterator result;
			result.root = root;
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

		core::slice<range<const_iterator> > sub(int length)
		{
			if (length < 0)
				return range<const_iterator>(*this+length, *this);
			else
				return range<const_iterator>(*this, *this+length);
		}

		fill<value_type> subcpy(int length)
		{
			if (length < 0)
				return fill<value_type>(-length, root->value);
			else
				return fill<value_type>(length, root->value);
		}

		core::slice<range<const_iterator> > sub()
		{
			return range<const_iterator>(*this, root->end());
		}

		fill<value_type> subcpy()
		{
			return fill<value_type>(root->count - index, root->value);
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

	core::slice<fill<value_type> > deref()
	{
		return *this;
	}

	template <class container>
	fill<typename container::iterator> sample(container &c)
	{
		return fill<typename container::iterator>(count, c.at(value));
	}

	template <class container>
	fill<typename container::const_iterator> sample(const container &c)
	{
		return fill<typename container::iterator>(count, c.at(value));
	}

	fill<int> idx()
	{
		return fill<int>(count, value.idx());
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

	core::slice<range<iterator> > sub(int start, int end)
	{
		return range<iterator>(at(start), at(end));
	}

	fill<value_type> subcpy(int start, int end)
	{
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return fill<value_type>(end-start, value);
	}

	core::slice<range<iterator> > sub(int start)
	{
		return range<iterator>(at(start), this->end());
	}

	fill<value_type> subcpy(int start)
	{
		start = start < 0 ? count + start : start;
		return fill<value_type>(count-start, value);
	}

	core::slice<range<iterator> > sub()
	{
		return range<iterator>(begin(), end());
	}

	fill<value_type> subcpy()
	{
		return *this;
	}

	core::slice<range<const_iterator> > sub(int start, int end) const
	{
		return range<const_iterator>(at(start), at(end));
	}

	fill<value_type> subcpy(int start, int end) const
	{
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return fill<value_type>(value, end-start);
	}

	core::slice<range<const_iterator> > sub(int start) const
	{
		return range<const_iterator>(at(start), this->end());
	}

	fill<value_type> subcpy(int start) const
	{
		start = start < 0 ? count + start : start;
		return fill<value_type>(value, count-start);
	}

	core::slice<range<const_iterator> > sub() const
	{
		return range<const_iterator>(begin(), end());
	}

	fill<value_type> subcpy() const
	{
		return fill<value_type>(value, count);
	}

	static core::slice<range<const_iterator> > sub(const_iterator start, const_iterator end)
	{
		return range<const_iterator>(start, end).deref();
	}

	void swap(fill<value_type> &root)
	{
		int tmp_count = count;
		value_type tmp_value = value;
		count = root.count;
		value = root.value;
		root.count = tmp_count;
		root.value = tmp_value;
	}

	fill<value_type> &operator=(const fill<value_type> &root)
	{
		count = root.count;
		value = root.value;
		return *this;
	}
};

template <class value_type1, class value_type2>
bool operator==(fill<value_type1> s1, fill<value_type2> s2)
{
	return (s1.count == s2.count && s1.value == s2.value);
}

template <class value_type1, class value_type2>
bool operator!=(fill<value_type1> s1, fill<value_type2> s2)
{
	return (s1.count != s2.count || s1.value != s2.value);
}

template <class value_type1, class value_type2>
bool operator<(fill<value_type1> s1, fill<value_type2> s2)
{
	return (s1.value < s2.value || (s1.value == s2.value &&
		   (s1.count < s2.count)));
}

template <class value_type1, class value_type2>
bool operator>(fill<value_type1> s1, fill<value_type2> s2)
{
	return (s1.value > s2.value || (s1.value == s2.value &&
		   (s1.count > s2.count)));
}

template <class value_type1, class value_type2>
bool operator<=(fill<value_type1> s1, fill<value_type2> s2)
{
	return (s1.value < s2.value || (s1.value == s2.value &&
		   (s1.count <= s2.count)));
}

template <class value_type1, class value_type2>
bool operator>=(fill<value_type1> s1, fill<value_type2> s2)
{
	return (s1.value > s2.value || (s1.value == s2.value &&
		   (s1.count >= s2.count)));
}

template <class value_type1, class container2>
bool operator==(fill<value_type1> s1, core::slice<container2> s2)
{
	return (compare(s1, s2) == 0);
}

template <class value_type1, class container2>
bool operator!=(fill<value_type1> s1, core::slice<container2> s2)
{
	return (compare(s1, s2) != 0);
}

template <class value_type1, class container2>
bool operator<(fill<value_type1> s1, core::slice<container2> s2)
{
	return (compare(s1, s2) < 0);
}

template <class value_type1, class container2>
bool operator>(fill<value_type1> s1, core::slice<container2> s2)
{
	return (compare(s1, s2) > 0);
}

template <class value_type1, class container2>
bool operator<=(fill<value_type1> s1, core::slice<container2> s2)
{
	return (compare(s1, s2) <= 0);
}

template <class value_type1, class container2>
bool operator>=(fill<value_type1> s1, core::slice<container2> s2)
{
	return (compare(s1, s2) >= 0);
}

template <class container1, class value_type2>
bool operator==(core::slice<container1> s1, fill<value_type2> s2)
{
	return (compare(s1, s2) == 0);
}

template <class container1, class value_type2>
bool operator!=(core::slice<container1> s1, fill<value_type2> s2)
{
	return (compare(s1, s2) != 0);
}

template <class container1, class value_type2>
bool operator<(core::slice<container1> s1, fill<value_type2> s2)
{
	return (compare(s1, s2) < 0);
}

template <class container1, class value_type2>
bool operator>(core::slice<container1> s1, fill<value_type2> s2)
{
	return (compare(s1, s2) > 0);
}

template <class container1, class value_type2>
bool operator<=(core::slice<container1> s1, fill<value_type2> s2)
{
	return (compare(s1, s2) <= 0);
}

template <class container1, class value_type2>
bool operator>=(core::slice<container1> s1, fill<value_type2> s2)
{
	return (compare(s1, s2) >= 0);
}

}
