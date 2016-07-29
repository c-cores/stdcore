#include <gtest/gtest.h>

#include <core/ascii_stream.h>
#include <core/slice.h>

using namespace core;

TEST(range_struct, base_constructor)
{
	range<int> x(0, 10);
	EXPECT_EQ(0, x.start);
	EXPECT_EQ(10, x.finish);
}

TEST(range_struct, copy_constructor)
{
	range<int> y(5, 10);
	range<int> x(y);
	EXPECT_EQ(x, y);
}

TEST(range_struct, index)
{
	range<int> x(0, 8);
	EXPECT_EQ(8, x.size());

	EXPECT_EQ(0, *x.at(0));
	EXPECT_EQ(2, *x.at(2));
	EXPECT_EQ(7, *x.at(-1));
	EXPECT_EQ(5, *x.at(-3));

	EXPECT_EQ(0, x.get(0));
	EXPECT_EQ(2, x.get(2));
	EXPECT_EQ(7, x.get(-1));
	EXPECT_EQ(5, x.get(-3));

	EXPECT_EQ(0, x[0]);
	EXPECT_EQ(2, x[2]);
	EXPECT_EQ(7, x[-1]);
	EXPECT_EQ(5, x[-3]);

	EXPECT_EQ(0, x.front());
	EXPECT_EQ(7, x.back());

	EXPECT_EQ(0, *x.begin());
	EXPECT_EQ(7, *x.rbegin());
}

TEST(range_struct, sub)
{
	range<int> x(0, 8);
	range<int> y(2, 6);

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

	y = range<int>(4, 8);
	// single input
	EXPECT_EQ(y, x.sub(4));
	EXPECT_EQ(y, x.sub(-4));
	EXPECT_EQ(y, x.subcpy(4));
	EXPECT_EQ(y, x.subcpy(-4));

	// ref
	EXPECT_EQ(x, x.sub());
	EXPECT_EQ(y, y.sub());
}

TEST(range_struct, swap)
{
	range<int> x(0, 10);
	range<int> y(10, 15);
	EXPECT_EQ(range<int>(0, 10), x);
	EXPECT_EQ(range<int>(10, 15), y);
	x.swap(y);
	EXPECT_EQ(range<int>(0, 10), y);
	EXPECT_EQ(range<int>(10, 15), x);
}

TEST(range_struct, compare)
{
	range<int> x(0, 10);
	range<int> y(10, 0);

	EXPECT_TRUE(x < y);
	EXPECT_FALSE(x > y);
	EXPECT_TRUE(x <= y);
	EXPECT_FALSE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);

	x = range<int>(0, 5);
	y = range<int>(0, 10);

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
