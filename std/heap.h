/*
 * heap.h
 *
 *  Created on: Nov 5, 2020
 *      Author: nbingham
 */

#pragma once

#include <std/sort.h>
#include <std/slice.h>
#include <std/io.h>

namespace core
{

template <class iterator_type>
void heap_down(iterator_type i)
{
	while (i) {
		iterator_type left = i + (i.idx() + 1);
		iterator_type right = left+1;
		iterator_type largest = i;

		if (left and *left > *largest) {
			largest = left;
		}
		if (right and *right > *largest) {
			largest = right;
		}

		if (largest != i) {
			i.swap(largest);
			i = largest;
		} else {
			break;
		}
	}
}

template <class iterator_type>
void heap_up(iterator_type i)
{
	while ((i-1)) {
		iterator_type n = i - ((i.idx() >> 1)+1);

		if (*i > *n) {
			i.swap(n);
			i = n;
		} else {
			break;
		}
	}
}

template <class container_type>
void heap_make(container_type &c)
{
	for (typename container_type::iterator i = c.begin() + (c.size()>>1); i != c.rend(); i--) {
		heap_down(i);
	}
}

template <class container_type>
void heap_push(container_type &c, const typename container_type::type &v)
{
	c.push_back(v);
	heap_up(c.rbegin());
}

template <class container_type>
void heap_replace(container_type &c, const typename container_type::type &v)
{
	*c.begin() = v;
	heap_down(c.begin());
}

template <class container_type>
void heap_drop(container_type &c)
{
	*c.begin() = *c.rbegin();
	c.drop_back();
	heap_down(c.begin());
}

template <class container_type>
typename container_type::type heap_pop(container_type &c)
{
	typename container_type::type result = *c.begin();
	heap_drop(c);
	return result;
}

template <class container_type>
void sort_heap_inplace(container_type &c)
{
	heap_make(c);
	slice<range<typename container_type::iterator> > heap = c.sub();
	
	while (heap.begin() != heap.end())
	{
		heap.rbegin().swap(heap.begin());
		heap.ref.finish--;
		heap_down(heap.begin());
	}
}

}

