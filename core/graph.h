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

	struct refactoring
	{
		refactoring() {}
		~refactoring() {}

		map<iterator, array<iterator> > replaced;

		void clear()
		{
			replaced.clear();
		}

		void erase(iterator left)
		{
			for (map<iterator, array<iterator> >::iterator j = replaced.begin(); j; j++)
				for (array<iterator>::iterator k = j->value.rbegin(); k; k--)
					if (*k == left)
						k.drop();

			replaced.insert(left, array<iterator>());
		}

		void erase(array<iterator> left)
		{
			for (map<iterator, array<iterator> >::iterator j = replaced.begin(); j; j++)
				for (array<iterator>::iterator k = j->second.rbegin(); k; k--)
					if (find(left, *k) != left.end())
						k.drop();

			for (array<iterator>::iterator i = left.begin(); i; i++)
				replaced.insert(*i, array<iterator>());
		}

		void replace(iterator key, iterator value)
		{
			for (map<iterator, array<iterator> >::iterator j = replaced.begin(); j; j++)
				for (array<iterator>::iterator k = j->second.rbegin(); k; k--)
					if (*k == key)
						*k = value;

			replaced.insert(key, array<iterator>(1, value));
		}

		void replace(iterator key, array<iterator> value)
		{
			for (map<iterator, array<iterator> >::iterator j = replaced.begin(); j; j++)
			{
				for (array<iterator>::iterator k = j->second.rbegin(); k; k--)
				{
					if (*k == key)
					{
						for (array<iterator>::iterator l = value.rbegin(); l; l--)
							j->second.push_back(*l);

						if (value.size() > 0)
							*k = value[0];
						else
							k->drop();
					}
				}
			}

			replaced.insert(key, value);
		}

		void copy(iterator key, iterator value)
		{
			array<iterator> nvalue;
			nvalue.reserve(2);
			nvalue.push_back(key);
			nvalue.push_back(value);

			for (map<iterator, array<iterator> >::iterator j = replaced.begin(); j; j++)
				for (array<iterator>::iterator k = j->second.rbegin(); k; k--)
					if (*k == key)
						j->second.push_back(value);

			replaced.insert(key, nvalue);
		}

		void copy(iterator key, array<iterator> value)
		{
			for (map<iterator, array<iterator> >::iterator j = replaced.begin(); j; j++)
				for (array<iterator>::iterator k = j->second.rbegin(); k; k--)
					if (*k == key)
						j->second.append_back(value);

			value.push_back(key);
			replaced.insert(key, value);
		}

		refactoring &merge(refactoring r)
		{
			replaced.insert(r.replaced.begin(), r.replaced.end());
			return *this;
		}

		refactoring &append(refactoring r)
		{
			for (map<iterator, array<iterator> >::iterator j = replaced.begin(); j != replaced.end(); j++)
			{
				for (array<iterator>::iterator k = j->second.rbegin(); k; k--)
				{
					map<iterator, array<iterator> >::iterator loc = r.replaced.find(*k);
					if (loc != r.replaced.end())
					{
						for (int l = (int)loc->second.size()-1; l > 0; l--)
							j->second.push_back(loc->second[l]);

						if (loc->second.size() > 0)
							j->second[k] = loc->second[0];
						else
							j->second.erase(j->second.begin() + k);
					}
				}
			}

			replaced.insert(r.replaced.begin(), r.replaced.end());
			return *this;
		}

		array<iterator> refactor(iterator left) const
		{
			map<iterator, array<iterator> >::const_iterator loc = receipt.replaced.find(left);
			if (loc != receipt.replaced.end())
				return loc->second;
			else
				return array<iterator>(1, left);
		}

		array<iterator> refactor(array<iterator> left) const
		{
			array<iterator> result;
			for (int i = (int)left.size()-1; i >= 0; i--)
			{
				map<iterator, array<iterator> >::const_iterator loc = receipt.replaced.find(left[i]);
				if (loc != receipt.replaced.end())
					result.insert(result.end(), loc->second.begin(), loc->second.end());
				else
					result.push_back(left[i]);
			}

			return result;
		}

		iterator unfactor(iterator left) const
		{
			array<iterator> result;
			for (map<iterator, array<iterator> >::const_iterator j = receipt.replaced.begin(); j != receipt.replaced.end(); j++)
			{
				bool found = false;
				for (int k = (int)left.size() - 1; k >= 0; k--)
					if (find(j->second.begin(), j->second.end(), left[k]) != j->second.end())
					{
						if (!found)
						{
							result.push_back(j->first);
							found = true;
						}

						left.erase(left.begin() + k);
					}
			}

			for (int i = 0; i < (int)left.size(); i++)
				result.push_back(left[i]);

			return result;
		}

		array<iterator> unfactor(array<iterator> left) const
		{
			for (map<iterator, array<iterator> >::const_iterator j = receipt.replaced.begin(); j != receipt.replaced.end(); j++)
				if (find(j->second.begin(), j->second.end(), left) != j->second.end())
					return j->first;

			return left;
		}
	};
};

}

