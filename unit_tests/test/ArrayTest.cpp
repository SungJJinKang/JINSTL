#include "test.h"

#include <jinstl/TArray.h>

TEST(ArrayTest, CopyConstruct)
{
	jinstl::TArray<int> testArray1{};
	testArray1.PushBack(1);
	testArray1.PushBack(2);
	testArray1.PushBack(3);

	jinstl::TArray<int> testArray2{ testArray1 };
	EXPECT_EQ(testArray1[0], 1);
	EXPECT_EQ(testArray1[1], 2);
	EXPECT_EQ(testArray1[2], 3);
	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
	EXPECT_EQ(testArray1.Count(), testArray2.Count());
	EXPECT_EQ(testArray2.Capacity(), testArray1.Count());

	const size_t originalCount = testArray2.Count();
	const size_t originalCapacity = testArray2.Capacity();

	testArray1[0] = 10;
	testArray1[1] = 1;
	testArray1[2] = 3;
	testArray1.~TArray();
	EXPECT_EQ(testArray1.Count(), 0);
	EXPECT_EQ(testArray1.Capacity(), 0);
	EXPECT_EQ(testArray1.Empty(), true);
	EXPECT_EQ(testArray2.Count(), originalCount);
	EXPECT_EQ(testArray2.Capacity(), originalCapacity);
	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
}

TEST(ArrayTest, MoveConstruct)
{
	jinstl::TArray<int> testArray1{};
	testArray1.PushBack(1);
	testArray1.PushBack(2);
	testArray1.PushBack(3);

	const size_t originalCapacity = testArray1.Capacity();
	const size_t originalCount = testArray1.Count();

	jinstl::TArray<int> testArray2{ std::move(testArray1) };
	EXPECT_EQ(testArray1.Capacity(), 0);
	EXPECT_EQ(testArray1.Count(), 0);
	EXPECT_EQ(testArray1.Empty(), true);

	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
	EXPECT_EQ(testArray2.Capacity(), originalCapacity);
	EXPECT_EQ(testArray2.Count(), originalCount);
}


TEST(ArrayTest, CopyAssignment1)
{
	jinstl::TArray<int> testArray1{};
	testArray1.PushBack(1);
	testArray1.PushBack(2);
	testArray1.PushBack(3);

	jinstl::TArray<int> testArray2{};
	testArray2 = testArray1;
	EXPECT_EQ(testArray1[0], 1);
	EXPECT_EQ(testArray1[1], 2);
	EXPECT_EQ(testArray1[2], 3);
	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
	EXPECT_EQ(testArray1.Count(), testArray2.Count());
	EXPECT_EQ(testArray2.Capacity(), testArray1.Count());

	const size_t originalCount = testArray2.Count();
	const size_t originalCapacity = testArray2.Capacity();

	testArray1[0] = 10;
	testArray1[1] = 1;
	testArray1[2] = 3;
	testArray1.~TArray();
	EXPECT_EQ(testArray1.Count(), 0);
	EXPECT_EQ(testArray1.Capacity(), 0);
	EXPECT_EQ(testArray1.Empty(), true);
	EXPECT_EQ(testArray2.Count(), originalCount);
	EXPECT_EQ(testArray2.Capacity(), originalCapacity);
	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
}

TEST(ArrayTest, CopyAssignment2)
{
	jinstl::TArray<int> testArray1{};
	testArray1.PushBack(1);
	testArray1.PushBack(2);
	testArray1.PushBack(3);

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(4);
	testArray2.PushBack(5);
	testArray2.PushBack(6);
	testArray2.PushBack(7);
	testArray2.PushBack(8);
	testArray2.PushBack(9);

	testArray2 = testArray1;
	EXPECT_EQ(testArray1[0], 1);
	EXPECT_EQ(testArray1[1], 2);
	EXPECT_EQ(testArray1[2], 3);
	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
	EXPECT_EQ(testArray1.Count(), testArray2.Count());

	const size_t originalCount = testArray2.Count();
	const size_t originalCapacity = testArray2.Capacity();

	testArray1[0] = 10;
	testArray1[1] = 1;
	testArray1[2] = 3;
	testArray1.~TArray();
	EXPECT_EQ(testArray1.Count(), 0);
	EXPECT_EQ(testArray1.Capacity(), 0);
	EXPECT_EQ(testArray1.Empty(), true);
	EXPECT_EQ(testArray2.Count(), originalCount);
	EXPECT_EQ(testArray2.Capacity(), originalCapacity);
	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
}

