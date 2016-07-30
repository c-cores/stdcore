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
	EXPECT_TRUE(find_first(x, 2) == x.at(0));
	EXPECT_TRUE(find_first(x, 8) == x.at(1));
	EXPECT_TRUE(find_first(x, 5) == x.at(2));
	EXPECT_TRUE(find_first(x, 3) == x.at(3));
	EXPECT_TRUE(find_first(x, 7) == x.at(5));
	EXPECT_TRUE(find_first(x, 4) == x.at(6));

	EXPECT_TRUE(find_first(x, 0) == x.end());
	EXPECT_TRUE(find_first(x, 1) == x.end());
	EXPECT_TRUE(find_first(x, 9) == x.end());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_TRUE(find_first(y, 2) == y.at(0));
	EXPECT_TRUE(find_first(y, 8) == y.at(1));
	EXPECT_TRUE(find_first(y, 5) == y.at(2));
	EXPECT_TRUE(find_first(y, 3) == y.at(3));
	EXPECT_TRUE(find_first(y, 7) == y.at(5));
	EXPECT_TRUE(find_first(y, 4) == y.at(6));

	EXPECT_TRUE(find_first(y, 0) == y.end());
	EXPECT_TRUE(find_first(y, 1) == y.end());
	EXPECT_TRUE(find_first(y, 9) == y.end());

	const array<int> &z = x;
	EXPECT_TRUE(find_first(z, 2) == z.at(0));
	EXPECT_TRUE(find_first(z, 8) == z.at(1));
	EXPECT_TRUE(find_first(z, 5) == z.at(2));
	EXPECT_TRUE(find_first(z, 3) == z.at(3));
	EXPECT_TRUE(find_first(z, 7) == z.at(5));
	EXPECT_TRUE(find_first(z, 4) == z.at(6));

	EXPECT_TRUE(find_first(z, 0) == z.end());
	EXPECT_TRUE(find_first(z, 1) == z.end());
	EXPECT_TRUE(find_first(z, 9) == z.end());
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
	EXPECT_TRUE(find_last(x, 2) == x.at(7));
	EXPECT_TRUE(find_last(x, 8) == x.at(8));
	EXPECT_TRUE(find_last(x, 5) == x.at(9));
	EXPECT_TRUE(find_last(x, 3) == x.at(3));
	EXPECT_TRUE(find_last(x, 7) == x.at(5));
	EXPECT_TRUE(find_last(x, 4) == x.at(6));

	EXPECT_TRUE(find_last(x, 0) == x.end());
	EXPECT_TRUE(find_last(x, 1) == x.end());
	EXPECT_TRUE(find_last(x, 9) == x.end());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_TRUE(find_last(y, 2) == y.at(7));
	EXPECT_TRUE(find_last(y, 8) == y.at(8));
	EXPECT_TRUE(find_last(y, 5) == y.at(9));
	EXPECT_TRUE(find_last(y, 3) == y.at(3));
	EXPECT_TRUE(find_last(y, 7) == y.at(5));
	EXPECT_TRUE(find_last(y, 4) == y.at(6));

	EXPECT_TRUE(find_last(y, 0) == y.end());
	EXPECT_TRUE(find_last(y, 1) == y.end());
	EXPECT_TRUE(find_last(y, 9) == y.end());

	const array<int> &z = x;
	EXPECT_TRUE(find_last(z, 2) == z.at(7));
	EXPECT_TRUE(find_last(z, 8) == z.at(8));
	EXPECT_TRUE(find_last(z, 5) == z.at(9));
	EXPECT_TRUE(find_last(z, 3) == z.at(3));
	EXPECT_TRUE(find_last(z, 7) == z.at(5));
	EXPECT_TRUE(find_last(z, 4) == z.at(6));

	EXPECT_TRUE(find_last(z, 0) == z.end());
	EXPECT_TRUE(find_last(z, 1) == z.end());
	EXPECT_TRUE(find_last(z, 9) == z.end());
}

