/*
 * slice.h
 *
 *  Created on: Oct 13, 2014
 *      Author: nbingham
 */

#pragma once

#include <memory.h>
#include <core/range.h>

namespace core
{

template <class container>
struct elem_type
{
	typedef typename container::type type;
};

template <class value>
struct elem_type<value*>
{
	typedef value type;
};

template <class container>
struct slice : container
{
	typedef typename elem_type<container>::type index_type;
	typedef typename elem_type<index_type>::type type;

	struct iterator : container::iterator
	{
		using container::iterator::root;
		typedef typename elem_type<typename container::iterator::type>::type type;

		iterator() {}
		iterator(const typename container::iterator &copy) : container::iterator(copy) {}
		~iterator() {}

		const type &operator*()
		{
			return *container::iterator::get();
		}

		const type *operator->()
		{
			return &(*container::iterator::get());
		}

		const type *ptr()
		{
			return &(*container::iterator::get());
		}

		const type &get()
		{
			return *container::iterator::get();
		}

		index_type &ref()
		{
			return container::iterator::get();
		}

		slice<range<slice<container>::iterator, int> > sub(int n)
		{
			iterator l = n < 0 ? *this+n : *this;
			iterator r = n < 0 ? *this : *this+n;
			return range<slice<container>::iterator, int>(l, r);
		}

		slice<container> subcpy(int n)
		{
			return container(container::iterator::sub(n));
		}

		slice<range<slice<container>::iterator, int> > sub()
		{
			iterator l = *this;
			iterator r = root->end();
			return range<slice<container>::iterator, int>(l, r);
		}

		slice<container> subcpy()
		{
			return container(container::iterator::sub());
		}
	};

	struct const_iterator : container::const_iterator
	{
		using container::const_iterator::root;
		typedef typename elem_type<typename container::const_iterator::type>::type type;

		const_iterator() {}
		const_iterator(const typename container::const_iterator &copy) : container::const_iterator(copy) {}
		~const_iterator() {}

		const type &operator*()
		{
			return *container::const_iterator::get();
		}

		const type *operator->()
		{
			return &(*container::const_iterator::get());
		}

		const type *ptr()
		{
			return &(*container::const_iterator::get());
		}

		const type &get()
		{
			return *container::const_iterator::get();
		}

		const index_type &ref()
		{
			return container::const_iterator::get();
		}

		slice<range<slice<container>::const_iterator, int> > sub(int n)
		{
			const_iterator l = n < 0 ? *this+n : *this;
			const_iterator r = n < 0 ? *this : *this+n;
			return range<slice<container>::const_iterator, int>(l, r);
		}

		slice<container> subcpy(int n)
		{
			return container(container::const_iterator::sub(n));
		}

		slice<range<slice<container>::const_iterator, int> > sub()
		{
			const_iterator l = *this;
			const_iterator r = root->end();
			return range<slice<container>::const_iterator, int>(l, r);
		}

		slice<container> subcpy()
		{
			return container(container::const_iterator::sub());
		}
	};

	slice() {}
	slice(const_iterator left, const_iterator right) : container(left, right) {}
	slice(iterator left, iterator right) : container(left, right) {}
	slice(const container &copy) : container(copy) {}
	~slice() {}

	iterator at(int i)
	{
		return iterator(container::at(i));
	}

	const_iterator at(int i) const
	{
		return const_iterator(container::at(i));
	}

	const type &get(int i) const
	{
		return container::get(i).get();
	}

	const type *ptr(int i) const
	{
		return container::get(i).ptr();
	}

	index_type &ref(int i)
	{
		return container::get(i);
	}

	index_type ref(int i) const
	{
		return container::get(i);
	}

	type operator[](int i) const
	{
		return container::get(i).get();
	}

	type front() const
	{
		return container::front().get();
	}

	type back() const
	{
		return container::back().get();
	}

	iterator begin()
	{
		return iterator(container::begin());
	}

	iterator end()
	{
		return iterator(container::end());
	}

	iterator rbegin()
	{
		return iterator(container::rbegin());
	}

	iterator rend()
	{
		return iterator(container::rend());
	}

	const_iterator begin() const
	{
		return const_iterator(container::begin());
	}

	const_iterator end() const
	{
		return const_iterator(container::end());
	}

	const_iterator rbegin() const
	{
		return const_iterator(container::rbegin());
	}

	const_iterator rend() const
	{
		return const_iterator(container::rend());
	}

	slice<range<slice<container>::iterator, int> > sub(int start, int end)
	{
		iterator l = start < 0 ? this->end()+start : this->begin()+start;
		iterator r = end < 0 ? this->end()+end : this->begin()+end;
		return range<slice<container>::iterator, int>(l, r);
	}

	slice<container> subcpy(int start, int end)
	{
		return container(container::sub(start, end));
	}

