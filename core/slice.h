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
struct slice;

template <class value_type, class step_type = value_type>
struct bound
{
	typedef value_type type;
	struct const_iterator;

	value_type start;
	int length;
	step_type step;

	struct const_iterator
	{
	protected:
		friend class bound<value_type, step_type>;

		const bound<value_type, step_type> *root;
		value_type value;
		int index;

		const_iterator(const bound<value_type, step_type> *root, int index)
		{
			this->root = root;
			this->index = index;
			this->value = root->start + root->step*index;
		}
	public:
		typedef value_type type;

		const_iterator()
		{
			this->root = NULL;
			this->index = -1;
		}

		~const_iterator()
		{

		}

		operator bool() const
		{
			return root != NULL && (root->length < 0 || (index >= 0 && index < root->length));
		}

		value_type operator*()
		{
			return value;
		}

		value_type get() const
		{
			return value;
		}

		int idx()
		{
			return index;
		}

		const_iterator &operator++(int)
		{
			value += root->step;
			index++;
			return *this;
		}

		const_iterator &operator--(int)
		{
			value -= root->step;
			index--;
			return *this;
		}

		const_iterator &operator++()
		{
			value += root->step;
			index++;
			return *this;
		}

		const_iterator &operator--()
		{
			value -= root->step;
			index--;
			return *this;
		}

		const_iterator &operator+=(int n)
		{
			value += root->step*n;
			index += n;
			return *this;
		}

		const_iterator &operator-=(int n)
		{
			value -= root->step*n;
			index -= n;
			return *this;
		}

		const_iterator operator+(int n) const
		{
			const_iterator result;
			result.root = root;
			result.value = value + root->step*n;
			result.index = index + n;
			return result;
		}

		const_iterator operator-(int n) const
		{
			const_iterator result;
			result.root = root;
			result.value = value - root->step*n;
			result.index = index - n;
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
			return index - i.index;
		}

		core::slice<bound<const_iterator, int> > sub(int length)
		{
			if (length < 0)
				return bound<const_iterator, int>(*this, -length, -1);
			else
				return bound<const_iterator, int>(*this, length);
		}

		bound<value_type> subcpy(int length)
		{
			if (length < 0)
				return bound<value_type, step_type>(value, -length, -root->step);
			else
				return bound<value_type, step_type>(value, length, root->step);
		}

		core::slice<bound<const_iterator, int> > sub()
		{
			return bound<const_iterator, int>(*this);
		}

		bound<value_type> subcpy()
		{
			return bound<value_type, step_type>(value, root->length - index, root->step);
		}
	};

	typedef const_iterator iterator;

	bound()
	{
		this->start = 0;
		this->length = -1;
		this->step = (step_type)1;
	}

	bound(value_type start)
	{
		this->start = start;
		this->length = -1;
		this->step = (step_type)1;
	}

	bound(value_type start, int length)
	{
		this->start = start;
		this->length = length;
		this->step = (step_type)1;
	}

	bound(value_type start, int length, step_type step)
	{
		this->start = start;
		this->length = length;
		this->step = step;
	}

	template <class container>
	bound(const container &a)
	{
		this->start = a.front();
		if (a.size() > 1)
			this->step = a.get(1) - a.get(0);
		else
			this->step = (step_type)1;

		this->length = a.size();
	}

	bound(const bound<value_type, step_type> &a)
	{
		this->start = a.start;
		this->length = a.length;
		this->step = a.step;
	}

	// Initialize this array as a copy of some other container
	template <class container>
	bound(typename container::const_iterator left, typename container::const_iterator right)
	{
		int count = right - left;
		this->start = *left;
		if (count > 1)
			this->step = *(left+1) - *left;
		else
			this->step = (step_type)1;

		this->length = (right-left);
	}

	// Initialize this array as a copy of some other container
	template <class container>
	bound(typename container::iterator left, typename container::iterator right)
	{
		int count = right - left;
		this->start = *left;
		if (count > 1)
			this->step = *(left+1) - *left;
		else
			this->step = (step_type)1;

		this->length = (right-left);
	}

