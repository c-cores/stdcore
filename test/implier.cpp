#include <gtest/gtest.h>

#include <std/implier.h>

using namespace core;

TEST(implier, compare)
{
	EXPECT_FALSE((implier<int, int>(5, 10) < implier<int, int>(2, 16)));
	EXPECT_FALSE((implier<int, int>(5, 16) < implier<int, int>(2, 10)));
	EXPECT_TRUE ((implier<int, int>(2, 10) < implier<int, int>(5, 16)));
	EXPECT_TRUE ((implier<int, int>(2, 16) < implier<int, int>(5, 10)));
	EXPECT_FALSE((implier<int, int>(5, 16) < implier<int, int>(2, 16)));
	EXPECT_FALSE((implier<int, int>(2, 16) < implier<int, int>(2, 10)));
	EXPECT_TRUE ((implier<int, int>(2, 16) < implier<int, int>(5, 16)));
	EXPECT_FALSE((implier<int, int>(2, 16) < implier<int, int>(2, 10)));

	EXPECT_TRUE ((implier<int, int>(5, 10) > implier<int, int>(2, 16)));
	EXPECT_TRUE ((implier<int, int>(5, 16) > implier<int, int>(2, 10)));
	EXPECT_FALSE((implier<int, int>(2, 10) > implier<int, int>(5, 16)));
	EXPECT_FALSE((implier<int, int>(2, 16) > implier<int, int>(5, 10)));
	EXPECT_TRUE ((implier<int, int>(5, 16) > implier<int, int>(2, 16)));
	EXPECT_FALSE((implier<int, int>(2, 16) > implier<int, int>(2, 10)));
	EXPECT_FALSE((implier<int, int>(2, 16) > implier<int, int>(5, 16)));
	EXPECT_FALSE((implier<int, int>(2, 16) > implier<int, int>(2, 10)));

	EXPECT_FALSE((implier<int, int>(5, 10) <= implier<int, int>(2, 16)));
	EXPECT_FALSE((implier<int, int>(5, 16) <= implier<int, int>(2, 10)));
	EXPECT_TRUE ((implier<int, int>(2, 10) <= implier<int, int>(5, 16)));
	EXPECT_TRUE ((implier<int, int>(2, 16) <= implier<int, int>(5, 10)));
	EXPECT_FALSE((implier<int, int>(5, 16) <= implier<int, int>(2, 16)));
	EXPECT_TRUE ((implier<int, int>(2, 16) <= implier<int, int>(2, 10)));
	EXPECT_TRUE ((implier<int, int>(2, 16) <= implier<int, int>(5, 16)));
	EXPECT_TRUE ((implier<int, int>(2, 16) <= implier<int, int>(2, 10)));

	EXPECT_TRUE ((implier<int, int>(5, 10) >= implier<int, int>(2, 16)));
	EXPECT_TRUE ((implier<int, int>(5, 16) >= implier<int, int>(2, 10)));
	EXPECT_FALSE((implier<int, int>(2, 10) >= implier<int, int>(5, 16)));
	EXPECT_FALSE((implier<int, int>(2, 16) >= implier<int, int>(5, 10)));
	EXPECT_TRUE ((implier<int, int>(5, 16) >= implier<int, int>(2, 16)));
	EXPECT_TRUE ((implier<int, int>(2, 16) >= implier<int, int>(2, 10)));
	EXPECT_FALSE((implier<int, int>(2, 16) >= implier<int, int>(5, 16)));
	EXPECT_TRUE ((implier<int, int>(2, 16) >= implier<int, int>(2, 10)));

	EXPECT_FALSE((implier<int, int>(5, 10) == implier<int, int>(2, 16)));
	EXPECT_FALSE((implier<int, int>(5, 16) == implier<int, int>(2, 10)));
	EXPECT_FALSE((implier<int, int>(2, 10) == implier<int, int>(5, 16)));
	EXPECT_FALSE((implier<int, int>(2, 16) == implier<int, int>(5, 10)));
	EXPECT_FALSE((implier<int, int>(5, 16) == implier<int, int>(2, 16)));
	EXPECT_TRUE ((implier<int, int>(2, 16) == implier<int, int>(2, 10)));
	EXPECT_FALSE((implier<int, int>(2, 16) == implier<int, int>(5, 16)));
	EXPECT_TRUE ((implier<int, int>(2, 16) == implier<int, int>(2, 10)));

	EXPECT_TRUE ((implier<int, int>(5, 10) != implier<int, int>(2, 16)));
	EXPECT_TRUE ((implier<int, int>(5, 16) != implier<int, int>(2, 10)));
	EXPECT_TRUE ((implier<int, int>(2, 10) != implier<int, int>(5, 16)));
	EXPECT_TRUE ((implier<int, int>(2, 16) != implier<int, int>(5, 10)));
	EXPECT_TRUE ((implier<int, int>(5, 16) != implier<int, int>(2, 16)));
	EXPECT_FALSE((implier<int, int>(2, 16) != implier<int, int>(2, 10)));
	EXPECT_TRUE ((implier<int, int>(2, 16) != implier<int, int>(5, 16)));
	EXPECT_FALSE((implier<int, int>(2, 16) != implier<int, int>(2, 10)));
}
