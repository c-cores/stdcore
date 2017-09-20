#include <gtest/gtest.h>

#include <std/search.h>
#include <std/array.h>
#include <std/list.h>
#include <std/fill.h>

using namespace core;

TEST(search, find_first)
{
	array<int> x = array_t<int>(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_first(x, 2).idx(), 0);
	EXPECT_EQ(find_first(x, 8).idx(), 1);
	EXPECT_EQ(find_first(x, 5).idx(), 2);
	EXPECT_EQ(find_first(x, 3).idx(), 3);
	EXPECT_EQ(find_first(x, 7).idx(), 5);
	EXPECT_EQ(find_first(x, 4).idx(), 6);

	EXPECT_EQ(find_first(x, 0).idx(), x.end().idx());
	EXPECT_EQ(find_first(x, 1).idx(), x.end().idx());
	EXPECT_EQ(find_first(x, 9).idx(), x.end().idx());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_first(y, 2).idx(), 0);
	EXPECT_EQ(find_first(y, 8).idx(), 1);
	EXPECT_EQ(find_first(y, 5).idx(), 2);
	EXPECT_EQ(find_first(y, 3).idx(), 3);
	EXPECT_EQ(find_first(y, 7).idx(), 5);
	EXPECT_EQ(find_first(y, 4).idx(), 6);

	EXPECT_EQ(find_first(y, 0).idx(), y.end().idx());
	EXPECT_EQ(find_first(y, 1).idx(), y.end().idx());
	EXPECT_EQ(find_first(y, 9).idx(), y.end().idx());

	const array<int> &z = x;
	EXPECT_EQ(find_first(z, 2).idx(), 0);
	EXPECT_EQ(find_first(z, 8).idx(), 1);
	EXPECT_EQ(find_first(z, 5).idx(), 2);
	EXPECT_EQ(find_first(z, 3).idx(), 3);
	EXPECT_EQ(find_first(z, 7).idx(), 5);
	EXPECT_EQ(find_first(z, 4).idx(), 6);

	EXPECT_EQ(find_first(z, 0).idx(), z.end().idx());
	EXPECT_EQ(find_first(z, 1).idx(), z.end().idx());
	EXPECT_EQ(find_first(z, 9).idx(), z.end().idx());
}

TEST(search, contains)
{
	array<int> x = array_t<int>(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
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
	array<int> x = array_t<int>(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_last(x, 2).idx(), 7);
	EXPECT_EQ(find_last(x, 8).idx(), 8);
	EXPECT_EQ(find_last(x, 5).idx(), 9);
	EXPECT_EQ(find_last(x, 3).idx(), 3);
	EXPECT_EQ(find_last(x, 7).idx(), 5);
	EXPECT_EQ(find_last(x, 4).idx(), 6);

	EXPECT_EQ(find_last(x, 0).idx(), x.rend().idx());
	EXPECT_EQ(find_last(x, 1).idx(), x.rend().idx());
	EXPECT_EQ(find_last(x, 9).idx(), x.rend().idx());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_last(y, 2).idx(), 7);
	EXPECT_EQ(find_last(y, 8).idx(), 8);
	EXPECT_EQ(find_last(y, 5).idx(), 9);
	EXPECT_EQ(find_last(y, 3).idx(), 3);
	EXPECT_EQ(find_last(y, 7).idx(), 5);
	EXPECT_EQ(find_last(y, 4).idx(), 6);

	EXPECT_EQ(find_last(y, 0).idx(), y.rend().idx());
	EXPECT_EQ(find_last(y, 1).idx(), y.rend().idx());
	EXPECT_EQ(find_last(y, 9).idx(), y.rend().idx());

	const array<int> &z = x;
	EXPECT_EQ(find_last(z, 2).idx(), 7);
	EXPECT_EQ(find_last(z, 8).idx(), 8);
	EXPECT_EQ(find_last(z, 5).idx(), 9);
	EXPECT_EQ(find_last(z, 3).idx(), 3);
	EXPECT_EQ(find_last(z, 7).idx(), 5);
	EXPECT_EQ(find_last(z, 4).idx(), 6);

	EXPECT_EQ(find_last(z, 0).idx(), z.rend().idx());
	EXPECT_EQ(find_last(z, 1).idx(), z.rend().idx());
	EXPECT_EQ(find_last(z, 9).idx(), z.rend().idx());
}

