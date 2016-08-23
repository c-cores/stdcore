#include <gtest/gtest.h>

#include <core/graph.h>

using namespace core;

TEST(graph_iterator, link)
{
	graph<int> g;

	graph<int>::iterator i0 = g.insert(5);
	graph<int>::iterator i1 = g.insert(10);
	graph<int>::iterator i2 = g.insert(3);
	graph<int>::iterator i3 = g.insert(6);

	array<graph<int>::iterator> empty;

	EXPECT_EQ(i0.next(), empty);
	EXPECT_EQ(i1.next(), empty);
	EXPECT_EQ(i2.next(), empty);
	EXPECT_EQ(i3.next(), empty);
	EXPECT_EQ(i0.prev(), empty);
	EXPECT_EQ(i1.prev(), empty);
	EXPECT_EQ(i2.prev(), empty);
	EXPECT_EQ(i3.prev(), empty);


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

	i0.link(i1);
	EXPECT_EQ(i0.next(), i0next);
	EXPECT_EQ(i1.next(), empty);
	EXPECT_EQ(i2.next(), empty);
	EXPECT_EQ(i3.next(), empty);
	EXPECT_EQ(i0.prev(), empty);
	EXPECT_EQ(i1.prev(), i1prev);
	EXPECT_EQ(i2.prev(), empty);
	EXPECT_EQ(i3.prev(), empty);

	i1.link(i2);
	EXPECT_EQ(i0.next(), i0next);
	EXPECT_EQ(i1.next(), i1next);
	EXPECT_EQ(i2.next(), empty);
	EXPECT_EQ(i3.next(), empty);
	EXPECT_EQ(i0.prev(), empty);
	EXPECT_EQ(i1.prev(), i1prev);
	EXPECT_EQ(i2.prev(), i2prev);
	EXPECT_EQ(i3.prev(), empty);

	i2.link(i3);
	EXPECT_EQ(i0.next(), i0next);
	EXPECT_EQ(i1.next(), i1next);
	EXPECT_EQ(i2.next(), i2next);
	EXPECT_EQ(i3.next(), empty);
	EXPECT_EQ(i0.prev(), empty);
	EXPECT_EQ(i1.prev(), i1prev);
	EXPECT_EQ(i2.prev(), i2prev);
	EXPECT_EQ(i3.prev(), i3prev);

	i3.link(i0);
	EXPECT_EQ(i0.next(), i0next);
	EXPECT_EQ(i1.next(), i1next);
	EXPECT_EQ(i2.next(), i2next);
	EXPECT_EQ(i3.next(), i3next);
	EXPECT_EQ(i0.prev(), i0prev);
	EXPECT_EQ(i1.prev(), i1prev);
	EXPECT_EQ(i2.prev(), i2prev);
	EXPECT_EQ(i3.prev(), i3prev);
}

TEST(graph_iterator, pop)
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

	EXPECT_EQ(i2.pop(), 3);

	EXPECT_EQ(i0.next(), i0next);
	EXPECT_EQ(i1.next(), empty);
	EXPECT_EQ(i3.next(), i3next);
	EXPECT_EQ(i0.prev(), i0prev);
	EXPECT_EQ(i1.prev(), i1prev);
	EXPECT_EQ(i3.prev(), empty);

	EXPECT_EQ(i0.pop(), 5);

	EXPECT_EQ(i1.next(), empty);
	EXPECT_EQ(i3.next(), empty);
	EXPECT_EQ(i1.prev(), empty);
	EXPECT_EQ(i3.prev(), empty);

	EXPECT_EQ(i1.pop(), 10);

	EXPECT_EQ(i3.next(), empty);
	EXPECT_EQ(i3.prev(), empty);

	EXPECT_EQ(i3.pop(), 6);

	EXPECT_EQ(g.left.right, &g.right);
	EXPECT_EQ(g.right.left, &g.left);
}

