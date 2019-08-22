#include <gtest/gtest.h>

#include <std/list.h>
#include <std/fill.h>
#include <std/sparse_range.h>

using namespace core;

TEST(list_struct, base_constructor)
{
	list<int> x;
	EXPECT_EQ(x.size(), 0);
	EXPECT_EQ(x.left->prev, x.left);
	EXPECT_EQ(x.left->next, x.right);
	EXPECT_EQ(x.right->prev, x.left);
	EXPECT_EQ(x.right->next, x.right);
}

TEST(list_struct, copy_constructor)
{
	list<int> x(list_t<int>(5, 1, 9, 7, 2, 5));
	EXPECT_EQ(x, list_t<int>(5, 1, 9, 7, 2, 5));
}

TEST(list_struct, fill_constructor)
{
	list<int> x = fill<int>(20, 10);
	EXPECT_EQ(20, x.size());
	for (int i = 0; i < x.size(); i++)
		EXPECT_EQ(x[i], 10);
}

TEST(list_struct, sparse_range_constructor)
{
	list<int> x = sparse_range<int>(0, 10);
	EXPECT_EQ(10, x.size());
	for (int i = 0; i < x.size(); i++)
		EXPECT_EQ(x[i], i);

	x = sparse_range<int>(10, 0, -1);
	EXPECT_EQ(10, x.size());
	for (int i = 0; i < x.size(); i++)
		EXPECT_EQ(x[i], 10-i);

	x = sparse_range<int>(0, 10, 2);
	EXPECT_EQ(5, x.size());
	for (int i = 0; i < x.size(); i++)
		EXPECT_EQ(x[i], i*2);

	x = sparse_range<int>(10, 0, -2);
	EXPECT_EQ(5, x.size());
	for (int i = 0; i < x.size(); i++)
		EXPECT_EQ(x[i], 10-i*2);
}

TEST(list_struct, value_constructor)
{
	list<int> x = list_t<int>(5, 1, 3, 5, 7, 9);
	EXPECT_EQ(5, x.size());
	for (int i = 0; i < x.size(); i++)
		EXPECT_EQ(x[i], i*2+1);
}

TEST(list_struct, index)
{
	list<int> x = list_t<int>(8, 5, 2, 3, 5, 6, 2, 1, 7);
	EXPECT_EQ(8, x.size());

	EXPECT_EQ(5, *x.at(0));
	EXPECT_EQ(3, *x.at(2));
	EXPECT_EQ(7, *x.at(-1));
	EXPECT_EQ(2, *x.at(-3));

	EXPECT_EQ(5, x.get(0));
	EXPECT_EQ(3, x.get(2));
	EXPECT_EQ(7, x.get(-1));
	EXPECT_EQ(2, x.get(-3));

	EXPECT_EQ(5, *x.ptr(0));
	EXPECT_EQ(3, *x.ptr(2));
	EXPECT_EQ(7, *x.ptr(-1));
	EXPECT_EQ(2, *x.ptr(-3));

	EXPECT_EQ(5, x[0]);
	EXPECT_EQ(3, x[2]);
	EXPECT_EQ(7, x[-1]);
	EXPECT_EQ(2, x[-3]);

	EXPECT_EQ(5, x.front());
	EXPECT_EQ(7, x.back());

	EXPECT_EQ(5, *x.begin());
	EXPECT_EQ(7, *x.rbegin());
}

