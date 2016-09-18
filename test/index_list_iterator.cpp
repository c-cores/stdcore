#include <gtest/gtest.h>

#include <core/index_list.h>
#include <core/fill.h>
#include <core/ascii_stream.h>
#include <core/sparse_range.h>
#include <core/compare.h>

using namespace core;

TEST(index_list_iterator, iterate)
{
	index_list<int> x = range<int>(0, 10);

	int j = 0;
	for (index_list<int>::iterator i = x.begin(); i != x.end(); i++)
	{
		EXPECT_EQ(j, *i);
		j++;
	}
	EXPECT_EQ(10, j);
}

TEST(index_list_iterator, index)
{
	index_list<int> x = index_list<int>::values(8, 5, 2, 3, 5, 6, 2, 1, 7);

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

	x.at(2).get() = 5;
	x.at(-3).get() = 9;

	EXPECT_EQ(5, *x.at(2));
	EXPECT_EQ(9, *x.at(-3));
}

TEST(index_list_iterator, sub)
{
	index_list<int> x = range<int>(0, 10);
	EXPECT_EQ(x.at(4).sub(3), range<int>(4, 7));
	EXPECT_EQ(x.at(7).sub(-3), range<int>(4, 7));
	EXPECT_EQ(x.at(4).sub(), range<int>(4, 10));
	EXPECT_EQ(x.at(4).subcpy(3), range<int>(4, 7));
	EXPECT_EQ(x.at(7).subcpy(-3), range<int>(4, 7));
	EXPECT_EQ(x.at(4).subcpy(), range<int>(4, 10));

	const index_list<int> y = range<int>(0, 10);
	EXPECT_EQ(y.at(4).sub(3), range<int>(4, 7));
	EXPECT_EQ(y.at(7).sub(-3), range<int>(4, 7));
	EXPECT_EQ(x.at(4).sub(), range<int>(4, 10));
	EXPECT_EQ(y.at(4).subcpy(3), range<int>(4, 7));
	EXPECT_EQ(y.at(7).subcpy(-3), range<int>(4, 7));
	EXPECT_EQ(x.at(4).subcpy(), range<int>(4, 10));
}

TEST(index_list_iterator, drop)
{
	index_list<int> x = range<int>(0, 10);

	index_list<int>::iterator i = x.at(0);
	i.drop(1);
	EXPECT_EQ(9, x.size());
	EXPECT_EQ(x, range<int>(1, 10));
	EXPECT_EQ(i.idx(), 0);

	i = x.at(2);
	i.drop(-2);
	EXPECT_EQ(7, x.size());
	EXPECT_EQ(x, range<int>(3, 10));
	EXPECT_EQ(i.idx(), 0);

	i = x.at(4);
	i.drop(-2);
	EXPECT_EQ(5, x.size());
	EXPECT_EQ(x, index_list<int>::values(5, 3, 4, 7, 8, 9));
	EXPECT_EQ(i.idx(), 2);

	i = x.at(2);
	i.drop(2);
	EXPECT_EQ(3, x.size());
	EXPECT_EQ(x, index_list<int>::values(3, 3, 4, 9));
	EXPECT_EQ(i.idx(), 2);

	i = x.at(2);
	i.drop(1);
	EXPECT_EQ(2, x.size());
	EXPECT_EQ(x, index_list<int>::values(2, 3, 4));
	EXPECT_EQ(i.idx(), 2);
}

