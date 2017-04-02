#pragma once

#include <std/array.h>
#include <std/map.h>
#include <std/algorithm.h>
#include <std/sort.h>

namespace core
{

template <class value_type>
struct graph
{
	struct iterator;
	struct const_iterator;

	typedef array<iterator> links;
	typedef array<const_iterator> const_links;
	typedef typename array<iterator>::iterator link_iterator;
	typedef typename array<const_iterator>::iterator const_link_iterator;
	typedef typename array<iterator>::const_iterator link_const_iterator;
	typedef typename array<const_iterator>::const_iterator const_link_const_iterator;

	struct end_node
	{
		end_node()
		{
			left = this;
			right = this;
			index = -1;
		}

		virtual ~end_node()
		{
		}

		end_node *left;
		end_node *right;
		int index;
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
		links next;
		links prev;
	};

	struct iterator
	{
	protected:
		friend class graph<value_type>;
		friend class const_iterator;
		graph<value_type> *root;
		end_node *loc;
	public:
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

		operator bool() const
		{
			return root != NULL && loc != &root->left && loc != &root->right;
		}

		value_type &operator*() const
		{
			return ((node*)loc)->value;
		}

		value_type *operator->() const
		{
			return &((node*)loc)->value;
		}

		value_type *ptr() const
		{
			return &((node*)loc)->value;
		}

		value_type &get() const
		{
			return ((node*)loc)->value;
		}

