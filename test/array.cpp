#include <gtest/gtest.h>

#include <core/array.h>
#include <core/ascii_stream.h>

using namespace core;

TEST(arraytest, constructor_unit)
{
	array<int> arr;
	EXPECT_EQ(0, arr.count);
	EXPECT_EQ(0, arr.capacity);
	EXPECT_EQ(NULL, arr.data);

	arr.push_back(1);
	arr.push_back(9);
	arr.push_back(7);
	arr.push_back(2);
	arr.push_back(5);

	array<int> arr1(arr);
	EXPECT_EQ(arr, arr1);

	array<int> arr2(20, 10);
	EXPECT_EQ(20, arr2.count);
	for (int i = 0; i < arr2.size(); i++)
		EXPECT_EQ(10, arr2[i]);
}

TEST(arraytest, sub_unit)
{
	array<int> arr;
	arr.push_back(5);
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(5);
	arr.push_back(6);
	arr.push_back(2);
	arr.push_back(1);
	arr.push_back(7);

	array<int> arr1;
	arr1.push_back(3);
	arr1.push_back(5);
	arr1.push_back(6);
	arr1.push_back(2);

	EXPECT_EQ(arr1, arr.sub(2, 5));
	EXPECT_EQ(arr1, arr.subcpy(2, 5));
	EXPECT_EQ(arr1, arr.sub(2, -3));
	EXPECT_EQ(arr1, arr.subcpy(2, -3));
	
	EXPECT_EQ(arr1, arr.sub(arr.at(2), arr.at(5)));
	EXPECT_EQ(arr1, arr.subcpy(arr.at(2), arr.at(5)));
}

TEST(arraytest, push_back_unit)
{
	array<int> arr;
	EXPECT_EQ(0, arr.count);
	EXPECT_EQ(0, arr.capacity);
	for (int i = 1; i < 11; i++)
	{
		arr.push_back(i);
		EXPECT_EQ(i, arr.count);
		EXPECT_GT(arr.capacity+1, arr.count);
	}

	arr.push_back(20, 20);
	EXPECT_EQ(30, arr.count);
	EXPECT_GT(arr.capacity+1, arr.count);

	arr.reserve(40);
	EXPECT_GT(arr.capacity+1, 40);
	arr.push_back_unsafe(8);
	EXPECT_EQ(31, arr.count);
	EXPECT_EQ(8, arr[30]);

	arr.push_back_unsafe(4, 2);
	EXPECT_EQ(35, arr.count);
	EXPECT_EQ(2, arr[34]);
}

TEST(arraytest, push_front_unit)
{
	array<int> arr;
	EXPECT_EQ(0, arr.count);
	EXPECT_EQ(0, arr.capacity);
	for (int i = 1; i < 11; i++)
	{
		arr.push_front(i);
		EXPECT_EQ(i, arr.count);
		EXPECT_GT(arr.capacity+1, arr.count);
	}

	// arr should now be
	// { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }
	EXPECT_EQ(10, arr[0]);
	EXPECT_EQ(8, arr[2]);
	EXPECT_EQ(3, arr[7]);
	EXPECT_EQ(1, arr[9]);

	arr.push_front(20, 10);
	EXPECT_EQ(30, arr.count);
	
	for (int i = 0; i < 20; i++)
		EXPECT_EQ(10, arr[i]);		
}
