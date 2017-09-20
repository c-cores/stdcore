#include <gtest/gtest.h>

#include <std/array.h>
#include <std/fill.h>
#include <std/list.h>

using namespace core;

TEST(slice_iterator, array_iterate)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.ref.push_back(i);

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
	array<int> x0 = array_t<int>(8, 5, 2, 3, 5, 6, 2, 1, 7);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.ref.push_back(i);

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
		x.ref.push_back(i);
	EXPECT_EQ(x.at(4).sub(3), range<int>(4, 7));
	EXPECT_EQ(x.at(7).sub(-3), range<int>(4, 7));
	EXPECT_EQ(x.at(4).sub(), range<int>(4, 10));
	EXPECT_EQ(x.at(4).subcpy(3), range<int>(4, 7));
	EXPECT_EQ(x.at(7).subcpy(-3), range<int>(4, 7));
	EXPECT_EQ(x.at(4).subcpy(), range<int>(4, 10));

	slice<array<array<int>::const_iterator> > y;
	for (array<int>::const_iterator i = x0.begin(); i; i++)
		y.ref.push_back(i);
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
		x.ref.push_back(i);

	slice<array<array<int>::iterator> >::iterator i = x.at(5);
	i.ref.alloc(5);
	EXPECT_EQ(15, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x.sub(0, 5), range<int>(0, 5));
	EXPECT_EQ(x.sub(10, 15), range<int>(5, 10));
	EXPECT_EQ(i.idx(), 5);

	i = x.at(0);
	i.ref.alloc(5);
	EXPECT_EQ(20, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x.sub(5, 10), range<int>(0, 5));
	EXPECT_EQ(x.sub(15, 20), range<int>(5, 10));
	EXPECT_EQ(i.idx(), 0);

	i = x.at(20);
	i.ref.alloc(5);
	EXPECT_EQ(25, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x.sub(5, 10), range<int>(0, 5));
	EXPECT_EQ(x.sub(15, 20), range<int>(5, 10));
	EXPECT_EQ(i.idx(), 20);
}

TEST(slice_iterator, array_drop)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.ref.push_back(i);

	slice<array<array<int>::iterator> >::iterator i = x.at(0);
	i.ref.drop(1);
	EXPECT_EQ(9, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, range<int>(1, 10));
	EXPECT_EQ(i.idx(), 0);

	i = x.at(2);
	i.ref.drop(-2);
	EXPECT_EQ(7, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, range<int>(3, 10));
	EXPECT_EQ(i.idx(), 0);

	i = x.at(4);
	i.ref.drop(-2);
	EXPECT_EQ(5, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array_t<int>(5, 3, 4, 7, 8, 9));
	EXPECT_EQ(i.idx(), 2);

	i = x.at(2);
	i.ref.drop(2);
	EXPECT_EQ(3, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array_t<int>(3, 3, 4, 9));
	EXPECT_EQ(i.idx(), 2);

	i = x.at(2);
	i.ref.drop(1);
	EXPECT_EQ(2, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array_t<int>(2, 3, 4));
	EXPECT_EQ(i.idx(), 2);
}

TEST(slice_iterator, array_pop)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.ref.push_back(i);

	slice<array<array<int>::iterator> > y;

	slice<array<array<int>::iterator> >::iterator i = x.at(0);
	y = i.ref.pop(1);
	EXPECT_EQ(9, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, range<int>(1, 10));
	EXPECT_EQ(1, y.ref.count);
	EXPECT_GE(y.ref.capacity, 1);
	EXPECT_NE((array<int>::iterator*)NULL, y.ref.data);
	EXPECT_EQ(0, y[0]);
	EXPECT_EQ(i.idx(), 0);

	i = x.at(2);
	y = i.ref.pop(-2);
	EXPECT_EQ(7, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, range<int>(3, 10));

	EXPECT_EQ(2, y.ref.count);
	EXPECT_GE(y.ref.capacity, 1);
	EXPECT_NE((array<int>::iterator*)NULL, y.ref.data);
	EXPECT_EQ(y, range<int>(1, 3));
	EXPECT_EQ(i.idx(), 0);

	i = x.at(4);
	y = i.ref.pop(-2);
	EXPECT_EQ(5, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array_t<int>(5, 3, 4, 7, 8, 9));

	EXPECT_EQ(2, y.ref.count);
	EXPECT_GE(y.ref.capacity, 2);
	EXPECT_NE((array<int>::iterator*)NULL, y.ref.data);
	EXPECT_EQ(y, range<int>(5, 7));
	EXPECT_EQ(i.idx(), 2);

	i = x.at(2);
	y = i.ref.pop(2);
	EXPECT_EQ(3, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array_t<int>(3, 3, 4, 9));

	EXPECT_EQ(2, y.ref.count);
	EXPECT_GE(y.ref.capacity, 2);
	EXPECT_NE((array<int>::iterator*)NULL, y.ref.data);
	EXPECT_EQ(y, array_t<int>(2, 7, 8));
	EXPECT_EQ(i.idx(), 2);

	i = x.at(2);
	y = i.ref.pop(1);
	EXPECT_EQ(2, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, range<int>(3, 5));

	EXPECT_EQ(1, y.ref.count);
	EXPECT_GE(y.ref.capacity, y.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, y.ref.data);
	EXPECT_EQ(y[0], 9);
	EXPECT_EQ(i.idx(), 2);
}

