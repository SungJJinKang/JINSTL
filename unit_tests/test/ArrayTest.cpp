#include "test.h"

#include <Array.h>

TEST(ArrayTest, PushBackAndCount)
{
	jinStl::Array<int> testArray{};
	testArray.Push_Back(1);
	testArray.Push_Back(2);
	testArray.Push_Back(3);
	EXPECT_EQ(testArray.Count(), 3);
}

TEST(ArrayTest, PushBackAndValue)
{
	jinStl::Array<int> testArray{};
	testArray.Push_Back(1);
	testArray.Push_Back(2);
	testArray.Push_Back(3);
	EXPECT_EQ(testArray[0], 1);
	EXPECT_EQ(testArray[1], 2);
	EXPECT_EQ(testArray[2], 3);
}

TEST(ArrayTest, ClearAndCapacity)
{
	jinStl::Array<int> testArray{};
	testArray.Push_Back(1);
	testArray.Push_Back(2);
	testArray.Push_Back(3);
	testArray.Push_Back(4);
	testArray.Push_Back(5);
	testArray.Push_Back(6);
	auto currentCapacity = testArray.Capacity();

	testArray.Clear();

	EXPECT_EQ(testArray.Capacity(), currentCapacity);
	EXPECT_EQ(testArray.Count(), 0);
}

TEST(ArrayTest, Resize1)
{
	jinStl::Array<int> testArray{};
	testArray.Push_Back(1);
	testArray.Push_Back(2);
	testArray.Push_Back(3);
	testArray.Push_Back(4);
	testArray.Push_Back(5);
	testArray.Push_Back(6);

	testArray.ResizeCount(2);

	EXPECT_EQ(testArray.Capacity(), 2);
	EXPECT_EQ(testArray.Count(), 2);
	EXPECT_EQ(testArray[0], 1);
	EXPECT_EQ(testArray[1], 2);
}

TEST(ArrayTest, Resize2)
{
	jinStl::Array<int> testArray{};
	testArray.Push_Back(1);
	testArray.Push_Back(2);

	testArray.ResizeCount(4);

	EXPECT_EQ(testArray.Capacity(), 4);
	EXPECT_EQ(testArray.Count(), 4);
	EXPECT_EQ(testArray[0], 1);
	EXPECT_EQ(testArray[1], 2);
}

TEST(ArrayTest, Resize3)
{
	jinStl::Array<int> testArray{};
	testArray.ResizeCount(4);

	EXPECT_EQ(testArray.Capacity(), 4);
	EXPECT_EQ(testArray.Count(), 4);
	EXPECT_EQ(testArray[0], 0);
	EXPECT_EQ(testArray[1], 0);
	EXPECT_EQ(testArray[2], 0);
	EXPECT_EQ(testArray[3], 0);
}