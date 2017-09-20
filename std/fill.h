/*
 * fill.h
 *
 *  Created on: May 29, 2016
 *      Author: nbingham
 */

#pragma once

#include <std/container.h>

namespace core
{

template <typename value_type>
struct fill;

template <typename value_type>
struct fill_const_iterator
{
protected:
	friend class fill<value_type>;

	const fill<value_type> *root;
	int index;

	fill_const_iterator<value_type>(const fill<value_type> *root, int index)
	{
		this->root = root;
		this->index = index;
	}
public:
	typedef value_type type;

	fill_const_iterator<value_type>()
	{
		this->root = NULL;
		this->index = 0;
	}

	~fill_const_iterator<value_type>()
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

	const value_type *operator->() const
	{
		return &root->value;
	}

	const value_type *ptr() const
	{
		return &root->value;
	}

	value_type get()
	{
		return root->value;
	}

	fill_const_iterator<value_type> &ref()
	{
		return *this;
	}

	const fill_const_iterator<value_type> &ref() const
	{
		return *this;
	}

	int idx() const
	{
		return index;
	}

	fill_const_iterator<value_type> operator++(int)
	{
		fill_const_iterator<value_type> result = *this;
		index++;
		return result;
	}

	fill_const_iterator<value_type> operator--(int)
	{
		fill_const_iterator<value_type> result = *this;
		index--;
		return result;
	}

	fill_const_iterator<value_type> &operator++()
	{
		index++;
		return *this;
	}

	fill_const_iterator<value_type> &operator--()
	{
		index--;
		return *this;
	}

	fill_const_iterator<value_type> &operator+=(int n)
	{
		index += n;
		return *this;
	}

	fill_const_iterator<value_type> &operator-=(int n)
	{
		index -= n;
		return *this;
	}

	fill_const_iterator<value_type> operator+(int n) const
	{
		fill_const_iterator<value_type> result;
		result.root = root;
		result.index = index + n;
		return result;
	}

	fill_const_iterator<value_type> operator-(int n) const
	{
		fill_const_iterator<value_type> result;
		result.root = root;
		result.index = index - n;
		return result;
	}

	bool operator==(fill_const_iterator<value_type> i) const
	{
		return index == i.index;
	}

	bool operator!=(fill_const_iterator<value_type> i) const
	{
		return index != i.index;
	}

	int operator-(fill_const_iterator<value_type> i) const
	{
		return index - i.index;
	}

	fill<value_type> sub(int length) const
	{
		if (length < 0)
			return fill<value_type>(-length < index ? -length : index, root->value);
		else
			return fill<value_type>(length < root->count - index ? length : root->count - index, root->value);
	}

	fill<value_type> subcpy(int length) const
	{
		if (length < 0)
			return fill<value_type>(-length < index ? -length : index, root->value);
		else
			return fill<value_type>(length < root->count - index ? length : root->count - index, root->value);
	}

	fill<value_type> sub() const
	{
		return fill<value_type>(root->count - index, root->value);
	}

	fill<value_type> subcpy() const
	{
		return fill<value_type>(root->count - index, root->value);
	}
};

template <class value_type>
struct fill : container<value_type, fill_const_iterator<value_type>, fill_const_iterator<value_type> >
{
	friend class fill_const_iterator<value_type>;
	
	typedef container<value_type, fill_const_iterator<value_type>, fill_const_iterator<value_type> > super;
	using typename super::iterator;
	using typename super::const_iterator;
	using typename super::type;

	int count;
	value_type value;

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

	// Utility

	int size() const
	{
		return count;
	}

	// Iterators

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

	const_iterator at(int i) const
	{
		if (i < 0)
			i += size();

		return const_iterator(this, i);
	}

	// Accessors

	value_type front() const
	{
		return value;
	}

	value_type back() const
	{
		return value;
	}

	value_type get(int i) const
	{
		return value;
	}

	value_type operator[](int i) const
	{
		return value;
	}

	// Slicing
	fill<value_type> sub(int start, int end) const
	{
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return fill<value_type>(end-start, value);
	}

	fill<value_type> sub(int start) const
	{
		start = start < 0 ? count + start : start;
		return fill<value_type>(count-start, value);
	}

	fill<value_type> sub() const
	{
		return fill<value_type>(count, value);
	}

	fill<value_type> subcpy(int start, int end) const
	{
		start = start < 0 ? count + start : start;
		end = end < 0 ? count + end : end;
		return fill<value_type>(end-start, value);
	}

	fill<value_type> subcpy(int start) const
	{
		start = start < 0 ? count + start : start;
		return fill<value_type>(count-start, value);
	}

	fill<value_type> subcpy() const
	{
		return fill<value_type>(count, value);
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

	// Modifiers

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

template <typename value_type>
fill<value_type> fill_t(int count, value_type value)
{
	return fill<value_type>(count, value);
}

}