	bound(const_iterator start, const_iterator finish)
	{
		this->start = start.get();
		this->length = finish-start;
		this->step = start.root->step;
	}

	virtual ~bound()
	{

	}

	int size() const
	{
		return length;
	}

	const_iterator at(int i) const
	{
		if (i < 0)
			i += size();

		return const_iterator(this, i);
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
		return start+step*(length-1);
	}

	const_iterator begin() const
	{
		return const_iterator(this, 0);
	}

	const_iterator end() const
	{
		return const_iterator(this, length);
	}

	const_iterator rbegin() const
	{
		return const_iterator(this, length-1);
	}

	const_iterator rend() const
	{
		return const_iterator(this, -1);
	}

	core::slice<bound<value_type, step_type> > deref()
	{
		return *this;
	}

	template <class container>
	core::slice<bound<typename container::iterator, step_type> > slice(container &c)
	{
		return bound<typename container::iterator, step_type>(c.at(start), length, step);
	}

	template <class container>
	core::slice<bound<typename container::const_iterator, step_type> > slice(const container &c)
	{
		return bound<typename container::iterator, step_type>(c.at(start), length, step);
	}

	core::slice<bound<iterator, int> > sub(int start, int end)
	{
		int count = size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return bound<iterator, int>(at(start), end-start);
	}

	bound<value_type, step_type> subcpy(int start, int end)
	{
		int count = size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return bound<iterator, int>(at(start), end-start);
	}

	core::slice<bound<iterator, int> > sub(int start)
	{
		int count = size();
		start = start < 0 ? count + start : start;
		return bound<iterator, int>(at(start), count-start);
	}

	bound<value_type, step_type> subcpy(int start)
	{
		int count = size();
		start = start < 0 ? count + start : start;
		return bound<iterator, int>(at(start), count-start);
	}

	core::slice<bound<iterator, int> > sub()
	{
		int count = size();
		return bound<iterator, int>(begin(), count);
	}

	bound<value_type, step_type> subcpy()
	{
		int count = size();
		return bound<iterator, int>(begin(), count);
	}

	core::slice<bound<const_iterator, int> > sub(int start, int end) const
	{
		int count = size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return bound<const_iterator, int>(at(start), end-start);
	}

	bound<value_type, step_type> subcpy(int start, int end) const
	{
		int count = size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return bound<const_iterator, int>(at(start), end-start);
	}

	core::slice<bound<const_iterator, int> > sub(int start) const
	{
		int count = size();
		start = start < 0 ? count + start : start;
		return bound<const_iterator, int>(at(start), count-start);
	}

	bound<value_type, step_type> subcpy(int start) const
	{
		int count = size();
		start = start < 0 ? count + start : start;
		return bound<const_iterator, int>(at(start), count-start);
	}

	core::slice<bound<const_iterator, int> > sub() const
	{
		return bound<const_iterator, int>(begin(), size());
	}

	bound<value_type, step_type> subcpy() const
	{
		return bound<const_iterator, int>(begin(), size());
	}

	void swap(bound<value_type, step_type> &root)
	{
		value_type tmp_start = start;
		int tmp_length = length;
		value_type tmp_step = step;
		start = root.start;
		length = root.length;
		step = root.step;
		root.start = tmp_start;
		root.length = tmp_length;
		root.step = tmp_step;
	}

	bound<value_type, step_type> &operator=(const bound<value_type, step_type> &root)
	{
		start = root.start;
		length = root.length;
		step = root.step;
		return *this;
	}
};

typedef bound<int> boundi;
typedef bound<float> boundf;

template <class value_type1, class step_type1, class value_type2, class step_type2>
bool operator==(bound<value_type1, step_type1> s1, bound<value_type2, step_type2> s2)
{
	return (s1.start == s2.start && s1.length == s2.length && s1.step == s2.step);
}

