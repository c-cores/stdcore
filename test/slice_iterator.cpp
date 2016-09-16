#include <gtest/gtest.h>

#include <core/array.h>
#include <core/fill.h>
#include <core/list.h>
#include <core/ascii_stream.h>

using namespace core;

TEST(slice_iterator, array_iterate)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);

	int j = 0;
	for (slice<array<array<int>::iterator> >::iterator i = x.begin(); i; i++)
	{
		EXPECT_EQ(j, *i);
		j++;
	}
	EXPECT_EQ(10, j);
}

TEST(slice_iterator, array_index)
{
	array<int> x0 = array<int>::values(8, 5, 2, 3, 5, 6, 2, 1, 7);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);

	EXPECT_EQ(5, *x.at(0));
	EXPECT_EQ(3, *x.at(2));
	EXPECT_EQ(7, *x.at(-1));
	EXPECT_EQ(2, *x.at(-3));

	EXPECT_EQ(5, x.at(0).get());
	EXPECT_EQ(3, x.at(2).get());
	EXPECT_EQ(7, x.at(-1).get());
	EXPECT_EQ(2, x.at(-3).get());

	EXPECT_EQ(5, *x.at(0).ptr());
	EXPECT_EQ(3, *x.at(2).ptr());
	EXPECT_EQ(7, *x.at(-1).ptr());
	EXPECT_EQ(2, *x.at(-3).ptr());

	EXPECT_EQ(0, x.at(0).idx());
	EXPECT_EQ(2, x.at(2).idx());
	EXPECT_EQ(x.size()-1, x.at(-1).idx());
	EXPECT_EQ(x.size()-3, x.at(-3).idx());
}

TEST(slice_iterator, array_sub)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);
	EXPECT_EQ(x.at(4).sub(3), range<int>(4, 7));
	EXPECT_EQ(x.at(7).sub(-3), range<int>(4, 7));
	EXPECT_EQ(x.at(4).sub(), range<int>(4, 10));
	EXPECT_EQ(x.at(4).subcpy(3), range<int>(4, 7));
	EXPECT_EQ(x.at(7).subcpy(-3), range<int>(4, 7));
	EXPECT_EQ(x.at(4).subcpy(), range<int>(4, 10));

	slice<array<array<int>::const_iterator> > y;
	for (array<int>::const_iterator i = x0.begin(); i; i++)
		y.push_back(i);
	EXPECT_EQ(y.at(4).sub(3), range<int>(4, 7));
	EXPECT_EQ(y.at(7).sub(-3), range<int>(4, 7));
	EXPECT_EQ(x.at(4).sub(), range<int>(4, 10));
	EXPECT_EQ(y.at(4).subcpy(3), range<int>(4, 7));
	EXPECT_EQ(y.at(7).subcpy(-3), range<int>(4, 7));
	EXPECT_EQ(x.at(4).subcpy(), range<int>(4, 10));
}

TEST(slice_iterator, array_alloc)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);

	slice<array<array<int>::iterator> >::iterator i = x.at(5);
	i.alloc(5);
	EXPECT_EQ(15, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x.sub(0, 5), range<int>(0, 5));
	EXPECT_EQ(x.sub(10, 15), range<int>(5, 10));
	EXPECT_EQ(i.idx(), 5);

	i = x.at(0);
	i.alloc(5);
	EXPECT_EQ(20, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x.sub(5, 10), range<int>(0, 5));
	EXPECT_EQ(x.sub(15, 20), range<int>(5, 10));
	EXPECT_EQ(i.idx(), 0);

	i = x.at(20);
	i.alloc(5);
	EXPECT_EQ(25, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x.sub(5, 10), range<int>(0, 5));
	EXPECT_EQ(x.sub(15, 20), range<int>(5, 10));
	EXPECT_EQ(i.idx(), 20);
}

TEST(slice_iterator, array_drop)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);

	slice<array<array<int>::iterator> >::iterator i = x.at(0);
	i.drop(1);
	EXPECT_EQ(9, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, range<int>(1, 10));
	EXPECT_EQ(i.idx(), 0);

	i = x.at(2);
	i.drop(-2);
	EXPECT_EQ(7, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, range<int>(3, 10));
	EXPECT_EQ(i.idx(), 0);

	i = x.at(4);
	i.drop(-2);
	EXPECT_EQ(5, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>::values(5, 3, 4, 7, 8, 9));
	EXPECT_EQ(i.idx(), 2);

	i = x.at(2);
	i.drop(2);
	EXPECT_EQ(3, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>::values(3, 3, 4, 9));
	EXPECT_EQ(i.idx(), 2);

	i = x.at(2);
	i.drop(1);
	EXPECT_EQ(2, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>::values(2, 3, 4));
	EXPECT_EQ(i.idx(), 2);
}

