#include <gtest/gtest.h>

#include <core/search.h>
#include <core/array.h>
#include <core/list.h>
#include <core/fill.h>
#include <core/ascii_stream.h>

using namespace core;

TEST(search, find_first)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_first(x, 2).idx(), x.at(0).idx());
	EXPECT_EQ(find_first(x, 8).idx(), x.at(1).idx());
	EXPECT_EQ(find_first(x, 5).idx(), x.at(2).idx());
	EXPECT_EQ(find_first(x, 3).idx(), x.at(3).idx());
	EXPECT_EQ(find_first(x, 7).idx(), x.at(5).idx());
	EXPECT_EQ(find_first(x, 4).idx(), x.at(6).idx());

	EXPECT_EQ(find_first(x, 0).idx(), x.end().idx());
	EXPECT_EQ(find_first(x, 1).idx(), x.end().idx());
	EXPECT_EQ(find_first(x, 9).idx(), x.end().idx());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_first(y, 2).idx(), y.at(0).idx());
	EXPECT_EQ(find_first(y, 8).idx(), y.at(1).idx());
	EXPECT_EQ(find_first(y, 5).idx(), y.at(2).idx());
	EXPECT_EQ(find_first(y, 3).idx(), y.at(3).idx());
	EXPECT_EQ(find_first(y, 7).idx(), y.at(5).idx());
	EXPECT_EQ(find_first(y, 4).idx(), y.at(6).idx());

	EXPECT_EQ(find_first(y, 0).idx(), y.end().idx());
	EXPECT_EQ(find_first(y, 1).idx(), y.end().idx());
	EXPECT_EQ(find_first(y, 9).idx(), y.end().idx());

	const array<int> &z = x;
	EXPECT_EQ(find_first(z, 2).idx(), z.at(0).idx());
	EXPECT_EQ(find_first(z, 8).idx(), z.at(1).idx());
	EXPECT_EQ(find_first(z, 5).idx(), z.at(2).idx());
	EXPECT_EQ(find_first(z, 3).idx(), z.at(3).idx());
	EXPECT_EQ(find_first(z, 7).idx(), z.at(5).idx());
	EXPECT_EQ(find_first(z, 4).idx(), z.at(6).idx());

	EXPECT_EQ(find_first(z, 0).idx(), z.end().idx());
	EXPECT_EQ(find_first(z, 1).idx(), z.end().idx());
	EXPECT_EQ(find_first(z, 9).idx(), z.end().idx());
}

TEST(search, contains)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_TRUE(contains(x, 2));
	EXPECT_TRUE(contains(x, 8));
	EXPECT_TRUE(contains(x, 5));
	EXPECT_TRUE(contains(x, 3));
	EXPECT_TRUE(contains(x, 7));
	EXPECT_TRUE(contains(x, 4));

	EXPECT_FALSE(contains(x, 0));
	EXPECT_FALSE(contains(x, 1));
	EXPECT_FALSE(contains(x, 9));

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_TRUE(contains(y, 2));
	EXPECT_TRUE(contains(y, 8));
	EXPECT_TRUE(contains(y, 5));
	EXPECT_TRUE(contains(y, 3));
	EXPECT_TRUE(contains(y, 7));
	EXPECT_TRUE(contains(y, 4));

	EXPECT_FALSE(contains(y, 0));
	EXPECT_FALSE(contains(y, 1));
	EXPECT_FALSE(contains(y, 9));

	const array<int> &z = x;
	EXPECT_TRUE(contains(z, 2));
	EXPECT_TRUE(contains(z, 8));
	EXPECT_TRUE(contains(z, 5));
	EXPECT_TRUE(contains(z, 3));
	EXPECT_TRUE(contains(z, 7));
	EXPECT_TRUE(contains(z, 4));

	EXPECT_FALSE(contains(z, 0));
	EXPECT_FALSE(contains(z, 1));
	EXPECT_FALSE(contains(z, 9));
}

