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

struct container
{
	
};

template <class container>
struct slice;

template <class value_type>
struct range
{
	typedef value_type type;
	struct const_iterator;

	value_type start;
	value_type finish;

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
			return root != NULL && value != root->start-1 && value != root->finish;
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
			return value - root->start;
		}

		const_iterator operator++(int)
		{
			const_iterator result = *this;
			value++;
			return result;
		}

		const_iterator operator--(int)
		{
			const_iterator result = *this;
			value--;
			return result;
		}

		const_iterator &operator++()
		{
			value++;
			return *this;
		}

		const_iterator &operator--()
		{
			value--;
			return *this;
		}

		const_iterator &operator+=(int n)
		{
			value += n;
			return *this;
		}

		const_iterator &operator-=(int n)
		{
			value -= n;
			return *this;
		}

		const_iterator operator+(int n) const
		{
			const_iterator result;
			result.root = root;
			result.value = value + n;
			return result;
		}

		const_iterator operator-(int n) const
		{
			const_iterator result;
			result.root = root;
			result.value = value - n;
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

		range<value_type> subcpy(int length)
		{
			if (length < 0)
				return range<value_type>(value + length, value);
			else
				return range<value_type>(value, value + length);
		}

		slice<range<const_iterator> > sub()
		{
			return range<const_iterator>(*this, root->end());
		}

		range<value_type> subcpy()
		{
			return range<value_type>(value, root->finish);
		}
	};

	typedef const_iterator iterator;

	range()
	{
	}

	range(value_type start, value_type finish)
	{
		this->start = start;
		this->finish = finish;
	}

	template <class value_type2>
	range(const range<value_type2> &a)
	{
		this->start = a.start;
		this->finish = a.finish;
	}

	range(const_iterator start, const_iterator finish)
	{
		this->start = *start;
		this->finish = *finish;
	}

	virtual ~range()
	{

	}

	// Utility

	int size() const
	{
		return finish - start;
	}

	// Iterators

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
		return const_iterator(this, finish-1);
	}

	const_iterator rend() const
	{
		return const_iterator(this, start-1);
	}

	const_iterator at(int i) const
	{
		if (i < 0)
			i += size();

		return const_iterator(this, start + i);
	}

	// Accessors

	value_type front() const
	{
		return start;
	}

	value_type back() const
	{
		return finish-1;
	}

	value_type get(int i) const
	{
		if (i < 0)
			i += size();
		return start + i;
	}

	value_type operator[](int i) const
	{
		if (i < 0)
			i += size();
		return start + i;
	}

	// Slicing

	core::slice<range<value_type> > deref()
	{
		return *this;
	}

	core::slice<range<iterator> > sub(int start, int end)
	{
		return range<iterator>(at(start), at(end));
	}

	range<value_type> subcpy(int start, int end)
	{
		int count = size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return range<value_type>(this->start + start, this->start + end);
	}

	core::slice<range<iterator> > sub(int start)
	{
		return range<iterator>(at(start), this->end());
	}

	range<value_type> subcpy(int start)
	{
		int count = size();
		start = start < 0 ? count + start : start;
		return range<value_type>(this->start + start, this->finish);
	}

	core::slice<range<iterator> > sub()
	{
		return range<iterator>(begin(), end());
	}

	range<value_type> subcpy()
	{
		int count = size();
		return range<value_type>(start, finish);
	}

	core::slice<range<const_iterator> > sub(int start, int end) const
	{
		return range<const_iterator>(at(start), at(end));
	}

	range<value_type> subcpy(int start, int end) const
	{
		int count = size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return range<value_type>(this->start + start, this->start + end);
	}

	core::slice<range<const_iterator> > sub(int start) const
	{
		return range<const_iterator>(at(start), this->end());
	}

	range<value_type> subcpy(int start) const
	{
		int count = size();
		start = start < 0 ? count + start : start;
		return range<value_type>(this->start + start, this->finish);
	}

	core::slice<range<const_iterator> > sub() const
	{
		return range<const_iterator>(begin(), end());
	}

	range<value_type> subcpy() const
	{
		return range<value_type>(start, finish);
	}

	static core::slice<range<const_iterator> > sub(const_iterator start, const_iterator end)
	{
		return range<const_iterator>(start, end).deref();
	}

	template <class container>
	range<typename container::iterator> sample(container &c)
	{
		return range<typename container::iterator>(c.at(start), c.at(finish)).deref();
	}

	template <class container>
	range<typename container::const_iterator> sample(const container &c)
	{
		return range<typename container::const_iterator>(c.at(start), c.at(finish)).deref();
	}

	range<int> idx()
	{
		return range<int>(start.idx(), finish.idx());
	}

	// Modifiers	
	
	void swap(range<value_type> &root)
	{
		value_type tmp_start = start;
		value_type tmp_finish = finish;
		start = root.start;
		finish = root.finish;
		root.start = tmp_start;
		root.finish = tmp_finish;
	}

	range<value_type> &operator=(const range<value_type> &root)
	{
		start = root.start;
		finish = root.finish;
		return *this;
	}
};