template <class value_type1, class step_type1, class value_type2, class step_type2>
bool operator!=(bound<value_type1, step_type1> s1, bound<value_type2, step_type2> s2)
{
	return (s1.start != s2.start || s1.length != s2.length || s1.step != s2.step);
}

template <class value_type1, class step_type1, class value_type2, class step_type2>
bool operator<(bound<value_type1, step_type1> s1, bound<value_type2, step_type2> s2)
{
	return (s1.start < s2.start || (s1.start == s2.start &&
		   (s1.step < s2.step   || (s1.step == s2.step   &&
		    s1.length < s2.length))));
}

template <class value_type1, class step_type1, class value_type2, class step_type2>
bool operator>(bound<value_type1, step_type1> s1, bound<value_type2, step_type2> s2)
{
	return (s1.start > s2.start || (s1.start == s2.start &&
		   (s1.step > s2.step   || (s1.step == s2.step   &&
			s1.length > s2.length))));
}

template <class value_type1, class step_type1, class value_type2, class step_type2>
bool operator<=(bound<value_type1, step_type1> s1, bound<value_type2, step_type2> s2)
{
	return (s1.start < s2.start || (s1.start == s2.start &&
		   (s1.step < s2.step   || (s1.step == s2.step   &&
			s1.length <= s2.length))));
}

template <class value_type1, class step_type1, class value_type2, class step_type2>
bool operator>=(bound<value_type1, step_type1> s1, bound<value_type2, step_type2> s2)
{
	return (s1.start > s2.start || (s1.start == s2.start &&
		   (s1.step > s2.step   || (s1.step == s2.step   &&
			s1.length >= s2.length))));
}

template <class value_type1, class step_type1, class container2>
bool operator==(bound<value_type1, step_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) == 0);
}

template <class value_type1, class step_type1, class container2>
bool operator!=(bound<value_type1, step_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) != 0);
}

template <class value_type1, class step_type1, class container2>
bool operator<(bound<value_type1, step_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) < 0);
}

template <class value_type1, class step_type1, class container2>
bool operator>(bound<value_type1, step_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) > 0);
}

template <class value_type1, class step_type1, class container2>
bool operator<=(bound<value_type1, step_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) <= 0);
}

template <class value_type1, class step_type1, class container2>
bool operator>=(bound<value_type1, step_type1> s1, slice<container2> s2)
{
	return (compare(s1, s2) >= 0);
}

template <class container1, class value_type2, class step_type2>
bool operator==(slice<container1> s1, bound<value_type2, step_type2> s2)
{
	return (compare(s1, s2) == 0);
}

template <class container1, class value_type2, class step_type2>
bool operator!=(slice<container1> s1, bound<value_type2, step_type2> s2)
{
	return (compare(s1, s2) != 0);
}

template <class container1, class value_type2, class step_type2>
bool operator<(slice<container1> s1, bound<value_type2, step_type2> s2)
{
	return (compare(s1, s2) < 0);
}

template <class container1, class value_type2, class step_type2>
bool operator>(slice<container1> s1, bound<value_type2, step_type2> s2)
{
	return (compare(s1, s2) > 0);
}

template <class container1, class value_type2, class step_type2>
bool operator<=(slice<container1> s1, bound<value_type2, step_type2> s2)
{
	return (compare(s1, s2) <= 0);
}

