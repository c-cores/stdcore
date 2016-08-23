#include <gtest/gtest.h>

#include <core/graph.h>

using namespace core;

TEST(graph, constructor)
{
	graph<int> g;
	EXPECT_EQ(g.left.right, &g.right);
	EXPECT_EQ(g.right.left, &g.left);
}

TEST(graph, insert)
{
	graph<int> g;

	g.insert(5);
	g.insert(10);
	g.insert(3);
	g.insert(6);

	graph<int>::iterator i = g.begin();
	EXPECT_FALSE((i == g.end()));
	if (i != g.end())
		EXPECT_EQ(*i, 5);
	i++;
	EXPECT_FALSE((i == g.end()));
	if (i != g.end())
		EXPECT_EQ(*i, 10);
	i++;
	EXPECT_FALSE((i == g.end()));
	if (i != g.end())
		EXPECT_EQ(*i, 3);
	i++;
	EXPECT_FALSE((i == g.end()));
	if (i != g.end())
		EXPECT_EQ(*i, 6);
	i++;
	EXPECT_TRUE((i == g.end()));
}

TEST(graph, clear)
{
	graph<int> g;

	g.insert(5);
	g.insert(10);
	g.insert(3);
	g.insert(6);

	graph<int>::iterator i = g.begin();
	EXPECT_FALSE((i == g.end()));
	if (i != g.end())
		EXPECT_EQ(*i, 5);
	i++;
	EXPECT_FALSE((i == g.end()));
	if (i != g.end())
		EXPECT_EQ(*i, 10);
	i++;
	EXPECT_FALSE((i == g.end()));
	if (i != g.end())
		EXPECT_EQ(*i, 3);
	i++;
	EXPECT_FALSE((i == g.end()));
	if (i != g.end())
		EXPECT_EQ(*i, 6);
	i++;
	EXPECT_TRUE((i == g.end()));

	g.clear();
	EXPECT_TRUE((g.begin() == g.end()));
}

TEST(graph_iterator, copy_constructor)
{
	graph<int> g;

	graph<int>::iterator i0 = g.insert(5);
	graph<int>::iterator i1 = g.insert(10);
	graph<int>::iterator i2 = g.insert(3);
	graph<int>::iterator i3 = g.insert(6);

	i0.link(i1);
	i1.link(i2);
	i2.link(i3);
	i3.link(i0);

	array<graph<int>::iterator> empty;

	array<graph<int>::iterator> i0next;
	i0next.push_back(i1);

	array<graph<int>::iterator> i1next;
	i1next.push_back(i2);

	array<graph<int>::iterator> i2next;
	i2next.push_back(i3);

	array<graph<int>::iterator> i3next;
	i3next.push_back(i0);

	array<graph<int>::iterator> i0prev;
	i0prev.push_back(i3);

	array<graph<int>::iterator> i1prev;
	i1prev.push_back(i0);

	array<graph<int>::iterator> i2prev;
	i2prev.push_back(i1);

	array<graph<int>::iterator> i3prev;
	i3prev.push_back(i2);

	EXPECT_EQ(i0.next(), i0next);
	EXPECT_EQ(i1.next(), i1next);
	EXPECT_EQ(i2.next(), i2next);
	EXPECT_EQ(i3.next(), i3next);
	EXPECT_EQ(i0.prev(), i0prev);
	EXPECT_EQ(i1.prev(), i1prev);
	EXPECT_EQ(i2.prev(), i2prev);
	EXPECT_EQ(i3.prev(), i3prev);

	graph<int> g2 = g;

	graph<int>::iterator i = g2.begin();
	EXPECT_EQ(*i, 5);
	i++;
	EXPECT_EQ(*i, 10);
	i++;
	EXPECT_EQ(*i, 3);
	i++;
	EXPECT_EQ(*i, 6);

	i = g2.begin();

	EXPECT_EQ(*i, 5);
	EXPECT_EQ(i.next().size(), 1);
	i = i.next()[0];
	EXPECT_EQ(*i, 10);
	EXPECT_EQ(i.next().size(), 1);
	i = i.next()[0];
	EXPECT_EQ(*i, 3);
	EXPECT_EQ(i.next().size(), 1);
	i = i.next()[0];
	EXPECT_EQ(*i, 6);
	EXPECT_EQ(i.next().size(), 1);
	i = i.next()[0];
	EXPECT_EQ(*i, 5);

	i = g2.begin();

	EXPECT_EQ(*i, 5);
	EXPECT_EQ(i.prev().size(), 1);
	i = i.prev()[0];
	EXPECT_EQ(*i, 6);
	EXPECT_EQ(i.prev().size(), 1);
	i = i.prev()[0];
	EXPECT_EQ(*i, 3);
	EXPECT_EQ(i.prev().size(), 1);
	i = i.prev()[0];
	EXPECT_EQ(*i, 10);
	EXPECT_EQ(i.prev().size(), 1);
	i = i.prev()[0];
	EXPECT_EQ(*i, 5);
}

