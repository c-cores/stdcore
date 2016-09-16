#include <gtest/gtest.h>

#include <core/array.h>
#include <core/list.h>
#include <core/fill.h>
#include <core/ascii_stream.h>
#include <core/sparse_range.h>

using namespace core;

TEST(slice_struct, base_constructor_array)
{
	array<int> y = range<int>(0, 10);
	slice<array<array<int>::iterator> > x = array<int>::values(5, 5, 2, 8, 3, 6).sample(y);
	EXPECT_EQ(x.size(), 5);
	EXPECT_EQ(5, x.get(0));
	EXPECT_EQ(2, x.get(1));
	EXPECT_EQ(8, x.get(2));
	EXPECT_EQ(3, x.get(3));
	EXPECT_EQ(6, x.get(4));
}

TEST(slice_struct, base_constructor_list)
{
	array<int> y = range<int>(0, 10);
	slice<list<array<int>::iterator> > x = list<int>::values(5, 5, 2, 8, 3, 6).sample(y);
	EXPECT_EQ(x.size(), 5);
	EXPECT_EQ(5, x.get(0));
	EXPECT_EQ(2, x.get(1));
	EXPECT_EQ(8, x.get(2));
	EXPECT_EQ(3, x.get(3));
	EXPECT_EQ(6, x.get(4));
}

TEST(slice_struct, base_constructor_range)
{
	array<int> y = range<int>(0, 10);
	slice<range<array<int>::iterator> > x = range<array<int>::iterator>(y.at(2), y.at(7));
	EXPECT_EQ(x.size(), 5);
	EXPECT_EQ(2, x.get(0));
	EXPECT_EQ(3, x.get(1));
	EXPECT_EQ(4, x.get(2));
	EXPECT_EQ(5, x.get(3));
	EXPECT_EQ(6, x.get(4));
}

TEST(slice_struct, base_constructor_fill)
{
	array<int> y = range<int>(0, 10);
	slice<fill<array<int>::iterator> > x = fill<array<int>::iterator>(5, y.at(2));
	EXPECT_EQ(x.size(), 5);
	EXPECT_EQ(2, x.get(0));
	EXPECT_EQ(2, x.get(1));
	EXPECT_EQ(2, x.get(2));
	EXPECT_EQ(2, x.get(3));
	EXPECT_EQ(2, x.get(4));
}

TEST(slice_struct, copy_constructor)
{
	array<int> y = range<int>(0, 10);
	slice<array<array<int>::iterator> > x = array<int>::values(5, 5, 2, 8, 3, 6).sample(y);
	slice<array<array<int>::iterator> > z = x;
	EXPECT_EQ(z.size(), 5);
	EXPECT_EQ(5, z.get(0));
	EXPECT_EQ(2, z.get(1));
	EXPECT_EQ(8, z.get(2));
	EXPECT_EQ(3, z.get(3));
	EXPECT_EQ(6, z.get(4));
}

TEST(slice_struct, range_constructor)
{
	array<int> y = range<int>(0, 10);
	slice<array<array<int>::iterator> > x = array<int>::values(5, 5, 2, 8, 3, 6).sample(y);
	slice<array<array<int>::iterator> > z(x.at(1), x.at(4));
	EXPECT_EQ(z.size(), 3);
	EXPECT_EQ(2, z.get(0));
	EXPECT_EQ(8, z.get(1));
	EXPECT_EQ(3, z.get(2));
}