TEST(list_struct, sub)
{
	list<int> x = list_t<int>(8, 5, 2, 3, 5, 6, 2, 1, 7);
	list<int> y = list_t<int>(4, 3, 5, 6, 2);
	list<int> z = list_t<int>(4, 6, 2, 1, 7);

	// positive start and end
	EXPECT_EQ(y, x.sub(2, 6));
	EXPECT_EQ(y, x.subcpy(2, 6));

	// positive start, negative end
	EXPECT_EQ(y, x.sub(2, -2));
	EXPECT_EQ(y, x.subcpy(2, -2));

	// negative start and end
	EXPECT_EQ(y, x.sub(-6, -2));
	EXPECT_EQ(y, x.subcpy(-6, -2));

	// negative start, positive end
	EXPECT_EQ(y, x.sub(-6, 6));
	EXPECT_EQ(y, x.subcpy(-6, 6));
	
	// single input
	EXPECT_EQ(z, x.sub(4));
	EXPECT_EQ(z, x.sub(-4));
	EXPECT_EQ(z, x.subcpy(4));
	EXPECT_EQ(z, x.subcpy(-4));

	// no inputs
	EXPECT_EQ(x, x.sub());
	EXPECT_EQ(y, y.sub());
	EXPECT_EQ(z, z.sub());
}

TEST(list_struct, drop)
{
	list<int> x = sparse_range<int>(0, 10);
	x.drop_back(5);
	EXPECT_EQ(sparse_range<int>(0, 5), x);

	x = sparse_range<int>(0, 10);
	x.drop_front(5);
	EXPECT_EQ(sparse_range<int>(5, 10), x);

	x = sparse_range<int>(0, 10);
	x.drop(3, 8);
	EXPECT_EQ(x, list<int>()
			+ sparse_range<int>(0, 3)
			+ sparse_range<int>(8, 10));

	x = sparse_range<int>(0, 10);
	x.drop(-7, -2);
	EXPECT_EQ(x, list<int>()
			+ sparse_range<int>(0, 3)
			+ sparse_range<int>(8, 10));
}

TEST(list_struct, pop)
{
	list<int> x = sparse_range<int>(0, 10);
	list<int> y = x.pop_back(5);
	EXPECT_EQ(sparse_range<int>(0, 5), x);
	EXPECT_EQ(sparse_range<int>(5, 10), y);

	x = sparse_range<int>(0, 10);
	y = x.pop_front(5);
	EXPECT_EQ(sparse_range<int>(5, 10), x);
	EXPECT_EQ(sparse_range<int>(0, 5), y);

	x = sparse_range<int>(0, 10);
	y = x.pop(3, 8);
	EXPECT_EQ(x, list<int>()
			+ sparse_range<int>(0, 3)
			+ sparse_range<int>(8, 10));
	EXPECT_EQ(y, sparse_range<int>(3, 8));

	x = sparse_range<int>(0, 10);
	y = x.pop(-7, -2);
	EXPECT_EQ(x, list<int>()
			+ sparse_range<int>(0, 3)
			+ sparse_range<int>(8, 10));
	EXPECT_EQ(y, sparse_range<int>(3, 8));
}

TEST(list_struct, push_back)
{
	list<int> x;
	EXPECT_EQ(0, x.size());
	for (int i = 0; i < 10; i++)
	{
		x.push_back(i);
		EXPECT_EQ(i+1, x.size());
	}

	x.push_back(20);
	EXPECT_EQ(11, x.size());
	EXPECT_EQ(x.sub(0, 10), sparse_range<int>(0, 10));
	EXPECT_EQ(x[10], 20);
}

TEST(list_struct, push_front)
{
	list<int> x;
	EXPECT_EQ(0, x.size());
	for (int i = 0; i < 10; i++)
	{
		x.push_front(9 - i);
		EXPECT_EQ(i+1, x.size());
	}

	EXPECT_EQ(sparse_range<int>(0, 10), x);
}

TEST(list_struct, append_back)
{
	list<int> x = fill<int>(1, 8);
	list<int> y = fill<int>(1, 3);
	list<int> z;
	EXPECT_EQ(1, x.size());
	EXPECT_EQ(1, y.size());

	z = x;
	x.append_back(y);
	EXPECT_EQ(z.size() + y.size(), x.size());
	EXPECT_EQ(z, x.sub(0, z.size()));
	EXPECT_EQ(y, x.sub(z.size(), z.size()+y.size()));

	z = y;
	y.append_back(x);
	EXPECT_EQ(z.size() + x.size(), y.size());
	EXPECT_EQ(z, y.sub(0, z.size()));
	EXPECT_EQ(x, y.sub(z.size(), z.size()+x.size()));

	z = x;
	x.append_back(y);
	EXPECT_EQ(z.size()+y.size(), x.size());
	EXPECT_EQ(z, x.sub(0, z.size()));
	EXPECT_EQ(y, x.sub(z.size(), z.size()+y.size()));
	
	z = x;
	x.append_back(list<int>());
	EXPECT_EQ(z, x);
}