TEST(search, count_all)
{
	array<int> x = array_t<int>(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(count_all(x, 2), 2);
	EXPECT_EQ(count_all(x, 8), 2);
	EXPECT_EQ(count_all(x, 5), 3);
	EXPECT_EQ(count_all(x, 3), 1);
	EXPECT_EQ(count_all(x, 7), 1);
	EXPECT_EQ(count_all(x, 4), 1);

	EXPECT_EQ(count_all(x, 0), 0);
	EXPECT_EQ(count_all(x, 1), 0);
	EXPECT_EQ(count_all(x, 9), 0);

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(count_all(y, 2), 2);
	EXPECT_EQ(count_all(y, 8), 2);
	EXPECT_EQ(count_all(y, 5), 3);
	EXPECT_EQ(count_all(y, 3), 1);
	EXPECT_EQ(count_all(y, 7), 1);
	EXPECT_EQ(count_all(y, 4), 1);

	EXPECT_EQ(count_all(y, 0), 0);
	EXPECT_EQ(count_all(y, 1), 0);
	EXPECT_EQ(count_all(y, 9), 0);

	const array<int> &z = x;
	EXPECT_EQ(count_all(z, 2), 2);
	EXPECT_EQ(count_all(z, 8), 2);
	EXPECT_EQ(count_all(z, 5), 3);
	EXPECT_EQ(count_all(z, 3), 1);
	EXPECT_EQ(count_all(z, 7), 1);
	EXPECT_EQ(count_all(z, 4), 1);

	EXPECT_EQ(count_all(z, 0), 0);
	EXPECT_EQ(count_all(z, 1), 0);
	EXPECT_EQ(count_all(z, 9), 0);
}

TEST(search, find_first_of)
{
	array<int> x = array_t<int>(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_first_of(x, range<int>(2, 5)).idx(), 0);
	EXPECT_EQ(find_first_of(x, range<int>(7, 10)).idx(), 1);
	EXPECT_EQ(find_first_of(x, range<int>(6, 8)).idx(), 5);
	EXPECT_EQ(find_first_of(x, array_t<int>(3, 4, 3, 1)).idx(), 3);
	EXPECT_EQ(find_first_of(x, array_t<int>(3, 7, 4, 7)).idx(), 5);
	EXPECT_EQ(find_first_of(x, array_t<int>(3, 2, 8, 5)).idx(), 0);

	EXPECT_EQ(find_first_of(x, array_t<int>(3, 0, 1, 9)).idx(), x.end().idx());
	EXPECT_EQ(find_first_of(x, array_t<int>(3, 10, 11, 12)).idx(), x.end().idx());
	EXPECT_EQ(find_first_of(x, array_t<int>(3, -1, 6, 9)).idx(), x.end().idx());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_first_of(y, range<int>(2, 5)).idx(), 0);
	EXPECT_EQ(find_first_of(y, range<int>(7, 10)).idx(), 1);
	EXPECT_EQ(find_first_of(y, range<int>(6, 8)).idx(), 5);
	EXPECT_EQ(find_first_of(y, array_t<int>(3, 4, 3, 1)).idx(), 3);
	EXPECT_EQ(find_first_of(y, array_t<int>(3, 7, 4, 7)).idx(), 5);
	EXPECT_EQ(find_first_of(y, array_t<int>(3, 2, 8, 5)).idx(), 0);

	EXPECT_EQ(find_first_of(y, array_t<int>(3, 0, 1, 9)).idx(), y.end().idx());
	EXPECT_EQ(find_first_of(y, array_t<int>(3, 10, 11, 12)).idx(), y.end().idx());
	EXPECT_EQ(find_first_of(y, array_t<int>(3, -1, 6, 9)).idx(), y.end().idx());

	const array<int> &z = x;
	EXPECT_EQ(find_first_of(z, range<int>(2, 5)).idx(), 0);
	EXPECT_EQ(find_first_of(z, range<int>(7, 10)).idx(), 1);
	EXPECT_EQ(find_first_of(z, range<int>(6, 8)).idx(), 5);
	EXPECT_EQ(find_first_of(z, array_t<int>(3, 4, 3, 1)).idx(), 3);
	EXPECT_EQ(find_first_of(z, array_t<int>(3, 7, 4, 7)).idx(), 5);
	EXPECT_EQ(find_first_of(z, array_t<int>(3, 2, 8, 5)).idx(), 0);

	EXPECT_EQ(find_first_of(z, array_t<int>(3, 0, 1, 9)).idx(), z.end().idx());
	EXPECT_EQ(find_first_of(z, array_t<int>(3, 10, 11, 12)).idx(), z.end().idx());
	EXPECT_EQ(find_first_of(z, array_t<int>(3, -1, 6, 9)).idx(), z.end().idx());
}

