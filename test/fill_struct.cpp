#include <gtest/gtest.h>

#include <core/fill.h>
#include <core/ascii_stream.h>

using namespace core;

TEST(fill_struct, base_constructor)
{
	fill<int> x(20, 10);
	EXPECT_EQ(20, x.count);
	EXPECT_EQ(10, x.value);
}

TEST(fill_struct, copy_constructor)
{
	fill<int> y(5, 10);
	fill<int> x(y);
	EXPECT_EQ(x, y);
}

TEST(fill_struct, index)
{
	fill<int> x(8, 5);

	EXPECT_EQ(8, x.size());

	EXPECT_EQ(5, *x.at(0));
	EXPECT_EQ(5, *x.at(2));
	EXPECT_EQ(5, *x.at(-1));
	EXPECT_EQ(5, *x.at(-3));

	EXPECT_EQ(5, x.get(0));
	EXPECT_EQ(5, x.get(2));
	EXPECT_EQ(5, x.get(-1));
	EXPECT_EQ(5, x.get(-3));

	EXPECT_EQ(5, x[0]);
	EXPECT_EQ(5, x[2]);
	EXPECT_EQ(5, x[-1]);
	EXPECT_EQ(5, x[-3]);

	EXPECT_EQ(5, x.front());
	EXPECT_EQ(5, x.back());

	EXPECT_EQ(5, *x.begin());
	EXPECT_EQ(5, *x.rbegin());
}

TEST(fill_struct, sub)
{
	fill<int> x(8, 5);
	fill<int> y(4, 5);

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
	EXPECT_EQ(y, x.sub(4));
	EXPECT_EQ(y, x.sub(-4));
	EXPECT_EQ(y, x.subcpy(4));
	EXPECT_EQ(y, x.subcpy(-4));

	// ref
	EXPECT_EQ(x, x.sub());
	EXPECT_EQ(y, y.sub());
}

TEST(fill_struct, swap)
{
	fill<int> x(10, 10);
	fill<int> y(8, 5);
	EXPECT_EQ(fill<int>(10, 10), x);
	EXPECT_EQ(fill<int>(8, 5), y);
	x.swap(y);
	EXPECT_EQ(fill<int>(10, 10), y);
	EXPECT_EQ(fill<int>(8, 5), x);
}

TEST(fill_struct, compare)
{
	fill<int> x(10, 5);
	fill<int> y(10, 6);

	EXPECT_TRUE(x < y);
	EXPECT_FALSE(x > y);
	EXPECT_TRUE(x <= y);
	EXPECT_FALSE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);

	x = fill<int>(9, 5);
	y = fill<int>(10, 5);

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

	x = fill<int>(10, 5);
	y = fill<int>(9, 6);

	EXPECT_TRUE(x < y);
	EXPECT_FALSE(x > y);
	EXPECT_TRUE(x <= y);
	EXPECT_FALSE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);

	x = fill<int>(10, 5);
	y = fill<int>(9, 4);

	EXPECT_FALSE(x < y);
	EXPECT_TRUE(x > y);
	EXPECT_FALSE(x <= y);
	EXPECT_TRUE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);
}
