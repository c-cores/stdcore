#include <gtest/gtest.h>

#include <core/array.h>
#include <core/range.h>
#include <core/fill.h>
#include <core/ascii_stream.h>

using namespace core;

TEST(array_struct, base_constructor)
{
	array<int> x;
	EXPECT_EQ(x.count, 0);
	EXPECT_EQ(x.capacity, 0);
	EXPECT_EQ(x.data, (int*)NULL);
}

TEST(array_struct, copy_constructor)
{
	array<int> x(array<int>::values(5, 1, 9, 7, 2, 5));
	EXPECT_EQ(x, array<int>::values(5, 1, 9, 7, 2, 5));

	// check negative lengths
	array<int> y = boundi(2).slice(x);
	EXPECT_EQ(y, array<int>::values(3, 7, 2, 5));
}

TEST(array_struct, fill_constructor)
{
	array<int> x = fill<int>(20, 10);
	EXPECT_EQ(20, x.count);
	for (int i = 0; i < x.count; i++)
		EXPECT_EQ(x[i], 10);
}

TEST(array_struct, range_constructor)
{
	array<int> x = range<int>(0, 10);
	EXPECT_EQ(10, x.count);
	for (int i = 0; i < x.count; i++)
		EXPECT_EQ(x[i], i);

	x = range<int>(10, 0, -1);
	EXPECT_EQ(10, x.count);
	for (int i = 0; i < x.count; i++)
		EXPECT_EQ(x[i], 10-i);

	x = range<int>(0, 10, 2);
	EXPECT_EQ(5, x.count);
	for (int i = 0; i < x.count; i++)
		EXPECT_EQ(x[i], i*2);

	x = range<int>(10, 0, -2);
	EXPECT_EQ(5, x.count);
	for (int i = 0; i < x.count; i++)
		EXPECT_EQ(x[i], 10-i*2);
}

TEST(array_struct, value_constructor)
{
	array<int> x = array<int>::values(5, 1, 3, 5, 7, 9);
	EXPECT_EQ(5, x.count);
	for (int i = 0; i < x.count; i++)
		EXPECT_EQ(x[i], i*2+1);
}

TEST(array_struct, index)
{
	array<int> x = array<int>::values(8, 5, 2, 3, 5, 6, 2, 1, 7);

	EXPECT_EQ(8, x.size());

	EXPECT_EQ(5, *x.at(0));
	EXPECT_EQ(3, *x.at(2));
	EXPECT_EQ(7, *x.at(-1));
	EXPECT_EQ(2, *x.at(-3));

	EXPECT_EQ(5, x.get(0));
	EXPECT_EQ(3, x.get(2));
	EXPECT_EQ(7, x.get(-1));
	EXPECT_EQ(2, x.get(-3));

	EXPECT_EQ(5, *x.ptr(0));
	EXPECT_EQ(3, *x.ptr(2));
	EXPECT_EQ(7, *x.ptr(-1));
	EXPECT_EQ(2, *x.ptr(-3));

	EXPECT_EQ(5, x[0]);
	EXPECT_EQ(3, x[2]);
	EXPECT_EQ(7, x[-1]);
	EXPECT_EQ(2, x[-3]);

	EXPECT_EQ(5, x.front());
	EXPECT_EQ(7, x.back());

	EXPECT_EQ(5, *x.begin());
	EXPECT_EQ(7, *x.rbegin());
}

TEST(array_struct, sub)
{
	array<int> x = array<int>::values(8, 5, 2, 3, 5, 6, 2, 1, 7);
	array<int> y = array<int>::values(4, 3, 5, 6, 2);
	array<int> z = array<int>::values(4, 6, 2, 1, 7);

	// positive start and end
	EXPECT_EQ(y, x.sub(2, 6));
	EXPECT_EQ(y, x.subcpy(2, 6));

	// positive start, negative end
	EXPECT_EQ(y, x.sub(2, -2));
	EXPECT_EQ(y, x.subcpy(2, -2));

	// negative start and end
	EXPECT_EQ(y, x.sub(-6, -2));
	EXPECT_EQ(y, x.subcpy(-6, -2));

	// negative start, positive end
	EXPECT_EQ(y, x.sub(-6, 6));
	EXPECT_EQ(y, x.subcpy(-6, 6));
	
	// single input
	EXPECT_EQ(z, x.sub(4));
	EXPECT_EQ(z, x.sub(-4));
	EXPECT_EQ(z, x.subcpy(4));
	EXPECT_EQ(z, x.subcpy(-4));

	// no inputs
	EXPECT_EQ(x, x.sub());
	EXPECT_EQ(y, y.sub());
	EXPECT_EQ(z, z.sub());
}