TEST(ArrayTest, MoveAssignment1)
{
	jinstl::TArray<int> testArray1{};
	testArray1.PushBack(1);
	testArray1.PushBack(2);
	testArray1.PushBack(3);

	const size_t originalCapacity = testArray1.Capacity();
	const size_t originalCount = testArray1.Count();

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(4);
	testArray2.PushBack(5);
	testArray2.PushBack(6);
	testArray2.PushBack(7);
	testArray2.PushBack(8);
	testArray2.PushBack(9);

	testArray2 = std::move(testArray1);
	EXPECT_EQ(testArray1.Capacity(), 0);
	EXPECT_EQ(testArray1.Count(), 0);
	EXPECT_EQ(testArray1.Empty(), true);

	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
	EXPECT_EQ(testArray2.Capacity(), originalCapacity);
	EXPECT_EQ(testArray2.Count(), originalCount);
}

TEST(ArrayTest, MoveAssignment2)
{
	jinstl::TArray<int> testArray1{};
	testArray1.PushBack(1);
	testArray1.PushBack(2);
	testArray1.PushBack(3);

	const size_t originalCapacity = testArray1.Capacity();
	const size_t originalCount = testArray1.Count();

	jinstl::TArray<int> testArray2{};
	testArray2 = std::move(testArray1);
	EXPECT_EQ(testArray1.Capacity(), 0);
	EXPECT_EQ(testArray1.Count(), 0);
	EXPECT_EQ(testArray1.Empty(), true);

	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
	EXPECT_EQ(testArray2.Capacity(), originalCapacity);
	EXPECT_EQ(testArray2.Count(), originalCount);
}

TEST(ArrayTest, PushBackAndCount)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);
	EXPECT_EQ(testArray.Count(), 3);
}

TEST(ArrayTest, PushBackAndValue)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);
	EXPECT_EQ(testArray[0], 1);
	EXPECT_EQ(testArray[1], 2);
	EXPECT_EQ(testArray[2], 3);
}

TEST(ArrayTest, PopBackAndCount)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);

	const size_t originalCapacity = testArray.Capacity();

	testArray.PopBack();

	EXPECT_EQ(testArray.Count(), 2);
	EXPECT_EQ(testArray.Capacity(), originalCapacity);

	testArray.PopBack();

	EXPECT_EQ(testArray.Count(), 1);
	EXPECT_EQ(testArray.Capacity(), originalCapacity);

	testArray.PopBack();

	EXPECT_EQ(testArray.Count(), 0);
	EXPECT_EQ(testArray.Capacity(), originalCapacity);
}

TEST(ArrayTest, PopBackAndValue)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);

	const size_t originalCapacity = testArray.Capacity();

	testArray.PopBack();

	EXPECT_EQ(testArray.Count(), 2);
	EXPECT_EQ(testArray.Capacity(), originalCapacity);
	EXPECT_EQ(testArray[0], 1);
	EXPECT_EQ(testArray[1], 2);

	testArray.PopBack();

	EXPECT_EQ(testArray.Count(), 1);
	EXPECT_EQ(testArray.Capacity(), originalCapacity);
	EXPECT_EQ(testArray[0], 1);

	testArray.PopBack();

	EXPECT_EQ(testArray.Count(), 0);
	EXPECT_EQ(testArray.Capacity(), originalCapacity);
}

TEST(ArrayTest, Insert1)
{
	jinstl::TArray<int> testArray{};

	testArray.Insert(0, 5);
	
	EXPECT_EQ(testArray[0], 5);
	EXPECT_EQ(testArray.Count(), 1);
}

TEST(ArrayTest, Insert2)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(5);
	testArray.PushBack(3);

	testArray.Insert(0, 1);

	EXPECT_EQ(testArray[0], 1);
	EXPECT_EQ(testArray[1], 5);
	EXPECT_EQ(testArray[2], 3);
	EXPECT_EQ(testArray.Count(), 3);
}

TEST(ArrayTest, Insert3)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(5);
	testArray.PushBack(3);

	testArray.Insert(1, 1);

	EXPECT_EQ(testArray[0], 5);
	EXPECT_EQ(testArray[1], 1);
	EXPECT_EQ(testArray[2], 3);
	EXPECT_EQ(testArray.Count(), 3);
}

TEST(ArrayTest, Insert4)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(5);
	testArray.PushBack(3);

	testArray.Insert(2, 1);

	EXPECT_EQ(testArray[0], 5);
	EXPECT_EQ(testArray[1], 3);
	EXPECT_EQ(testArray[2], 1);
	EXPECT_EQ(testArray.Count(), 3);
}