	slice<range<slice<container>::const_iterator, int> > sub(int start, int end) const
	{
		const_iterator l = start < 0 ? this->end()+start : this->begin()+start;
		const_iterator r = end < 0 ? this->end()+end : this->begin()+end;
		return range<slice<container>::const_iterator, int>(l, r);
	}

	slice<container> subcpy(int start, int end) const
	{
		return container(container::sub(start, end));
	}

	slice<range<slice<container>::iterator, int> > sub(int start)
	{
		iterator l = start < 0 ? this->end()+start : this->begin()+start;
		return range<slice<container>::iterator, int>(l, this->end());
	}

	slice<container> subcpy(int start)
	{
		return container(container::sub(start));
	}

	slice<range<slice<container>::const_iterator, int> > sub(int start) const
	{
		const_iterator l = start < 0 ? this->end()+start : this->begin()+start;
		return slice<range<slice<container>::const_iterator, int> >(l, this->end());
	}

	slice<container> subcpy(int start) const
	{
		return container(container::sub(start));
	}

	static slice<range<slice<container>::iterator, int> > sub(iterator start, iterator end)
	{
		return range<slice<container>::iterator, int>(start, end);
	}

	static slice<container> subcpy(iterator start, iterator end)
	{
		return container(start, end);
	}

	static slice<range<slice<container>::const_iterator, int> > sub(const_iterator start, const_iterator end)
	{
		return range<slice<container>::const_iterator, int>(start, end);
	}

	static slice<container> subcpy(const_iterator start, const_iterator end)
	{
		return container(start, end);
	}

	slice<container> &sub()
	{
		return *this;
	}

	slice<container> &subcpy()
	{
		return *this;
	}

	slice<const container> sub() const
	{
		return *this;
	}

	slice<const container> subcpy() const
	{
		return *this;
	}

	container &ref()
	{
		return *this;
	}
};

template <class container1, class container2>
int compare(const container1 &a, const container2 &b)
{
	typename container1::const_iterator i = a.begin();
	typename container2::const_iterator j = b.begin();
	for (; i != a.end() && j != b.end(); i++, j++)
	{
		if (*i < *j)
			return -1;
		else if (*j < *i)
			return 1;
	}
	if (j != b.end())
		return -1;
	else if (i != a.end())
		return 1;
	else
		return 0;
}

template <class container1, class container2>
bool operator==(slice<container1> s1, slice<container2> s2)
{
	return (compare(s1, s2) == 0);
}

template <class container1, class container2>
bool operator!=(slice<container1> s1, slice<container2> s2)
{
	return (compare(s1, s2) != 0);
}

template <class container1, class container2>
bool operator<(slice<container1> s1, slice<container2> s2)
{
	return (compare(s1, s2) < 0);
}

template <class container1, class container2>
bool operator>(slice<container1> s1, slice<container2> s2)
{
	return (compare(s1, s2) > 0);
}

template <class container1, class container2>
bool operator<=(slice<container1> s1, slice<container2> s2)
{
	return (compare(s1, s2) <= 0);
}

template <class container1, class container2>
bool operator>=(slice<container1> s1, slice<container2> s2)
{
	return (compare(s1, s2) >= 0);
}

template <class value_type1, class step_type1, class container2>
bool operator==(range<value_type1, step_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) == 0);
}

template <class value_type1, class step_type1, class container2>
bool operator!=(range<value_type1, step_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) != 0);
}

template <class value_type1, class step_type1, class container2>
bool operator<(range<value_type1, step_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) < 0);
}

template <class value_type1, class step_type1, class container2>
bool operator>(range<value_type1, step_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) > 0);
}

template <class value_type1, class step_type1, class container2>
bool operator<=(range<value_type1, step_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) <= 0);
}

template <class value_type1, class step_type1, class container2>
bool operator>=(range<value_type1, step_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) >= 0);
}

template <class container1, class value_type2, class step_type2>
bool operator==(slice<container1> s1, range<value_type2, step_type2> s2)
{
	return (compare(s1, s2) == 0);
}

template <class container1, class value_type2, class step_type2>
bool operator!=(slice<container1> s1, range<value_type2, step_type2> s2)
{
	return (compare(s1, s2) != 0);
}

template <class container1, class value_type2, class step_type2>
bool operator<(slice<container1> s1, range<value_type2, step_type2> s2)
{
	return (compare(s1, s2) < 0);
}

template <class container1, class value_type2, class step_type2>
bool operator>(slice<container1> s1, range<value_type2, step_type2> s2)
{
	return (compare(s1, s2) > 0);
}

template <class container1, class value_type2, class step_type2>
bool operator<=(slice<container1> s1, range<value_type2, step_type2> s2)
{
	return (compare(s1, s2) <= 0);
}

template <class container1, class value_type2, class step_type2>
bool operator>=(slice<container1> s1, range<value_type2, step_type2> s2)
{
	return (compare(s1, s2) >= 0);
}

}

