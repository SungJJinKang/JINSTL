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