TEST(slice_iterator, array_pop)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);

	slice<array<array<int>::iterator> > y;

	slice<array<array<int>::iterator> >::iterator i = x.at(0);
	y = i.pop(1);
	EXPECT_EQ(9, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, range<int>(1, 10));
	EXPECT_EQ(1, y.count);
	EXPECT_GE(y.capacity, 1);
	EXPECT_NE((array<int>::iterator*)NULL, y.data);
	EXPECT_EQ(0, y[0]);
	EXPECT_EQ(i.idx(), 0);

	i = x.at(2);
	y = i.pop(-2);
	EXPECT_EQ(7, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, range<int>(3, 10));

	EXPECT_EQ(2, y.count);
	EXPECT_GE(y.capacity, 1);
	EXPECT_NE((array<int>::iterator*)NULL, y.data);
	EXPECT_EQ(y, range<int>(1, 3));
	EXPECT_EQ(i.idx(), 0);

	i = x.at(4);
	y = i.pop(-2);
	EXPECT_EQ(5, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>::values(5, 3, 4, 7, 8, 9));

	EXPECT_EQ(2, y.count);
	EXPECT_GE(y.capacity, 2);
	EXPECT_NE((array<int>::iterator*)NULL, y.data);
	EXPECT_EQ(y, range<int>(5, 7));
	EXPECT_EQ(i.idx(), 2);

	i = x.at(2);
	y = i.pop(2);
	EXPECT_EQ(3, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>::values(3, 3, 4, 9));

	EXPECT_EQ(2, y.count);
	EXPECT_GE(y.capacity, 2);
	EXPECT_NE((array<int>::iterator*)NULL, y.data);
	EXPECT_EQ(y, array<int>::values(2, 7, 8));
	EXPECT_EQ(i.idx(), 2);

	i = x.at(2);
	y = i.pop(1);
	EXPECT_EQ(2, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, range<int>(3, 5));

	EXPECT_EQ(1, y.count);
	EXPECT_GE(y.capacity, y.count);
	EXPECT_NE((array<int>::iterator*)NULL, y.data);
	EXPECT_EQ(y[0], 9);
	EXPECT_EQ(i.idx(), 2);
}

TEST(slice_iterator, array_push)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);

	// We can't use operator<< here because that uses
	// the push function and we can't use the push function
	// to test the push function :/
	slice<array<array<int>::iterator> >::iterator i = x.at(0);
	i.push(x0.at(5));
	EXPECT_EQ(11, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x[0], 5);
	EXPECT_EQ(x.sub(1, 11), range<int>(0, 10));
	EXPECT_EQ(i.idx(), 1);

	i = x.at(5);
	i.push(x0.at(3));
	EXPECT_EQ(12, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x[0], 5);
	EXPECT_EQ(x.sub(1, 5), range<int>(0, 4));
	EXPECT_EQ(x[5], 3);
	EXPECT_EQ(x.sub(6, 12), range<int>(4, 10));
	EXPECT_EQ(i.idx(), 6);

	i = x.at(12);
	i.push(x0.at(8));
	EXPECT_EQ(13, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x[0], 5);
	EXPECT_EQ(x.sub(1, 5), range<int>(0, 4));
	EXPECT_EQ(x[5], 3);
	EXPECT_EQ(x.sub(6, 12), range<int>(4, 10));
	EXPECT_EQ(x[12], 8);
	EXPECT_EQ(i.idx(), 13);
}