TEST(ArrayTest, Insert5)
{
	jinstl::TArray<int> testArray{};
	testArray.ReserveCapacity(100);

	testArray.Insert(0, 5);

	EXPECT_EQ(testArray[0], 5);
	EXPECT_EQ(testArray.Count(), 1);
}

TEST(ArrayTest, Insert6)
{
	jinstl::TArray<int> testArray{};
	testArray.ReserveCapacity(100);
	testArray.PushBack(5);
	testArray.PushBack(3);
	EXPECT_EQ(testArray[0], 5);
	EXPECT_EQ(testArray[1], 3);

	testArray.Insert(0, 1);

	EXPECT_EQ(testArray[0], 1);
	EXPECT_EQ(testArray[1], 5);
	EXPECT_EQ(testArray[2], 3);
	EXPECT_EQ(testArray.Count(), 3);
}

TEST(ArrayTest, Insert7)
{
	jinstl::TArray<int> testArray{};
	testArray.ReserveCapacity(100);
	testArray.PushBack(5);
	testArray.PushBack(3);

	testArray.Insert(1, 1);

	EXPECT_EQ(testArray[0], 5);
	EXPECT_EQ(testArray[1], 1);
	EXPECT_EQ(testArray[2], 3);
	EXPECT_EQ(testArray.Count(), 3);
}

TEST(ArrayTest, Insert8)
{
	jinstl::TArray<int> testArray{};
	testArray.ReserveCapacity(100);
	testArray.PushBack(5);
	testArray.PushBack(3);

	testArray.Insert(2, 1);

	EXPECT_EQ(testArray[0], 5);
	EXPECT_EQ(testArray[1], 3);
	EXPECT_EQ(testArray[2], 1);
	EXPECT_EQ(testArray.Count(), 3);
}

TEST(ArrayTest, CopyInsertArray1)
{
	jinstl::TArray<int> testArray1{};
	testArray1.PushBack(5);
	testArray1.PushBack(4);

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(1);
	testArray2.PushBack(2);
	testArray2.PushBack(3);

	testArray1.Insert(0, testArray2);

	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
	EXPECT_EQ(testArray2.Count(), 3);

	EXPECT_EQ(testArray1[0], 1);
	EXPECT_EQ(testArray1[1], 2);
	EXPECT_EQ(testArray1[2], 3);
	EXPECT_EQ(testArray1[3], 5);
	EXPECT_EQ(testArray1[4], 4);
	EXPECT_EQ(testArray1.Count(), 5);
}

TEST(ArrayTest, CopyInsertArray2)
{
	jinstl::TArray<int> testArray1{};
	testArray1.PushBack(5);
	testArray1.PushBack(4);

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(1);
	testArray2.PushBack(2);
	testArray2.PushBack(3);

	testArray1.Insert(1, testArray2);

	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
	EXPECT_EQ(testArray2.Count(), 3);

	EXPECT_EQ(testArray1[0], 5);
	EXPECT_EQ(testArray1[1], 1);
	EXPECT_EQ(testArray1[2], 2);
	EXPECT_EQ(testArray1[3], 3);
	EXPECT_EQ(testArray1[4], 4);
	EXPECT_EQ(testArray1.Count(), 5);
}

TEST(ArrayTest, CopyInsertArray3)
{
	jinstl::TArray<int> testArray1{};
	testArray1.PushBack(5);
	testArray1.PushBack(4);

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(1);
	testArray2.PushBack(2);
	testArray2.PushBack(3);

	testArray1.Insert(2, testArray2);

	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
	EXPECT_EQ(testArray2.Count(), 3);

	EXPECT_EQ(testArray1[0], 5);
	EXPECT_EQ(testArray1[1], 4);
	EXPECT_EQ(testArray1[2], 1);
	EXPECT_EQ(testArray1[3], 2);
	EXPECT_EQ(testArray1[4], 3);
	EXPECT_EQ(testArray1.Count(), 5);
}


TEST(ArrayTest, CopyInsertArray4)
{
	jinstl::TArray<int> testArray1{};
	testArray1.ReserveCapacity(100);
	testArray1.PushBack(5);
	testArray1.PushBack(4);

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(1);
	testArray2.PushBack(2);
	testArray2.PushBack(3);

	testArray1.Insert(0, testArray2);

	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
	EXPECT_EQ(testArray2.Count(), 3);

	EXPECT_EQ(testArray1[0], 1);
	EXPECT_EQ(testArray1[1], 2);
	EXPECT_EQ(testArray1[2], 3);
	EXPECT_EQ(testArray1[3], 5);
	EXPECT_EQ(testArray1[4], 4);
	EXPECT_EQ(testArray1.Count(), 5);
}

