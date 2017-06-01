#pragma once

#include <std/graph.h>
#include <std/implier.h>

namespace core
{

struct partite_base
{
	partite_base()
	{
		part = -1;
	}
	
	~partite_base()
	{
	}

	int part;
};

template <int p, class value_type>
struct partite_node : partite_base
{
	partite_node()
	{
		part = p;
	}
	
	~partite_node()
	{
	}

	value_type value;
};

template <int n>
struct partite : graph<partite_base*>
{
	partite()
	{
		for (int i = 0; i < n+1; i++)
			parts[i] = &right;
	}

	~partite()
	{
		for (iterator i = begin(); i != end(); i++)
		{
			delete *i;
			*i = NULL;
		}
	}

	end_node *parts[n+1];

	iterator insert(const partite_base* &value)
	{
		if (value.part < 0 || value.part >= n)
			return end();

		node *result = new node(value);
		result->left = parts[value.part+1]->left;
		result->right = parts[value.part+1];
		result->left->right = result;
		result->right->left = result;
		result->index = parts[value.part+1]->index;
		update_index(parts[value.part+1]);
		
		for (int i = value.part; i >= 0 && parts[i] == parts[value.part+1]; i--)
			parts[i] = result;

		return iterator(this, result);
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

