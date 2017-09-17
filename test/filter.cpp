#include <gtest/gtest.h>

#include <std/filter.h>
#include <std/array.h>
#include <std/list.h>
#include <std/fill.h>

using namespace core;

TEST(search, filter)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(filter(x, 2).idx(), array<int>::values(2, 0, 7));
	EXPECT_EQ(filter(x, 8).idx(), array<int>::values(2, 1, 8));
	EXPECT_EQ(filter(x, 5).idx(), array<int>::values(3, 2, 4, 9));
	EXPECT_EQ(filter(x, 3).idx(), array<int>::values(1, 3));
	EXPECT_EQ(filter(x, 7).idx(), array<int>::values(1, 5));
	EXPECT_EQ(filter(x, 4).idx(), array<int>::values(1, 6));

	EXPECT_EQ(filter(x, 0).idx(), array<int>());
	EXPECT_EQ(filter(x, 1).idx(), array<int>());
	EXPECT_EQ(filter(x, 9).idx(), array<int>());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(filter(y, 2).idx(), array<int>::values(2, 0, 7));
	EXPECT_EQ(filter(y, 8).idx(), array<int>::values(2, 1, 8));
	EXPECT_EQ(filter(y, 5).idx(), array<int>::values(3, 2, 4, 9));
	EXPECT_EQ(filter(y, 3).idx(), array<int>::values(1, 3));
	EXPECT_EQ(filter(y, 7).idx(), array<int>::values(1, 5));
	EXPECT_EQ(filter(y, 4).idx(), array<int>::values(1, 6));

	EXPECT_EQ(filter(y, 0).idx(), array<int>());
	EXPECT_EQ(filter(y, 1).idx(), array<int>());
	EXPECT_EQ(filter(y, 9).idx(), array<int>());

	const array<int> &z = x;
	EXPECT_EQ(filter(z, 2).idx(), array<int>::values(2, 0, 7));
	EXPECT_EQ(filter(z, 8).idx(), array<int>::values(2, 1, 8));
	EXPECT_EQ(filter(z, 5).idx(), array<int>::values(3, 2, 4, 9));
	EXPECT_EQ(filter(z, 3).idx(), array<int>::values(1, 3));
	EXPECT_EQ(filter(z, 7).idx(), array<int>::values(1, 5));
	EXPECT_EQ(filter(z, 4).idx(), array<int>::values(1, 6));

	EXPECT_EQ(filter(z, 0).idx(), array<int>());
	EXPECT_EQ(filter(z, 1).idx(), array<int>());
	EXPECT_EQ(filter(z, 9).idx(), array<int>());
}

TEST(search, filter_each)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(filter_each(x, range<int>(2, 5)).idx(), array<int>::values(4, 0, 3, 6, 7));
	EXPECT_EQ(filter_each(x, range<int>(7, 10)).idx(), array<int>::values(3, 1, 5, 8));
	EXPECT_EQ(filter_each(x, range<int>(6, 8)).idx(), array<int>::values(1, 5));
	EXPECT_EQ(filter_each(x, array<int>::values(3, 4, 3, 1)).idx(), array<int>::values(2, 3, 6));
	EXPECT_EQ(filter_each(x, array<int>::values(3, 7, 4, 7)).idx(), array<int>::values(2, 5, 6));
	EXPECT_EQ(filter_each(x, array<int>::values(3, 2, 8, 5)).idx(), array<int>::values(7, 0, 1, 2, 4, 7, 8, 9));

	EXPECT_EQ(filter_each(x, array<int>()).idx(), array<int>());
	EXPECT_EQ(filter_each(x, array<int>::values(3, 0, 1, 9)).idx(), array<int>());
	EXPECT_EQ(filter_each(x, array<int>::values(3, 10, 11, 12)).idx(), array<int>());
	EXPECT_EQ(filter_each(x, array<int>::values(3, -1, 6, 9)).idx(), array<int>());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(filter_each(y, range<int>(2, 5)).idx(), array<int>::values(4, 0, 3, 6, 7));
	EXPECT_EQ(filter_each(y, range<int>(7, 10)).idx(), array<int>::values(3, 1, 5, 8));
	EXPECT_EQ(filter_each(y, range<int>(6, 8)).idx(), array<int>::values(1, 5));
	EXPECT_EQ(filter_each(y, array<int>::values(3, 4, 3, 1)).idx(), array<int>::values(2, 3, 6));
	EXPECT_EQ(filter_each(y, array<int>::values(3, 7, 4, 7)).idx(), array<int>::values(2, 5, 6));
	EXPECT_EQ(filter_each(y, array<int>::values(3, 2, 8, 5)).idx(), array<int>::values(7, 0, 1, 2, 4, 7, 8, 9));

	EXPECT_EQ(filter_each(y, array<int>()).idx(), array<int>());
	EXPECT_EQ(filter_each(y, array<int>::values(3, 0, 1, 9)).idx(), array<int>());
	EXPECT_EQ(filter_each(y, array<int>::values(3, 10, 11, 12)).idx(), array<int>());
	EXPECT_EQ(filter_each(y, array<int>::values(3, -1, 6, 9)).idx(), array<int>());

	const array<int> &z = x;
	EXPECT_EQ(filter_each(z, range<int>(2, 5)).idx(), array<int>::values(4, 0, 3, 6, 7));
	EXPECT_EQ(filter_each(z, range<int>(7, 10)).idx(), array<int>::values(3, 1, 5, 8));
	EXPECT_EQ(filter_each(z, range<int>(6, 8)).idx(), array<int>::values(1, 5));
	EXPECT_EQ(filter_each(z, array<int>::values(3, 4, 3, 1)).idx(), array<int>::values(2, 3, 6));
	EXPECT_EQ(filter_each(z, array<int>::values(3, 7, 4, 7)).idx(), array<int>::values(2, 5, 6));
	EXPECT_EQ(filter_each(z, array<int>::values(3, 2, 8, 5)).idx(), array<int>::values(7, 0, 1, 2, 4, 7, 8, 9));

	EXPECT_EQ(filter_each(z, array<int>()).idx(), array<int>());
	EXPECT_EQ(filter_each(z, array<int>::values(3, 0, 1, 9)).idx(), array<int>());
	EXPECT_EQ(filter_each(z, array<int>::values(3, 10, 11, 12)).idx(), array<int>());
	EXPECT_EQ(filter_each(z, array<int>::values(3, -1, 6, 9)).idx(), array<int>());
}