TEST(array_struct, alloc_back)
{
	array<int> x;
	x.alloc_back(10);
	EXPECT_EQ(10, x.count);
	EXPECT_GE(x.capacity, 10);
	for (int i = 0; i < 10; i++)
		x[i] = i;

	EXPECT_EQ(range<int>(0, 10), x);

	x.reserve(100);
	EXPECT_GE(x.capacity, 100);
	x.alloc_back(20);
	EXPECT_EQ(x.count, 30);
	for (int i = 10; i < 30; i++)
		x[i] = 30 - i;

	EXPECT_EQ(range<int>(0, 10), x.sub(0, 10));
	EXPECT_EQ(range<int>(20, 0, -1), x.sub(10, 30));
}

TEST(array_struct, alloc_front)
{
	array<int> x;
	x.alloc_front(10);
	EXPECT_EQ(10, x.count);
	EXPECT_GE(x.capacity, 10);
	for (int i = 0; i < 10; i++)
		x[i] = i;

	EXPECT_EQ(range<int>(0, 10), x);

	x.reserve(100);
	EXPECT_GE(x.capacity, 100);
	x.alloc_front(20);
	EXPECT_EQ(x.count, 30);
	for (int i = 0; i < 20; i++)
		x[i] = 20 - i;

	EXPECT_EQ(range<int>(0, 10), x.sub(20, 30));
	EXPECT_EQ(range<int>(20, 0, -1), x.sub(0, 20));
}

TEST(array_struct, drop)
{
	array<int> x = range<int>(0, 10);
	x.drop_back(5);
	EXPECT_EQ(range<int>(0, 5), x);

	x = range<int>(0, 10);
	x.drop_front(5);
	EXPECT_EQ(range<int>(5, 10), x);

	x = range<int>(0, 10);
	x.drop(3, 8);
	EXPECT_EQ(x, array<int>()
			<< range<int>(0, 3)
			<< range<int>(8, 10));

	x = range<int>(0, 10);
	x.drop(-7, -2);
	EXPECT_EQ(x, array<int>()
			<< range<int>(0, 3)
			<< range<int>(8, 10));
}

TEST(array_struct, pop)
{
	array<int> x = range<int>(0, 10);
	array<int> y = x.pop_back(5);
	EXPECT_EQ(range<int>(0, 5), x);
	EXPECT_EQ(range<int>(5, 10), y);

	x = range<int>(0, 10);
	y = x.pop_front(5);
	EXPECT_EQ(range<int>(5, 10), x);
	EXPECT_EQ(range<int>(0, 5), y);

	x = range<int>(0, 10);
	y = x.pop(3, 8);
	EXPECT_EQ(x, array<int>()
			<< range<int>(0, 3)
			<< range<int>(8, 10));
	EXPECT_EQ(y, range<int>(3, 8));

	x = range<int>(0, 10);
	y = x.pop(-7, -2);
	EXPECT_EQ(x, array<int>()
			<< range<int>(0, 3)
			<< range<int>(8, 10));
	EXPECT_EQ(y, range<int>(3, 8));
}