TEST(slice_iterator, array_push)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.ref.push_back(i);

	// We can't use operator<< here because that uses
	// the push function and we can't use the push function
	// to test the push function :/
	slice<array<array<int>::iterator> >::iterator i = x.at(0);
	i.ref.push(x0.at(5));
	EXPECT_EQ(11, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x[0], 5);
	EXPECT_EQ(x.sub(1, 11), range<int>(0, 10));
	EXPECT_EQ(i.idx(), 1);

	i = x.at(5);
	i.ref.push(x0.at(3));
	EXPECT_EQ(12, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x[0], 5);
	EXPECT_EQ(x.sub(1, 5), range<int>(0, 4));
	EXPECT_EQ(x[5], 3);
	EXPECT_EQ(x.sub(6, 12), range<int>(4, 10));
	EXPECT_EQ(i.idx(), 6);

	i = x.at(12);
	i.ref.push(x0.at(8));
	EXPECT_EQ(13, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
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
		x.ref.push_back(i);
	array<int> y0 = range<int>(0, 4);
	slice<array<array<int>::iterator> > y;
	for (array<int>::iterator i = y0.begin(); i; i++)
		y.ref.push_back(i);

	// We can't use operator<< here because that uses
	// the append function and we can't use the append function
	// to test the append function :/
	slice<array<array<int>::iterator> >::iterator i = x.begin();
	i.ref.append(y.ref);
	EXPECT_EQ(14, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 14), range<int>(0, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 4));

	i = x.at(7);
	i.ref.append(y.ref);
	EXPECT_EQ(18, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 7), range<int>(0, 3));
	EXPECT_EQ(x.sub(7, 11), range<int>(0, 4));
	EXPECT_EQ(x.sub(11, 18), range<int>(3, 10));
	EXPECT_EQ(i.idx(), 11);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 4));

	i = x.end();
	i.ref.append(y.ref);
	EXPECT_EQ(22, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 7), range<int>(0, 3));
	EXPECT_EQ(x.sub(7, 11), range<int>(0, 4));
	EXPECT_EQ(x.sub(11, 18), range<int>(3, 10));
	EXPECT_EQ(x.sub(18, 22), range<int>(0, 4));
	EXPECT_EQ(i.idx(), x.size());
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 4));

	x.ref.clear();
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.ref.push_back(i);

	i = x.begin();
	i.ref.append(y.ref.sub());
	EXPECT_EQ(14, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 14), range<int>(0, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 4));

	i = x.at(7);
	i.ref.append(y.ref.sub());
	EXPECT_EQ(18, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 7), range<int>(0, 3));
	EXPECT_EQ(x.sub(7, 11), range<int>(0, 4));
	EXPECT_EQ(x.sub(11, 18), range<int>(3, 10));
	EXPECT_EQ(i.idx(), 11);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 4));

	i = x.end();
	i.ref.append(y.ref.sub());
	EXPECT_EQ(22, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
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
		x.ref.push_back(i);
	array<int> y0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > y;
	for (array<int>::iterator i = y0.begin(); i; i++)
		y.ref.push_back(i);

	slice<array<array<int>::iterator> >::iterator i = x.at(4);
	i.ref.replace(3, *y.at(5).ref);
	EXPECT_EQ(8, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 4)
			+ 5
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.ref.replace(3, *y.at(3).ref);
	EXPECT_EQ(6, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 4)
			+ 3
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.ref.replace(1, *y.at(8).ref);
	EXPECT_EQ(6, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 4)
			+ 8
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.ref.replace(-1, *y.at(9).ref);
	EXPECT_EQ(6, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 3)
			+ 9
			+ 8
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.ref.replace(-1, *y.at(6).ref);
	EXPECT_EQ(6, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 3)
			+ 6
			+ 8
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.ref.replace(-4, *y.at(2).ref);
	EXPECT_EQ(3, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
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
		x.ref.push_back(i);
	array<int> y0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > y;
	for (array<int>::iterator i = y0.begin(); i; i++)
		y.ref.push_back(i);

	slice<array<array<int>::iterator> >::iterator i = x.at(4);
	i.ref.replace(3, y.ref.sub(0, 3));
	EXPECT_EQ(10, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 4)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.ref.replace(3, y.ref.sub(0, 1));
	EXPECT_EQ(8, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 4)
			+ y[0]
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.ref.replace(1, y.ref.sub(0, 3));
	EXPECT_EQ(10, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 4)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 4);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.ref.replace(-1, y.ref.sub(0, 6));
	EXPECT_EQ(15, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 3)
			+ y.sub(0, 6)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 9);
	EXPECT_EQ(x0, range<int>(0, 10));
	EXPECT_EQ(y0, range<int>(0, 10));

	i = x.at(4);
	i.ref.replace(-1, y.ref.sub(0, 2));
	EXPECT_EQ(16, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
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
	i.ref.replace(-1, y.ref.sub(0, 6));
	EXPECT_EQ(21, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
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
	i.ref.replace(-4, y.ref.sub(0, 2));
	EXPECT_EQ(19, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
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
	i.ref.replace(-4, fill<array<int>::iterator>(4, *y.at(9).ref));
	EXPECT_EQ(19, x.ref.count);
	EXPECT_GE(x.ref.capacity, x.ref.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.ref.data);
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
		x.ref.push_back(i);

	x.at(5).swap(x.at(2));
	EXPECT_EQ(5, x[2]);
	EXPECT_EQ(2, x[5]);
	EXPECT_EQ(x0, array_t<int>(10, 0, 1, 5, 3, 4, 2, 6, 7, 8, 9));

	x.begin().swap(x.rbegin());
	EXPECT_EQ(9, x[0]);
	EXPECT_EQ(0, x[9]);
	EXPECT_EQ(x0, array_t<int>(10, 9, 1, 5, 3, 4, 2, 6, 7, 8, 0));
}