TEST(list_struct, append_front)
{
	list<int> x = fill<int>(1, 8);
	list<int> y = fill<int>(1, 3);
	list<int> z;
	EXPECT_EQ(1, x.size());
	EXPECT_EQ(1, y.size());

	z = x;
	x.append_front(y);
	EXPECT_EQ(z.size()+y.size(), x.size());
	EXPECT_EQ(y, x.sub(0, y.size()));
	EXPECT_EQ(z, x.sub(y.size(), y.size()+z.size()));
	
	z = y;
	y.append_front(x);
	EXPECT_EQ(3, y.size());
	EXPECT_EQ(x, y.sub(0, x.size()));
	EXPECT_EQ(z, y.sub(x.size(), x.size()+z.size()));

	z = x;
	x.append_front(y);
	EXPECT_EQ(z.size()+y.size(), x.size());
	EXPECT_EQ(y, x.sub(0, y.size()));
	EXPECT_EQ(z, x.sub(y.size(), y.size()+z.size()));

	z = x;
	x.append_front(list<int>());
	EXPECT_EQ(z, x);
}

TEST(list_struct, replace)
{
	list<int> x = sparse_range<int>(0, 10);
	EXPECT_EQ(x, sparse_range<int>(0, 10));

	x.replace(0, 3, 5);
	EXPECT_EQ(x, list<int>()
			+ 5
			+ sparse_range<int>(3, 10));

	x = sparse_range<int>(0, 10);
	x.replace(7, 10, 5);
	EXPECT_EQ(x, list<int>()
				+ sparse_range<int>(0, 7)
				+ 5);

	x = sparse_range<int>(0, 10);
	x.replace(3, 7, 5);
	EXPECT_EQ(x, list<int>()
				+ sparse_range<int>(0, 3)
				+ 5
				+ sparse_range<int>(7, 10));

	x = sparse_range<int>(0, 10);
	x.replace(-7, -3, 5);
	EXPECT_EQ(x, list<int>()
				+ sparse_range<int>(0, 3)
				+ 5
				+ sparse_range<int>(7, 10));

	x = sparse_range<int>(0, 10);
	x.replace(-7, 7, 5);
	EXPECT_EQ(x, list<int>()
				+ sparse_range<int>(0, 3)
				+ 5
				+ sparse_range<int>(7, 10));

	x = sparse_range<int>(0, 10);
	x.replace(3, -3, 5);
	EXPECT_EQ(x, list<int>()
				+ sparse_range<int>(0, 3)
				+ 5
				+ sparse_range<int>(7, 10));

	x = sparse_range<int>(0, 10);
	x.replace_front(3, 5);
	EXPECT_EQ(x, list<int>()
			+ 5
			+ sparse_range<int>(3, 10));

	x = sparse_range<int>(0, 10);
	x.replace_back(3, 5);
	EXPECT_EQ(x, list<int>()
				+ sparse_range<int>(0, 7)
				+ 5);
}

