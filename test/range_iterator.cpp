#include <gtest/gtest.h>

#include <core/range.h>
#include <core/ascii_stream.h>

using namespace core;

TEST(range_iterator, iterate)
{
	range<int> x(0, 10, 2);

	int j = 0;
	for (range<int>::iterator i = x.begin(); i; i++)
	{
		EXPECT_EQ(j, *i);
		j += 2;
	}
	EXPECT_EQ(10, j);
}

TEST(range_iterator, index)
{
	range<int> x(0, 20, 2);

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

TEST(range_iterator, sub)
{
	range<int> x(0, 20, 2);
	EXPECT_EQ(x.at(4).sub(3), range<int>(8, 14, 2));
	EXPECT_EQ(x.at(7).sub(-3), range<int>(8, 14, 2));
	EXPECT_EQ(x.at(4).sub(), range<int>(8, 20, 2));
	EXPECT_EQ(x.at(4).subcpy(3), range<int>(8, 14, 2));
	EXPECT_EQ(x.at(7).subcpy(-3), range<int>(8, 14, 2));
	EXPECT_EQ(x.at(4).subcpy(), range<int>(8, 20, 2));
}
