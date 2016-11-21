#include <gtest/gtest.h>

#include <std/map.h>
#include <std/sort.h>

using namespace core;

TEST(map, insert)
{
	map<int, int> x;
	x.insert(1, 10);
	EXPECT_EQ(x.size(), 1);
	EXPECT_EQ(x.get(0).key, 1);
	EXPECT_EQ(x.get(0).value, 10);

	x.insert(5, 7);
	EXPECT_EQ(x.size(), 2);
	EXPECT_EQ(x.get(0).key, 1);
	EXPECT_EQ(x.get(0).value, 10);
	EXPECT_EQ(x.get(1).key, 5);
	EXPECT_EQ(x.get(1).value, 7);

	x.insert(0, 20);
	EXPECT_EQ(x.size(), 3);
	EXPECT_EQ(x.get(0).key, 0);
	EXPECT_EQ(x.get(0).value, 20);
	EXPECT_EQ(x.get(1).key, 1);
	EXPECT_EQ(x.get(1).value, 10);
	EXPECT_EQ(x.get(2).key, 5);
	EXPECT_EQ(x.get(2).value, 7);

	x.insert(3, 5);
	EXPECT_EQ(x.size(), 4);
	EXPECT_EQ(x.get(0).key, 0);
	EXPECT_EQ(x.get(0).value, 20);
	EXPECT_EQ(x.get(1).key, 1);
	EXPECT_EQ(x.get(1).value, 10);
	EXPECT_EQ(x.get(2).key, 3);
	EXPECT_EQ(x.get(2).value, 5);
	EXPECT_EQ(x.get(3).key, 5);
	EXPECT_EQ(x.get(3).value, 7);

	x.clear();
	EXPECT_EQ(x.size(), 0);

	list<implier<int, int> > y;
	srand(0);
	for (int i = 0; i < 10; i++)
	{
		int key = rand();
		int value = rand();
		x.insert(key, value);
		y.push_back(implier<int, int>(key, value));
	}

	sort_quick_inplace(y);
	EXPECT_EQ(x.size(), y.size());

	list<implier<int, int> >::iterator i = y.begin();
	map<int, int>::iterator j = x.begin();
	for (; i != y.end() && j != x.end(); i++, j++)
	{
		EXPECT_EQ(i->key, j->key);
		EXPECT_EQ(i->value, j->value);
	}
}

TEST(map, find)
{
	map<int, int> x;
	x.insert(1, 10);
	x.insert(5, 7);
	x.insert(0, 20);
	x.insert(3, 5);
	EXPECT_EQ(x.find(10), x.end());
	EXPECT_EQ(x.find(2), x.end());
	EXPECT_EQ(x.find(4), x.end());
	EXPECT_EQ(x.find(8), x.end());

	x.clear();
	srand(0);
	for (int i = 0; i < 10; i++)
	{
		int key = rand();
		int value = rand();
		x.insert(key, value);
	}

	map<int, int>::iterator j = x.begin();
	for (; j != x.end(); j++)
	{
		EXPECT_EQ(x.find(j->key), j);
	}
}

TEST(map, operator_index)
{
	map<int, int> x;
	list<implier<int, int> > y;
	srand(0);
	for (int i = 0; i < 10; i++)
	{
		int key = rand();
		int value = rand();
		x[key] = value;
		y.push_back(implier<int, int>(key, value));
	}

	sort_quick_inplace(y);
	EXPECT_EQ(x.size(), y.size());

	list<implier<int, int> >::iterator i = y.begin();
	map<int, int>::iterator j = x.begin();
	for (; i != y.end() && j != x.end(); i++, j++)
	{
		EXPECT_EQ(i->key, j->key);
		EXPECT_EQ(i->value, j->value);
		EXPECT_EQ(x[j->key], j->value);
	}
}
