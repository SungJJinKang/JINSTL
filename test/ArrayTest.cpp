#include "test.h"

#include "../Array.h"

TEST(ArrayTest, Push) {
	dooms::stl::Array<int> testArray;
	testArray.Push_Back(5);
	testArray.Push_Back(2);
	EXPECT_EQ(testArray.Count(), 2);
}