TEST(slice_struct, index_array)
{
	array<int> y = array<int>::values(8, 5, 2, 3, 5, 6, 2, 1, 7);
	slice<array<array<int>::iterator> > x = array<array<int>::iterator>(range<array<int>::iterator>(y.begin(), y.end()));

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

TEST(slice_struct, index_list)
{
	array<int> y = array<int>::values(8, 5, 2, 3, 5, 6, 2, 1, 7);
	slice<list<array<int>::iterator> > x = list<array<int>::iterator>(range<array<int>::iterator>(y.begin(), y.end()));

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

TEST(slice_struct, index_range)
{
	array<int> y = array<int>::values(8, 5, 2, 3, 5, 6, 2, 1, 7);
	slice<range<array<int>::iterator> > x = range<array<int>::iterator>(y.begin(), y.end());

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

TEST(slice_struct, sub_array)
{
	array<int> x0 = array<int>::values(8, 5, 2, 3, 5, 6, 2, 1, 7);
	array<int> y = array<int>::values(4, 3, 5, 6, 2);
	array<int> z = array<int>::values(4, 6, 2, 1, 7);

	slice<array<array<int>::iterator> > x = array<array<int>::iterator>(range<array<int>::iterator>(x0.begin(), x0.end()));

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

TEST(slice_struct, sub_list)
{
	array<int> x0 = array<int>::values(8, 5, 2, 3, 5, 6, 2, 1, 7);
	array<int> y = array<int>::values(4, 3, 5, 6, 2);
	array<int> z = array<int>::values(4, 6, 2, 1, 7);

	slice<list<array<int>::iterator> > x = list<array<int>::iterator>(range<array<int>::iterator>(x0.begin(), x0.end()));

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

TEST(slice_struct, sub_range)
{
	array<int> x0 = array<int>::values(8, 5, 2, 3, 5, 6, 2, 1, 7);
	array<int> y = array<int>::values(4, 3, 5, 6, 2);
	array<int> z = array<int>::values(4, 6, 2, 1, 7);

	slice<range<array<int>::iterator> > x = range<array<int>::iterator>(x0.begin(), x0.end());

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

TEST(slice_struct, array_alloc_back)
{
	array<int> y = range<int>(0, 30);
	slice<array<array<int>::iterator> > x;
	x.alloc_back(10);
	EXPECT_EQ(10, x.count);
	EXPECT_GE(x.capacity, 10);
	for (int i = 0; i < 10; i++)
		x.ref(i) = y.at(i);

	EXPECT_EQ(range<int>(0, 10), x);

	x.reserve(100);
	EXPECT_GE(x.capacity, 100);
	x.alloc_back(20);
	EXPECT_EQ(x.count, 30);
	for (int i = 10; i < 30; i++)
		x.ref(i) = y.at(30 - i);

	EXPECT_EQ(range<int>(0, 10), x.sub(0, 10));
	EXPECT_EQ(sparse_range<int>(20, 0, -1), x.sub(10, 30));
}

TEST(slice_struct, array_alloc_front)
{
	array<int> y = range<int>(0, 30);
	slice<array<array<int>::iterator> > x;
	x.alloc_front(10);
	EXPECT_EQ(10, x.count);
	EXPECT_GE(x.capacity, 10);
	for (int i = 0; i < 10; i++)
		x.ref(i) = y.at(i);

	EXPECT_EQ(range<int>(0, 10), x);

	x.reserve(100);
	EXPECT_GE(x.capacity, 100);
	x.alloc_front(20);
	EXPECT_EQ(x.count, 30);
	for (int i = 0; i < 20; i++)
		x.ref(i) = y.at(20 - i);

	EXPECT_EQ(range<int>(0, 10), x.sub(20, 30));
	EXPECT_EQ(sparse_range<int>(20, 0, -1), x.sub(0, 20));
}

TEST(slice_struct, array_drop)
{
	array<int> y = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = y.begin(); i; i++)
		x.push_back(i);
	x.drop_back(5);
	EXPECT_EQ(range<int>(0, 5), x);

	x.clear();
	for (array<int>::iterator i = y.begin(); i; i++)
		x.push_back(i);
	x.drop_front(5);
	EXPECT_EQ(range<int>(5, 10), x);

	x.clear();
	for (array<int>::iterator i = y.begin(); i; i++)
		x.push_back(i);
	x.drop(3, 8);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 3)
			+ range<int>(8, 10));

	x.clear();
	for (array<int>::iterator i = y.begin(); i; i++)
		x.push_back(i);
	x.drop(-7, -2);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 3)
			+ range<int>(8, 10));
}

TEST(slice_struct, array_pop)
{
	array<int> z = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = z.begin(); i; i++)
		x.push_back(i);

	slice<array<array<int>::iterator> > y = x.pop_back(5);
	EXPECT_EQ(range<int>(0, 5), x);
	EXPECT_EQ(range<int>(5, 10), y);

	x.clear();
	for (array<int>::iterator i = z.begin(); i; i++)
		x.push_back(i);
	y = x.pop_front(5);
	EXPECT_EQ(range<int>(5, 10), x);
	EXPECT_EQ(range<int>(0, 5), y);

	x.clear();
	for (array<int>::iterator i = z.begin(); i; i++)
		x.push_back(i);
	y = x.pop(3, 8);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 3)
			+ range<int>(8, 10));
	EXPECT_EQ(y, range<int>(3, 8));

	x.clear();
	for (array<int>::iterator i = z.begin(); i; i++)
		x.push_back(i);
	y = x.pop(-7, -2);
	EXPECT_EQ(x, array<int>()
			+ range<int>(0, 3)
			+ range<int>(8, 10));
	EXPECT_EQ(y, range<int>(3, 8));
}

