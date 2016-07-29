#include <gtest/gtest.h>

#include <core/sort.h>
#include <core/array.h>
#include <core/list.h>
#include <core/fill.h>
#include <core/ascii_stream.h>

using namespace core;

TEST(sort, swap)
{
	int x = 5;
	int y = 10;

	swap(x, y);

	EXPECT_EQ(x, 10);
	EXPECT_EQ(y, 5);
}

TEST(sort, median_iterator)
{
	array<int> x = array<int>::values(3, 1, 2, 3);
	EXPECT_EQ(median_iterator(x.at(0), x.at(1), x.at(2)), x.at(1));

	x = array<int>::values(3, 3, 2, 1);
	EXPECT_EQ(median_iterator(x.at(0), x.at(1), x.at(2)), x.at(1));

	x = array<int>::values(3, 2, 1, 3);
	EXPECT_EQ(median_iterator(x.at(0), x.at(1), x.at(2)), x.at(0));

	x = array<int>::values(3, 2, 3, 1);
	EXPECT_EQ(median_iterator(x.at(0), x.at(1), x.at(2)), x.at(0));

	x = array<int>::values(3, 1, 3, 2);
	EXPECT_EQ(median_iterator(x.at(0), x.at(1), x.at(2)), x.at(2));

	x = array<int>::values(3, 3, 1, 2);
	EXPECT_EQ(median_iterator(x.at(0), x.at(1), x.at(2)), x.at(2));
}

TEST(sort, sort_selection)
{
	array<int> x = array<int>::values(10, 5, 5, 4, 3, 2, 3, 4, 2, 1, 1);
	array<int> y = sort_selection(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 5, 5, 4, 3, 2, 3, 4, 2, 1, 1));

	x = array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5);
	y = sort_selection(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));

	x = array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5);
	y = sort_selection(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5));

	x = array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1);
	y = sort_selection(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1));
}

TEST(sort, sort_selection_inplace)
{
	array<int> x = array<int>::values(10, 5, 5, 4, 3, 2, 3, 4, 2, 1, 1);
	array<int> y = sort_selection_inplace(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));

	x = array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5);
	y = sort_selection_inplace(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));

	x = array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5);
	y = sort_selection_inplace(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));

	x = array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1);
	y = sort_selection_inplace(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
}

TEST(sort, sort_quick)
{
	array<int> x = array<int>::values(10, 5, 5, 4, 3, 2, 3, 4, 2, 1, 1);
	array<int> y = sort_quick(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 5, 5, 4, 3, 2, 3, 4, 2, 1, 1));

	x = array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5);
	y = sort_quick(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));

	x = array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5);
	y = sort_quick(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5));

	x = array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1);
	y = sort_quick(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1));
}

TEST(sort, sort_quick_inplace)
{
	array<int> x = array<int>::values(10, 5, 5, 4, 3, 2, 3, 4, 2, 1, 1);
	array<int> y = sort_quick_inplace(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));

	x = array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5);
	y = sort_quick_inplace(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));

	x = array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5);
	y = sort_quick_inplace(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));

	x = array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1);
	y = sort_quick_inplace(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
}

TEST(sort, is_sorted)
{
	EXPECT_FALSE(is_sorted(array<int>::values(10, 5, 5, 4, 3, 2, 3, 4, 2, 1, 1)));
	EXPECT_TRUE(is_sorted(array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5)));
	EXPECT_FALSE(is_sorted(array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5)));
	EXPECT_FALSE(is_sorted(array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1)));
}

TEST(sort, is_rsorted)
{
	EXPECT_FALSE(is_rsorted(array<int>::values(10, 5, 5, 4, 3, 2, 3, 4, 2, 1, 1)));
	EXPECT_FALSE(is_rsorted(array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5)));
	EXPECT_FALSE(is_rsorted(array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5)));
	EXPECT_TRUE(is_rsorted(array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1)));
}

TEST(sort, reverse)
{
	array<int> x = array<int>::values(10, 5, 5, 4, 3, 2, 3, 4, 2, 1, 1);
	array<int> y = reverse(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 4, 3, 2, 3, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 5, 5, 4, 3, 2, 3, 4, 2, 1, 1));

	x = array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5);
	y = reverse(x);
	EXPECT_EQ(y, array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1));
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));

	x = array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5);
	y = reverse(x);
	EXPECT_EQ(y, array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5));
	EXPECT_EQ(x, array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5));

	x = array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1);
	y = reverse(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1));
}

TEST(sort, reverse_inplace)
{
	array<int> x = array<int>::values(10, 5, 5, 4, 3, 2, 3, 4, 2, 1, 1);
	array<int> y = reverse_inplace(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 4, 3, 2, 3, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 4, 3, 2, 3, 4, 5, 5));

	x = array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5);
	y = reverse_inplace(x);
	EXPECT_EQ(y, array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1));
	EXPECT_EQ(x, array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1));

	x = array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5);
	y = reverse_inplace(x);
	EXPECT_EQ(y, array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5));
	EXPECT_EQ(x, array<int>::values(10, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5));

	x = array<int>::values(10, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1);
	y = reverse_inplace(x);
	EXPECT_EQ(y, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
	EXPECT_EQ(x, array<int>::values(10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5));
}