TEST(search, find_last)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_last(x, 2).idx(), x.at(7).idx());
	EXPECT_EQ(find_last(x, 8).idx(), x.at(8).idx());
	EXPECT_EQ(find_last(x, 5).idx(), x.at(9).idx());
	EXPECT_EQ(find_last(x, 3).idx(), x.at(3).idx());
	EXPECT_EQ(find_last(x, 7).idx(), x.at(5).idx());
	EXPECT_EQ(find_last(x, 4).idx(), x.at(6).idx());

	EXPECT_EQ(find_last(x, 0).idx(), x.rend().idx());
	EXPECT_EQ(find_last(x, 1).idx(), x.rend().idx());
	EXPECT_EQ(find_last(x, 9).idx(), x.rend().idx());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_last(y, 2).idx(), y.at(7).idx());
	EXPECT_EQ(find_last(y, 8).idx(), y.at(8).idx());
	EXPECT_EQ(find_last(y, 5).idx(), y.at(9).idx());
	EXPECT_EQ(find_last(y, 3).idx(), y.at(3).idx());
	EXPECT_EQ(find_last(y, 7).idx(), y.at(5).idx());
	EXPECT_EQ(find_last(y, 4).idx(), y.at(6).idx());

	EXPECT_EQ(find_last(y, 0).idx(), y.rend().idx());
	EXPECT_EQ(find_last(y, 1).idx(), y.rend().idx());
	EXPECT_EQ(find_last(y, 9).idx(), y.rend().idx());

	const array<int> &z = x;
	EXPECT_EQ(find_last(z, 2).idx(), z.at(7).idx());
	EXPECT_EQ(find_last(z, 8).idx(), z.at(8).idx());
	EXPECT_EQ(find_last(z, 5).idx(), z.at(9).idx());
	EXPECT_EQ(find_last(z, 3).idx(), z.at(3).idx());
	EXPECT_EQ(find_last(z, 7).idx(), z.at(5).idx());
	EXPECT_EQ(find_last(z, 4).idx(), z.at(6).idx());

	EXPECT_EQ(find_last(z, 0).idx(), z.rend().idx());
	EXPECT_EQ(find_last(z, 1).idx(), z.rend().idx());
	EXPECT_EQ(find_last(z, 9).idx(), z.rend().idx());
}

TEST(search, find_all)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_all(x, 2).idx(), array<int>::values(2, 0, 7));
	EXPECT_EQ(find_all(x, 8).idx(), array<int>::values(2, 1, 8));
	EXPECT_EQ(find_all(x, 5).idx(), array<int>::values(3, 2, 4, 9));
	EXPECT_EQ(find_all(x, 3).idx(), array<int>::values(1, 3));
	EXPECT_EQ(find_all(x, 7).idx(), array<int>::values(1, 5));
	EXPECT_EQ(find_all(x, 4).idx(), array<int>::values(1, 6));

	EXPECT_EQ(find_all(x, 0).idx(), array<int>());
	EXPECT_EQ(find_all(x, 1).idx(), array<int>());
	EXPECT_EQ(find_all(x, 9).idx(), array<int>());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_all(y, 2).idx(), array<int>::values(2, 0, 7));
	EXPECT_EQ(find_all(y, 8).idx(), array<int>::values(2, 1, 8));
	EXPECT_EQ(find_all(y, 5).idx(), array<int>::values(3, 2, 4, 9));
	EXPECT_EQ(find_all(y, 3).idx(), array<int>::values(1, 3));
	EXPECT_EQ(find_all(y, 7).idx(), array<int>::values(1, 5));
	EXPECT_EQ(find_all(y, 4).idx(), array<int>::values(1, 6));

	EXPECT_EQ(find_all(y, 0).idx(), array<int>());
	EXPECT_EQ(find_all(y, 1).idx(), array<int>());
	EXPECT_EQ(find_all(y, 9).idx(), array<int>());

	const array<int> &z = x;
	EXPECT_EQ(find_all(z, 2).idx(), array<int>::values(2, 0, 7));
	EXPECT_EQ(find_all(z, 8).idx(), array<int>::values(2, 1, 8));
	EXPECT_EQ(find_all(z, 5).idx(), array<int>::values(3, 2, 4, 9));
	EXPECT_EQ(find_all(z, 3).idx(), array<int>::values(1, 3));
	EXPECT_EQ(find_all(z, 7).idx(), array<int>::values(1, 5));
	EXPECT_EQ(find_all(z, 4).idx(), array<int>::values(1, 6));

	EXPECT_EQ(find_all(z, 0).idx(), array<int>());
	EXPECT_EQ(find_all(z, 1).idx(), array<int>());
	EXPECT_EQ(find_all(z, 9).idx(), array<int>());
}

