#include <gtest/gtest.h>

#include <std/ascii_stream.h>
#include <std/sparse_range.h>
#include <std/compare.h>

using namespace core;

TEST(sparse_range_struct, base_constructor)
{
	sparse_range<int> x(0, 10);
	EXPECT_EQ(0, x.start);
	EXPECT_EQ(10, x.finish);
	EXPECT_EQ(1, x.step);

	sparse_range<int> y(0, 10, 2);
	EXPECT_EQ(0, y.start);
	EXPECT_EQ(10, y.finish);
	EXPECT_EQ(2, y.step);
}

TEST(sparse_range_struct, copy_constructor)
{
	sparse_range<int> y(5, 10);
	sparse_range<int> x(y);
	EXPECT_EQ(x, y);
}

TEST(sparse_range_struct, index)
{
	sparse_range<int> x(0, 16, 2);
	EXPECT_EQ(8, x.size());

	EXPECT_EQ(0, *x.at(0));
	EXPECT_EQ(4, *x.at(2));
	EXPECT_EQ(14, *x.at(-1));
	EXPECT_EQ(10, *x.at(-3));

	EXPECT_EQ(0, x.get(0));
	EXPECT_EQ(4, x.get(2));
	EXPECT_EQ(14, x.get(-1));
	EXPECT_EQ(10, x.get(-3));

	EXPECT_EQ(0, x[0]);
	EXPECT_EQ(4, x[2]);
	EXPECT_EQ(14, x[-1]);
	EXPECT_EQ(10, x[-3]);

	EXPECT_EQ(0, x.front());
	EXPECT_EQ(14, x.back());

	EXPECT_EQ(0, *x.begin());
	EXPECT_EQ(14, *x.rbegin());
}

TEST(sparse_range_struct, sub)
{
	sparse_range<int> x(0, 16, 2);
	sparse_range<int> y(4, 12, 2);

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

	y = sparse_range<int>(8, 16, 2);
	// single input
	EXPECT_EQ(y, x.sub(4));
	EXPECT_EQ(y, x.sub(-4));
	EXPECT_EQ(y, x.subcpy(4));
	EXPECT_EQ(y, x.subcpy(-4));

	// ref
	EXPECT_EQ(x, x.sub());
	EXPECT_EQ(y, y.sub());
}

TEST(sparse_range_struct, swap)
{
	sparse_range<int> x(0, 10);
	sparse_range<int> y(10, 15);
	EXPECT_EQ(sparse_range<int>(0, 10), x);
	EXPECT_EQ(sparse_range<int>(10, 15), y);
	x.swap(y);
	EXPECT_EQ(sparse_range<int>(0, 10), y);
	EXPECT_EQ(sparse_range<int>(10, 15), x);
}

TEST(sparse_range_struct, compare)
{
	sparse_range<int> x(0, 10);
	sparse_range<int> y(10, 0);

	EXPECT_TRUE(x < y);
	EXPECT_FALSE(x > y);
	EXPECT_TRUE(x <= y);
	EXPECT_FALSE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);

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

	x = sparse_range<int>(0, 10, 2);
	y = sparse_range<int>(10, 0, -2);

	EXPECT_TRUE(x < y);
	EXPECT_FALSE(x > y);
	EXPECT_TRUE(x <= y);
	EXPECT_FALSE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);

	x = sparse_range<int>(0, 5, 2);
	y = sparse_range<int>(0, 10, 2);

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
}
