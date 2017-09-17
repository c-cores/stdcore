#include <gtest/gtest.h>

#include <std/sparse_range.h>
#include <std/compare.h>

using namespace core;

TEST(sparse_range_iterator, iterate)
{
	sparse_range<int> x(0, 10, 2);

	int j = 0;
	for (sparse_range<int>::iterator i = x.begin(); i; i++)
	{
		EXPECT_EQ(j, *i);
		j += 2;
	}
	EXPECT_EQ(10, j);
}

TEST(sparse_range_iterator, index)
{
	sparse_range<int> x(0, 20, 2);

	EXPECT_EQ(0, *x.at(0));
	EXPECT_EQ(4, *x.at(2));
	EXPECT_EQ(18, *x.at(-1));
	EXPECT_EQ(14, *x.at(-3));

	EXPECT_EQ(0, x.at(0).get());
	EXPECT_EQ(4, x.at(2).get());
	EXPECT_EQ(18, x.at(-1).get());
	EXPECT_EQ(14, x.at(-3).get());

	EXPECT_EQ(0, x.at(0).idx());
	EXPECT_EQ(2, x.at(2).idx());
	EXPECT_EQ(x.size()-1, x.at(-1).idx());
	EXPECT_EQ(x.size()-3, x.at(-3).idx());
}

TEST(sparse_range_iterator, sub)
{
	sparse_range<int> x(0, 20, 2);
	EXPECT_EQ(x.at(4).sub(3), sparse_range<int>(8, 14, 2));
	EXPECT_EQ(x.at(7).sub(-3), sparse_range<int>(8, 14, 2));
	EXPECT_EQ(x.at(4).sub(), sparse_range<int>(8, 20, 2));
	EXPECT_EQ(x.at(4).subcpy(3), sparse_range<int>(8, 14, 2));
	EXPECT_EQ(x.at(7).subcpy(-3), sparse_range<int>(8, 14, 2));
	EXPECT_EQ(x.at(4).subcpy(), sparse_range<int>(8, 20, 2));
}