TEST(search, find_all)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_TRUE(find_all(x, 2) == array<array<int>::iterator>::values(2, x.at(0), x.at(7)));
	EXPECT_TRUE(find_all(x, 8) == array<array<int>::iterator>::values(2, x.at(1), x.at(8)));
	EXPECT_TRUE(find_all(x, 5) == array<array<int>::iterator>::values(3, x.at(2), x.at(4), x.at(9)));
	EXPECT_TRUE(find_all(x, 3) == array<array<int>::iterator>::values(1, x.at(3)));
	EXPECT_TRUE(find_all(x, 7) == array<array<int>::iterator>::values(1, x.at(5)));
	EXPECT_TRUE(find_all(x, 4) == array<array<int>::iterator>::values(1, x.at(6)));

	EXPECT_TRUE(find_all(x, 0) == array<array<int>::iterator>());
	EXPECT_TRUE(find_all(x, 1) == array<array<int>::iterator>());
	EXPECT_TRUE(find_all(x, 9) == array<array<int>::iterator>());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_TRUE(find_all(y, 2) == array<slice<range<array<int>::iterator> >::iterator>::values(2, y.at(0), y.at(7)));
	EXPECT_TRUE(find_all(y, 8) == array<slice<range<array<int>::iterator> >::iterator>::values(2, y.at(1), y.at(8)));
	EXPECT_TRUE(find_all(y, 5) == array<slice<range<array<int>::iterator> >::iterator>::values(3, y.at(2), y.at(4), y.at(9)));
	EXPECT_TRUE(find_all(y, 3) == array<slice<range<array<int>::iterator> >::iterator>::values(1, y.at(3)));
	EXPECT_TRUE(find_all(y, 7) == array<slice<range<array<int>::iterator> >::iterator>::values(1, y.at(5)));
	EXPECT_TRUE(find_all(y, 4) == array<slice<range<array<int>::iterator> >::iterator>::values(1, y.at(6)));

	EXPECT_TRUE(find_all(y, 0) == array<slice<range<array<int>::iterator> >::iterator>());
	EXPECT_TRUE(find_all(y, 1) == array<slice<range<array<int>::iterator> >::iterator>());
	EXPECT_TRUE(find_all(y, 9) == array<slice<range<array<int>::iterator> >::iterator>());

	const array<int> &z = x;
	EXPECT_TRUE(find_all(z, 2) == array<array<int>::const_iterator>::values(2, z.at(0), z.at(7)));
	EXPECT_TRUE(find_all(z, 8) == array<array<int>::const_iterator>::values(2, z.at(1), z.at(8)));
	EXPECT_TRUE(find_all(z, 5) == array<array<int>::const_iterator>::values(3, z.at(2), z.at(4), z.at(9)));
	EXPECT_TRUE(find_all(z, 3) == array<array<int>::const_iterator>::values(1, z.at(3)));
	EXPECT_TRUE(find_all(z, 7) == array<array<int>::const_iterator>::values(1, z.at(5)));
	EXPECT_TRUE(find_all(z, 4) == array<array<int>::const_iterator>::values(1, z.at(6)));

	EXPECT_TRUE(find_all(z, 0) == array<array<int>::const_iterator>());
	EXPECT_TRUE(find_all(z, 1) == array<array<int>::const_iterator>());
	EXPECT_TRUE(find_all(z, 9) == array<array<int>::const_iterator>());
}

TEST(search, find_first_of)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_TRUE(find_first_of(x, range<int>(2, 5)) == x.at(0));
	EXPECT_TRUE(find_first_of(x, range<int>(7, 10)) == x.at(1));
	EXPECT_TRUE(find_first_of(x, range<int>(6, 8)) == x.at(5));
	EXPECT_TRUE(find_first_of(x, array<int>::values(3, 4, 3, 1)) == x.at(3));
	EXPECT_TRUE(find_first_of(x, array<int>::values(3, 7, 4, 7)) == x.at(5));
	EXPECT_TRUE(find_first_of(x, array<int>::values(3, 2, 8, 5)) == x.at(0));

	EXPECT_TRUE(find_first_of(x, array<int>::values(0, 1, 9)) == x.end());
	EXPECT_TRUE(find_first_of(x, array<int>::values(10, 11, 12)) == x.end());
	EXPECT_TRUE(find_first_of(x, array<int>::values(-1, 6, 9)) == x.end());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_TRUE(find_first_of(y, range<int>(2, 5)) == y.at(0));
	EXPECT_TRUE(find_first_of(y, range<int>(7, 10)) == y.at(1));
	EXPECT_TRUE(find_first_of(y, range<int>(6, 8)) == y.at(5));
	EXPECT_TRUE(find_first_of(y, array<int>::values(3, 4, 3, 1)) == y.at(3));
	EXPECT_TRUE(find_first_of(y, array<int>::values(3, 7, 4, 7)) == y.at(5));
	EXPECT_TRUE(find_first_of(y, array<int>::values(3, 2, 8, 5)) == y.at(0));

	EXPECT_TRUE(find_first_of(y, array<int>::values(0, 1, 9)) == y.end());
	EXPECT_TRUE(find_first_of(y, array<int>::values(10, 11, 12)) == y.end());
	EXPECT_TRUE(find_first_of(y, array<int>::values(-1, 6, 9)) == y.end());

	const array<int> &z = x;
	EXPECT_TRUE(find_first_of(z, range<int>(2, 5)) == z.at(0));
	EXPECT_TRUE(find_first_of(z, range<int>(7, 10)) == z.at(1));
	EXPECT_TRUE(find_first_of(z, range<int>(6, 8)) == z.at(5));
	EXPECT_TRUE(find_first_of(z, array<int>::values(3, 4, 3, 1)) == z.at(3));
	EXPECT_TRUE(find_first_of(z, array<int>::values(3, 7, 4, 7)) == z.at(5));
	EXPECT_TRUE(find_first_of(z, array<int>::values(3, 2, 8, 5)) == z.at(0));

	EXPECT_TRUE(find_first_of(z, array<int>::values(0, 1, 9)) == z.end());
	EXPECT_TRUE(find_first_of(z, array<int>::values(10, 11, 12)) == z.end());
	EXPECT_TRUE(find_first_of(z, array<int>::values(-1, 6, 9)) == z.end());
}