TEST(search, find_first_of)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_first_of(x, range<int>(2, 5)).idx(), x.at(0).idx());
	EXPECT_EQ(find_first_of(x, range<int>(7, 10)).idx(), x.at(1).idx());
	EXPECT_EQ(find_first_of(x, range<int>(6, 8)).idx(), x.at(5).idx());
	EXPECT_EQ(find_first_of(x, array<int>::values(3, 4, 3, 1)).idx(), x.at(3).idx());
	EXPECT_EQ(find_first_of(x, array<int>::values(3, 7, 4, 7)).idx(), x.at(5).idx());
	EXPECT_EQ(find_first_of(x, array<int>::values(3, 2, 8, 5)).idx(), x.at(0).idx());

	EXPECT_EQ(find_first_of(x, array<int>::values(0, 1, 9)).idx(), x.end().idx());
	EXPECT_EQ(find_first_of(x, array<int>::values(10, 11, 12)).idx(), x.end().idx());
	EXPECT_EQ(find_first_of(x, array<int>::values(-1, 6, 9)).idx(), x.end().idx());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_first_of(y, range<int>(2, 5)).idx(), y.at(0).idx());
	EXPECT_EQ(find_first_of(y, range<int>(7, 10)).idx(), y.at(1).idx());
	EXPECT_EQ(find_first_of(y, range<int>(6, 8)).idx(), y.at(5).idx());
	EXPECT_EQ(find_first_of(y, array<int>::values(3, 4, 3, 1)).idx(), y.at(3).idx());
	EXPECT_EQ(find_first_of(y, array<int>::values(3, 7, 4, 7)).idx(), y.at(5).idx());
	EXPECT_EQ(find_first_of(y, array<int>::values(3, 2, 8, 5)).idx(), y.at(0).idx());

	EXPECT_EQ(find_first_of(y, array<int>::values(0, 1, 9)).idx(), y.end().idx());
	EXPECT_EQ(find_first_of(y, array<int>::values(10, 11, 12)).idx(), y.end().idx());
	EXPECT_EQ(find_first_of(y, array<int>::values(-1, 6, 9)).idx(), y.end().idx());

	const array<int> &z = x;
	EXPECT_EQ(find_first_of(z, range<int>(2, 5)).idx(), z.at(0).idx());
	EXPECT_EQ(find_first_of(z, range<int>(7, 10)).idx(), z.at(1).idx());
	EXPECT_EQ(find_first_of(z, range<int>(6, 8)).idx(), z.at(5).idx());
	EXPECT_EQ(find_first_of(z, array<int>::values(3, 4, 3, 1)).idx(), z.at(3).idx());
	EXPECT_EQ(find_first_of(z, array<int>::values(3, 7, 4, 7)).idx(), z.at(5).idx());
	EXPECT_EQ(find_first_of(z, array<int>::values(3, 2, 8, 5)).idx(), z.at(0).idx());

	EXPECT_EQ(find_first_of(z, array<int>::values(0, 1, 9)).idx(), z.end().idx());
	EXPECT_EQ(find_first_of(z, array<int>::values(10, 11, 12)).idx(), z.end().idx());
	EXPECT_EQ(find_first_of(z, array<int>::values(-1, 6, 9)).idx(), z.end().idx());
}

