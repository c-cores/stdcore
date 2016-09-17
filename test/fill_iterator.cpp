#include <gtest/gtest.h>

#include <core/fill.h>
#include <core/ascii_stream.h>
#include <core/compare.h>

using namespace core;

TEST(fill_iterator, iterate)
{
	fill<int> x(10, 5);

	int j = 0;
	for (fill<int>::iterator i = x.begin(); i; i++)
	{
		EXPECT_EQ(5, *i);
		j++;
	}
	EXPECT_EQ(10, j);
}


TEST(fill_iterator, index)
{
	fill<int> x(10, 5);

	EXPECT_EQ(5, *x.at(0));
	EXPECT_EQ(5, *x.at(2));
	EXPECT_EQ(5, *x.at(-1));
	EXPECT_EQ(5, *x.at(-3));

	EXPECT_EQ(5, x.at(0).get());
	EXPECT_EQ(5, x.at(2).get());
	EXPECT_EQ(5, x.at(-1).get());
	EXPECT_EQ(5, x.at(-3).get());

	EXPECT_EQ(0, x.at(0).idx());
	EXPECT_EQ(2, x.at(2).idx());
	EXPECT_EQ(x.size()-1, x.at(-1).idx());
	EXPECT_EQ(x.size()-3, x.at(-3).idx());
}

TEST(fill_iterator, sub)
{
	fill<int> x(10, 5);
	EXPECT_EQ(x.at(4).sub(3), fill<int>(3, 5));
	EXPECT_EQ(x.at(7).sub(-3), fill<int>(3, 5));
	EXPECT_EQ(x.at(4).sub(), fill<int>(6, 5));
	EXPECT_EQ(x.at(4).subcpy(3), fill<int>(3, 5));
	EXPECT_EQ(x.at(7).subcpy(-3), fill<int>(3, 5));
	EXPECT_EQ(x.at(4).subcpy(), fill<int>(6, 5));
}
