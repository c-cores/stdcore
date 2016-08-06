#include <gtest/gtest.h>

#include <core/pair.h>

using namespace core;

TEST(pair, constructor)
{
	pair<int, char> x(5, 'h');
	EXPECT_EQ(x.first, 5);
	EXPECT_EQ(x.second, 'h');
}

TEST(pair, compare)
{
	pair<int, int> x(5, 10);
	pair<int, int> y(6, 5);
	EXPECT_FALSE((x == y));
	EXPECT_TRUE ((x != y));
	EXPECT_TRUE ((x < y));
	EXPECT_FALSE((x > y));
	EXPECT_TRUE ((x <= y));
	EXPECT_FALSE((x >= y));

	y.first = 5;

	EXPECT_FALSE((x == y));
	EXPECT_TRUE ((x != y));
	EXPECT_FALSE((x < y));
	EXPECT_TRUE ((x > y));
	EXPECT_FALSE((x <= y));
	EXPECT_TRUE ((x >= y));

	y.second = 10;

	EXPECT_TRUE ((x == y));
	EXPECT_FALSE((x != y));
	EXPECT_FALSE((x < y));
	EXPECT_FALSE((x > y));
	EXPECT_TRUE ((x <= y));
	EXPECT_TRUE ((x >= y));
}