TEST(search, contains_one_of)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_TRUE(contains_one_of(x, range<int>(2, 5)));
	EXPECT_TRUE(contains_one_of(x, range<int>(7, 10)));
	EXPECT_TRUE(contains_one_of(x, range<int>(6, 8)));
	EXPECT_TRUE(contains_one_of(x, array<int>::values(3, 4, 3, 1)));
	EXPECT_TRUE(contains_one_of(x, array<int>::values(3, 7, 4, 7)));
	EXPECT_TRUE(contains_one_of(x, array<int>::values(3, 2, 8, 5)));

	EXPECT_FALSE(contains_one_of(x, array<int>::values(0, 1, 9)));
	EXPECT_FALSE(contains_one_of(x, array<int>::values(10, 11, 12)));
	EXPECT_FALSE(contains_one_of(x, array<int>::values(-1, 6, 9)));

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_TRUE(contains_one_of(y, range<int>(2, 5)));
	EXPECT_TRUE(contains_one_of(y, range<int>(7, 10)));
	EXPECT_TRUE(contains_one_of(y, range<int>(6, 8)));
	EXPECT_TRUE(contains_one_of(y, array<int>::values(3, 4, 3, 1)));
	EXPECT_TRUE(contains_one_of(y, array<int>::values(3, 7, 4, 7)));
	EXPECT_TRUE(contains_one_of(y, array<int>::values(3, 2, 8, 5)));

	EXPECT_FALSE(contains_one_of(y, array<int>::values(0, 1, 9)));
	EXPECT_FALSE(contains_one_of(y, array<int>::values(10, 11, 12)));
	EXPECT_FALSE(contains_one_of(y, array<int>::values(-1, 6, 9)));

	const array<int> &z = x;
	EXPECT_TRUE(contains_one_of(z, range<int>(2, 5)));
	EXPECT_TRUE(contains_one_of(z, range<int>(7, 10)));
	EXPECT_TRUE(contains_one_of(z, range<int>(6, 8)));
	EXPECT_TRUE(contains_one_of(z, array<int>::values(3, 4, 3, 1)));
	EXPECT_TRUE(contains_one_of(z, array<int>::values(3, 7, 4, 7)));
	EXPECT_TRUE(contains_one_of(z, array<int>::values(3, 2, 8, 5)));

	EXPECT_FALSE(contains_one_of(z, array<int>::values(0, 1, 9)));
	EXPECT_FALSE(contains_one_of(z, array<int>::values(10, 11, 12)));
	EXPECT_FALSE(contains_one_of(z, array<int>::values(-1, 6, 9)));
}

TEST(search, find_last_of)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_last_of(x, range<int>(2, 5)).idx(), x.at(7).idx());
	EXPECT_EQ(find_last_of(x, range<int>(7, 10)).idx(), x.at(8).idx());
	EXPECT_EQ(find_last_of(x, range<int>(6, 8)).idx(), x.at(5).idx());
	EXPECT_EQ(find_last_of(x, array<int>::values(3, 4, 3, 1)).idx(), x.at(6).idx());
	EXPECT_EQ(find_last_of(x, array<int>::values(3, 7, 4, 7)).idx(), x.at(6).idx());
	EXPECT_EQ(find_last_of(x, array<int>::values(3, 2, 8, 5)).idx(), x.at(9).idx());

	EXPECT_EQ(find_last_of(x, array<int>::values(0, 1, 9)).idx(), x.rend().idx());
	EXPECT_EQ(find_last_of(x, array<int>::values(10, 11, 12)).idx(), x.rend().idx());
	EXPECT_EQ(find_last_of(x, array<int>::values(-1, 6, 9)).idx(), x.rend().idx());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_last_of(y, range<int>(2, 5)).idx(), y.at(7).idx());
	EXPECT_EQ(find_last_of(y, range<int>(7, 10)).idx(), y.at(8).idx());
	EXPECT_EQ(find_last_of(y, range<int>(6, 8)).idx(), y.at(5).idx());
	EXPECT_EQ(find_last_of(y, array<int>::values(3, 4, 3, 1)).idx(), y.at(6).idx());
	EXPECT_EQ(find_last_of(y, array<int>::values(3, 7, 4, 7)).idx(), y.at(6).idx());
	EXPECT_EQ(find_last_of(y, array<int>::values(3, 2, 8, 5)).idx(), y.at(9).idx());

	EXPECT_EQ(find_last_of(y, array<int>::values(0, 1, 9)).idx(), y.rend().idx());
	EXPECT_EQ(find_last_of(y, array<int>::values(10, 11, 12)).idx(), y.rend().idx());
	EXPECT_EQ(find_last_of(y, array<int>::values(-1, 6, 9)).idx(), y.rend().idx());

	const array<int> &z = x;
	EXPECT_EQ(find_last_of(z, range<int>(2, 5)).idx(), z.at(7).idx());
	EXPECT_EQ(find_last_of(z, range<int>(7, 10)).idx(), z.at(8).idx());
	EXPECT_EQ(find_last_of(z, range<int>(6, 8)).idx(), z.at(5).idx());
	EXPECT_EQ(find_last_of(z, array<int>::values(3, 4, 3, 1)).idx(), z.at(6).idx());
	EXPECT_EQ(find_last_of(z, array<int>::values(3, 7, 4, 7)).idx(), z.at(6).idx());
	EXPECT_EQ(find_last_of(z, array<int>::values(3, 2, 8, 5)).idx(), z.at(9).idx());

	EXPECT_EQ(find_last_of(z, array<int>::values(0, 1, 9)).idx(), z.rend().idx());
	EXPECT_EQ(find_last_of(z, array<int>::values(10, 11, 12)).idx(), z.rend().idx());
	EXPECT_EQ(find_last_of(z, array<int>::values(-1, 6, 9)).idx(), z.rend().idx());
}