TEST(ArrayTest, CopyInsertArray5)
{
	jinstl::TArray<int> testArray1{};
	testArray1.ReserveCapacity(100);
	testArray1.PushBack(5);
	testArray1.PushBack(4);

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(1);
	testArray2.PushBack(2);
	testArray2.PushBack(3);

	testArray1.Insert(1, testArray2);

	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
	EXPECT_EQ(testArray2.Count(), 3);

	EXPECT_EQ(testArray1[0], 5);
	EXPECT_EQ(testArray1[1], 1);
	EXPECT_EQ(testArray1[2], 2);
	EXPECT_EQ(testArray1[3], 3);
	EXPECT_EQ(testArray1[4], 4);
	EXPECT_EQ(testArray1.Count(), 5);
}

TEST(ArrayTest, CopyInsertArray6)
{
	jinstl::TArray<int> testArray1{};
	testArray1.ReserveCapacity(100);
	testArray1.PushBack(5);
	testArray1.PushBack(4);

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(1);
	testArray2.PushBack(2);
	testArray2.PushBack(3);

	testArray1.Insert(2, testArray2);

	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);
	EXPECT_EQ(testArray2.Count(), 3);

	EXPECT_EQ(testArray1[0], 5);
	EXPECT_EQ(testArray1[1], 4);
	EXPECT_EQ(testArray1[2], 1);
	EXPECT_EQ(testArray1[3], 2);
	EXPECT_EQ(testArray1[4], 3);
	EXPECT_EQ(testArray1.Count(), 5);
}

TEST(ArrayTest, MoveInsertArray1)
{
	jinstl::TArray<int> testArray1{};
	testArray1.PushBack(5);
	testArray1.PushBack(4);

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(1);
	testArray2.PushBack(2);
	testArray2.PushBack(3);
	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);

	testArray1.Insert(0, std::move(testArray2));
	
	EXPECT_EQ(testArray2.Count(), 0);
	EXPECT_EQ(testArray2.Capacity(), 0);

	EXPECT_EQ(testArray1[0], 1);
	EXPECT_EQ(testArray1[1], 2);
	EXPECT_EQ(testArray1[2], 3);
	EXPECT_EQ(testArray1[3], 5);
	EXPECT_EQ(testArray1[4], 4);
	EXPECT_EQ(testArray1.Count(), 5);
}

TEST(ArrayTest, MoveInsertArray2)
{
	jinstl::TArray<int> testArray1{};
	testArray1.PushBack(5);
	testArray1.PushBack(4);

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(1);
	testArray2.PushBack(2);
	testArray2.PushBack(3);

	testArray1.Insert(1, std::move(testArray2));

	EXPECT_EQ(testArray2.Count(), 0);
	EXPECT_EQ(testArray2.Capacity(), 0);

	EXPECT_EQ(testArray1[0], 5);
	EXPECT_EQ(testArray1[1], 1);
	EXPECT_EQ(testArray1[2], 2);
	EXPECT_EQ(testArray1[3], 3);
	EXPECT_EQ(testArray1[4], 4);
	EXPECT_EQ(testArray1.Count(), 5);
}

TEST(ArrayTest, MoveInsertArray3)
{
	jinstl::TArray<int> testArray1{};
	testArray1.PushBack(5);
	testArray1.PushBack(4);

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(1);
	testArray2.PushBack(2);
	testArray2.PushBack(3);

	testArray1.Insert(2, std::move(testArray2));

	EXPECT_EQ(testArray2.Count(), 0);
	EXPECT_EQ(testArray2.Capacity(), 0);

	EXPECT_EQ(testArray1[0], 5);
	EXPECT_EQ(testArray1[1], 4);
	EXPECT_EQ(testArray1[2], 1);
	EXPECT_EQ(testArray1[3], 2);
	EXPECT_EQ(testArray1[4], 3);
	EXPECT_EQ(testArray1.Count(), 5);
}

TEST(ArrayTest, MoveInsertArray4)
{
	jinstl::TArray<int> testArray1{};
	testArray1.ReserveCapacity(100);
	testArray1.PushBack(5);
	testArray1.PushBack(4);

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(1);
	testArray2.PushBack(2);
	testArray2.PushBack(3);
	EXPECT_EQ(testArray2[0], 1);
	EXPECT_EQ(testArray2[1], 2);
	EXPECT_EQ(testArray2[2], 3);

	testArray1.Insert(0, std::move(testArray2));

	EXPECT_EQ(testArray2.Count(), 0);
	EXPECT_EQ(testArray2.Capacity(), 0);

	EXPECT_EQ(testArray1[0], 1);
	EXPECT_EQ(testArray1[1], 2);
	EXPECT_EQ(testArray1[2], 3);
	EXPECT_EQ(testArray1[3], 5);
	EXPECT_EQ(testArray1[4], 4);
	EXPECT_EQ(testArray1.Count(), 5);
}