typedef range<int> rangei;
typedef range<float> rangef;

template <class value_type1, class value_type2>
bool operator==(range<value_type1> s1, range<value_type2> s2)
{
	return (s1.start == s2.start && s1.finish == s2.finish);
}

template <class value_type1, class value_type2>
bool operator!=(range<value_type1> s1, range<value_type2> s2)
{
	return (s1.start != s2.start || s1.finish != s2.finish);
}

template <class value_type1, class value_type2>
bool operator<(range<value_type1> s1, range<value_type2> s2)
{
	return (s1.start < s2.start || (s1.start == s2.start &&
		    s1.finish < s2.finish));
}

template <class value_type1, class value_type2>
bool operator>(range<value_type1> s1, range<value_type2> s2)
{
	return (s1.start > s2.start || (s1.start == s2.start &&
			s1.finish > s2.finish));
}

template <class value_type1, class value_type2>
bool operator<=(range<value_type1> s1, range<value_type2> s2)
{
	return (s1.start < s2.start || (s1.start == s2.start &&
			s1.finish <= s2.finish));
}

template <class value_type1, class value_type2>
bool operator>=(range<value_type1> s1, range<value_type2> s2)
{
	return (s1.start > s2.start || (s1.start == s2.start &&
			s1.finish >= s2.finish));
}

template <class value_type1, class container2>
bool operator==(range<value_type1> s1, slice<container2> s2)
{
	return equal_to(s1, s2);
}

template <class value_type1, class container2>
bool operator!=(range<value_type1> s1, slice<container2> s2)
{
	return !equal_to(s1, s2);
}

template <class value_type1, class container2>
bool operator<(range<value_type1> s1, slice<container2> s2)
{
	return less_than(s1, s2);
}

template <class value_type1, class container2>
bool operator>(range<value_type1> s1, slice<container2> s2)
{
	return greater_than(s1, s2);
}

template <class value_type1, class container2>
bool operator<=(range<value_type1> s1, slice<container2> s2)
{
	return !greater_than(s1, s2);
}

template <class value_type1, class container2>
bool operator>=(range<value_type1> s1, slice<container2> s2)
{
	return !less_than(s1, s2);
}

template <class container1, class value_type2>
bool operator==(slice<container1> s1, range<value_type2> s2)
{
	return equal_to(s1, s2);
}

template <class container1, class value_type2>
bool operator!=(slice<container1> s1, range<value_type2> s2)
{
	return !equal_to(s1, s2);
}

template <class container1, class value_type2>
bool operator<(slice<container1> s1, range<value_type2> s2)
{
	return less_than(s1, s2);
}

template <class container1, class value_type2>
bool operator>(slice<container1> s1, range<value_type2> s2)
{
	return greater_than(s1, s2);
}

template <class container1, class value_type2>
bool operator<=(slice<container1> s1, range<value_type2> s2)
{
	return !greater_than(s1, s2);
}