		int idx() const
		{
			return loc->index;
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

		links &next() const
		{
			return ((node*)loc)->next;
		}

		links &prev() const
		{
			return ((node*)loc)->prev;
		}

		bool operator==(iterator iter) const
		{
			return loc->index == iter.loc->index;
		}

		bool operator!=(iterator iter) const
		{
			return loc->index != iter.loc->index;
		}

		bool operator<(iterator iter) const
		{
			return loc->index < iter.loc->index;
		}

		bool operator>(iterator iter) const
		{
			return loc->index > iter.loc->index;
		}

		bool operator<=(iterator iter) const
		{
			return loc->index <= iter.loc->index;
		}

		bool operator>=(iterator iter) const
		{
			return loc->index >= iter.loc->index;
		}

		bool operator==(const_iterator iter) const
		{
			return loc->index == iter.loc->index;
		}

		bool operator!=(const_iterator iter) const
		{
			return loc->index != iter.loc->index;
		}

		bool operator<(const_iterator iter) const
		{
			return loc->index < iter.loc->index;
		}

		bool operator>(const_iterator iter) const
		{
			return loc->index > iter.loc->index;
		}

		bool operator<=(const_iterator iter) const
		{
			return loc->index <= iter.loc->index;
		}

		bool operator>=(const_iterator iter) const
		{
			return loc->index >= iter.loc->index;
		}

		int operator-(iterator i) const
		{
			return loc->index - i.loc->index;
		}

		int operator-(const_iterator i) const
		{
			return loc->index - i.loc->index;
		}

		void drop()
		{
			links n = next();
			links p = prev();
			for (link_iterator i = n.begin(); i != n.end(); i++)
				remove(i->prev(), *this);
			for (link_iterator i = p.begin(); i != p.end(); i++)
				remove(i->next(), *this);
			loc->left->right = loc->right;
			loc->right->left = loc->left;
			end_node *del = loc;
			loc = loc->left;
			delete del;
			root->update_index(loc);
		}

		value_type pop()
		{
			links n = next();
			links p = prev();
			for (link_iterator i = n.begin(); i != n.end(); i++)
				remove(i->prev(), *this);
			for (link_iterator i = p.begin(); i != p.end(); i++)
				remove(i->next(), *this);
			value_type result = get();
			loc->left->right = loc->right;
			loc->right->left = loc->left;
			end_node *del = loc;
			loc = loc->left;
			delete del;
			root->update_index(loc);
			return result;
		}

		iterator link(iterator n) const
		{
			lower_bound(next(), n).push(n);
			lower_bound(n.prev(), n).push(*this);
			return n;
		}

		links link(links n) const
		{
			for (int i = 0; i < n.size(); i++)
				link(n[i]);
			return n;
		}

		void unlink(iterator n) const
		{
			remove(next(), n);
			remove(n.prev(), *this);
		}

		iterator push(const value_type &value) const
		{
			return link(root->insert(value));
		}

		iterator rlink(iterator n) const
		{
			lower_bound(prev(), n).push(n);
			lower_bound(n.next(), n).push(*this);
			return n;
		}

		void runlink(iterator n) const
		{
			remove(prev(), n);
			remove(n.next(), *this);
		}

		iterator rpush(const value_type &value) const
		{
			return rlink(root->insert(value));
		}

		iterator &operator=(const iterator &copy)
		{
			root = copy.root;
			loc = copy.loc;
			return *this;
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
		typedef value_type type;

		const_iterator()
		{
			root = NULL;
			loc = NULL;
		}

		const_iterator(const graph<value_type> *root, const end_node *loc)
		{
			this->root = root;
			this->loc = loc;
		}

		const_iterator(const const_iterator &copy)
		{
			root = copy.root;
			loc = copy.loc;
		}

		operator bool() const
		{
			return root != NULL && loc != &root->left && loc != &root->right;
		}

		value_type &operator*() const
		{
			return ((node*)loc)->value;
		}

		value_type *operator->() const
		{
			return &((node*)loc)->value;
		}

		value_type *ptr() const
		{
			return &((node*)loc)->value;
		}

		value_type &get() const
		{
			return ((node*)loc)->value;
		}

		int idx() const
		{
			return loc->index;
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

		const_links next() const
		{
			const_links result;
			result.reserve(((node*)loc)->next.size());
			for (int i = 0; i < ((node*)loc)->next.size(); i++)
				result.push_back_unsafe(const_iterator(root, ((node*)loc)->next[i].loc));
			return result;
		}

		const_links prev() const
		{
			const_links result;
			result.reserve(((node*)loc)->prev.size());
			for (int i = 0; i < ((node*)loc)->prev.size(); i++)
				result.push_back_unsafe(const_iterator(root, ((node*)loc)->prev[i].loc));
			return result;
		}

		int operator-(const_iterator i) const
		{
			return loc->index - i.loc->index;
		}

		int operator-(iterator i) const
		{
			return loc->index - i.loc->index;
		}

		bool operator==(iterator iter) const
		{
			return loc->index == iter.loc->index;
		}

		bool operator!=(iterator iter) const
		{
			return loc->index != iter.loc->index;
		}

		bool operator<(iterator iter) const
		{
			return loc->index < iter.loc->index;
		}

		bool operator>(iterator iter) const
		{
			return loc->index > iter.loc->index;
		}

		bool operator<=(iterator iter) const
		{
			return loc->index <= iter.loc->index;
		}

		bool operator>=(iterator iter) const
		{
			return loc->index >= iter.loc->index;
		}

		bool operator==(const_iterator iter) const
		{
			return loc->index == iter.loc->index;
		}

		bool operator!=(const_iterator iter) const
		{
			return loc->index != iter.loc->index;
		}

		bool operator<(const_iterator iter) const
		{
			return loc->index < iter.loc->index;
		}

		bool operator>(const_iterator iter) const
		{
			return loc->index > iter.loc->index;
		}

		bool operator<=(const_iterator iter) const
		{
			return loc->index <= iter.loc->index;
		}

		bool operator>=(const_iterator iter) const
		{
			return loc->index >= iter.loc->index;
		}

		const_iterator &operator=(const const_iterator &copy)
		{
			root = copy.root;
			loc = copy.loc;
			return *this;
		}

		const_iterator &operator=(const iterator &copy)
		{
			root = copy.root;
			loc = copy.loc;
			return *this;
		}
	};

	end_node left;
	end_node right;

	graph()
	{
		left.right = &right;
		right.left = &left;
		right.index = 0;
	}

	graph(const graph<value_type> &copy)
	{
		left.right = &right;
		right.left = &left;
		right.index = 0;

		map<const node*, node*> node_map;
		for (const_iterator i = copy.begin(); i != copy.end(); i++)
			node_map.insert((const node*)i.loc, (node*)insert(*i).loc);

		for (typename map<const node*, node*>::iterator i = node_map.begin(); i; i++)
		{
			i->value->next.reserve(i->key->next.size());
			for (link_const_iterator j = i->key->next.begin(); j; j++)
			{
				typename map<const node*, node*>::iterator loc = node_map.find((const node*)j->loc);
				if (loc)
					i->value->next.push_back(iterator(this, loc->value));
			}

			i->value->prev.reserve(i->key->prev.size());
			for (link_const_iterator j = i->key->prev.begin(); j; j++)
			{
				typename map<const node*, node*>::iterator loc = node_map.find((const node*)j->loc);
				if (loc)
					i->value->prev.push_back(iterator(this, loc->value));
			}
		}
	}

	virtual ~graph()
	{
		clear();
	}

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
		right.index = 0;
	}

	int size()
	{
		return right.index;
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

	const_iterator begin() const
	{
		return const_iterator(this, left.right);
	}

	const_iterator rbegin() const
	{
		return const_iterator(this, right.left);
	}

	const_iterator end() const
	{
		return const_iterator(this, &right);
	}

	const_iterator rend() const
	{
		return const_iterator(this, &left);
	}

	links next(const links &curr) const
	{
		links result;
		for (link_const_iterator i = curr.begin(); i != curr.end(); i++)
			sort_merge(result, i->next());
		return result;
	}

	const_links next(const const_links &curr) const
	{
		const_links result;
		for (const_link_const_iterator i = curr.begin(); i != curr.end(); i++)
			sort_merge(result, i->next());
		return result;
	}

	links prev(const links &curr) const
	{
		links result;
		for (link_const_iterator i = curr.begin(); i != curr.end(); i++)
			sort_merge(result, i->prev());
		collapse_inplace(result);
		return result;
	}

	const_links prev(const const_links &curr) const
	{
		const_links result;
		for (const_link_const_iterator i = curr.begin(); i != curr.end(); i++)
			sort_merge(result, i->prev());
		collapse_inplace(result);
		return result;
	}

	map<iterator, array<link_iterator> > next_conj(links curr) const
	{
		map<iterator, array<link_iterator> > result;
		for (link_iterator i = curr.begin(); i != curr.end(); i++)
		{
			links n = i->next();

			for (int j = 0; j < n.size(); j++)
				sort_insert(result[n[j]], i);
		}

		for (typename map<iterator, array<link_iterator> >::iterator i = result.rbegin(); i != result.rend(); i--)
			if (!is_subset(i->value.deref(), i->key.prev()))
				i.drop();

		return result;
	}

	map<iterator, array<link_iterator> > prev_conj(links curr) const
	{
		map<iterator, array<link_iterator> > result;
		for (link_iterator i = curr.begin(); i != curr.end(); i++)
		{
			links p = i->prev();

			for (int j = 0; j < p.size(); j++)
				sort_insert(result[p[j]], i);
		}

		for (typename map<iterator, array<link_iterator> >::iterator i = result.rbegin(); i != result.rend(); i--)
			if (!is_subset(i->value.deref(), i->key.next()))
				i.drop();

		return result;
	}

	virtual iterator insert(const value_type &value)
	{
		node *result = new node(value);
		result->left = right.left;
		result->right = &right;
		result->left->right = result;
		result->right->left = result;
		result->index = right.index;
		right.index++;
		return iterator(this, result);
	}

	graph<value_type> &operator=(const graph<value_type> &copy)
	{
		clear();

		map<const node*, node*> node_map;
		for (const_iterator i = copy.begin(); i != copy.end(); i++)
			node_map.insert((const node*)i.loc, (node*)insert(*i).loc);

		for (typename map<const node*, node*>::iterator i = node_map.begin(); i; i++)
		{
			i->value->next.reserve(i->key->next.size());
			for (typename array<iterator>::const_iterator j = i->key->next.begin(); j; j++)
			{
				typename map<const node*, node*>::iterator loc = node_map.find((const node*)j->loc);
				if (loc)
					i->value->next.push_back(iterator(this, loc->value));
			}

			i->value->prev.reserve(i->key->prev.size());
			for (typename array<iterator>::const_iterator j = i->key->prev.begin(); j; j++)
			{
				typename map<const node*, node*>::iterator loc = node_map.find((const node*)j->loc);
				if (loc)
					i->value->prev.push_back(iterator(this, loc->value));
			}
		}
		return *this;
	}

	/*struct refactoring
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
					if (find(left, *k))
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
			for (map<iterator, array<iterator> >::iterator j = replaced.begin(); j; j++)
			{
				for (array<iterator>::iterator k = j->second.rbegin(); k; k--)
				{
					map<iterator, array<iterator> >::iterator loc = r.replaced.find(*k);
					if (loc)
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
			if (loc)
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
				if (loc)
					result.insert(result.end(), loc->second.begin(), loc->second.end());
				else
					result.push_back(left[i]);
			}

			return result;
		}

		iterator unfactor(iterator left) const
		{
			array<iterator> result;
			for (map<iterator, array<iterator> >::const_iterator j = receipt.replaced.begin(); j; j++)
			{
				bool found = false;
				for (int k = (int)left.size() - 1; k >= 0; k--)
					if (find(j->second.begin(), j->second.end(), left[k]))
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
			for (map<iterator, array<iterator> >::const_iterator j = receipt.replaced.begin(); j; j++)
				if (find(j->second.begin(), j->second.end(), left))
					return j->first;

			return left;
		}
	};*/

protected:
	void update_index(end_node *loc)
	{
		for (; loc != &right; loc = loc->right)
			loc->right->index = loc->index + 1;
	}
};

}