TEST(array_struct, push_back)
{
	array<int> x;
	EXPECT_EQ(0, x.count);
	EXPECT_EQ(0, x.capacity);
	for (int i = 0; i < 10; i++)
	{
		x.push_back(i);
		EXPECT_EQ(i+1, x.count);
		EXPECT_GE(x.capacity, x.count);
	}

	x.push_back(20);
	EXPECT_EQ(11, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_EQ(x.sub(0, 10), range<int>(0, 10));
	EXPECT_EQ(x[10], 20);

	x.reserve(40);
	EXPECT_GE(x.capacity, 40);
	x.push_back_unsafe(8);
	EXPECT_EQ(12, x.count);
	EXPECT_EQ(x.sub(0, 10), range<int>(0, 10));
	EXPECT_EQ(20, x[10]);
	EXPECT_EQ(8, x[11]);
}

TEST(array_struct, push_front)
{
	array<int> x;
	EXPECT_EQ(0, x.count);
	EXPECT_EQ(0, x.capacity);
	for (int i = 0; i < 10; i++)
	{
		x.push_front(9 - i);
		EXPECT_EQ(i+1, x.count);
		EXPECT_GE(x.capacity, x.count);
	}

	EXPECT_EQ(range<int>(0, 10), x);
}

TEST(array_struct, append_back)
{
	array<int> x = fill<int>(1, 8);
	array<int> y = fill<int>(1, 3);
	array<int> z;
	EXPECT_EQ(1, x.count);
	EXPECT_EQ(1, y.count);

	z = x;
	x.append_back(y);
	EXPECT_EQ(z.count + y.count, x.count);
	EXPECT_EQ(z, x.sub(0, z.count));
	EXPECT_EQ(y, x.sub(z.count, z.count+y.count));

	z = y;
	y.append_back(x);
	EXPECT_EQ(z.count + x.count, y.count);
	EXPECT_EQ(z, y.sub(0, z.count));
	EXPECT_EQ(x, y.sub(z.count, z.count+x.count));

	z = x;
	x.append_back(y);
	EXPECT_EQ(z.count+y.count, x.count);
	EXPECT_EQ(z, x.sub(0, z.count));
	EXPECT_EQ(y, x.sub(z.count, z.count+y.count));
	
	z = x;
	x.append_back(array<int>());
	EXPECT_EQ(z, x);

	y.reserve(100);
	EXPECT_EQ(3, y.count);
	EXPECT_GE(y.capacity, 100);

	z = y;
	y.append_back_unsafe(x);
	EXPECT_EQ(8, y.count);
	EXPECT_GE(y.capacity, 100);
	EXPECT_EQ(z, y.sub(0, z.count));
	EXPECT_EQ(x, y.sub(z.count, z.count+x.count));
}

TEST(array_struct, append_front)
{
	array<int> x = fill<int>(1, 8);
	array<int> y = fill<int>(1, 3);
	array<int> z;
	EXPECT_EQ(1, x.count);
	EXPECT_EQ(1, y.count);

	z = x;
	x.append_front(y);
	EXPECT_EQ(z.count+y.count, x.count);
	EXPECT_EQ(y, x.sub(0, y.count));
	EXPECT_EQ(z, x.sub(y.count, y.count+z.count));
	
	z = y;
	y.append_front(x);
	EXPECT_EQ(3, y.count);
	EXPECT_EQ(x, y.sub(0, x.count));
	EXPECT_EQ(z, y.sub(x.count, x.count+z.count));

	z = x;
	x.append_front(y);
	EXPECT_EQ(z.count+y.count, x.count);
	EXPECT_EQ(y, x.sub(0, y.count));
	EXPECT_EQ(z, x.sub(y.count, y.count+z.count));

	z = x;
	x.append_front(array<int>());
	EXPECT_EQ(z, x);
}

TEST(array_struct, replace)
{
	array<int> x = range<int>(0, 10);
	EXPECT_EQ(x, range<int>(0, 10));

	x.replace(0, 3, 5);
	EXPECT_EQ(x, array<int>()
			<< 5
			<< range<int>(3, 10));

	x = range<int>(0, 10);
	x.replace(7, 10, 5);
	EXPECT_EQ(x, array<int>()
				<< range<int>(0, 7)
				<< 5);

	x = range<int>(0, 10);
	x.replace(3, 7, 5);
	EXPECT_EQ(x, array<int>()
				<< range<int>(0, 3)
				<< 5
				<< range<int>(7, 10));

	x = range<int>(0, 10);
	x.replace(-7, -3, 5);
	EXPECT_EQ(x, array<int>()
				<< range<int>(0, 3)
				<< 5
				<< range<int>(7, 10));

	x = range<int>(0, 10);
	x.replace(-7, 7, 5);
	EXPECT_EQ(x, array<int>()
				<< range<int>(0, 3)
				<< 5
				<< range<int>(7, 10));

	x = range<int>(0, 10);
	x.replace(3, -3, 5);
	EXPECT_EQ(x, array<int>()
				<< range<int>(0, 3)
				<< 5
				<< range<int>(7, 10));

	x = range<int>(0, 10);
	x.replace_front(3, 5);
	EXPECT_EQ(x, array<int>()
			<< 5
			<< range<int>(3, 10));

	x = range<int>(0, 10);
	x.replace_back(3, 5);
	EXPECT_EQ(x, array<int>()
				<< range<int>(0, 7)
				<< 5);
}

TEST(array_struct, replace_container)
{
	array<int> x = range<int>(0, 10);
	EXPECT_EQ(x, range<int>(0, 10));
	array<int> y = array<int>::values(5, 2, 5, 3, 7, 2);

	x.replace(0, 3, y);
	EXPECT_EQ(x, array<int>()
			<< y
			<< range<int>(3, 10));

	x = range<int>(0, 10);
	x.replace(7, 10, y);
	EXPECT_EQ(x, array<int>()
				<< range<int>(0, 7)
				<< y);

	x = range<int>(0, 10);
	x.replace(3, 7, y);
	EXPECT_EQ(x, array<int>()
				<< range<int>(0, 3)
				<< y
				<< range<int>(7, 10));

	x = range<int>(0, 10);
	x.replace(-7, -3, y);
	EXPECT_EQ(x, array<int>()
				<< range<int>(0, 3)
				<< y
				<< range<int>(7, 10));

	x = range<int>(0, 10);
	x.replace(-7, 7, y);
	EXPECT_EQ(x, array<int>()
				<< range<int>(0, 3)
				<< y
				<< range<int>(7, 10));

	x = range<int>(0, 10);
	x.replace(3, -3, y);
	EXPECT_EQ(x, array<int>()
				<< range<int>(0, 3)
				<< y
				<< range<int>(7, 10));

	x = range<int>(0, 10);
	x.replace_front(3, y);
	EXPECT_EQ(x, array<int>()
			<< y
			<< range<int>(3, 10));

	x = range<int>(0, 10);
	x.replace_back(3, y);
	EXPECT_EQ(x, array<int>()
				<< range<int>(0, 7)
				<< y);

	// check negative lengths
	x = range<int>(0, 10);
	x.replace_back(3, boundi(1).slice(y));
	EXPECT_EQ(x, array<int>()
				<< range<int>(0, 7)
				<< y.sub(1));
}

TEST(array_struct, swap)
{
	array<int> x = range<int>(0, 10);
	array<int> y = fill<int>(8, 5);
	EXPECT_EQ(range<int>(0, 10), x);
	EXPECT_EQ(fill<int>(8, 5), y);
	x.swap(y);
	EXPECT_EQ(range<int>(0, 10), y);
	EXPECT_EQ(fill<int>(8, 5), x);
}

TEST(array_struct, resize)
{
	array<int> x;
	x.resize(20, 10);
	EXPECT_EQ(fill<int>(20, 10), x);

	x.resize(10, 5);
	EXPECT_EQ(fill<int>(10, 10), x);
}

TEST(array_struct, reserve)
{
	array<int> x;
	x.reserve(100);
	EXPECT_GE(x.capacity, 100);
	EXPECT_EQ(0, x.count);
	EXPECT_NE((int*)NULL, x.data);
}

TEST(array_struct, clear)
{
	array<int> x = range<int>(0, 10);
	EXPECT_EQ(10, x.count);
	EXPECT_GE(x.capacity, 10);
	EXPECT_NE((int*)NULL, x.data);

	x.clear();
	EXPECT_EQ(0, x.count);
	EXPECT_GE(x.capacity, 10);
	EXPECT_NE((int*)NULL, x.data);
}

TEST(array_struct, release)
{
	array<int> x = range<int>(0, 10);
	EXPECT_EQ(10, x.count);
	EXPECT_GE(x.capacity, 10);
	EXPECT_NE((int*)NULL, x.data);

	x.release();
	EXPECT_EQ(0, x.count);
	EXPECT_EQ(x.capacity, 0);
	EXPECT_EQ((int*)NULL, x.data);
}

TEST(array_struct, assign)
{
	array<int> x = range<int>(0, 10);
	EXPECT_EQ(10, x.count);
	EXPECT_GE(x.capacity, 10);
	EXPECT_NE((int*)NULL, x.data);

	array<int> y, z;

	y = x;
	z = x.sub();
	EXPECT_EQ(y, x);
	EXPECT_EQ(z, x);
	EXPECT_EQ(y, z);
}

TEST(array_struct, compare)
{
	array<int> x = range<int>(0, 10);
	array<int> y = range<int>(10, 0, -1);

	EXPECT_TRUE(x < y);
	EXPECT_FALSE(x > y);
	EXPECT_TRUE(x <= y);
	EXPECT_FALSE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);

	x.clear();
	y.clear();

	x = range<int>(0, 5);
	y = range<int>(0, 10);

	EXPECT_TRUE(x < y);
	EXPECT_FALSE(x > y);
	EXPECT_TRUE(x <= y);
	EXPECT_FALSE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);

	x = y;

	EXPECT_FALSE(x < y);
	EXPECT_FALSE(x > y);
	EXPECT_TRUE(x <= y);
	EXPECT_TRUE(x >= y);
	EXPECT_TRUE(x == y);
	EXPECT_FALSE(x != y);

	x.clear();
	y.clear();

	for (int i = 0; i < 5; i++)
		x.push_back(i);
	for (int i = 0; i < 10; i++)
	{
		y.push_back(i);
		x.push_back(10+i);
	}

	EXPECT_FALSE(x < y);
	EXPECT_TRUE(x > y);
	EXPECT_FALSE(x <= y);
	EXPECT_TRUE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);
}
