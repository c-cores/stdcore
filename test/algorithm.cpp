#include <gtest/gtest.h>

#include <core/array.h>
#include <core/list.h>
#include <core/range.h>
#include <core/fill.h>
#include <core/ascii_stream.h>
#include <core/algorithm.h>

using namespace core;

TEST(algorithm, collapse)
{
	array<int> x;

	x = range<int>(0, 10);
	EXPECT_EQ(x, range<int>(0, 10));
	collapse_inplace(x);
	EXPECT_EQ(x, range<int>(0, 10));

	x = fill<int>(10, 4);
	EXPECT_EQ(x, fill<int>(10, 4));
	collapse_inplace(x);
	EXPECT_EQ(x, fill<int>(1, 4));

	x = array<int>::values(10, 1, 1, 2, 3, 3, 4, 3, 4, 5, 5);
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 3, 3, 4, 3, 4, 5, 5));
	collapse_inplace(x);
	EXPECT_EQ(x, array<int>::values(7, 1, 2, 3, 4, 3, 4, 5));

	array<int> y;

	x = range<int>(0, 10);
	EXPECT_EQ(x, range<int>(0, 10));
	y = collapse(x);
	EXPECT_EQ(x, range<int>(0, 10));
	EXPECT_EQ(y, range<int>(0, 10));

	x = fill<int>(10, 4);
	EXPECT_EQ(x, fill<int>(10, 4));
	y = collapse(x);
	EXPECT_EQ(x, fill<int>(10, 4));
	EXPECT_EQ(y, fill<int>(1, 4));

	x = array<int>::values(10, 1, 1, 2, 3, 3, 4, 3, 4, 5, 5);
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 3, 3, 4, 3, 4, 5, 5));
	y = collapse(x);
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 3, 3, 4, 3, 4, 5, 5));
	EXPECT_EQ(y, array<int>::values(7, 1, 2, 3, 4, 3, 4, 5));
}

TEST(algorithm, unique)
{
	array<int> x;

	x = range<int>(0, 10);
	EXPECT_EQ(x, range<int>(0, 10));
	unique_inplace(x);
	EXPECT_EQ(x, range<int>(0, 10));

	x = fill<int>(10, 4);
	EXPECT_EQ(x, fill<int>(10, 4));
	unique_inplace(x);
	EXPECT_EQ(x, fill<int>(1, 4));

	x = array<int>::values(10, 1, 1, 2, 3, 3, 4, 3, 4, 5, 5);
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 3, 3, 4, 3, 4, 5, 5));
	unique_inplace(x);
	EXPECT_EQ(x, array<int>::values(5, 1, 2, 3, 4, 5));

	array<int> y;

	x = range<int>(0, 10);
	EXPECT_EQ(x, range<int>(0, 10));
	y = unique(x);
	EXPECT_EQ(x, range<int>(0, 10));
	EXPECT_EQ(y, range<int>(0, 10));

	x = fill<int>(10, 4);
	EXPECT_EQ(x, fill<int>(10, 4));
	y = unique(x);
	EXPECT_EQ(x, fill<int>(10, 4));
	EXPECT_EQ(y, fill<int>(1, 4));

	x = array<int>::values(10, 1, 1, 2, 3, 3, 4, 3, 4, 5, 5);
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 3, 3, 4, 3, 4, 5, 5));
	y = unique(x);
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 3, 3, 4, 3, 4, 5, 5));
	EXPECT_EQ(y, array<int>::values(5, 1, 2, 3, 4, 5));
}