TEST(ArrayTest, MoveInsertArray5)
{
	jinstl::TArray<int> testArray1{};
	testArray1.ReserveCapacity(100);
	testArray1.PushBack(5);
	testArray1.PushBack(4);

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(1);
	testArray2.PushBack(2);
	testArray2.PushBack(3);

	testArray1.Insert(1, std::move(testArray2));

	EXPECT_EQ(testArray2.Count(), 0);
	EXPECT_EQ(testArray2.Capacity(), 0);

	EXPECT_EQ(testArray1[0], 5);
	EXPECT_EQ(testArray1[1], 1);
	EXPECT_EQ(testArray1[2], 2);
	EXPECT_EQ(testArray1[3], 3);
	EXPECT_EQ(testArray1[4], 4);
	EXPECT_EQ(testArray1.Count(), 5);
}

TEST(ArrayTest, MoveInsertArray6)
{
	jinstl::TArray<int> testArray1{};
	testArray1.ReserveCapacity(100);
	testArray1.PushBack(5);
	testArray1.PushBack(4);

	jinstl::TArray<int> testArray2{};
	testArray2.PushBack(1);
	testArray2.PushBack(2);
	testArray2.PushBack(3);

	testArray1.Insert(2, std::move(testArray2));

	EXPECT_EQ(testArray2.Count(), 0);
	EXPECT_EQ(testArray2.Capacity(), 0);

	EXPECT_EQ(testArray1[0], 5);
	EXPECT_EQ(testArray1[1], 4);
	EXPECT_EQ(testArray1[2], 1);
	EXPECT_EQ(testArray1[3], 2);
	EXPECT_EQ(testArray1[4], 3);
	EXPECT_EQ(testArray1.Count(), 5);
}

TEST(ArrayTest, ClearAndCapacity)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);
	testArray.PushBack(4);
	testArray.PushBack(5);
	testArray.PushBack(6);
	auto currentCapacity = testArray.Capacity();

	testArray.Clear();

	EXPECT_EQ(testArray.Capacity(), currentCapacity);
	EXPECT_EQ(testArray.Count(), 0);
}

TEST(ArrayTest, ClearNoDestructorAndCapacity)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);
	testArray.PushBack(4);
	testArray.PushBack(5);
	testArray.PushBack(6);
	auto currentCapacity = testArray.Capacity();

	testArray.ClearNoDestructor();

	EXPECT_EQ(testArray.Capacity(), currentCapacity);
	EXPECT_EQ(testArray.Count(), 0);
}

TEST(ArrayTest, Remove)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);
	testArray.PushBack(4);
	testArray.PushBack(5);
	testArray.PushBack(6);

	auto currentCapacity = testArray.Capacity();
	
	EXPECT_EQ(testArray.Capacity(), currentCapacity);
	EXPECT_EQ(testArray.Count(), 6);

	testArray.Remove(1);
	EXPECT_EQ(testArray[0], 1);
	EXPECT_EQ(testArray[1], 3);
	EXPECT_EQ(testArray[2], 4);
	EXPECT_EQ(testArray[3], 5);
	EXPECT_EQ(testArray[4], 6);
	EXPECT_EQ(testArray.Capacity(), currentCapacity);
	EXPECT_EQ(testArray.Count(), 5);

	testArray.Remove(4);
	EXPECT_EQ(testArray[0], 1);
	EXPECT_EQ(testArray[1], 3);
	EXPECT_EQ(testArray[2], 4);
	EXPECT_EQ(testArray[3], 5);
	EXPECT_EQ(testArray.Capacity(), currentCapacity);
	EXPECT_EQ(testArray.Count(), 4);

	testArray.Remove(0);
	EXPECT_EQ(testArray[0], 3);
	EXPECT_EQ(testArray[1], 4);
	EXPECT_EQ(testArray[2], 5);
	EXPECT_EQ(testArray.Capacity(), currentCapacity);
	EXPECT_EQ(testArray.Count(), 3);

	testArray.Remove(0);
	EXPECT_EQ(testArray[0], 4);
	EXPECT_EQ(testArray[1], 5);
	EXPECT_EQ(testArray.Capacity(), currentCapacity);
	EXPECT_EQ(testArray.Count(), 2);

	testArray.Remove(1);
	EXPECT_EQ(testArray[0], 4);
	EXPECT_EQ(testArray.Capacity(), currentCapacity);
	EXPECT_EQ(testArray.Count(), 1);

	testArray.Remove(0);
	EXPECT_EQ(testArray.Capacity(), currentCapacity);
	EXPECT_EQ(testArray.Count(), 0);
}