TEST(search, find_last_of)
{
	array<int> x = array<int>::values(10, 2, 8, 5, 3, 5, 7, 4, 2, 8, 5);
	EXPECT_TRUE(find_last_of(x, range<int>(2, 5)) == x.at(7));
	EXPECT_TRUE(find_last_of(x, range<int>(7, 10)) == x.at(8));
	EXPECT_TRUE(find_last_of(x, range<int>(6, 8)) == x.at(5));
	EXPECT_TRUE(find_last_of(x, array<int>::values(3, 4, 3, 1)) == x.at(6));
	EXPECT_TRUE(find_last_of(x, array<int>::values(3, 7, 4, 7)) == x.at(6));
	EXPECT_TRUE(find_last_of(x, array<int>::values(3, 2, 8, 5)) == x.at(9));

	EXPECT_TRUE(find_last_of(x, array<int>::values(0, 1, 9)) == x.end());
	EXPECT_TRUE(find_last_of(x, array<int>::values(10, 11, 12)) == x.end());
	EXPECT_TRUE(find_last_of(x, array<int>::values(-1, 6, 9)) == x.end());

	slice<range<array<int>::iterator> > y = x.sub();
	EXPECT_TRUE(find_last_of(y, range<int>(2, 5)) == y.at(7));
	EXPECT_TRUE(find_last_of(y, range<int>(7, 10)) == y.at(8));
	EXPECT_TRUE(find_last_of(y, range<int>(6, 8)) == y.at(5));
	EXPECT_TRUE(find_last_of(y, array<int>::values(3, 4, 3, 1)) == y.at(6));
	EXPECT_TRUE(find_last_of(y, array<int>::values(3, 7, 4, 7)) == y.at(6));
	EXPECT_TRUE(find_last_of(y, array<int>::values(3, 2, 8, 5)) == y.at(9));

	EXPECT_TRUE(find_last_of(y, array<int>::values(0, 1, 9)) == y.end());
	EXPECT_TRUE(find_last_of(y, array<int>::values(10, 11, 12)) == y.end());
	EXPECT_TRUE(find_last_of(y, array<int>::values(-1, 6, 9)) == y.end());

	const array<int> &z = x;
	EXPECT_TRUE(find_last_of(z, range<int>(2, 5)) == z.at(7));
	EXPECT_TRUE(find_last_of(z, range<int>(7, 10)) == z.at(8));
	EXPECT_TRUE(find_last_of(z, range<int>(6, 8)) == z.at(5));
	EXPECT_TRUE(find_last_of(z, array<int>::values(3, 4, 3, 1)) == z.at(6));
	EXPECT_TRUE(find_last_of(z, array<int>::values(3, 7, 4, 7)) == z.at(6));
	EXPECT_TRUE(find_last_of(z, array<int>::values(3, 2, 8, 5)) == z.at(9));

	EXPECT_TRUE(find_last_of(z, array<int>::values(0, 1, 9)) == z.end());
	EXPECT_TRUE(find_last_of(z, array<int>::values(10, 11, 12)) == z.end());
	EXPECT_TRUE(find_last_of(z, array<int>::values(-1, 6, 9)) == z.end());
}