TEST(slice_struct, array_push_back)
{
	array<int> z = array<int>() + range<int>(0, 10) + 20 + 8;
	slice<array<array<int>::iterator> > x;

	EXPECT_EQ(0, x.count);
	EXPECT_EQ(0, x.capacity);
	for (int i = 0; i < 10; i++)
	{
		x.push_back(z.at(i));
		EXPECT_EQ(i+1, x.count);
		EXPECT_GE(x.capacity, x.count);
	}

	x.push_back(z.at(10));
	EXPECT_EQ(11, x.count);
	EXPECT_GE(x.capacity, x.count);
	EXPECT_EQ(x.sub(0, 10), range<int>(0, 10));
	EXPECT_EQ(x[10], 20);

	x.reserve(40);
	EXPECT_GE(x.capacity, 40);
	x.push_back_unsafe(z.at(11));
	EXPECT_EQ(12, x.count);
	EXPECT_EQ(x.sub(0, 10), range<int>(0, 10));
	EXPECT_EQ(20, x[10]);
	EXPECT_EQ(8, x[11]);
}

TEST(slice_struct, array_push_front)
{
	array<int> z = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;

	EXPECT_EQ(0, x.count);
	EXPECT_EQ(0, x.capacity);
	for (int i = 0; i < 10; i++)
	{
		x.push_front(z.at(9 - i));
		EXPECT_EQ(i+1, x.count);
		EXPECT_GE(x.capacity, x.count);
	}

	EXPECT_EQ(range<int>(0, 10), x);
}

TEST(slice_struct, array_append_back)
{
	array<int> x0 = fill<int>(1, 8);
	array<int> y0 = fill<int>(1, 3);
	slice<array<array<int>::iterator> > x;
	slice<array<array<int>::iterator> > y;
	slice<array<array<int>::iterator> > z;
	x.push_back(x0.begin());
	y.push_back(y0.begin());
	EXPECT_EQ(1, x.count);
	EXPECT_EQ(1, y.count);

	z = x;
	x.append_back(y.ref());
	EXPECT_EQ(z.count + y.count, x.count);
	EXPECT_EQ(z, x.sub(0, z.count));
	EXPECT_EQ(y, x.sub(z.count, z.count+y.count));

	z = y;
	y.append_back(x.ref());
	EXPECT_EQ(z.count + x.count, y.count);
	EXPECT_EQ(z, y.sub(0, z.count));
	EXPECT_EQ(x, y.sub(z.count, z.count+x.count));

	z = x;
	x.append_back(y.ref());
	EXPECT_EQ(z.count+y.count, x.count);
	EXPECT_EQ(z, x.sub(0, z.count));
	EXPECT_EQ(y, x.sub(z.count, z.count+y.count));
	
	z = x;
	x.append_back(array<array<int>::iterator>());
	EXPECT_EQ(z, x);

	y.reserve(100);
	EXPECT_EQ(3, y.count);
	EXPECT_GE(y.capacity, 100);

	z = y;
	y.append_back_unsafe(x.ref());
	EXPECT_EQ(8, y.count);
	EXPECT_GE(y.capacity, 100);
	EXPECT_EQ(z, y.sub(0, z.count));
	EXPECT_EQ(x, y.sub(z.count, z.count+x.count));
}

TEST(slice_struct, array_append_front)
{
	array<int> x0 = fill<int>(1, 8);
	array<int> y0 = fill<int>(1, 3);
	slice<array<array<int>::iterator> > x;
	slice<array<array<int>::iterator> > y;
	slice<array<array<int>::iterator> > z;
	x.push_back(x0.begin());
	y.push_back(y0.begin());
	EXPECT_EQ(1, x.count);
	EXPECT_EQ(1, y.count);

	z = x;
	x.append_front(y.ref());
	EXPECT_EQ(z.count+y.count, x.count);
	EXPECT_EQ(y, x.sub(0, y.count));
	EXPECT_EQ(z, x.sub(y.count, y.count+z.count));
	
	z = y;
	y.append_front(x.ref());
	EXPECT_EQ(3, y.count);
	EXPECT_EQ(x, y.sub(0, x.count));
	EXPECT_EQ(z, y.sub(x.count, x.count+z.count));

	z = x;
	x.append_front(y.ref());
	EXPECT_EQ(z.count+y.count, x.count);
	EXPECT_EQ(y, x.sub(0, y.count));
	EXPECT_EQ(z, x.sub(y.count, y.count+z.count));

	z = x;
	x.append_front(array<array<int>::iterator>());
	EXPECT_EQ(z, x);
}

