#include <gtest/gtest.h>

#include <std/array.h>
#include <std/list.h>
#include <std/heap.h>

using namespace core;

TEST(heap, heap_make)
{
	core::array<int> x = array_t<int>(7, 3, 1, 2, 3, 6, 3, 7);
	
	heap_make(x);

	EXPECT_EQ(x, array_t<int>(7, 7, 6, 3, 3, 1, 3, 2));
}

TEST(heap, heap_pop)
{
	core::array<int> x = array_t<int>(7, 7, 6, 3, 3, 1, 3, 2);

	EXPECT_EQ(heap_pop(x), 7);
	EXPECT_EQ(heap_pop(x), 6);
	EXPECT_EQ(heap_pop(x), 3);
	EXPECT_EQ(heap_pop(x), 3);
	EXPECT_EQ(heap_pop(x), 3);
	EXPECT_EQ(heap_pop(x), 2);
	EXPECT_EQ(heap_pop(x), 1);
}

TEST(heap, heap_push)
{
	core::array<int> x;

	heap_push(x, 3);
	EXPECT_EQ(x, array_t<int>(1, 3));
	heap_push(x, 1);
	EXPECT_EQ(x, array_t<int>(2, 3, 1));
	heap_push(x, 2);
	EXPECT_EQ(x, array_t<int>(3, 3, 1, 2));
	heap_push(x, 3);
	EXPECT_EQ(x, array_t<int>(4, 3, 3, 2, 1));
	heap_push(x, 6);
	EXPECT_EQ(x, array_t<int>(5, 6, 3, 2, 1, 3));
	heap_push(x, 3);
	EXPECT_EQ(x, array_t<int>(6, 6, 3, 3, 1, 3, 2));
	heap_push(x, 7);
	EXPECT_EQ(x, array_t<int>(7, 7, 3, 6, 1, 3, 2, 3));
}