TEST(index_list_iterator, pop)
{
	index_list<int> x = range<int>(0, 10);
	index_list<int> y;

	index_list<int>::iterator i = x.at(0);
	y = i.pop(1);
	EXPECT_EQ(9, x.size());
	EXPECT_EQ(x, range<int>(1, 10));
	EXPECT_EQ(1, y.size());
	EXPECT_EQ(0, y[0]);
	EXPECT_EQ(i.idx(), 0);

	i = x.at(2);
	y = i.pop(-2);
	EXPECT_EQ(7, x.size());
	EXPECT_EQ(x, range<int>(3, 10));

	EXPECT_EQ(2, y.size());
	EXPECT_EQ(y, range<int>(1, 3));
	EXPECT_EQ(i.idx(), 0);

	i = x.at(4);
	y = i.pop(-2);
	EXPECT_EQ(5, x.size());
	EXPECT_EQ(x, index_list<int>::values(5, 3, 4, 7, 8, 9));

	EXPECT_EQ(2, y.size());
	EXPECT_EQ(y, range<int>(5, 7));
	EXPECT_EQ(i.idx(), 2);

	i = x.at(2);
	y = i.pop(2);
	EXPECT_EQ(3, x.size());
	EXPECT_EQ(x, index_list<int>::values(3, 3, 4, 9));

	EXPECT_EQ(2, y.size());
	EXPECT_EQ(y, index_list<int>::values(2, 7, 8));
	EXPECT_EQ(i.idx(), 2);

	i = x.at(2);
	y = i.pop(1);
	EXPECT_EQ(2, x.size());
	EXPECT_EQ(x, range<int>(3, 5));

	EXPECT_EQ(1, y.size());
	EXPECT_EQ(y[0], 9);
	EXPECT_EQ(i.idx(), 2);
}

TEST(index_list_iterator, push)
{
	index_list<int> x = range<int>(0, 10);

	// We can't use operator<< here because that uses
	// the push function and we can't use the push function
	// to test the push function :/
	index_list<int>::iterator i = x.at(0);
	i.push(5);
	EXPECT_EQ(11, x.size());
	EXPECT_EQ(x[0], 5);
	EXPECT_EQ(x.sub(1, 11), range<int>(0, 10));
	EXPECT_EQ(i.idx(), 1);

	i = x.at(5);
	i.push(3);
	EXPECT_EQ(12, x.size());
	EXPECT_EQ(x[0], 5);
	EXPECT_EQ(x.sub(1, 5), range<int>(0, 4));
	EXPECT_EQ(x[5], 3);
	EXPECT_EQ(x.sub(6, 12), range<int>(4, 10));
	EXPECT_EQ(i.idx(), 6);

	i = x.at(12);
	i.push(8);
	EXPECT_EQ(13, x.size());
	EXPECT_EQ(x[0], 5);
	EXPECT_EQ(x.sub(1, 5), range<int>(0, 4));
	EXPECT_EQ(x[5], 3);
	EXPECT_EQ(x.sub(6, 12), range<int>(4, 10));
	EXPECT_EQ(x[12], 8);
	EXPECT_EQ(i.idx(), 13);
}

TEST(index_list_iterator, append)
{
	index_list<int> x = range<int>(0, 10);
	index_list<int> y = range<int>(0, 4);

	// We can't use operator<< here because that uses
	// the append function and we can't use the append function
	// to test the append function :/
	index_list<int>::iterator i = x.begin();
	i.append(y);
	EXPECT_EQ(14, x.size());
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 14), range<int>(0, 10));
	EXPECT_EQ(i.idx(), 4);

	i = x.at(7);
	i.append(y);
	EXPECT_EQ(18, x.size());
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 7), range<int>(0, 3));
	EXPECT_EQ(x.sub(7, 11), range<int>(0, 4));
	EXPECT_EQ(x.sub(11, 18), range<int>(3, 10));
	EXPECT_EQ(i.idx(), 11);

	i = x.end();
	i.append(y);
	EXPECT_EQ(22, x.size());
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 7), range<int>(0, 3));
	EXPECT_EQ(x.sub(7, 11), range<int>(0, 4));
	EXPECT_EQ(x.sub(11, 18), range<int>(3, 10));
	EXPECT_EQ(x.sub(18, 22), range<int>(0, 4));
	EXPECT_EQ(i.idx(), x.size());

	x = range<int>(0, 10);

	i = x.begin();
	i.append(y.sub());
	EXPECT_EQ(14, x.size());
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 14), range<int>(0, 10));
	EXPECT_EQ(i.idx(), 4);

	i = x.at(7);
	i.append(y.sub());
	EXPECT_EQ(18, x.size());
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 7), range<int>(0, 3));
	EXPECT_EQ(x.sub(7, 11), range<int>(0, 4));
	EXPECT_EQ(x.sub(11, 18), range<int>(3, 10));
	EXPECT_EQ(i.idx(), 11);

	i = x.end();
	i.append(y.sub());
	EXPECT_EQ(22, x.size());
	EXPECT_EQ(x.sub(0, 4), range<int>(0, 4));
	EXPECT_EQ(x.sub(4, 7), range<int>(0, 3));
	EXPECT_EQ(x.sub(7, 11), range<int>(0, 4));
	EXPECT_EQ(x.sub(11, 18), range<int>(3, 10));
	EXPECT_EQ(x.sub(18, 22), range<int>(0, 4));
	EXPECT_EQ(i.idx(), x.size());
}