template <class container1, class value_type2>
bool operator>=(slice<container1> s1, range<value_type2> s2)
{
	return !less_than(s1, s2);
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

	struct const_iterator;

	struct iterator : container::iterator
	{
		using container::iterator::root;
		typedef typename container::iterator::type iter_type;
		typedef typename elem_type<typename container::iterator::type>::type type;

		iterator() {}
		iterator(const typename container::iterator &copy) : container::iterator(copy) {}
		~iterator() {}

		operator bool() const
		{
			return (bool)ref() && (bool)container::iterator::get();
		}

		operator iter_type() const
		{
			return container::iterator::get();
		}

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

		typename container::iterator &ref()
		{
			return *this;
		}

		const typename container::iterator &ref() const
		{
			return *this;
		}

		iterator operator++(int)
		{
			iterator result = *this;
			container::iterator::operator++();
			return result;
		}

		iterator operator--(int)
		{
			iterator result = *this;
			container::iterator::operator--();
			return result;
		}

		iterator &operator++()
		{
			container::iterator::operator++();
			return *this;
		}

		iterator &operator--()
		{
			container::iterator::operator--();
			return *this;
		}

		iterator &operator+=(int n)
		{
			container::iterator::operator+=(n);
			return *this;
		}

		iterator &operator-=(int n)
		{
			container::iterator::operator-=(n);
			return *this;
		}

		iterator operator+(int n) const
		{
			return container::iterator::operator+(n);
		}

		iterator operator-(int n) const
		{
			return container::iterator::operator-(n);
		}

		bool operator==(iterator i) const
		{
			return container::iterator::operator==(i);
		}

		bool operator!=(iterator i) const
		{
			return container::iterator::operator!=(i);
		}

		bool operator==(const_iterator i) const
		{
			return container::iterator::operator==(i);
		}

		bool operator!=(const_iterator i) const
		{
			return container::iterator::operator!=(i);
		}

		int operator-(iterator i) const
		{
			return container::iterator::operator-(i);
		}

		int operator-(const_iterator i) const
		{
			return container::iterator::operator-(i);
		}

		slice<container> sub(int length)
		{
			if (length < 0)
				return container(range<iterator>(*this+length, *this));
			else
				return container(range<iterator>(*this, *this+length));
		}

		slice<container> subcpy(int length)
		{
			if (length < 0)
				return container(range<iterator>(*this+length, *this));
			else
				return container(range<iterator>(*this, *this+length));
		}

		slice<container> sub()
		{
			return container(range<iterator>(*this, root->end()));
		}

		slice<container> subcpy()
		{
			return container(range<iterator>(*this, root->end()));
		}

		void swap(iterator i)
		{
			ref().get().swap(i.ref().get());
		}

		void swap(const_iterator i)
		{
			ref().get().swap(i.ref().get());
		}

		iterator &operator=(iterator i)
		{
			container::iterator::operator=(i);
			return *this;
		}
	};

	struct const_iterator : container::const_iterator
	{
		using container::const_iterator::root;
		typedef typename container::const_iterator::type iter_type;
		typedef typename elem_type<typename container::const_iterator::type>::type type;

		const_iterator() {}
		const_iterator(const typename container::const_iterator &copy) : container::const_iterator(copy) {}
		~const_iterator() {}

		operator bool() const
		{
			return (bool)ref() && (bool)container::const_iterator::get();
		}

		operator iter_type() const
		{
			return container::const_iterator::get();
		}

		type operator*()
		{
			return *container::const_iterator::get();
		}

		type *operator->()
		{
			return &(*container::const_iterator::get());
		}

		type *ptr()
		{
			return &(*container::const_iterator::get());
		}

		type &get()
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

		const_iterator operator++(int)
		{
			const_iterator result = *this;
			container::const_iterator::operator++();
			return result;
		}

		const_iterator operator--(int)
		{
			const_iterator result = *this;
			container::const_iterator::operator--();
			return result;
		}

		const_iterator &operator++()
		{
			container::const_iterator::operator++();
			return *this;
		}

		const_iterator &operator--()
		{
			container::const_iterator::operator--();
			return *this;
		}

		const_iterator &operator+=(int n)
		{
			container::const_iterator::operator+=(n);
			return *this;
		}

		const_iterator &operator-=(int n)
		{
			container::const_iterator::operator-=(n);
			return *this;
		}

		const_iterator operator+(int n) const
		{
			return container::const_iterator::operator+(n);
		}

		const_iterator operator-(int n) const
		{
			return container::const_iterator::operator-(n);
		}

		bool operator==(iterator i) const
		{
			return container::const_iterator::operator==(i);
		}

		bool operator!=(iterator i) const
		{
			return container::const_iterator::operator!=(i);
		}

		bool operator==(const_iterator i) const
		{
			return container::const_iterator::operator==(i);
		}

		bool operator!=(const_iterator i) const
		{
			return container::const_iterator::operator!=(i);
		}

		int operator-(iterator i) const
		{
			return container::const_iterator::operator-(i);
		}

		int operator-(const_iterator i) const
		{
			return container::const_iterator::operator-(i);
		}

		slice<container> sub(int length)
		{
			if (length < 0)
				return container(range<const_iterator>(*this+length, *this));
			else
				return container(range<const_iterator>(*this, *this+length));
		}

		slice<container> subcpy(int length)
		{
			if (length < 0)
				return container(range<const_iterator>(*this+length, *this));
			else
				return container(range<const_iterator>(*this, *this+length));
		}

		slice<container> sub()
		{
			return container(range<const_iterator>(*this, root->end()));
		}

		slice<container> subcpy()
		{
			return container(range<const_iterator>(*this, root->end()));
		}

		const_iterator &operator=(const_iterator i)
		{
			container::const_iterator::operator=(i);
			return *this;
		}
	};

	slice() {}
	slice(const_iterator left, const_iterator right) : container(left, right) {}
	slice(iterator left, iterator right) : container(left, right) {}

	template <class container2>
	slice(const container2 &copy) : container(copy) {}

	~slice() {}

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

	iterator at(int i)
	{
		return iterator(container::at(i));
	}

	const_iterator at(int i) const
	{
		return const_iterator(container::at(i));
	}

	type &front()
	{
		return container::front().get();
	}

	type &back()
	{
		return container::back().get();
	}

	const type front() const
	{
		return container::front().get();
	}

	const type back() const
	{
		return container::back().get();
	}

	type &get(int i)
	{
		return container::get(i).get();
	}

	type *ptr(int i)
	{
		return container::get(i).ptr();
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

	type &operator[](int i)
	{
		return container::get(i).get();
	}

	const type &operator[](int i) const
	{
		return container::get(i).get();
	}

	container &ref()
	{
		return *this;
	}

	core::slice<container> sub(int start, int end)
	{
		iterator first = start < 0 ? this->end() + start : this->begin() + start;
		iterator last = end < 0 ? this->end() + end : this->begin() + end;
		return container(range<iterator>(first, last));
	}

	core::slice<container> subcpy(int start, int end)
	{
		iterator first = start < 0 ? this->end() + start : this->begin() + start;
		iterator last = end < 0 ? this->end() + end : this->begin() + end;
		return container(range<iterator>(first, last));
	}

	core::slice<container> sub(int start)
	{
		iterator first = start < 0 ? this->end() + start : this->begin() + start;
		return container(range<iterator>(first, this->end()));
	}

	core::slice<container> subcpy(int start)
	{
		iterator first = start < 0 ? this->end() + start : this->begin() + start;
		return container(range<iterator>(first, this->end()));
	}

	core::slice<container> sub()
	{
		return container(range<iterator>(begin(), end()));
	}

	core::slice<container> subcpy()
	{
		return container(range<iterator>(begin(), end()));
	}

	core::slice<container> sub(int start, int end) const
	{
		const_iterator first = start < 0 ? this->end() + start : this->begin() + start;
		const_iterator last = end < 0 ? this->end() + end : this->begin() + end;
		return container(range<const_iterator>(first, last));
	}

	core::slice<container> subcpy(int start, int end) const
	{
		const_iterator first = start < 0 ? this->end() + start : this->begin() + start;
		const_iterator last = end < 0 ? this->end() + end : this->begin() + end;
		return container(range<const_iterator>(first, last));
	}

	core::slice<container> sub(int start) const
	{
		const_iterator first = start < 0 ? this->end() + start : this->begin() + start;
		return container(range<const_iterator>(first, end()));
	}

	core::slice<container> subcpy(int start) const
	{
		const_iterator first = start < 0 ? this->end() + start : this->begin() + start;
		return container(range<const_iterator>(first, end()));
	}

	core::slice<container> sub() const
	{
		return container(range<const_iterator>(begin(), end()));
	}

	core::slice<container> subcpy() const
	{
		return container(range<const_iterator>(begin(), end()));
	}

	static core::slice<container> sub(iterator start, iterator end)
	{
		return container(start, end).deref();
	}

	static core::slice<container> sub(const_iterator start, const_iterator end)
	{
		return container(start, end).deref();
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
bool equal_to(const container1 &a, const container2 &b)
{
	typename container1::const_iterator i = a.begin();
	typename container2::const_iterator j = b.begin();
	for (; i && j; i++, j++)
		if (!(*i == *j))
			return false;

	return !(i || j);
}

template <class container1, class container2>
bool less_than(const container1 &a, const container2 &b)
{
	typename container1::const_iterator i = a.begin();
	typename container2::const_iterator j = b.begin();
	for (; i && j; i++, j++)
	{
		if (*i < *j)
			return true;
		else if (!(*i == *j))
	    	return false;
	}

	return j;
}

template <class container1, class container2>
bool greater_than(const container1 &a, const container2 &b)
{
	typename container1::const_iterator i = a.begin();
	typename container2::const_iterator j = b.begin();
	for (; i && j; i++, j++)
	{
		if (*i > *j)
			return true;
		else if (!(*i == *j))
	    	return false;
	}

	return i;
}

template <class container1, class container2>
bool operator==(slice<container1> s1, slice<container2> s2)
{
	return equal_to(s1, s2);
}

template <class container1, class container2>
bool operator!=(slice<container1> s1, slice<container2> s2)
{
	return !equal_to(s1, s2);
}

template <class container1, class container2>
bool operator<(slice<container1> s1, slice<container2> s2)
{
	return less_than(s1, s2);
}

template <class container1, class container2>
bool operator>(slice<container1> s1, slice<container2> s2)
{
	return greater_than(s1, s2);
}

template <class container1, class container2>
bool operator<=(slice<container1> s1, slice<container2> s2)
{
	return !greater_than(s1, s2);
}

template <class container1, class container2>
bool operator>=(slice<container1> s1, slice<container2> s2)
{
	return !less_than(s1, s2);
}

}