TEST(search, contains_one_of)
{
	array<int> x = array_t<int>(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_TRUE(contains_one_of(x, range<int>(2, 5)));
	EXPECT_TRUE(contains_one_of(x, range<int>(7, 10)));
	EXPECT_TRUE(contains_one_of(x, range<int>(6, 8)));
	EXPECT_TRUE(contains_one_of(x, array_t<int>(3, 4, 3, 1)));
	EXPECT_TRUE(contains_one_of(x, array_t<int>(3, 7, 4, 7)));
	EXPECT_TRUE(contains_one_of(x, array_t<int>(3, 2, 8, 5)));

	EXPECT_FALSE(contains_one_of(x, array_t<int>(3, 0, 1, 9)));
	EXPECT_FALSE(contains_one_of(x, array_t<int>(3, 10, 11, 12)));
	EXPECT_FALSE(contains_one_of(x, array_t<int>(3, -1, 6, 9)));

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_TRUE(contains_one_of(y, range<int>(2, 5)));
	EXPECT_TRUE(contains_one_of(y, range<int>(7, 10)));
	EXPECT_TRUE(contains_one_of(y, range<int>(6, 8)));
	EXPECT_TRUE(contains_one_of(y, array_t<int>(3, 4, 3, 1)));
	EXPECT_TRUE(contains_one_of(y, array_t<int>(3, 7, 4, 7)));
	EXPECT_TRUE(contains_one_of(y, array_t<int>(3, 2, 8, 5)));

	EXPECT_FALSE(contains_one_of(y, array_t<int>(3, 0, 1, 9)));
	EXPECT_FALSE(contains_one_of(y, array_t<int>(3, 10, 11, 12)));
	EXPECT_FALSE(contains_one_of(y, array_t<int>(3, -1, 6, 9)));

	const array<int> &z = x;
	EXPECT_TRUE(contains_one_of(z, range<int>(2, 5)));
	EXPECT_TRUE(contains_one_of(z, range<int>(7, 10)));
	EXPECT_TRUE(contains_one_of(z, range<int>(6, 8)));
	EXPECT_TRUE(contains_one_of(z, array_t<int>(3, 4, 3, 1)));
	EXPECT_TRUE(contains_one_of(z, array_t<int>(3, 7, 4, 7)));
	EXPECT_TRUE(contains_one_of(z, array_t<int>(3, 2, 8, 5)));

	EXPECT_FALSE(contains_one_of(z, array_t<int>(3, 0, 1, 9)));
	EXPECT_FALSE(contains_one_of(z, array_t<int>(3, 10, 11, 12)));
	EXPECT_FALSE(contains_one_of(z, array_t<int>(3, -1, 6, 9)));
}

TEST(search, find_last_of)
{
	array<int> x = array_t<int>(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_last_of(x, range<int>(2, 5)).idx(), 7);
	EXPECT_EQ(find_last_of(x, range<int>(7, 10)).idx(), 8);
	EXPECT_EQ(find_last_of(x, range<int>(6, 8)).idx(), 5);
	EXPECT_EQ(find_last_of(x, array_t<int>(3, 4, 3, 1)).idx(), 6);
	EXPECT_EQ(find_last_of(x, array_t<int>(3, 7, 4, 7)).idx(), 6);
	EXPECT_EQ(find_last_of(x, array_t<int>(3, 2, 8, 5)).idx(), 9);

	EXPECT_EQ(find_last_of(x, array_t<int>(3, 0, 1, 9)).idx(), x.rend().idx());
	EXPECT_EQ(find_last_of(x, array_t<int>(3, 10, 11, 12)).idx(), x.rend().idx());
	EXPECT_EQ(find_last_of(x, array_t<int>(3, -1, 6, 9)).idx(), x.rend().idx());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_last_of(y, range<int>(2, 5)).idx(), 7);
	EXPECT_EQ(find_last_of(y, range<int>(7, 10)).idx(), 8);
	EXPECT_EQ(find_last_of(y, range<int>(6, 8)).idx(), 5);
	EXPECT_EQ(find_last_of(y, array_t<int>(3, 4, 3, 1)).idx(), 6);
	EXPECT_EQ(find_last_of(y, array_t<int>(3, 7, 4, 7)).idx(), 6);
	EXPECT_EQ(find_last_of(y, array_t<int>(3, 2, 8, 5)).idx(), 9);

	EXPECT_EQ(find_last_of(y, array_t<int>(3, 0, 1, 9)).idx(), y.rend().idx());
	EXPECT_EQ(find_last_of(y, array_t<int>(3, 10, 11, 12)).idx(), y.rend().idx());
	EXPECT_EQ(find_last_of(y, array_t<int>(3, -1, 6, 9)).idx(), y.rend().idx());

	const array<int> &z = x;
	EXPECT_EQ(find_last_of(z, range<int>(2, 5)).idx(), 7);
	EXPECT_EQ(find_last_of(z, range<int>(7, 10)).idx(), 8);
	EXPECT_EQ(find_last_of(z, range<int>(6, 8)).idx(), 5);
	EXPECT_EQ(find_last_of(z, array_t<int>(3, 4, 3, 1)).idx(), 6);
	EXPECT_EQ(find_last_of(z, array_t<int>(3, 7, 4, 7)).idx(), 6);
	EXPECT_EQ(find_last_of(z, array_t<int>(3, 2, 8, 5)).idx(), 9);

	EXPECT_EQ(find_last_of(z, array_t<int>(3, 0, 1, 9)).idx(), z.rend().idx());
	EXPECT_EQ(find_last_of(z, array_t<int>(3, 10, 11, 12)).idx(), z.rend().idx());
	EXPECT_EQ(find_last_of(z, array_t<int>(3, -1, 6, 9)).idx(), z.rend().idx());
}