TEST(list_struct, replace_container)
{
	list<int> x = sparse_range<int>(0, 10);
	EXPECT_EQ(x, sparse_range<int>(0, 10));
	list<int> y = list_t<int>(5, 2, 5, 3, 7, 2);

	x.replace(0, 3, y);
	EXPECT_EQ(x, list<int>()
			+ y
			+ sparse_range<int>(3, 10));

	x = sparse_range<int>(0, 10);
	x.replace(7, 10, y);
	EXPECT_EQ(x, list<int>()
				+ sparse_range<int>(0, 7)
				+ y);

	x = sparse_range<int>(0, 10);
	x.replace(3, 7, y);
	EXPECT_EQ(x, list<int>()
				+ sparse_range<int>(0, 3)
				+ y
				+ sparse_range<int>(7, 10));

	x = sparse_range<int>(0, 10);
	x.replace(-7, -3, y);
	EXPECT_EQ(x, list<int>()
				+ sparse_range<int>(0, 3)
				+ y
				+ sparse_range<int>(7, 10));

	x = sparse_range<int>(0, 10);
	x.replace(-7, 7, y);
	EXPECT_EQ(x, list<int>()
				+ sparse_range<int>(0, 3)
				+ y
				+ sparse_range<int>(7, 10));

	x = sparse_range<int>(0, 10);
	x.replace(3, -3, y);
	EXPECT_EQ(x, list<int>()
				+ sparse_range<int>(0, 3)
				+ y
				+ sparse_range<int>(7, 10));

	x = sparse_range<int>(0, 10);
	x.replace_front(3, y);
	EXPECT_EQ(x, list<int>()
			+ y
			+ sparse_range<int>(3, 10));

	x = sparse_range<int>(0, 10);
	x.replace_back(3, y);
	EXPECT_EQ(x, list<int>()
				+ sparse_range<int>(0, 7)
				+ y);
}

TEST(list_struct, swap)
{
	list<int> x = sparse_range<int>(0, 10);
	list<int> y = fill<int>(8, 5);
	EXPECT_EQ(sparse_range<int>(0, 10), x);
	EXPECT_EQ(fill<int>(8, 5), y);
	x.swap(y);
	EXPECT_EQ(sparse_range<int>(0, 10), y);
	EXPECT_EQ(fill<int>(8, 5), x);
}

TEST(list_struct, resize)
{
	list<int> x;
	x.resize(20, 10);
	EXPECT_EQ(fill<int>(20, 10), x);

	x.resize(10, 5);
	EXPECT_EQ(fill<int>(10, 10), x);
}

TEST(list_struct, clear)
{
	list<int> x = sparse_range<int>(0, 10);
	EXPECT_EQ(10, x.size());

	x.clear();
	EXPECT_EQ(0, x.size());
}

TEST(list_struct, release)
{
	list<int> x = sparse_range<int>(0, 10);
	EXPECT_EQ(10, x.size());

	x.release();
	EXPECT_EQ(0, x.size());
}

TEST(list_struct, assign)
{
	list<int> x = sparse_range<int>(0, 10);
	EXPECT_EQ(10, x.size());

	list<int> y, z;

	y = x;
	z = x.sub();
	EXPECT_EQ(y, x);
	EXPECT_EQ(z, x);
	EXPECT_EQ(y, z);
}

TEST(list_struct, compare)
{
	list<int> x = sparse_range<int>(0, 10);
	list<int> y = sparse_range<int>(10, 0, -1);

	EXPECT_TRUE(x < y);
	EXPECT_FALSE(x > y);
	EXPECT_TRUE(x <= y);
	EXPECT_FALSE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);

	x.clear();
	y.clear();

	x = sparse_range<int>(0, 5);
	y = sparse_range<int>(0, 10);

	EXPECT_TRUE(x < y);
	EXPECT_FALSE(x > y);
	EXPECT_TRUE(x <= y);
	EXPECT_FALSE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);

	x = y;

	EXPECT_FALSE(x < y);
	EXPECT_FALSE(x > y);
	EXPECT_TRUE(x <= y);
	EXPECT_TRUE(x >= y);
	EXPECT_TRUE(x == y);
	EXPECT_FALSE(x != y);

	x.clear();
	y.clear();

	for (int i = 0; i < 5; i++)
		x.push_back(i);
	for (int i = 0; i < 10; i++)
	{
		y.push_back(i);
		x.push_back(10+i);
	}

	EXPECT_FALSE(x < y);
	EXPECT_TRUE(x > y);
	EXPECT_FALSE(x <= y);
	EXPECT_TRUE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);
}