TEST(graph_iterator, drop)
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

	i2.drop();

	EXPECT_EQ(i0.next(), i0next);
	EXPECT_EQ(i1.next(), empty);
	EXPECT_EQ(i3.next(), i3next);
	EXPECT_EQ(i0.prev(), i0prev);
	EXPECT_EQ(i1.prev(), i1prev);
	EXPECT_EQ(i3.prev(), empty);

	i0.drop();

	EXPECT_EQ(i1.next(), empty);
	EXPECT_EQ(i3.next(), empty);
	EXPECT_EQ(i1.prev(), empty);
	EXPECT_EQ(i3.prev(), empty);

	i1.drop();

	EXPECT_EQ(i3.next(), empty);
	EXPECT_EQ(i3.prev(), empty);

	i3.drop();

	EXPECT_EQ(g.left.right, &g.right);
	EXPECT_EQ(g.right.left, &g.left);
}

TEST(graph_iterator, unlink)
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

	i2.unlink(i3);

	EXPECT_EQ(i0.next(), i0next);
	EXPECT_EQ(i1.next(), i1next);
	EXPECT_EQ(i2.next(), empty);
	EXPECT_EQ(i3.next(), i3next);
	EXPECT_EQ(i0.prev(), i0prev);
	EXPECT_EQ(i1.prev(), i1prev);
	EXPECT_EQ(i2.prev(), i2prev);
	EXPECT_EQ(i3.prev(), empty);

	i0.unlink(i3);

	EXPECT_EQ(i0.next(), i0next);
	EXPECT_EQ(i1.next(), i1next);
	EXPECT_EQ(i2.next(), empty);
	EXPECT_EQ(i3.next(), i3next);
	EXPECT_EQ(i0.prev(), i0prev);
	EXPECT_EQ(i1.prev(), i1prev);
	EXPECT_EQ(i2.prev(), i2prev);
	EXPECT_EQ(i3.prev(), empty);

	i0.unlink(i1);

	EXPECT_EQ(i0.next(), empty);
	EXPECT_EQ(i1.next(), i1next);
	EXPECT_EQ(i2.next(), empty);
	EXPECT_EQ(i3.next(), i3next);
	EXPECT_EQ(i0.prev(), i0prev);
	EXPECT_EQ(i1.prev(), empty);
	EXPECT_EQ(i2.prev(), i2prev);
	EXPECT_EQ(i3.prev(), empty);

	i0.unlink(i1);

	EXPECT_EQ(i0.next(), empty);
	EXPECT_EQ(i1.next(), i1next);
	EXPECT_EQ(i2.next(), empty);
	EXPECT_EQ(i3.next(), i3next);
	EXPECT_EQ(i0.prev(), i0prev);
	EXPECT_EQ(i1.prev(), empty);
	EXPECT_EQ(i2.prev(), i2prev);
	EXPECT_EQ(i3.prev(), empty);

	i1.unlink(i2);

	EXPECT_EQ(i0.next(), empty);
	EXPECT_EQ(i1.next(), empty);
	EXPECT_EQ(i2.next(), empty);
	EXPECT_EQ(i3.next(), i3next);
	EXPECT_EQ(i0.prev(), i0prev);
	EXPECT_EQ(i1.prev(), empty);
	EXPECT_EQ(i2.prev(), empty);
	EXPECT_EQ(i3.prev(), empty);

	i0.unlink(i3);

	EXPECT_EQ(i0.next(), empty);
	EXPECT_EQ(i1.next(), empty);
	EXPECT_EQ(i2.next(), empty);
	EXPECT_EQ(i3.next(), i3next);
	EXPECT_EQ(i0.prev(), i0prev);
	EXPECT_EQ(i1.prev(), empty);
	EXPECT_EQ(i2.prev(), empty);
	EXPECT_EQ(i3.prev(), empty);

	i3.unlink(i0);

	EXPECT_EQ(i0.next(), empty);
	EXPECT_EQ(i1.next(), empty);
	EXPECT_EQ(i2.next(), empty);
	EXPECT_EQ(i3.next(), empty);
	EXPECT_EQ(i0.prev(), empty);
	EXPECT_EQ(i1.prev(), empty);
	EXPECT_EQ(i2.prev(), empty);
	EXPECT_EQ(i3.prev(), empty);
}
