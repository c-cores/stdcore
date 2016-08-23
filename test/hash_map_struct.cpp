#include <gtest/gtest.h>

#include <core/hash_map.h>
#include <core/search.h>
#include <core/math.h>

using namespace core;

TEST(hash_map, constructor)
{
	srand(5);
	uint32_t val = rand();
	srand(5);
	hash_map<int, int> h;
	EXPECT_EQ(h.size(), 0);
	EXPECT_EQ(h.buckets.size(), 17);
	EXPECT_EQ(h.salt, val);
	EXPECT_EQ(h.shift, 28);
}

TEST(hash_map, insert)
{
	srand(0);

	hash_map<int, int> h;
	array<int> counts(fill<int>(101, 0));
	EXPECT_EQ(h.size(), 0);
	EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));

	for (int i = 0; i < 1000; i++)
	{
		int value = rand()%101 - 50;
		int value2 = value+1;
		counts[value+50]++;
		h.insert(value, value2);
		EXPECT_EQ(h.size(), i+1);
		EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));
		for (int j = 0; j < 101; j++)
			EXPECT_EQ(count_all(h, j-50), counts[j]);
	}
}

TEST(hash_map, find)
{
	srand(0);

	hash_map<int, int> h;
	array<int> counts(fill<int>(101, 0));
	EXPECT_EQ(h.size(), 0);
	EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));

	for (int i = 0; i < 100; i++)
	{
		int value = rand()%101 - 50;
		int value2 = value+1;
		counts[value+50]++;
		h.insert(value, value2);
		EXPECT_EQ(h.size(), i+1);
		EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));
		for (int j = 0; j < 101; j++)
			EXPECT_EQ(count_all(h, j-50), counts[j]);
	}

	for (int i = 0; i < counts.size(); i++)
	{
		hash_map<int, int>::iterator result = h.find(i-50);
		if (counts[i] > 0)
		{
			EXPECT_FALSE((result == h.end()));
			if (result != h.end())
			{
				EXPECT_EQ(result->key, i-50);
				EXPECT_EQ(result->value, i-49);
			}
		}
		else
			EXPECT_TRUE((result == h.end()));
	}
}

TEST(hash_map, contains)
{
	srand(0);

	hash_map<int, int> h;
	array<int> counts(fill<int>(101, 0));
	EXPECT_EQ(h.size(), 0);
	EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));

	for (int i = 0; i < 100; i++)
	{
		int value = rand()%101 - 50;
		int value2 = value+1;
		counts[value+50]++;
		h.insert(value, value2);
		EXPECT_EQ(h.size(), i+1);
		EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));
		for (int j = 0; j < 101; j++)
			EXPECT_EQ(count_all(h, j-50), counts[j]);
	}

	for (int i = 0; i < counts.size(); i++)
	{
		if (counts[i] > 0)
			EXPECT_TRUE(h.contains(i-50));
		else
			EXPECT_FALSE(h.contains(i-50));
	}
}
