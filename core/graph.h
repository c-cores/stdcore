#pragma once

#include "array.h"
#include "map.h"
#include "algorithm.h"

namespace core
{

template <class value_type>
struct graph
{
	struct iterator;
	struct const_iterator;

	struct end_node
	{
	private:
		friend class graph<value_type>;
		friend class iterator;
		friend class const_iterator;
		end_node *left;
		end_node *right;
	
	public:
		end_node()
		{
			left = this;
			right = this;
		}

		virtual ~end_node()
		{
		}
	};

	struct node : end_node 
	{
		node()
		{
		}

		node(const value_type &value)
		{
			this->value = value;
		}

		virtual ~node()
		{
		}

		value_type value;
		array<iterator> next;
		array<iterator> prev;
	};

	graph()
	{
		left.right = &right;
		right.left = &left;
	}

	graph(const graph<value_type> &copy)
	{
		clear();

		map<node*, node*> node_map;
		for (const_iterator i = copy.begin(); i; i++)
			node_map.insert(i.loc, insert(*i).loc);
		
		for (typename map<node*, node*>::iterator i = node_map.begin(); i; i++)
		{
			i->second->next.reserve(i->left->next.size());
			for (typename array<iterator>::const_iterator j = i->left->next.begin(); j; j++)
			{
				typename map<node*, node*>::iterator loc = node_map.find(j->loc);
				if (loc)
					i->value->next.push_back(loc->value);
			}

			i->second->prev.reserve(i->left->prev.size());
			for (typename array<iterator>::const_iterator j = i->left->prev.begin(); j; j++)
			{
				typename map<node*, node*>::iterator loc = node_map.find(j->loc);
				if (loc)
					i->value->prev.push_back(loc->value);
			}
		}
	}

	~graph()
	{
		clear();
	}

	end_node left;
	end_node right;

	struct iterator
	{
	protected:
		friend class graph<value_type>;
		friend class const_iterator;
		graph<value_type> *root;
		end_node *loc;
	public:
		typedef graph<value_type> container;
		typedef value_type type;

		iterator()
		{
			root = NULL;
			loc = NULL;
		}

		iterator(graph<value_type> *root, end_node *loc)
		{
			this->root = root;
			this->loc = loc;
		}

		iterator(const iterator &copy)
		{
			root = copy.root;
			loc = copy.loc;
		}

		operator bool()
		{
			return loc != &root->left && loc != &root->right;
		}

		value_type &operator*()
		{
			return ((node*)loc)->value;
		}

		value_type *operator->()
		{
			return &((node*)loc)->value;
		}

		value_type *pointer()
		{
			return &((node*)loc)->value;
		}

		value_type &value()
		{
			return ((node*)loc)->value;
		}

		iterator &operator++(int)
		{
			loc = loc->right;
			return *this;
		}

		iterator &operator--(int)
		{
			loc = loc->left;
			return *this;
		}

		iterator &operator++()
		{
			loc = loc->right;
			return *this;
		}

		iterator &operator--()
		{
			loc = loc->left;
			return *this;
		}

		iterator &operator+=(int n)
		{
			for (int i = 0; i < n && loc != &root->right; i++)
				loc = loc->right;

			return *this;
		}

		iterator &operator-=(int n)
		{
			for (int i = 0; i < n && loc != &root->left; i++)
				loc = loc->left;

			return *this;
		}

		iterator operator+(int n) const
		{
			iterator result(*this);
			result += n;
			return result;
		}

		iterator operator-(int n) const
		{
			iterator result(*this);
			result -= n;
			return result;
		}

		array<iterator> &next()
		{
			return ((node*)loc)->next;
		}

		array<iterator> &prev()
		{
			return ((node*)loc)->prev;
		}

		iterator &operator=(const iterator &copy)
		{
			root = copy.root;
			loc = copy.loc;
			return *this;
		}

		int operator-(iterator i) const
		{
			int count = 0;
			while (i.loc != loc && i.loc != &i.root->right)
			{
				count++;
				i.loc = i.loc->right;
			}

			while (i.loc != loc && i.loc != &i.root->left)
			{
				count--;
				i.loc = i.loc->left;
			}

			return count;
		}

		int operator-(const_iterator i) const
		{
			int count = 0;
			while (i.loc != loc && i.loc != &i.root->right)
			{
				count++;
				i.loc = i.loc->right;
			}

			while (i.loc != loc && i.loc != &i.root->left)
			{
				count--;
				i.loc = i.loc->left;
			}

			return count;
		}

		bool operator==(const iterator &iter)
		{
			return loc == iter.loc;
		}

		bool operator!=(const iterator &iter)
		{
			return loc != iter.loc;
		}

		value_type pop()
		{
			for (typename array<iterator>::iterator i = next().begin(); i != next().end(); i++)
				remove(i->prev(), *this);
			for (typename array<iterator>::iterator i = prev().begin(); i != prev().end(); i++)
				remove(i->next(), *this);
			value_type result = value();
			loc->left->right = loc->right;
			loc->right->left = loc->left;
			delete loc;
			root = NULL;
			loc = NULL;
			return result;
		}

		iterator link(iterator n)
		{
			next().push_back(n);
			n.prev().push_back(*this);
			return n;
		}