TEST(graph_iterator, assign)
{
	graph<int> g;

	graph<int>::iterator i0 = g.insert(5);
	graph<int>::iterator i1 = g.insert(10);
	graph<int>::iterator i2 = g.insert(3);
	graph<int>::iterator i3 = g.insert(6);

	i0.link(i1);
	i1.link(i2);
	i2.link(i3);
	i3.link(i0);

	array<graph<int>::iterator> empty;

	array<graph<int>::iterator> i0next;
	i0next.push_back(i1);

	array<graph<int>::iterator> i1next;
	i1next.push_back(i2);

	array<graph<int>::iterator> i2next;
	i2next.push_back(i3);

	array<graph<int>::iterator> i3next;
	i3next.push_back(i0);

	array<graph<int>::iterator> i0prev;
	i0prev.push_back(i3);

	array<graph<int>::iterator> i1prev;
	i1prev.push_back(i0);

	array<graph<int>::iterator> i2prev;
	i2prev.push_back(i1);

	array<graph<int>::iterator> i3prev;
	i3prev.push_back(i2);

	EXPECT_EQ(i0.next(), i0next);
	EXPECT_EQ(i1.next(), i1next);
	EXPECT_EQ(i2.next(), i2next);
	EXPECT_EQ(i3.next(), i3next);
	EXPECT_EQ(i0.prev(), i0prev);
	EXPECT_EQ(i1.prev(), i1prev);
	EXPECT_EQ(i2.prev(), i2prev);
	EXPECT_EQ(i3.prev(), i3prev);

	graph<int> g2;

	g2.insert(5);
	g2.insert(4);

	EXPECT_EQ(*g2.begin(), 5);
	EXPECT_EQ(*g2.rbegin(), 4);

	g2 = g;

	graph<int>::iterator i = g2.begin();
	EXPECT_EQ(*i, 5);
	i++;
	EXPECT_EQ(*i, 10);
	i++;
	EXPECT_EQ(*i, 3);
	i++;
	EXPECT_EQ(*i, 6);

	i = g2.begin();

	EXPECT_EQ(*i, 5);
	EXPECT_EQ(i.next().size(), 1);
	i = i.next()[0];
	EXPECT_EQ(*i, 10);
	EXPECT_EQ(i.next().size(), 1);
	i = i.next()[0];
	EXPECT_EQ(*i, 3);
	EXPECT_EQ(i.next().size(), 1);
	i = i.next()[0];
	EXPECT_EQ(*i, 6);
	EXPECT_EQ(i.next().size(), 1);
	i = i.next()[0];
	EXPECT_EQ(*i, 5);

	i = g2.begin();

	EXPECT_EQ(*i, 5);
	EXPECT_EQ(i.prev().size(), 1);
	i = i.prev()[0];
	EXPECT_EQ(*i, 6);
	EXPECT_EQ(i.prev().size(), 1);
	i = i.prev()[0];
	EXPECT_EQ(*i, 3);
	EXPECT_EQ(i.prev().size(), 1);
	i = i.prev()[0];
	EXPECT_EQ(*i, 10);
	EXPECT_EQ(i.prev().size(), 1);
	i = i.prev()[0];
	EXPECT_EQ(*i, 5);
}