TEST(search, find_all_of)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_all_of(x, range<int>(2, 5)).idx(), array<int>::values(4, 0, 3, 6, 7));
	EXPECT_EQ(find_all_of(x, range<int>(7, 10)).idx(), array<int>::values(3, 1, 5, 8));
	EXPECT_EQ(find_all_of(x, range<int>(6, 8)).idx(), array<int>::values(1, 5));
	EXPECT_EQ(find_all_of(x, array<int>::values(3, 4, 3, 1)).idx(), array<int>::values(2, 3, 6));
	EXPECT_EQ(find_all_of(x, array<int>::values(3, 7, 4, 7)).idx(), array<int>::values(2, 5, 6));
	EXPECT_EQ(find_all_of(x, array<int>::values(3, 2, 8, 5)).idx(), array<int>::values(7, 0, 1, 2, 4, 7, 8, 9));

	EXPECT_EQ(find_all_of(x, array<int>()).idx(), array<int>());
	EXPECT_EQ(find_all_of(x, array<int>::values(0, 1, 9)).idx(), array<int>());
	EXPECT_EQ(find_all_of(x, array<int>::values(10, 11, 12)).idx(), array<int>());
	EXPECT_EQ(find_all_of(x, array<int>::values(-1, 6, 9)).idx(), array<int>());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_all_of(y, range<int>(2, 5)).idx(), array<int>::values(4, 0, 3, 6, 7));
	EXPECT_EQ(find_all_of(y, range<int>(7, 10)).idx(), array<int>::values(3, 1, 5, 8));
	EXPECT_EQ(find_all_of(y, range<int>(6, 8)).idx(), array<int>::values(1, 5));
	EXPECT_EQ(find_all_of(y, array<int>::values(3, 4, 3, 1)).idx(), array<int>::values(2, 3, 6));
	EXPECT_EQ(find_all_of(y, array<int>::values(3, 7, 4, 7)).idx(), array<int>::values(2, 5, 6));
	EXPECT_EQ(find_all_of(y, array<int>::values(3, 2, 8, 5)).idx(), array<int>::values(7, 0, 1, 2, 4, 7, 8, 9));

	EXPECT_EQ(find_all_of(y, array<int>()).idx(), array<int>());
	EXPECT_EQ(find_all_of(y, array<int>::values(0, 1, 9)).idx(), array<int>());
	EXPECT_EQ(find_all_of(y, array<int>::values(10, 11, 12)).idx(), array<int>());
	EXPECT_EQ(find_all_of(y, array<int>::values(-1, 6, 9)).idx(), array<int>());

	const array<int> &z = x;
	EXPECT_EQ(find_all_of(z, range<int>(2, 5)).idx(), array<int>::values(4, 0, 3, 6, 7));
	EXPECT_EQ(find_all_of(z, range<int>(7, 10)).idx(), array<int>::values(3, 1, 5, 8));
	EXPECT_EQ(find_all_of(z, range<int>(6, 8)).idx(), array<int>::values(1, 5));
	EXPECT_EQ(find_all_of(z, array<int>::values(3, 4, 3, 1)).idx(), array<int>::values(2, 3, 6));
	EXPECT_EQ(find_all_of(z, array<int>::values(3, 7, 4, 7)).idx(), array<int>::values(2, 5, 6));
	EXPECT_EQ(find_all_of(z, array<int>::values(3, 2, 8, 5)).idx(), array<int>::values(7, 0, 1, 2, 4, 7, 8, 9));

	EXPECT_EQ(find_all_of(z, array<int>()).idx(), array<int>());
	EXPECT_EQ(find_all_of(z, array<int>::values(0, 1, 9)).idx(), array<int>());
	EXPECT_EQ(find_all_of(z, array<int>::values(10, 11, 12)).idx(), array<int>());
	EXPECT_EQ(find_all_of(z, array<int>::values(-1, 6, 9)).idx(), array<int>());
}