TEST(index_list_iterator, replace)
{
	index_list<int> x = range<int>(0, 10);
	index_list<int> y = range<int>(0, 10);

	index_list<int>::iterator i = x.at(4);
	i.replace(3, 5);
	EXPECT_EQ(8, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ range<int>(0, 4)
			+ 5
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 5);

	i = x.at(4);
	i.replace(3, 3);
	EXPECT_EQ(6, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ range<int>(0, 4)
			+ 3
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 5);

	i = x.at(4);
	i.replace(1, 8);
	EXPECT_EQ(6, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ range<int>(0, 4)
			+ 8
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 5);

	i = x.at(4);
	i.replace(-1, 9);
	EXPECT_EQ(6, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ range<int>(0, 3)
			+ 9
			+ 8
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 4);

	i = x.at(4);
	i.replace(-1, 6);
	EXPECT_EQ(6, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ range<int>(0, 3)
			+ 6
			+ 8
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 4);

	i = x.at(4);
	i.replace(-4, 2);
	EXPECT_EQ(3, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ 2
			+ 8
			+ range<int>(9, 10));
	EXPECT_EQ(i.idx(), 1);
}

TEST(index_list_iterator, replace_container)
{
	index_list<int> x = range<int>(0, 10);
	index_list<int> y = range<int>(0, 10);

	index_list<int>::iterator i = x.at(4);
	i.replace(3, y.sub(0, 3));
	EXPECT_EQ(10, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ range<int>(0, 4)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 7);

	i = x.at(4);
	i.replace(3, y.sub(0, 1));
	EXPECT_EQ(8, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ range<int>(0, 4)
			+ y[0]
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 5);

	i = x.at(4);
	i.replace(1, y.sub(0, 3));
	EXPECT_EQ(10, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ range<int>(0, 4)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 7);

	i = x.at(4);
	i.replace(-1, y.sub(0, 6));
	EXPECT_EQ(15, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ range<int>(0, 3)
			+ y.sub(0, 6)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 9);

	i = x.at(4);
	i.replace(-1, y.sub(0, 2));
	EXPECT_EQ(16, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ range<int>(0, 3)
			+ y.sub(0, 2)
			+ y.sub(1, 6)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 5);

	i = x.at(4);
	i.replace(-1, y.sub(0, 6));
	EXPECT_EQ(21, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ range<int>(0, 3)
			+ y.sub(0, 6)
			+ y.sub(1, 2)
			+ y.sub(1, 6)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 9);

	i = x.at(4);
	i.replace(-4, y.sub(0, 2));
	EXPECT_EQ(19, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ y.sub(0, 2)
			+ y.sub(1, 6)
			+ y.sub(1, 2)
			+ y.sub(1, 6)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 2);

	i = x.at(4);
	i.replace(-4, fill<int>(4, 10));
	EXPECT_EQ(19, x.size());
	EXPECT_EQ(x, index_list<int>()
			+ fill<int>(4, 10)
			+ y.sub(3, 6)
			+ y.sub(1, 2)
			+ y.sub(1, 6)
			+ y.sub(0, 3)
			+ range<int>(7, 10));
	EXPECT_EQ(i.idx(), 4);
}

TEST(index_list_iterator, swap)
{
	index_list<int> x = range<int>(0, 10);

	x.at(5).swap(x.at(2));
	EXPECT_EQ(5, x[2]);
	EXPECT_EQ(2, x[5]);

	x.begin().swap(x.rbegin());
	EXPECT_EQ(9, x[0]);
	EXPECT_EQ(0, x[9]);
}