TEST(slice_struct, array_replace)
{
	array<int> z = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = z.begin(); i; i++)
		x.push_back(i);
	EXPECT_EQ(x, range<int>(0, 10));

	x.replace(0, 3, z.at(5));
	EXPECT_EQ(x, array<int>()
			+ 5
			+ range<int>(3, 10));

	x.clear();
	for (array<int>::iterator i = z.begin(); i; i++)
		x.push_back(i);
	x.replace(7, 10, z.at(5));
	EXPECT_EQ(x, array<int>()
				+ range<int>(0, 7)
				+ 5);

	x.clear();
	for (array<int>::iterator i = z.begin(); i; i++)
		x.push_back(i);
	x.replace(3, 7, z.at(5));
	EXPECT_EQ(x, array<int>()
				+ range<int>(0, 3)
				+ 5
				+ range<int>(7, 10));

	x.clear();
	for (array<int>::iterator i = z.begin(); i; i++)
		x.push_back(i);
	x.replace(-7, -3, z.at(5));
	EXPECT_EQ(x, array<int>()
				+ range<int>(0, 3)
				+ 5
				+ range<int>(7, 10));

	x.clear();
	for (array<int>::iterator i = z.begin(); i; i++)
		x.push_back(i);
	x.replace(-7, 7, z.at(5));
	EXPECT_EQ(x, array<int>()
				+ range<int>(0, 3)
				+ 5
				+ range<int>(7, 10));

	x.clear();
	for (array<int>::iterator i = z.begin(); i; i++)
		x.push_back(i);
	x.replace(3, -3, z.at(5));
	EXPECT_EQ(x, array<int>()
				+ range<int>(0, 3)
				+ 5
				+ range<int>(7, 10));

	x.clear();
	for (array<int>::iterator i = z.begin(); i; i++)
		x.push_back(i);
	x.replace_front(3, z.at(5));
	EXPECT_EQ(x, array<int>()
			+ 5
			+ range<int>(3, 10));

	x.clear();
	for (array<int>::iterator i = z.begin(); i; i++)
		x.push_back(i);
	x.replace_back(3, z.at(5));
	EXPECT_EQ(x, array<int>()
				+ range<int>(0, 7)
				+ 5);
}

TEST(slice_struct, array_replace_container)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);
	EXPECT_EQ(x, range<int>(0, 10));
	array<int> y = array<int>::values(5, 2, 5, 3, 7, 2);

	x.replace(0, 3, y.sub().ref());
	EXPECT_EQ(x, array<int>()
			+ y
			+ range<int>(3, 10));

	x.clear();
	for (array<int>::iterator i = x0.begin(); i; i++)
			x.push_back(i);
	x.replace(7, 10, y.sub().ref());
	EXPECT_EQ(x, array<int>()
				+ range<int>(0, 7)
				+ y);

	x.clear();
	for (array<int>::iterator i = x0.begin(); i; i++)
			x.push_back(i);
	x.replace(3, 7, y.sub().ref());
	EXPECT_EQ(x, array<int>()
				+ range<int>(0, 3)
				+ y
				+ range<int>(7, 10));

	x.clear();
	for (array<int>::iterator i = x0.begin(); i; i++)
			x.push_back(i);
	x.replace(-7, -3, y.sub().ref());
	EXPECT_EQ(x, array<int>()
				+ range<int>(0, 3)
				+ y
				+ range<int>(7, 10));

	x.clear();
	for (array<int>::iterator i = x0.begin(); i; i++)
			x.push_back(i);
	x.replace(-7, 7, y.sub().ref());
	EXPECT_EQ(x, array<int>()
				+ range<int>(0, 3)
				+ y
				+ range<int>(7, 10));

	x.clear();
	for (array<int>::iterator i = x0.begin(); i; i++)
			x.push_back(i);
	x.replace(3, -3, y.sub().ref());
	EXPECT_EQ(x, array<int>()
				+ range<int>(0, 3)
				+ y
				+ range<int>(7, 10));

	x.clear();
	for (array<int>::iterator i = x0.begin(); i; i++)
			x.push_back(i);
	x.replace_front(3, y.sub().ref());
	EXPECT_EQ(x, array<int>()
			+ y
			+ range<int>(3, 10));

	x.clear();
	for (array<int>::iterator i = x0.begin(); i; i++)
			x.push_back(i);
	x.replace_back(3, y.sub().ref());
	EXPECT_EQ(x, array<int>()
				+ range<int>(0, 7)
				+ y);
}

