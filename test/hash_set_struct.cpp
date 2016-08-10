#include <gtest/gtest.h>

#include <core/hash_set.h>
#include <core/math.h>

using namespace core;

TEST(hash_set, constructor)
{
	srand(5);
	uint32_t val = rand();
	srand(5);
	hash_set<int, murmur3_32> h;
	EXPECT_EQ(h.size(), 0);
	EXPECT_EQ(h.buckets.size(), 17);
	EXPECT_EQ(h.salt, val);
	EXPECT_EQ(h.shift, 28);
}