TEST(search, find_first_pattern)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_first_pattern(x, array<int>::values(3, 2, 8, 5)).idx(), x.at(0).idx());
	EXPECT_EQ(find_first_pattern(x, array<int>::values(2, 8, 5)).idx(), x.at(1).idx());
	EXPECT_EQ(find_first_pattern(x, array<int>::values(1, 5)).idx(), x.at(2).idx());
	EXPECT_EQ(find_first_pattern(x, array<int>::values(3, 3, 5, 7)).idx(), x.at(3).idx());
	EXPECT_EQ(find_first_pattern(x, array<int>::values(3, 5, 7, 4)).idx(), x.at(4).idx());
	EXPECT_EQ(find_first_pattern(x, array<int>::values(4, 4, 2, 8, 5)).idx(), x.at(6).idx());

	EXPECT_EQ(find_first_pattern(x, array<int>()).idx(), x.begin().idx());
	EXPECT_EQ(find_first_pattern(x, array<int>::values(1, 1)).idx(), x.end().idx());
	EXPECT_EQ(find_first_pattern(x, array<int>::values(3, 8, 5, 4)).idx(), x.end().idx());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_first_pattern(y, array<int>::values(3, 2, 8, 5)).idx(), y.at(0).idx());
	EXPECT_EQ(find_first_pattern(y, array<int>::values(2, 8, 5)).idx(), y.at(1).idx());
	EXPECT_EQ(find_first_pattern(y, array<int>::values(1, 5)).idx(), y.at(2).idx());
	EXPECT_EQ(find_first_pattern(y, array<int>::values(3, 3, 5, 7)).idx(), y.at(3).idx());
	EXPECT_EQ(find_first_pattern(y, array<int>::values(3, 5, 7, 4)).idx(), y.at(4).idx());
	EXPECT_EQ(find_first_pattern(y, array<int>::values(4, 4, 2, 8, 5)).idx(), y.at(6).idx());

	EXPECT_EQ(find_first_pattern(y, array<int>()).idx(), y.begin().idx());
	EXPECT_EQ(find_first_pattern(y, array<int>::values(1, 1)).idx(), y.end().idx());
	EXPECT_EQ(find_first_pattern(y, array<int>::values(3, 8, 5, 4)).idx(), y.end().idx());

	const array<int> &z = x;
	EXPECT_EQ(find_first_pattern(z, array<int>::values(3, 2, 8, 5)).idx(), z.at(0).idx());
	EXPECT_EQ(find_first_pattern(z, array<int>::values(2, 8, 5)).idx(), z.at(1).idx());
	EXPECT_EQ(find_first_pattern(z, array<int>::values(1, 5)).idx(), z.at(2).idx());
	EXPECT_EQ(find_first_pattern(z, array<int>::values(3, 3, 5, 7)).idx(), z.at(3).idx());
	EXPECT_EQ(find_first_pattern(z, array<int>::values(3, 5, 7, 4)).idx(), z.at(4).idx());
	EXPECT_EQ(find_first_pattern(z, array<int>::values(4, 4, 2, 8, 5)).idx(), z.at(6).idx());

	EXPECT_EQ(find_first_pattern(z, array<int>()).idx(), z.begin().idx());
	EXPECT_EQ(find_first_pattern(z, array<int>::values(1, 1)).idx(), z.end().idx());
	EXPECT_EQ(find_first_pattern(z, array<int>::values(3, 8, 5, 4)).idx(), z.end().idx());
}