TEST(slice_iterator, array_append)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);
	array<int> y0 = range<int>(0, 4);
	slice<array<array<int>::iterator> > y;
	for (array<int>::iterator i = y0.begin(); i; i++)
		y.push_back(i);

	// We can't use operator<< here because that uses
	// the append function and we can't use the append function
	// to test the append function :/
	slice<array<array<int>::iterator> >::iterator i = x.begin();
	i.append(y.ref());
	EXPECT_EQ(14, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 14), range<int>(0, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 4));

	i = x.at(7);
	i.append(y.ref());
	EXPECT_EQ(18, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 7), range<int>(0, 3));
	EXPECT_EQ(x.sub(7, 11), range<int>(0, 4));
	EXPECT_EQ(x.sub(11, 18), range<int>(3, 10));
	EXPECT_EQ(i.idx(), 11);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 4));

	i = x.end();
	i.append(y.ref());
	EXPECT_EQ(22, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 7), range<int>(0, 3));
	EXPECT_EQ(x.sub(7, 11), range<int>(0, 4));
	EXPECT_EQ(x.sub(11, 18), range<int>(3, 10));
	EXPECT_EQ(x.sub(18, 22), range<int>(0, 4));
	EXPECT_EQ(i.idx(), x.size());
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 4));

	x.clear();
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);

	i = x.begin();
	i.append(y.ref().sub());
	EXPECT_EQ(14, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 14), range<int>(0, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 4));

	i = x.at(7);
	i.append(y.ref().sub());
	EXPECT_EQ(18, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 7), range<int>(0, 3));
	EXPECT_EQ(x.sub(7, 11), range<int>(0, 4));
	EXPECT_EQ(x.sub(11, 18), range<int>(3, 10));
	EXPECT_EQ(i.idx(), 11);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 4));

	i = x.end();
	i.append(y.ref().sub());
	EXPECT_EQ(22, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 7), range<int>(0, 3));
	EXPECT_EQ(x.sub(7, 11), range<int>(0, 4));
	EXPECT_EQ(x.sub(11, 18), range<int>(3, 10));
	EXPECT_EQ(x.sub(18, 22), range<int>(0, 4));
	EXPECT_EQ(i.idx(), x.size());
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 4));
}

TEST(slice_iterator, array_replace)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);
	array<int> y0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > y;
	for (array<int>::iterator i = y0.begin(); i; i++)
		y.push_back(i);

	slice<array<array<int>::iterator> >::iterator i = x.at(4);
	i.replace(3, y.ref(5));
	EXPECT_EQ(8, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 4)
			+ 5
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.replace(3, y.ref(3));
	EXPECT_EQ(6, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 4)
			+ 3
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.replace(1, y.ref(8));
	EXPECT_EQ(6, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 4)
			+ 8
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.replace(-1, y.ref(9));
	EXPECT_EQ(6, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 3)
			+ 9
			+ 8
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.replace(-1, y.ref(6));
	EXPECT_EQ(6, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 3)
			+ 6
			+ 8
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.replace(-4, y.ref(2));
	EXPECT_EQ(3, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ 2
			+ 8
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 1);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));
}

TEST(slice_iterator, array_replace_container)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);
	array<int> y0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > y;
	for (array<int>::iterator i = y0.begin(); i; i++)
		y.push_back(i);

	slice<array<array<int>::iterator> >::iterator i = x.at(4);
	i.replace(3, y.ref().sub(0, 3));
	EXPECT_EQ(10, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 4)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.replace(3, y.ref().sub(0, 1));
	EXPECT_EQ(8, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 4)
			+ y[0]
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.replace(1, y.ref().sub(0, 3));
	EXPECT_EQ(10, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 4)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.replace(-1, y.ref().sub(0, 6));
	EXPECT_EQ(15, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 3)
			+ y.sub(0, 6)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 9);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.replace(-1, y.ref().sub(0, 2));
	EXPECT_EQ(16, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 3)
			+ y.sub(0, 2)
			+ y.sub(1, 6)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 5);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.replace(-1, y.ref().sub(0, 6));
	EXPECT_EQ(21, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 3)
			+ y.sub(0, 6)
			+ y.sub(1, 2)
			+ y.sub(1, 6)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 9);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.replace(-4, y.ref().sub(0, 2));
	EXPECT_EQ(19, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ y.sub(0, 2)
			+ y.sub(1, 6)
			+ y.sub(1, 2)
			+ y.sub(1, 6)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 2);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.replace(-4, fill<array<int>::iterator>(4, y.ref(9)));
	EXPECT_EQ(19, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
	EXPECT_EQ(x, array<int>()
			+ fill<int>(4, y.get(9))
			+ y.sub(3, 6)
			+ y.sub(1, 2)
			+ y.sub(1, 6)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));
}

TEST(slice_iterator, array_swap)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);

	x.at(5).ref().swap(x.at(2).ref());
	EXPECT_EQ(5, x[2]);
	EXPECT_EQ(2, x[5]);
	EXPECT_EQ(x0, range<int>(0, 10));

	x.begin().ref().swap(x.rbegin().ref());
	EXPECT_EQ(9, x[0]);
	EXPECT_EQ(0, x[9]);
	EXPECT_EQ(x0, range<int>(0, 10));
}
