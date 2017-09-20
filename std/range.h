#pragma once

#include <std/container.h>

#ifndef NULL
#define NULL 0
#endif

namespace core
{

template <typename value_type>
struct range;

template <typename value_type>
struct range_const_iterator
{
	friend class range<value_type>;

protected:
	const range<value_type> *root;
	value_type value;

	range_const_iterator(const range<value_type> *root, value_type value)
	{
		this->root = root;
		this->value = value;
	}
public:
	typedef value_type type;

	range_const_iterator()
	{
		this->root = NULL;
	}

	~range_const_iterator()
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
	
	int idx() const
	{
		return value - root->start;
	}

	range_const_iterator<value_type> operator++(int)
	{
		range_const_iterator<value_type> result = *this;
		value++;
		return result;
	}

	range_const_iterator<value_type> operator--(int)
	{
		range_const_iterator<value_type> result = *this;
		value--;
		return result;
	}

	range_const_iterator<value_type> &operator++()
	{
		value++;
		return *this;
	}

	range_const_iterator<value_type> &operator--()
	{
		value--;
		return *this;
	}

	range_const_iterator<value_type> &operator+=(int n)
	{
		value += n;
		return *this;
	}

	range_const_iterator<value_type> &operator-=(int n)
	{
		value -= n;
		return *this;
	}

	range_const_iterator<value_type> operator+(int n) const
	{
		range_const_iterator<value_type> result;
		result.root = root;
		result.value = value + n;
		return result;
	}

	range_const_iterator<value_type> operator-(int n) const
	{
		range_const_iterator<value_type> result;
		result.root = root;
		result.value = value - n;
		return result;
	}

	bool operator==(range_const_iterator<value_type> i) const
	{
		return value == i.value;
	}

	bool operator!=(range_const_iterator<value_type> i) const
	{
		return value != i.value;
	}

	int operator-(range_const_iterator<value_type> i) const
	{
		return value - i.value;
	}

	range<value_type> sub(int length) const
	{
		value_type bound = value+length;
		if (length < 0)
			return range<value_type>(bound < root->start ? root->start : bound, value);
		else
			return range<value_type>(value, bound > root->finish ? root->finish : bound);
	}

	range<value_type> subcpy(int length) const
	{
		value_type bound = value+length;
		if (length < 0)
			return range<value_type>(bound < root->start ? root->start : bound, value);
		else
			return range<value_type>(value, bound > root->finish ? root->finish : bound);
	}

	range<value_type> sub() const
	{
		return range<value_type>(value, root->finish);
	}

	range<value_type> subcpy() const
	{
		return range<value_type>(value, root->finish);
	}
};

template <class value_type>
struct range : container<value_type, range_const_iterator<value_type>, range_const_iterator<value_type> >
{
	typedef container<value_type, range_const_iterator<value_type>, range_const_iterator<value_type> > super;
	
	using typename super::type;
	using typename super::iterator;
	using typename super::const_iterator;

	value_type start;
	value_type finish;

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
	range<value_type> sub(int start, int end) const
	{
		int count = size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return range<value_type>(this->start + start, this->start + end);
	}

	range<value_type> sub(int start) const
	{
		int count = size();
		start = start < 0 ? count + start : start;
		return range<value_type>(this->start + start, this->finish);
	}

	range<value_type> sub() const
	{
		return range<value_type>(start, finish);
	}

	range<value_type> subcpy(int start, int end) const
	{
		int count = size();
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return range<value_type>(this->start + start, this->start + end);
	}

	range<value_type> subcpy(int start) const
	{
		int count = size();
		start = start < 0 ? count + start : start;
		return range<value_type>(this->start + start, this->finish);
	}

	range<value_type> subcpy() const
	{
		return range<value_type>(start, finish);
	}

	template <class container>
	range<typename container::iterator> sample(container &c) const
	{
		return range<typename container::iterator>(c.at(start), c.at(finish));
	}

	template <class container>
	range<typename container::const_iterator> sample(const container &c) const
	{
		return range<typename container::const_iterator>(c.at(start), c.at(finish));
	}

	range<int> idx() const
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

// Faster comparison algorithms

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

// Constructers that auto-determine value_type
template <typename value_type>
range<value_type> range_t(value_type start, value_type finish)
{
	return range<value_type>(start, finish);
}

}