TEST(search, find_last_pattern)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_last_pattern(x, array<int>::values(3, 2, 8, 5)).idx(), x.at(7).idx());
	EXPECT_EQ(find_last_pattern(x, array<int>::values(2, 8, 5)).idx(), x.at(8).idx());
	EXPECT_EQ(find_last_pattern(x, array<int>::values(1, 5)).idx(), x.at(9).idx());
	EXPECT_EQ(find_last_pattern(x, array<int>::values(3, 3, 5, 7)).idx(), x.at(3).idx());
	EXPECT_EQ(find_last_pattern(x, array<int>::values(3, 5, 7, 4)).idx(), x.at(4).idx());
	EXPECT_EQ(find_last_pattern(x, array<int>::values(4, 4, 2, 8, 5)).idx(), x.at(6).idx());

	EXPECT_EQ(find_last_pattern(x, array<int>()).idx(), x.rbegin().idx());
	EXPECT_EQ(find_last_pattern(x, array<int>::values(1, 1)).idx(), x.rend().idx());
	EXPECT_EQ(find_last_pattern(x, array<int>::values(3, 8, 5, 4)).idx(), x.rend().idx());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_last_pattern(y, array<int>::values(3, 2, 8, 5)).idx(), y.at(7).idx());
	EXPECT_EQ(find_last_pattern(y, array<int>::values(2, 8, 5)).idx(), y.at(8).idx());
	EXPECT_EQ(find_last_pattern(y, array<int>::values(1, 5)).idx(), y.at(9).idx());
	EXPECT_EQ(find_last_pattern(y, array<int>::values(3, 3, 5, 7)).idx(), y.at(3).idx());
	EXPECT_EQ(find_last_pattern(y, array<int>::values(3, 5, 7, 4)).idx(), y.at(4).idx());
	EXPECT_EQ(find_last_pattern(y, array<int>::values(4, 4, 2, 8, 5)).idx(), y.at(6).idx());

	EXPECT_EQ(find_last_pattern(y, array<int>()).idx(), y.rbegin().idx());
	EXPECT_EQ(find_last_pattern(y, array<int>::values(1, 1)).idx(), y.rend().idx());
	EXPECT_EQ(find_last_pattern(y, array<int>::values(3, 8, 5, 4)).idx(), y.rend().idx());

	const array<int> &z = x;
	EXPECT_EQ(find_last_pattern(z, array<int>::values(3, 2, 8, 5)).idx(), z.at(7).idx());
	EXPECT_EQ(find_last_pattern(z, array<int>::values(2, 8, 5)).idx(), z.at(8).idx());
	EXPECT_EQ(find_last_pattern(z, array<int>::values(1, 5)).idx(), z.at(9).idx());
	EXPECT_EQ(find_last_pattern(z, array<int>::values(3, 3, 5, 7)).idx(), z.at(3).idx());
	EXPECT_EQ(find_last_pattern(z, array<int>::values(3, 5, 7, 4)).idx(), z.at(4).idx());
	EXPECT_EQ(find_last_pattern(z, array<int>::values(4, 4, 2, 8, 5)).idx(), z.at(6).idx());

	EXPECT_EQ(find_last_pattern(z, array<int>()).idx(), z.rbegin().idx());
	EXPECT_EQ(find_last_pattern(z, array<int>::values(1, 1)).idx(), z.rend().idx());
	EXPECT_EQ(find_last_pattern(z, array<int>::values(3, 8, 5, 4)).idx(), z.rend().idx());
}