template <class container1, class value_type2, class step_type2>
bool operator>=(slice<container1> s1, bound<value_type2, step_type2> s2)
{
	return (compare(s1, s2) >= 0);
}

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

		operator bool() const
		{
			return (bool)ref() && (bool)container::iterator::get();
		}

		type operator*()
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

		type get() const
		{
			return *container::iterator::get();
		}

		typename container::iterator &ref()
		{
			return *this;
		}

		const typename container::iterator &ref() const
		{
			return *this;
		}

		slice<bound<iterator, int> > sub(int length)
		{
			if (length < 0)
				return bound<iterator, int>(*this+length, -length);
			else
				return bound<iterator, int>(*this, length);
		}

		slice<bound<iterator, int> > subcpy(int length)
		{
			if (length < 0)
				return bound<iterator, int>(*this+length, -length);
			else
				return bound<iterator, int>(*this, length);
		}

		slice<bound<iterator, int> > sub()
		{
			return bound<iterator, int>(*this);
		}

		slice<bound<iterator, int> > subcpy()
		{
			return bound<iterator, int>(*this);
		}
	};

	struct const_iterator : container::const_iterator
	{
		using container::const_iterator::root;
		typedef typename elem_type<typename container::const_iterator::type>::type type;

		const_iterator() {}
		const_iterator(const typename container::const_iterator &copy) : container::const_iterator(copy) {}
		~const_iterator() {}

		operator bool() const
		{
			return (bool)ref() && (bool)container::const_iterator::get();
		}

		type operator*()
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

		type get() const
		{
			return *container::const_iterator::get();
		}

		typename container::const_iterator &ref()
		{
			return *this;
		}

		const typename container::const_iterator &ref() const
		{
			return *this;
		}

		slice<bound<const_iterator, int> > sub(int length)
		{
			if (length < 0)
				return bound<const_iterator, int>(*this+length, -length);
			else
				return bound<const_iterator, int>(*this, length);
		}

		slice<bound<const_iterator, int> > subcpy(int length)
		{
			if (length < 0)
				return bound<const_iterator, int>(*this+length, -length);
			else
				return bound<const_iterator, int>(*this, length);
		}

		slice<bound<const_iterator, int> > sub()
		{
			return bound<const_iterator, int>(*this);
		}

		slice<bound<const_iterator, int> > subcpy()
		{
			return bound<const_iterator, int>(*this);
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

	container &ref()
	{
		return *this;
	}

	core::slice<bound<iterator, int> > sub(int start, int end)
	{
		int count = container::size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return bound<iterator, int>(at(start), end-start);
	}

	core::slice<bound<iterator, int> > subcpy(int start, int end)
	{
		int count = container::size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return bound<iterator, int>(at(start), end-start);
	}

	core::slice<bound<iterator, int> > sub(int start)
	{
		int count = container::size();
		start = start < 0 ? count + start : start;
		return bound<iterator, int>(at(start), count-start);
	}

	core::slice<bound<iterator, int> > subcpy(int start)
	{
		int count = container::size();
		start = start < 0 ? count + start : start;
		return bound<iterator, int>(at(start), count-start);
	}

	core::slice<bound<iterator, int> > sub()
	{
		return bound<iterator, int>(begin(), container::size());
	}

	core::slice<bound<iterator, int> > subcpy()
	{
		return bound<iterator, int>(begin(), container::size());
	}

	core::slice<bound<const_iterator, int> > sub(int start, int end) const
	{
		int count = container::size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return bound<const_iterator, int>(at(start), end-start);
	}

	core::slice<bound<const_iterator, int> > subcpy(int start, int end) const
	{
		int count = container::size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return bound<const_iterator, int>(at(start), end-start);
	}

	core::slice<bound<const_iterator, int> > sub(int start) const
	{
		int count = container::size();
		start = start < 0 ? count + start : start;
		return bound<const_iterator, int>(at(start), count-start);
	}

	core::slice<bound<const_iterator, int> > subcpy(int start) const
	{
		int count = container::size();
		start = start < 0 ? count + start : start;
		return bound<const_iterator, int>(at(start), count-start);
	}

	core::slice<bound<const_iterator, int> > sub() const
	{
		return bound<const_iterator, int>(begin(), container::size());
	}

	core::slice<bound<const_iterator, int> > subcpy() const
	{
		return bound<const_iterator, int>(begin(), container::size());
	}
};

template <class container1, class container2>
int compare(const container1 &a, const container2 &b)
{
	typename container1::const_iterator i = a.begin();
	typename container2::const_iterator j = b.begin();
	for (; i && j; i++, j++)
	{
		if (*i < *j)
			return -1;
		else if (*j < *i)
			return 1;
	}
	if (j)
		return -1;
	else if (i)
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

