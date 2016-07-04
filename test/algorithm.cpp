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

	x = range<int>(0, 10);
	EXPECT_EQ(x, range<int>(0, 10));
	x = collapse(x);
	EXPECT_EQ(x, range<int>(0, 10));

	x = fill<int>(10, 4);
	EXPECT_EQ(x, fill<int>(10, 4));
	x = collapse(x);
	EXPECT_EQ(x, fill<int>(1, 4));

	x = array<int>::values(10, 1, 1, 2, 3, 3, 4, 3, 4, 5, 5);
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 3, 3, 4, 3, 4, 5, 5));
	x = collapse(x);
	EXPECT_EQ(x, array<int>::values(7, 1, 2, 3, 4, 3, 4, 5));
}


