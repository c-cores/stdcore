#include <gtest/gtest.h>

#include <std/hash_set.h>
#include <std/search.h>
#include <std/math.h>

using namespace core;

TEST(hash_set, constructor)
{
	srand(5);
	uint32_t val = rand();
	srand(5);
	hash_set<int> h;
	EXPECT_EQ(h.size(), 0);
	EXPECT_EQ(h.buckets.size(), 17);
	EXPECT_EQ(h.salt, val);
	EXPECT_EQ(h.shift, 28);
}

TEST(hash_set, insert)
{
	srand(0);

	hash_set<int> h;
	array<int> counts(fill<int>(101, 0));
	EXPECT_EQ(h.size(), 0);
	EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));

	for (int i = 0; i < 1000; i++)
	{
		int value = rand()%101 - 50;
		counts[value+50]++;
		h.insert_duplicate(value);
		EXPECT_EQ(h.size(), i+1);
		EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));
		for (int j = 0; j < 101; j++)
			EXPECT_EQ(count_all(h, j-50), counts[j]);
	}
}

TEST(hash_set, find)
{
	srand(0);

	hash_set<int> h;
	array<int> counts(fill<int>(101, 0));
	EXPECT_EQ(h.size(), 0);
	EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));

	for (int i = 0; i < 100; i++)
	{
		int value = rand()%101 - 50;
		counts[value+50]++;
		h.insert_duplicate(value);
		EXPECT_EQ(h.size(), i+1);
		EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));
		for (int j = 0; j < 101; j++)
			EXPECT_EQ(count_all(h, j-50), counts[j]);
	}

	for (int i = 0; i < counts.size(); i++)
	{
		hash_set<int>::iterator result = h.find(i-50);
		if (counts[i] > 0)
		{
			EXPECT_FALSE((result == h.end()));
			if (result != h.end())
				EXPECT_EQ(*result, i-50);
		}
		else
			EXPECT_TRUE((result == h.end()));
	}
}

TEST(hash_set, count_all)
{
	srand(0);

	hash_set<int> h;
	array<int> counts(fill<int>(101, 0));
	EXPECT_EQ(h.size(), 0);
	EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));

	for (int i = 0; i < 100; i++)
	{
		int value = rand()%101 - 50;
		counts[value+50]++;
		h.insert_duplicate(value);
		EXPECT_EQ(h.size(), i+1);
		EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));
		for (int j = 0; j < 101; j++)
			EXPECT_EQ(count_all(h, j-50), counts[j]);
	}

	for (int i = 0; i < counts.size(); i++)
		EXPECT_EQ(h.count_all(i-50), counts[i]);
}

TEST(hash_set, contains)
{
	srand(0);

	hash_set<int> h;
	array<int> counts(fill<int>(101, 0));
	EXPECT_EQ(h.size(), 0);
	EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));

	for (int i = 0; i < 100; i++)
	{
		int value = rand()%101 - 50;
		counts[value+50]++;
		h.insert_duplicate(value);
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
