#include <gtest/gtest.h>

#include <std/hash_set.h>

using namespace core;

TEST(hash_set, increment)
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
		h.insert(value);
		EXPECT_EQ(h.size(), i+1);
		EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));
		for (int j = 0; j < 101; j++)
			EXPECT_EQ(count_all(h, j-50), counts[j]);
	}

	array<int> countsstar(fill<int>(101, 0));
	array<int> countsget(fill<int>(101, 0));
	array<int> countsptr(fill<int>(101, 0));
	for (hash_set<int>::iterator i = h.begin(); i != h.end(); i++)
	{
		countsstar[*i+50]++;
		countsget[i.get()+50]++;
		countsptr[*(i.ptr())+50]++;
	}

	EXPECT_EQ(counts, countsstar);
	EXPECT_EQ(counts, countsget);
	EXPECT_EQ(counts, countsptr);
}

TEST(hash_set, decrement)
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
		h.insert(value);
		EXPECT_EQ(h.size(), i+1);
		EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));
		for (int j = 0; j < 101; j++)
			EXPECT_EQ(count_all(h, j-50), counts[j]);
	}

	array<int> countsstar(fill<int>(101, 0));
	array<int> countsget(fill<int>(101, 0));
	array<int> countsptr(fill<int>(101, 0));
	for (hash_set<int>::iterator i = h.rbegin(); i != h.rend(); i--)
	{
		countsstar[*i+50]++;
		countsget[i.get()+50]++;
		countsptr[*(i.ptr())+50]++;
	}

	EXPECT_EQ(counts, countsstar);
	EXPECT_EQ(counts, countsget);
	EXPECT_EQ(counts, countsptr);
}

TEST(hash_set, at)
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
		h.insert(value);
		EXPECT_EQ(h.size(), i+1);
		EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));
		for (int j = 0; j < 101; j++)
			EXPECT_EQ(count_all(h, j-50), counts[j]);
	}

	array<int> counts2(fill<int>(101, 0));
	for (int i = 0; i < h.size(); i++)
	{
		counts2[*h.at(i)+50]++;
	}

	EXPECT_EQ(counts, counts2);
}

TEST(hash_set, drop_forward)
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
		h.insert(value);
		EXPECT_EQ(h.size(), i+1);
		EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));
		for (int j = 0; j < 101; j++)
			EXPECT_EQ(count_all(h, j-50), counts[j]);
	}

	for (int i = 0; i < 20; i++)
	{
		int loc = rand()%h.size();
		counts[*h.at(loc)+50]--;
		h.at(loc).drop();
	}

	array<int> counts2(fill<int>(101, 0));
	for (hash_set<int>::iterator i = h.begin(); i != h.end(); i++)
		counts2[*i+50]++;

	EXPECT_EQ(counts, counts2);
}

TEST(hash_set, drop_backward)
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
		h.insert(value);
		EXPECT_EQ(h.size(), i+1);
		EXPECT_EQ(h.buckets.size(), max(17, (1 << log2i(h.size()))+1));
		for (int j = 0; j < 101; j++)
			EXPECT_EQ(count_all(h, j-50), counts[j]);
	}

	for (int i = 0; i < 20; i++)
	{
		int loc = rand()%h.size();
		counts[*h.at(loc)+50]--;
		h.at(loc+1).drop(-1);
	}

	array<int> counts2(fill<int>(101, 0));
	for (hash_set<int>::iterator i = h.begin(); i != h.end(); i++)
		counts2[*i+50]++;

	EXPECT_EQ(counts, counts2);
}