TEST(ArrayTest, Contain)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);
	testArray.PushBack(4);
	testArray.PushBack(5);
	testArray.PushBack(6);

	EXPECT_EQ(testArray.Contain(1), true);
	EXPECT_EQ(testArray.Contain(6), true);
	EXPECT_EQ(testArray.Contain(5), true);
	EXPECT_EQ(testArray.Contain(51), false);
	EXPECT_EQ(testArray.Contain(0), false);
}

TEST(ArrayTest, SwapPopBack)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);
	testArray.PushBack(4);
	testArray.PushBack(5);
	testArray.PushBack(6);

	testArray.SwapPopBack(1);
	EXPECT_EQ(testArray[1], 6);

	testArray.SwapPopBack(0);
	EXPECT_EQ(testArray[0], 5);
	EXPECT_EQ(testArray.LastElement(), 4);
}

TEST(ArrayTest, Find)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);
	testArray.PushBack(4);
	testArray.PushBack(5);
	testArray.PushBack(6);
	testArray.EmplaceBack(7);

	EXPECT_EQ(testArray.Find(1), 0);
	EXPECT_EQ(testArray.Find(6), 5);
	EXPECT_EQ(testArray.Find(5), 4);
	EXPECT_EQ(testArray.Find(51), testArray.Count());
	EXPECT_EQ(testArray.Find(0), testArray.Count());
}

TEST(ArrayTest, Resize1)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);
	testArray.PushBack(4);
	testArray.PushBack(5);
	testArray.PushBack(6);

	testArray.ResizeCountWithInitialization(2);

	EXPECT_EQ(testArray.Capacity(), 2);
	EXPECT_EQ(testArray.Count(), 2);
	EXPECT_EQ(testArray[0], 1);
	EXPECT_EQ(testArray[1], 2);
}

TEST(ArrayTest, Resize2)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);

	testArray.ResizeCountWithInitialization(4);

	EXPECT_EQ(testArray.Capacity(), 4);
	EXPECT_EQ(testArray.Count(), 4);
	EXPECT_EQ(testArray[0], 1);
	EXPECT_EQ(testArray[1], 2);
}

TEST(ArrayTest, Resize3)
{
	jinstl::TArray<int> testArray{};
	testArray.ResizeCountWithInitialization(4);

	EXPECT_EQ(testArray.Capacity(), 4);
	EXPECT_EQ(testArray.Count(), 4);
	EXPECT_EQ(testArray[0], 0);
	EXPECT_EQ(testArray[1], 0);
	EXPECT_EQ(testArray[2], 0);
	EXPECT_EQ(testArray[3], 0);
}


TEST(ArrayTest, Resize4)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);

	testArray.ResizeCountWithInitialization(0);

	EXPECT_EQ(testArray.Capacity(), 0);
	EXPECT_EQ(testArray.Count(), 0);
}

TEST(ArrayTest, Resize5)
{
	jinstl::TArray<int> testArray{};

	testArray.ResizeCountWithInitialization(2, 5);

	EXPECT_EQ(testArray[0], 5);
	EXPECT_EQ(testArray[1], 5);
	EXPECT_EQ(testArray.Capacity(), 2);
	EXPECT_EQ(testArray.Count(), 2);
}

namespace resizeTest6
{
	struct A
	{
		int _a;
		A(int a) : _a(a){}
	};

	TEST(ArrayTest, Resize6)
	{
		jinstl::TArray<A> testArray{};
		testArray.ResizeCountWithInitialization(2, 3);

		EXPECT_EQ(testArray[0]._a, 3);
		EXPECT_EQ(testArray[1]._a, 3);
		EXPECT_EQ(testArray.Capacity(), 2);
		EXPECT_EQ(testArray.Count(), 2);
	}
}

TEST(ArrayTest, Reserve1)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);

	testArray.ReserveCapacity(5);
	
	EXPECT_EQ(testArray.Capacity(), 5);
	EXPECT_EQ(testArray.Count(), 2);
}

TEST(ArrayTest, Reserve2)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);

	const size_t originalCapacity = testArray.Capacity();
	const size_t originalCount = testArray.Count();

	testArray.ReserveCapacity(0);

	EXPECT_EQ(testArray.Capacity(), originalCapacity);
	EXPECT_EQ(testArray.Count(), originalCount);
}


