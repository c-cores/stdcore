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

		const fill<value_type> *root;
		int index;

		const_iterator(const fill<value_type> *root, int index)
		{
			this->root = root;
			this->index = index;
		}
	public:
		const_iterator()
		{
			this->root = NULL;
			this->index = 0;
		}

		~const_iterator()
		{

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

		slice<const fill<value_type> > sub(int n)
		{
			const_iterator l = n < 0 ? *this+n : *this;
			const_iterator r = n < 0 ? *this : *this + n;

			return slice<const fill<value_type> >(l, r);
		}

		fill<value_type> subcpy(int n)
		{
			if (n < 0)
				n = -n;
			return fill<value_type>(n, root->value);
		}

		slice<const fill<value_type> > sub()
		{
			return slice<const fill<value_type> >(*this, root->end());
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

	slice<const fill<value_type> > sub(int start, int end) const
	{
		const_iterator l = start < 0 ? this->end()+start : this->begin()+start;
		const_iterator r = end < 0 ? this->end()+end : this->begin()+end;
		return slice<const fill<value_type> >(l, r);
	}

	slice<const fill<value_type> > sub(int start) const
	{
		const_iterator l = start < 0 ? this->end()+start : this->begin()+start;
		return slice<const fill<value_type> >(l, end());
	}

	fill<value_type> subcpy(int start, int end) const
	{
		int l = start < 0 ? count+start : start;
		int r = end < 0 ? count+end : end;
		return fill<value_type>(r-l, value);
	}

	fill<value_type> subcpy(int start) const
	{
		int l = start < 0 ? count+start : start;
		return fill<value_type>(count-l, value);
	}

	static slice<const fill<value_type> > sub(const_iterator start, const_iterator end)
	{
		return slice<const fill<value_type> >(start, end);
	}

	static fill<value_type> subcpy(const_iterator start, const_iterator end)
	{
		return fill<value_type>(end.index-start.index, start.root->value);
	}

	slice<const fill<value_type> > sub() const
	{
		return slice<const fill<value_type> >(begin(), end());
	}

	fill<value_type> subcpy() const
	{
		return *this;
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
bool operator==(fill<value_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) == 0);
}

template <class value_type1, class container2>
bool operator!=(fill<value_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) != 0);
}

template <class value_type1, class container2>
bool operator<(fill<value_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) < 0);
}

template <class value_type1, class container2>
bool operator>(fill<value_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) > 0);
}

template <class value_type1, class container2>
bool operator<=(fill<value_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) <= 0);
}

template <class value_type1, class container2>
bool operator>=(fill<value_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) >= 0);
}

template <class container1, class value_type2>
bool operator==(slice<container1> s1, fill<value_type2> s2)
{
	return (compare(s1, s2) == 0);
}

template <class container1, class value_type2>
bool operator!=(slice<container1> s1, fill<value_type2> s2)
{
	return (compare(s1, s2) != 0);
}

template <class container1, class value_type2>
bool operator<(slice<container1> s1, fill<value_type2> s2)
{
	return (compare(s1, s2) < 0);
}

template <class container1, class value_type2>
bool operator>(slice<container1> s1, fill<value_type2> s2)
{
	return (compare(s1, s2) > 0);
}

template <class container1, class value_type2>
bool operator<=(slice<container1> s1, fill<value_type2> s2)
{
	return (compare(s1, s2) <= 0);
}

template <class container1, class value_type2>
bool operator>=(slice<container1> s1, fill<value_type2> s2)
{
	return (compare(s1, s2) >= 0);
}

}
