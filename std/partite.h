#pragma once

#include <std/graph.h>
#include <std/implier.h>

namespace core
{

template <int n, class value_type>
struct partite : graph<implier<int, value_type> >
{
	partite()
	{
		for (int i = 0; i < n+1; i++)
			parts[i] = &right;
	}

	~partite()
	{
	}

	end_node *parts[n+1];

	iterator insert(const implier<int, value_type> &value)
	{
		if (value.key < 0 || value.key >= n)
			return end();

		node *result = new node(value);
		result->left = parts[value.key+1]->left;
		result->right = parts[value.key+1];
		result->left->right = result;
		result->right->left = result;
		result->index = parts[value.key+1]->index;
		update_index(parts[value.key+1]);
		
		for (int i = value.key; i >= 0 && parts[i] == parts[value.key+1]; i--)
			parts[i] = result;

		return iterator(this, result);
	}

	iterator insert(int part, const value_type &value)
	{
		return insert(implier<int, value_type>(part, value));
	}

	iterator begin(int part)
	{
		return iterator(this, parts[part]);
	}

	iterator end(int part)
	{
		return iterator(this, parts[part+1]);
	}

	iterator rbegin(int part)
	{
		return iterator(this, parts[part+1]->left);
	}

	iterator rend(int part)
	{
		return iterator(this, parts[part]->left);
	}

	const_iterator begin(int part) const
	{
		return const_iterator(this, parts[part]);
	}

	const_iterator end(int part) const
	{
		return const_iterator(this, parts[part]);
	}

	const_iterator rbegin(int part) const
	{
		return const_iterator(this, parts[part+1]->left);
	}

	const_iterator rend(int part) const
	{
		return const_iterator(this, parts[part]->left);
	}
};

}

