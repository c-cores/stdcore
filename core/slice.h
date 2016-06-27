/*
 * slice.h
 *
 *  Created on: Oct 13, 2014
 *      Author: nbingham
 */

#pragma once

#include <memory.h>

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
	struct iterator;
	struct const_iterator;

	slice() {}
	slice(const_iterator left, const_iterator right) : container(left, right) {}
	slice(const container &copy) : container(copy) {}
	~slice() {}

	struct iterator : container::iterator
	{
		using container::iterator::root;

		iterator() {}
		iterator(const typename container::iterator &copy) : container::iterator(copy) {}
		~iterator() {}

		type &operator*()
		{
			return *container::iterator::get();
		}
		type *operator->()
		{
			return &(*container::iterator::get());
		}

		type *ptr()
		{
			return &(*container::iterator::get());
		}

		type &get()
		{
			return *container::iterator::get();
		}

		slice<container> sub(int n)
		{
			iterator l = n < 0 ? *this+n : *this;
			iterator r = n < 0 ? *this : *this+n;
			return slice<container>(l, r);
		}

		index_type subcpy(int n)
		{
			return object(sub(n));
		}

		slice<container> sub()
		{
			return slice<container>(*this, root->end());
		}

		index_type subcpy()
		{
			return index_type(sub());
		}
	};

	struct const_iterator : container::const_iterator
	{
		using container::const_iterator::root;

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

		slice<const container> sub(int n)
		{
			iterator l = n < 0 ? *this+n : *this;
			iterator r = n < 0 ? *this : *this+n;
			return slice<const container>(l, r);
		}

		index_type subcpy(int n)
		{
			return index_type(sub(n));
		}

		slice<const container> sub()
		{
			return slice<const container>(*this, root->end());
		}

		index_type subcpy()
		{
			return index_type(sub());
		}
	};

	const_iterator at(int i) const
	{
		return const_iterator(container::at(i));
	}

	type get(int i) const
	{
		return container::get(i).get();
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

	slice<container> sub(int start, int end)
	{
		iterator l = start < 0 ? this->end()+start : this->begin()+start;
		iterator r = end < 0 ? this->end()+end : this->begin()+end;
		return slice<container>(l, r);
	}

	slice<const container> sub(int start, int end) const
	{
		const_iterator l = start < 0 ? this->end()+start : this->begin()+start;
		const_iterator r = end < 0 ? this->end()+end : this->begin()+end;
		return slice<const container>(l, r);
	}

	slice<container> sub(int start)
	{
		iterator l = start < 0 ? this->end()+start : this->begin()+start;
		return slice<container>(l, this->end());
	}

	slice<const container> sub(int start) const
	{
		const_iterator l = start < 0 ? this->end()+start : this->begin()+start;
		return slice<const container>(l, this->end());
	}

	static slice<container> sub(iterator start, iterator end)
	{
		return slice<container>(start, end);
	}

	static slice<const container> sub(const_iterator start, const_iterator end)
	{
		return slice<const container>(start, end);
	}

	slice<container> &sub()
	{
		return *this;
	}

	slice<const container> sub() const
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

}