TEST(search, filter_pattern)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(filter_pattern(x, array<int>::values(3, 2, 8, 5)).idx(), array<int>::values(2, 0, 7));
	EXPECT_EQ(filter_pattern(x, array<int>::values(2, 8, 5)).idx(), array<int>::values(2, 1, 8));
	EXPECT_EQ(filter_pattern(x, array<int>::values(1, 5)).idx(), array<int>::values(3, 2, 4, 9));
	EXPECT_EQ(filter_pattern(x, array<int>::values(3, 3, 5, 7)).idx(), array<int>::values(1, 3));
	EXPECT_EQ(filter_pattern(x, array<int>::values(3, 5, 7, 4)).idx(), array<int>::values(1, 4));
	EXPECT_EQ(filter_pattern(x, array<int>::values(4, 4, 2, 8, 5)).idx(), array<int>::values(1, 6));

	EXPECT_EQ(filter_pattern(x, array<int>()).idx(), range<int>(0, 10));
	EXPECT_EQ(filter_pattern(x, array<int>::values(1, 1)).idx(), array<int>());
	EXPECT_EQ(filter_pattern(x, array<int>::values(3, 8, 5, 4)).idx(), array<int>());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(filter_pattern(y, array<int>::values(3, 2, 8, 5)).idx(), array<int>::values(2, 0, 7));
	EXPECT_EQ(filter_pattern(y, array<int>::values(2, 8, 5)).idx(), array<int>::values(2, 1, 8));
	EXPECT_EQ(filter_pattern(y, array<int>::values(1, 5)).idx(), array<int>::values(3, 2, 4, 9));
	EXPECT_EQ(filter_pattern(y, array<int>::values(3, 3, 5, 7)).idx(), array<int>::values(1, 3));
	EXPECT_EQ(filter_pattern(y, array<int>::values(3, 5, 7, 4)).idx(), array<int>::values(1, 4));
	EXPECT_EQ(filter_pattern(y, array<int>::values(4, 4, 2, 8, 5)).idx(), array<int>::values(1, 6));

	EXPECT_EQ(filter_pattern(y, array<int>()).idx(), range<int>(0, 10));
	EXPECT_EQ(filter_pattern(y, array<int>::values(1, 1)).idx(), array<int>());
	EXPECT_EQ(filter_pattern(y, array<int>::values(3, 8, 5, 4)).idx(), array<int>());

	const array<int> &z = x;
	EXPECT_EQ(filter_pattern(z, array<int>::values(3, 2, 8, 5)).idx(), array<int>::values(2, 0, 7));
	EXPECT_EQ(filter_pattern(z, array<int>::values(2, 8, 5)).idx(), array<int>::values(2, 1, 8));
	EXPECT_EQ(filter_pattern(z, array<int>::values(1, 5)).idx(), array<int>::values(3, 2, 4, 9));
	EXPECT_EQ(filter_pattern(z, array<int>::values(3, 3, 5, 7)).idx(), array<int>::values(1, 3));
	EXPECT_EQ(filter_pattern(z, array<int>::values(3, 5, 7, 4)).idx(), array<int>::values(1, 4));
	EXPECT_EQ(filter_pattern(z, array<int>::values(4, 4, 2, 8, 5)).idx(), array<int>::values(1, 6));

	EXPECT_EQ(filter_pattern(z, array<int>()).idx(), range<int>(0, 10));
	EXPECT_EQ(filter_pattern(z, array<int>::values(1, 1)).idx(), array<int>());
	EXPECT_EQ(filter_pattern(z, array<int>::values(3, 8, 5, 4)).idx(), array<int>());
}