		void unlink(iterator n)
		{
			remove(next(), n);
			remove(n.prev(), *this);
		}

		iterator push(const value_type &value)
		{
			return link(root->insert(value));
		}
	};

	struct const_iterator
	{
	protected:
		friend class graph<value_type>;
		friend class iterator;
		const graph<value_type> *root;
		const end_node *loc;
	public:
		typedef graph<value_type> container;
		typedef value_type type;

		const_iterator()
		{
			root = NULL;
			loc = NULL;
		}

		const_iterator(graph<value_type> *root, end_node *loc)
		{
			this->root = root;
			this->loc = loc;
		}

		const_iterator(const const_iterator &copy)
		{
			root = copy.root;
			loc = copy.loc;
		}

		operator bool()
		{
			return loc != &root->left && loc != &root->right;
		}

		const value_type &operator*()
		{
			return ((node*)loc)->value;
		}

		const value_type *operator->()
		{
			return &((node*)loc)->value;
		}

		const value_type *pointer()
		{
			return &((node*)loc)->value;
		}

		const value_type &value()
		{
			return ((node*)loc)->value;
		}

		const_iterator &operator++(int)
		{
			loc = loc->right;
			return *this;
		}

		const_iterator &operator--(int)
		{
			loc = loc->left;
			return *this;
		}

		const_iterator &operator++()
		{
			loc = loc->right;
			return *this;
		}

		const_iterator &operator--()
		{
			loc = loc->left;
			return *this;
		}

		const_iterator &operator+=(int n)
		{
			for (int i = 0; i < n; i++)
				(*this)++;

			return *this;
		}

		const_iterator &operator-=(int n)
		{
			for (int i = 0; i < n; i++)
				(*this)--;

			return *this;
		}

		const_iterator operator+(int n) const
		{
			const_iterator result(*this);
			for (int i = 0; i < n; i++)
				result++;

			return result;
		}

		const_iterator operator-(int n) const
		{
			const_iterator result(*this);
			for (int i = 0; i < n; i++)
				result--;

			return result;
		}

		array<const_iterator> &next()
		{
			return ((node*)loc)->next;
		}

		array<const_iterator> &prev()
		{
			return ((node*)loc)->prev;
		}

		int operator-(const_iterator i) const
		{
			int count = 0;
			for (const_iterator j = i; j.loc != loc && j.loc != &j.root->right; j++)
				count++;
			return count;
		}

		int operator-(iterator i) const
		{
			int count = 0;
			for (const_iterator j = i; j.loc != loc && j.loc != &j.root->right; j++)
				count++;
			return count;
		}

		const_iterator &operator=(const const_iterator &copy)
		{
			root = copy.root;
			loc = copy.loc;
			return *this;
		}

		bool operator==(const const_iterator &iter) const
		{
			return loc == iter.loc;
		}

		bool operator!=(const const_iterator &iter) const
		{
			return loc != iter.loc;
		}

		const_iterator &operator=(const iterator &copy)
		{
			root = copy.root;
			loc = copy.loc;
			return *this;
		}

		bool operator==(const iterator &iter) const
		{
			return loc == iter.loc;
		}

		bool operator!=(const iterator &iter) const
		{
			return loc != iter.loc;
		}
	};

	void clear()
	{
		end_node *curr = left.right, *prev;
		while (curr != &right)
		{
			prev = curr;
			curr = curr->right;
			delete prev;
		}
		left.right = &right;
		right.left = &left;
	}

	iterator begin()
	{
		return iterator(this, left.right);
	}

	iterator rbegin()
	{
		return iterator(this, right.left);
	}

	iterator end()
	{
		return iterator(this, &right);
	}

	iterator rend()
	{
		return iterator(this, &left);
	}

	iterator begin() const
	{
		return const_iterator(this, left.right);
	}

	iterator rbegin() const
	{
		return const_iterator(this, right.left);
	}

	iterator end() const
	{
		return const_iterator(this, &right);
	}

	iterator rend() const
	{
		return const_iterator(this, &left);
	}

	iterator insert(const value_type &value)
	{
		node *result = new node(value);
		result->left = right.left;
		result->right = &right;
		result->left->right = result;
		result->right->left = result;
		return iterator(this, result);
	}

	graph<value_type> &operator=(const graph<value_type> &copy)
	{
		clear();

		map<node*, node*> node_map;
		for (const_iterator i = copy.begin(); i; i++)
			node_map.insert(i.loc, insert(*i).loc);
		
		for (typename map<node*, node*>::iterator i = node_map.begin(); i; i++)
		{
			i->second->next.reserve(i->left->next.size());
			for (typename array<iterator>::iterator j = i->left->next.begin(); j; j++)
			{
				typename map<node*, node*>::iterator loc = node_map.find(j->loc);
				if (loc)
					i->second->next.push_back(iterator(this, loc->value));
			}

			i->second->prev.reserve(i->left->prev.size());
			for (typename array<iterator>::iterator j = i->left->prev.begin(); j; j++)
			{
				typename map<node*, node*>::iterator loc = node_map.find(j->loc);
				if (loc)
					i->value->prev.push_back(iterator(this, loc->value));
			}
		}
		return *this;
	}
};

}