TEST(slice_struct, array_swap)
{
	array<int> x0 = range<int>(0, 10);
	array<int> y0 = fill<int>(8, 5);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);
	slice<array<array<int>::iterator> > y;
	for (array<int>::iterator i = y0.begin(); i; i++)
		y.push_back(i);

	EXPECT_EQ(range<int>(0, 10), x);
	EXPECT_EQ(fill<int>(8, 5), y);
	x.swap(y);
	EXPECT_EQ(range<int>(0, 10), y);
	EXPECT_EQ(fill<int>(8, 5), x);
}

TEST(slice_struct, array_resize)
{
	array<int> y = array<int>::values(5, 2, 4, 3, 5, 7);
	slice<array<array<int>::iterator> > x;
	x.resize(20, y.at(0));
	EXPECT_EQ(fill<int>(20, y.get(0)), x);

	x.resize(10, y.at(3));
	EXPECT_EQ(fill<int>(10, y.get(0)), x);
}

TEST(slice_struct, array_reserve)
{
	slice<array<array<int>::iterator> > x;
	x.reserve(100);
	EXPECT_GE(x.capacity, 100);
	EXPECT_EQ(0, x.count);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
}

TEST(slice_struct, array_clear)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);
	EXPECT_EQ(10, x.count);
	EXPECT_GE(x.capacity, 10);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);

	x.clear();
	EXPECT_EQ(0, x.count);
	EXPECT_GE(x.capacity, 10);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);
}

TEST(slice_struct, array_release)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);
	EXPECT_EQ(10, x.count);
	EXPECT_GE(x.capacity, 10);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);

	x.release();
	EXPECT_EQ(0, x.count);
	EXPECT_EQ(x.capacity, 0);
	EXPECT_EQ((array<int>::iterator*)NULL, x.data);
}

TEST(slice_struct, array_assign)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);
	EXPECT_EQ(10, x.count);
	EXPECT_GE(x.capacity, 10);
	EXPECT_NE((array<int>::iterator*)NULL, x.data);

	slice<array<array<int>::iterator> > y;

	y = x;
	EXPECT_EQ(y, x);
}

TEST(slice_struct, array_compare)
{
	array<int> x0 = range<int>(0, 10);
	slice<array<array<int>::iterator> > x;
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);
	array<int> y0 = sparse_range<int>(10, 0, -1);
	slice<array<array<int>::iterator> > y;
	for (array<int>::iterator i = y0.begin(); i; i++)
		y.push_back(i);

	EXPECT_TRUE(x < y);
	EXPECT_FALSE(x > y);
	EXPECT_TRUE(x <= y);
	EXPECT_FALSE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);

	x.clear();
	x0.clear();
	y.clear();
	y0.clear();

	x0 = range<int>(0, 5);
	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);
	y0 = range<int>(0, 10);
	for (array<int>::iterator i = y0.begin(); i; i++)
		y.push_back(i);

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

	x0.clear();
	y0.clear();
	x.clear();
	y.clear();

	for (int i = 0; i < 5; i++)
		x0.push_back(i);
	for (int i = 0; i < 10; i++)
	{
		y0.push_back(i);
		x0.push_back(10+i);
	}

	for (array<int>::iterator i = x0.begin(); i; i++)
		x.push_back(i);
	for (array<int>::iterator i = y0.begin(); i; i++)
		y.push_back(i);

	EXPECT_FALSE(x < y);
	EXPECT_TRUE(x > y);
	EXPECT_FALSE(x <= y);
	EXPECT_TRUE(x >= y);
	EXPECT_FALSE(x == y);
	EXPECT_TRUE(x != y);
}