TEST(search, count_all_of)
{
	array<int> x = array_t<int>(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(count_all_of(x, range<int>(2, 5)), 4);
	EXPECT_EQ(count_all_of(x, range<int>(7, 10)), 3);
	EXPECT_EQ(count_all_of(x, range<int>(6, 8)), 1);
	EXPECT_EQ(count_all_of(x, array_t<int>(3, 4, 3, 1)), 2);
	EXPECT_EQ(count_all_of(x, array_t<int>(3, 7, 4, 7)), 2);
	EXPECT_EQ(count_all_of(x, array_t<int>(3, 2, 8, 5)), 7);

	EXPECT_EQ(count_all_of(x, array<int>()), 0);
	EXPECT_EQ(count_all_of(x, array_t<int>(3, 0, 1, 9)), 0);
	EXPECT_EQ(count_all_of(x, array_t<int>(3, 10, 11, 12)), 0);
	EXPECT_EQ(count_all_of(x, array_t<int>(3, -1, 6, 9)), 0);

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(count_all_of(y, range<int>(2, 5)), 4);
	EXPECT_EQ(count_all_of(y, range<int>(7, 10)), 3);
	EXPECT_EQ(count_all_of(y, range<int>(6, 8)), 1);
	EXPECT_EQ(count_all_of(y, array_t<int>(3, 4, 3, 1)), 2);
	EXPECT_EQ(count_all_of(y, array_t<int>(3, 7, 4, 7)), 2);
	EXPECT_EQ(count_all_of(y, array_t<int>(3, 2, 8, 5)), 7);

	EXPECT_EQ(count_all_of(y, array<int>()), 0);
	EXPECT_EQ(count_all_of(y, array_t<int>(3, 0, 1, 9)), 0);
	EXPECT_EQ(count_all_of(y, array_t<int>(3, 10, 11, 12)), 0);
	EXPECT_EQ(count_all_of(y, array_t<int>(3, -1, 6, 9)), 0);

	const array<int> &z = x;
	EXPECT_EQ(count_all_of(z, range<int>(2, 5)), 4);
	EXPECT_EQ(count_all_of(z, range<int>(7, 10)), 3);
	EXPECT_EQ(count_all_of(z, range<int>(6, 8)), 1);
	EXPECT_EQ(count_all_of(z, array_t<int>(3, 4, 3, 1)), 2);
	EXPECT_EQ(count_all_of(z, array_t<int>(3, 7, 4, 7)), 2);
	EXPECT_EQ(count_all_of(z, array_t<int>(3, 2, 8, 5)), 7);

	EXPECT_EQ(count_all_of(z, array<int>()), 0);
	EXPECT_EQ(count_all_of(z, array_t<int>(3, 0, 1, 9)), 0);
	EXPECT_EQ(count_all_of(z, array_t<int>(3, 10, 11, 12)), 0);
	EXPECT_EQ(count_all_of(z, array_t<int>(3, -1, 6, 9)), 0);
}

TEST(search, find_first_pattern)
{
	array<int> x = array_t<int>(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_first_pattern(x, array_t<int>(3, 2, 8, 5)).idx(), 0);
	EXPECT_EQ(find_first_pattern(x, array_t<int>(2, 8, 5)).idx(), 1);
	EXPECT_EQ(find_first_pattern(x, array_t<int>(1, 5)).idx(), 2);
	EXPECT_EQ(find_first_pattern(x, array_t<int>(3, 3, 5, 7)).idx(), 3);
	EXPECT_EQ(find_first_pattern(x, array_t<int>(3, 5, 7, 4)).idx(), 4);
	EXPECT_EQ(find_first_pattern(x, array_t<int>(4, 4, 2, 8, 5)).idx(), 6);

	EXPECT_EQ(find_first_pattern(x, array<int>()).idx(), x.begin().idx());
	EXPECT_EQ(find_first_pattern(x, array_t<int>(1, 1)).idx(), x.end().idx());
	EXPECT_EQ(find_first_pattern(x, array_t<int>(3, 8, 5, 4)).idx(), x.end().idx());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_first_pattern(y, array_t<int>(3, 2, 8, 5)).idx(), 0);
	EXPECT_EQ(find_first_pattern(y, array_t<int>(2, 8, 5)).idx(), 1);
	EXPECT_EQ(find_first_pattern(y, array_t<int>(1, 5)).idx(), 2);
	EXPECT_EQ(find_first_pattern(y, array_t<int>(3, 3, 5, 7)).idx(), 3);
	EXPECT_EQ(find_first_pattern(y, array_t<int>(3, 5, 7, 4)).idx(), 4);
	EXPECT_EQ(find_first_pattern(y, array_t<int>(4, 4, 2, 8, 5)).idx(), 6);

	EXPECT_EQ(find_first_pattern(y, array<int>()).idx(), y.begin().idx());
	EXPECT_EQ(find_first_pattern(y, array_t<int>(1, 1)).idx(), y.end().idx());
	EXPECT_EQ(find_first_pattern(y, array_t<int>(3, 8, 5, 4)).idx(), y.end().idx());

	const array<int> &z = x;
	EXPECT_EQ(find_first_pattern(z, array_t<int>(3, 2, 8, 5)).idx(), 0);
	EXPECT_EQ(find_first_pattern(z, array_t<int>(2, 8, 5)).idx(), 1);
	EXPECT_EQ(find_first_pattern(z, array_t<int>(1, 5)).idx(), 2);
	EXPECT_EQ(find_first_pattern(z, array_t<int>(3, 3, 5, 7)).idx(), 3);
	EXPECT_EQ(find_first_pattern(z, array_t<int>(3, 5, 7, 4)).idx(), 4);
	EXPECT_EQ(find_first_pattern(z, array_t<int>(4, 4, 2, 8, 5)).idx(), 6);

	EXPECT_EQ(find_first_pattern(z, array<int>()).idx(), z.begin().idx());
	EXPECT_EQ(find_first_pattern(z, array_t<int>(1, 1)).idx(), z.end().idx());
	EXPECT_EQ(find_first_pattern(z, array_t<int>(3, 8, 5, 4)).idx(), z.end().idx());
}