TEST(ArrayTest, Reserve3)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);

	const size_t originalCapacity = testArray.Capacity();
	const size_t originalCount = testArray.Count();

	testArray.ReserveCapacity(originalCapacity);

	EXPECT_EQ(testArray.Capacity(), originalCapacity);
	EXPECT_EQ(testArray.Count(), originalCount);
}

TEST(ArrayTest, RawPointer)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	
	EXPECT_EQ(*testArray.RawPointer(), 1);
	EXPECT_EQ(*(testArray.RawPointer() + 1), 2);
}

TEST(ArrayTest, Destory)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);

	testArray.~TArray();

	EXPECT_EQ(testArray.RawPointer(), nullptr);
	EXPECT_EQ(testArray.Capacity(), 0);
	EXPECT_EQ(testArray.Count(), 0);
}

TEST(ArrayTest, Empty)
{
	jinstl::TArray<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	
	EXPECT_EQ(testArray.Empty(), false);
	testArray.PopBack();
	EXPECT_EQ(testArray.Empty(), false);
	testArray.PopBack();
	EXPECT_EQ(testArray.Empty(), true);
}

namespace
{
	struct A
	{
		int value;

		A()
		: value(0)
		{
			
		}

		A(int a)
		: value(a)
		{

		}
	};

	TEST(ArrayTest, EmplaceBack)
	{
		jinstl::TArray<A> testArray{};
		testArray.EmplaceBack(2);
		testArray.EmplaceBack(1);
		testArray.EmplaceBack(0);

		EXPECT_EQ(testArray[0].value, 2);
		EXPECT_EQ(testArray[1].value, 1);
		EXPECT_EQ(testArray[2].value, 0);
		EXPECT_EQ(testArray.Count(), 3);

		testArray.PopBack();
		testArray.PopBack();
		testArray.PopBack();
		EXPECT_EQ(testArray.Count(), 0);
	}

	TEST(ArrayTest, LastElement)
	{
		jinstl::TArray<A> testArray{};
		testArray.EmplaceBack(2);
		testArray.EmplaceBack(1);
		testArray.EmplaceBack(0);

		EXPECT_EQ(testArray.LastElement().value, 0);
		testArray.PopBack();
		EXPECT_EQ(testArray.LastElement().value, 1);
		testArray.PopBack();
		EXPECT_EQ(testArray.LastElement().value, 2);
	}
	
	TEST(ArrayTest, FirstElement)
	{
		jinstl::TArray<A> testArray{};
		testArray.EmplaceBack(2);
		testArray.EmplaceBack(1);
		testArray.EmplaceBack(0);

		EXPECT_EQ(testArray.FirstElement().value, 2);
		testArray.PopBack();
		EXPECT_EQ(testArray.FirstElement().value, 2);
		testArray.PopBack();
		EXPECT_EQ(testArray.FirstElement().value, 2);
	}

}

namespace test1
{
	inline extern int ConstructTime = 0;
	inline extern int DestructTime = 0;
	
	struct B
	{

		int value;

		B() = delete;
		B(int a)
			: value(a)
		{
			ConstructTime++;
		}

		~B()
		{
			DestructTime++;
		}
	};

	TEST(ArrayTest, ConstructDestructCount1)
	{
		jinstl::TArray<B> testArray{};
		testArray.EmplaceBack(2);
		EXPECT_EQ(ConstructTime, 1);
		testArray.EmplaceBack(1);
		EXPECT_EQ(ConstructTime, 2);
		testArray.EmplaceBack(0);
		EXPECT_EQ(ConstructTime, 3);
		testArray.EmplaceBack(0);
		EXPECT_EQ(ConstructTime, 4);
		testArray.EmplaceBack(0);
		EXPECT_EQ(ConstructTime, 5);

		testArray.PopBack();
		EXPECT_EQ(ConstructTime, 5);
		EXPECT_EQ(DestructTime, 1);
		testArray.PopBack();
		EXPECT_EQ(ConstructTime, 5);
		EXPECT_EQ(DestructTime, 2);
		testArray.PopBack();
		EXPECT_EQ(ConstructTime, 5);
		EXPECT_EQ(DestructTime, 3);
		testArray.PopBack();
		EXPECT_EQ(ConstructTime, 5);
		EXPECT_EQ(DestructTime, 4);
		testArray.PopBack();
		EXPECT_EQ(ConstructTime, 5);
		EXPECT_EQ(DestructTime, 5);
	}

}


namespace test2
{
	inline extern int ConstructTime = 0;
	inline extern int DestructTime = 0;

	struct B
	{

		int value;
		
		B()
		{
			ConstructTime++;
		}

		B(int a)
			: value(a)
		{
			ConstructTime++;
		}