TEST(search, find_last_pattern)
{
	array<int> x = array_t<int>(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(find_last_pattern(x, array_t<int>(3, 2, 8, 5)).idx(), 7);
	EXPECT_EQ(find_last_pattern(x, array_t<int>(2, 8, 5)).idx(), 8);
	EXPECT_EQ(find_last_pattern(x, array_t<int>(1, 5)).idx(), 9);
	EXPECT_EQ(find_last_pattern(x, array_t<int>(3, 3, 5, 7)).idx(), 3);
	EXPECT_EQ(find_last_pattern(x, array_t<int>(3, 5, 7, 4)).idx(), 4);
	EXPECT_EQ(find_last_pattern(x, array_t<int>(4, 4, 2, 8, 5)).idx(), 6);

	EXPECT_EQ(find_last_pattern(x, array<int>()).idx(), x.rbegin().idx());
	EXPECT_EQ(find_last_pattern(x, array_t<int>(1, 1)).idx(), x.rend().idx());
	EXPECT_EQ(find_last_pattern(x, array_t<int>(3, 8, 5, 4)).idx(), x.rend().idx());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(find_last_pattern(y, array_t<int>(3, 2, 8, 5)).idx(), 7);
	EXPECT_EQ(find_last_pattern(y, array_t<int>(2, 8, 5)).idx(), 8);
	EXPECT_EQ(find_last_pattern(y, array_t<int>(1, 5)).idx(), 9);
	EXPECT_EQ(find_last_pattern(y, array_t<int>(3, 3, 5, 7)).idx(), 3);
	EXPECT_EQ(find_last_pattern(y, array_t<int>(3, 5, 7, 4)).idx(), 4);
	EXPECT_EQ(find_last_pattern(y, array_t<int>(4, 4, 2, 8, 5)).idx(), 6);

	EXPECT_EQ(find_last_pattern(y, array<int>()).idx(), y.rbegin().idx());
	EXPECT_EQ(find_last_pattern(y, array_t<int>(1, 1)).idx(), y.rend().idx());
	EXPECT_EQ(find_last_pattern(y, array_t<int>(3, 8, 5, 4)).idx(), y.rend().idx());

	const array<int> &z = x;
	EXPECT_EQ(find_last_pattern(z, array_t<int>(3, 2, 8, 5)).idx(), 7);
	EXPECT_EQ(find_last_pattern(z, array_t<int>(2, 8, 5)).idx(), 8);
	EXPECT_EQ(find_last_pattern(z, array_t<int>(1, 5)).idx(), 9);
	EXPECT_EQ(find_last_pattern(z, array_t<int>(3, 3, 5, 7)).idx(), 3);
	EXPECT_EQ(find_last_pattern(z, array_t<int>(3, 5, 7, 4)).idx(), 4);
	EXPECT_EQ(find_last_pattern(z, array_t<int>(4, 4, 2, 8, 5)).idx(), 6);

	EXPECT_EQ(find_last_pattern(z, array<int>()).idx(), z.rbegin().idx());
	EXPECT_EQ(find_last_pattern(z, array_t<int>(1, 1)).idx(), z.rend().idx());
	EXPECT_EQ(find_last_pattern(z, array_t<int>(3, 8, 5, 4)).idx(), z.rend().idx());
}

TEST(search, count_all_pattern)
{
	array<int> x = array_t<int>(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_EQ(count_all_pattern(x, array_t<int>(3, 2, 8, 5)), 2);
	EXPECT_EQ(count_all_pattern(x, array_t<int>(2, 8, 5)), 2);
	EXPECT_EQ(count_all_pattern(x, array_t<int>(1, 5)), 3);
	EXPECT_EQ(count_all_pattern(x, array_t<int>(3, 3, 5, 7)), 1);
	EXPECT_EQ(count_all_pattern(x, array_t<int>(3, 5, 7, 4)), 1);
	EXPECT_EQ(count_all_pattern(x, array_t<int>(4, 4, 2, 8, 5)), 1);

	EXPECT_EQ(count_all_pattern(x, array<int>()), x.size());
	EXPECT_EQ(count_all_pattern(x, array_t<int>(1, 1)), 0);
	EXPECT_EQ(count_all_pattern(x, array_t<int>(3, 8, 5, 4)), 0);

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(count_all_pattern(y, array_t<int>(3, 2, 8, 5)), 2);
	EXPECT_EQ(count_all_pattern(y, array_t<int>(2, 8, 5)), 2);
	EXPECT_EQ(count_all_pattern(y, array_t<int>(1, 5)), 3);
	EXPECT_EQ(count_all_pattern(y, array_t<int>(3, 3, 5, 7)), 1);
	EXPECT_EQ(count_all_pattern(y, array_t<int>(3, 5, 7, 4)), 1);
	EXPECT_EQ(count_all_pattern(y, array_t<int>(4, 4, 2, 8, 5)), 1);

	EXPECT_EQ(count_all_pattern(y, array<int>()), y.size());
	EXPECT_EQ(count_all_pattern(y, array_t<int>(1, 1)), 0);
	EXPECT_EQ(count_all_pattern(y, array_t<int>(3, 8, 5, 4)), 0);

	const array<int> &z = x;
	EXPECT_EQ(count_all_pattern(z, array_t<int>(3, 2, 8, 5)), 2);
	EXPECT_EQ(count_all_pattern(z, array_t<int>(2, 8, 5)), 2);
	EXPECT_EQ(count_all_pattern(z, array_t<int>(1, 5)), 3);
	EXPECT_EQ(count_all_pattern(z, array_t<int>(3, 3, 5, 7)), 1);
	EXPECT_EQ(count_all_pattern(z, array_t<int>(3, 5, 7, 4)), 1);
	EXPECT_EQ(count_all_pattern(z, array_t<int>(4, 4, 2, 8, 5)), 1);

	EXPECT_EQ(count_all_pattern(z, array<int>()), z.size());
	EXPECT_EQ(count_all_pattern(z, array_t<int>(1, 1)), 0);
	EXPECT_EQ(count_all_pattern(z, array_t<int>(3, 8, 5, 4)), 0);
}

TEST(search, lower_bound)
{
	array<int> x = array_t<int>(12, 1, 2, 5, 6, 6, 8, 8, 10, 16, 29, 29, 29);
	EXPECT_EQ(lower_bound(x, 1).idx(), 0);
	EXPECT_EQ(lower_bound(x, 2).idx(), 1);
	EXPECT_EQ(lower_bound(x, 5).idx(), 2);
	EXPECT_EQ(lower_bound(x, 6).idx(), 3);
	EXPECT_EQ(lower_bound(x, 8).idx(), 5);
	EXPECT_EQ(lower_bound(x, 10).idx(), 7);
	EXPECT_EQ(lower_bound(x, 16).idx(), 8);
	EXPECT_EQ(lower_bound(x, 29).idx(), 9);

	EXPECT_EQ(lower_bound(x, 0).idx(), 0);
	EXPECT_EQ(lower_bound(x, 4).idx(), 2);
	EXPECT_EQ(lower_bound(x, 7).idx(), 5);
	EXPECT_EQ(lower_bound(x, 9).idx(), 7);
	EXPECT_EQ(lower_bound(x, 11).idx(), 8);
	EXPECT_EQ(lower_bound(x, 20).idx(), 9);
	EXPECT_EQ(lower_bound(x, 40).idx(), 12);

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(lower_bound(y, 1).idx(), 0);
	EXPECT_EQ(lower_bound(y, 2).idx(), 1);
	EXPECT_EQ(lower_bound(y, 5).idx(), 2);
	EXPECT_EQ(lower_bound(y, 6).idx(), 3);
	EXPECT_EQ(lower_bound(y, 8).idx(), 5);
	EXPECT_EQ(lower_bound(y, 10).idx(), 7);
	EXPECT_EQ(lower_bound(y, 16).idx(), 8);
	EXPECT_EQ(lower_bound(y, 29).idx(), 9);

	EXPECT_EQ(lower_bound(y, 0).idx(), 0);
	EXPECT_EQ(lower_bound(y, 4).idx(), 2);
	EXPECT_EQ(lower_bound(y, 7).idx(), 5);
	EXPECT_EQ(lower_bound(y, 9).idx(), 7);
	EXPECT_EQ(lower_bound(y, 11).idx(), 8);
	EXPECT_EQ(lower_bound(y, 20).idx(), 9);
	EXPECT_EQ(lower_bound(y, 40).idx(), 12);

	const array<int> &z = x;
	EXPECT_EQ(lower_bound(z, 1).idx(), 0);
	EXPECT_EQ(lower_bound(z, 2).idx(), 1);
	EXPECT_EQ(lower_bound(z, 5).idx(), 2);
	EXPECT_EQ(lower_bound(z, 6).idx(), 3);
	EXPECT_EQ(lower_bound(z, 8).idx(), 5);
	EXPECT_EQ(lower_bound(z, 10).idx(), 7);
	EXPECT_EQ(lower_bound(z, 16).idx(), 8);
	EXPECT_EQ(lower_bound(z, 29).idx(), 9);

	EXPECT_EQ(lower_bound(z, 0).idx(), 0);
	EXPECT_EQ(lower_bound(z, 4).idx(), 2);
	EXPECT_EQ(lower_bound(z, 7).idx(), 5);
	EXPECT_EQ(lower_bound(z, 9).idx(), 7);
	EXPECT_EQ(lower_bound(z, 11).idx(), 8);
	EXPECT_EQ(lower_bound(z, 20).idx(), 9);
	EXPECT_EQ(lower_bound(z, 40).idx(), 12);
}

TEST(search, upper_bound)
{
	array<int> x = array_t<int>(12, 1, 2, 5, 6, 6, 8, 8, 10, 16, 29, 29, 29);
	EXPECT_EQ(upper_bound(x, 1).idx(), 1);
	EXPECT_EQ(upper_bound(x, 2).idx(), 2);
	EXPECT_EQ(upper_bound(x, 5).idx(), 3);
	EXPECT_EQ(upper_bound(x, 6).idx(), 5);
	EXPECT_EQ(upper_bound(x, 8).idx(), 7);
	EXPECT_EQ(upper_bound(x, 10).idx(), 8);
	EXPECT_EQ(upper_bound(x, 16).idx(), 9);
	EXPECT_EQ(upper_bound(x, 29).idx(), 12);

	EXPECT_EQ(upper_bound(x, 0).idx(), 0);
	EXPECT_EQ(upper_bound(x, 4).idx(), 2);
	EXPECT_EQ(upper_bound(x, 7).idx(), 5);
	EXPECT_EQ(upper_bound(x, 9).idx(), 7);
	EXPECT_EQ(upper_bound(x, 11).idx(), 8);
	EXPECT_EQ(upper_bound(x, 20).idx(), 9);
	EXPECT_EQ(upper_bound(x, 40).idx(), 12);

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_EQ(upper_bound(y, 1).idx(), 1);
	EXPECT_EQ(upper_bound(y, 2).idx(), 2);
	EXPECT_EQ(upper_bound(y, 5).idx(), 3);
	EXPECT_EQ(upper_bound(y, 6).idx(), 5);
	EXPECT_EQ(upper_bound(y, 8).idx(), 7);
	EXPECT_EQ(upper_bound(y, 10).idx(), 8);
	EXPECT_EQ(upper_bound(y, 16).idx(), 9);
	EXPECT_EQ(upper_bound(y, 29).idx(), 12);

	EXPECT_EQ(upper_bound(y, 0).idx(), 0);
	EXPECT_EQ(upper_bound(y, 4).idx(), 2);
	EXPECT_EQ(upper_bound(y, 7).idx(), 5);
	EXPECT_EQ(upper_bound(y, 9).idx(), 7);
	EXPECT_EQ(upper_bound(y, 11).idx(), 8);
	EXPECT_EQ(upper_bound(y, 20).idx(), 9);
	EXPECT_EQ(upper_bound(y, 40).idx(), 12);

	const array<int> &z = x;
	EXPECT_EQ(upper_bound(z, 1).idx(), 1);
	EXPECT_EQ(upper_bound(z, 2).idx(), 2);
	EXPECT_EQ(upper_bound(z, 5).idx(), 3);
	EXPECT_EQ(upper_bound(z, 6).idx(), 5);
	EXPECT_EQ(upper_bound(z, 8).idx(), 7);
	EXPECT_EQ(upper_bound(z, 10).idx(), 8);
	EXPECT_EQ(upper_bound(z, 16).idx(), 9);
	EXPECT_EQ(upper_bound(z, 29).idx(), 12);

	EXPECT_EQ(upper_bound(z, 0).idx(), 0);
	EXPECT_EQ(upper_bound(z, 4).idx(), 2);
	EXPECT_EQ(upper_bound(z, 7).idx(), 5);
	EXPECT_EQ(upper_bound(z, 9).idx(), 7);
	EXPECT_EQ(upper_bound(z, 11).idx(), 8);
	EXPECT_EQ(upper_bound(z, 20).idx(), 9);
	EXPECT_EQ(upper_bound(z, 40).idx(), 12);
}