		~B()
		{
			DestructTime++;
		}
	};

	TEST(ArrayTest, ConstructDestructCount2)
	{
		jinstl::TArray<B> testArray{};
		testArray.EmplaceBack(2);
		EXPECT_EQ(ConstructTime, 1);
		testArray.EmplaceBack(1);
		EXPECT_EQ(ConstructTime, 2);
		testArray.EmplaceBack(0);
		EXPECT_EQ(ConstructTime, 3);
		testArray.EmplaceBack(0);
		EXPECT_EQ(ConstructTime, 4);
		testArray.EmplaceBack(0);
		EXPECT_EQ(ConstructTime, 5);
		testArray.EmplaceBack(0);
		EXPECT_EQ(ConstructTime, 6);
		testArray.EmplaceBack(0);
		EXPECT_EQ(ConstructTime, 7);

		testArray.ResizeCountWithInitialization(0);
		EXPECT_EQ(ConstructTime, 7);
		EXPECT_EQ(DestructTime, 7);
	}

}

namespace test3
{
	inline extern int ConstructTime = 0;
	inline extern int DestructTime = 0;

	struct B
	{

		int value;

		B()
		{
			ConstructTime++;
		}

		B(int a)
			: value(a)
		{
			ConstructTime++;
		}

		~B()
		{
			DestructTime++;
		}
	};

	TEST(ArrayTest, ConstructDestructCount3)
	{
		jinstl::TArray<B> testArray{};
		testArray.EmplaceBack(2);
		testArray.EmplaceBack(1);
		testArray.EmplaceBack(0);
		testArray.EmplaceBack(0);
		testArray.EmplaceBack(0);
		testArray.EmplaceBack(0);
		testArray.EmplaceBack(0);

		testArray.ResizeCountWithInitialization(2);
		EXPECT_EQ(ConstructTime, 7);
		EXPECT_EQ(DestructTime, 5);
	}

}

namespace test4
{
	inline extern int ConstructTime = 0;
	inline extern int DestructTime = 0;

	struct B
	{

		int value;

		B()
		{
			ConstructTime++;
		}

		B(int a)
			: value(a)
		{
			ConstructTime++;
		}

		~B()
		{
			DestructTime++;
		}
	};

	TEST(ArrayTest, ConstructDestructCount4)
	{
		jinstl::TArray<B> testArray{};
		testArray.EmplaceBack(2);
		testArray.EmplaceBack(1);
		testArray.EmplaceBack(0);
		testArray.EmplaceBack(0);
		testArray.EmplaceBack(0);
		testArray.EmplaceBack(0);
		testArray.EmplaceBack(0);

		testArray.Clear();
		EXPECT_EQ(ConstructTime, 7);
		EXPECT_EQ(DestructTime, 7);
	}

}


namespace test5
{
	inline extern int ConstructTime = 0;
	inline extern int DestructTime = 0;

	struct B
	{

		int value;
		
		B(int a)
			: value(a)
		{
			ConstructTime++;
		}

		B(const B& b)
			: value(b.value)
		{
			ConstructTime++;
		}
		B(B&& b) noexcept
			: value(b.value)
		{
			
		}
		
		~B()
		{
			DestructTime++;
		}
	};

	TEST(ArrayTest, ConstructDestructCount5)
	{
		jinstl::TArray<B> testArray1{};
		testArray1.EmplaceBack(2);
		testArray1.EmplaceBack(1);
		testArray1.EmplaceBack(0);

		EXPECT_EQ(ConstructTime, 3);

		jinstl::TArray<B> testArray2{ testArray1 };

		//EXPECT_EQ(ConstructTime, 6);
	}

}


namespace test6
{
	inline extern int ConstructTime = 0;
	inline extern int DestructTime = 0;

	struct B
	{

		int value;

		B(int a)
			: value(a)
		{
			ConstructTime++;
		}

		B(const B& b)
			: value(b.value)
		{
			ConstructTime++;
		}
		B(B&& b) noexcept
			: value(b.value)
		{

		}

		~B()
		{
			DestructTime++;
		}
	};

	TEST(ArrayTest, ConstructDestructCount6)
	{
		jinstl::TArray<B> testArray1{};
		testArray1.EmplaceBack(2);
		testArray1.EmplaceBack(1);
		testArray1.EmplaceBack(0);

		EXPECT_EQ(ConstructTime, 3);
		EXPECT_EQ(DestructTime, 0);

		jinstl::TArray<B> testArray2{ std::move(testArray1) };

		EXPECT_EQ(ConstructTime, 3);
		EXPECT_EQ(DestructTime, 0);
	}

}