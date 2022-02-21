#include "test.h"

#include <Array.h>

TEST(ArrayTest, CopyConstruct)
{
	jinStl::Array<int> testArray1{};
	testArray1.PushBack(1);
	testArray1.PushBack(2);
	testArray1.PushBack(3);

	jinStl::Array<int> testArray2{ testArray1 };
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
	testArray1.~Array();
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
	jinStl::Array<int> testArray1{};
	testArray1.PushBack(1);
	testArray1.PushBack(2);
	testArray1.PushBack(3);

	const size_t originalCapacity = testArray1.Capacity();
	const size_t originalCount = testArray1.Count();

	jinStl::Array<int> testArray2{ std::move(testArray1) };
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
	jinStl::Array<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);
	EXPECT_EQ(testArray.Count(), 3);
}

TEST(ArrayTest, PushBackAndValue)
{
	jinStl::Array<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);
	EXPECT_EQ(testArray[0], 1);
	EXPECT_EQ(testArray[1], 2);
	EXPECT_EQ(testArray[2], 3);
}

TEST(ArrayTest, PopBackAndCount)
{
	jinStl::Array<int> testArray{};
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

	testArray.PopBack();
	testArray.PopBack();
	testArray.PopBack();
	testArray.PopBack();
}

TEST(ArrayTest, PopBackAndValue)
{
	jinStl::Array<int> testArray{};
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

	testArray.PopBack();
	testArray.PopBack();
	testArray.PopBack();
	testArray.PopBack();
}

TEST(ArrayTest, ClearAndCapacity)
{
	jinStl::Array<int> testArray{};
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

TEST(ArrayTest, Resize1)
{
	jinStl::Array<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	testArray.PushBack(3);
	testArray.PushBack(4);
	testArray.PushBack(5);
	testArray.PushBack(6);

	testArray.ResizeCount(2);

	EXPECT_EQ(testArray.Capacity(), 2);
	EXPECT_EQ(testArray.Count(), 2);
	EXPECT_EQ(testArray[0], 1);
	EXPECT_EQ(testArray[1], 2);
}

TEST(ArrayTest, Resize2)
{
	jinStl::Array<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);

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


TEST(ArrayTest, Resize4)
{
	jinStl::Array<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);

	testArray.ResizeCount(0);

	EXPECT_EQ(testArray.Capacity(), 0);
	EXPECT_EQ(testArray.Count(), 0);
}

TEST(ArrayTest, Reserve1)
{
	jinStl::Array<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);

	testArray.Reserve(5);
	
	EXPECT_EQ(testArray.Capacity(), 5);
	EXPECT_EQ(testArray.Count(), 2);
}

TEST(ArrayTest, Reserve2)
{
	jinStl::Array<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);

	const size_t originalCapacity = testArray.Capacity();
	const size_t originalCount = testArray.Count();

	testArray.Reserve(0);

	EXPECT_EQ(testArray.Capacity(), originalCapacity);
	EXPECT_EQ(testArray.Count(), originalCount);
}


TEST(ArrayTest, Reserve3)
{
	jinStl::Array<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);

	const size_t originalCapacity = testArray.Capacity();
	const size_t originalCount = testArray.Count();

	testArray.Reserve(originalCapacity);

	EXPECT_EQ(testArray.Capacity(), originalCapacity);
	EXPECT_EQ(testArray.Count(), originalCount);
}

TEST(ArrayTest, RawPointer)
{
	jinStl::Array<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);
	
	EXPECT_EQ(*testArray.RawPointer(), 1);
	EXPECT_EQ(*(testArray.RawPointer() + 1), 2);
}

TEST(ArrayTest, Destory)
{
	jinStl::Array<int> testArray{};
	testArray.PushBack(1);
	testArray.PushBack(2);

	testArray.~Array();

	EXPECT_EQ(testArray.RawPointer(), nullptr);
	EXPECT_EQ(testArray.Capacity(), 0);
	EXPECT_EQ(testArray.Count(), 0);
}

TEST(ArrayTest, Empty)
{
	jinStl::Array<int> testArray{};
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
		jinStl::Array<A> testArray{};
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
		jinStl::Array<A> testArray{};
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
		jinStl::Array<A> testArray{};
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
		jinStl::Array<B> testArray{};
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
		jinStl::Array<B> testArray{};
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

		testArray.ResizeCount(0);
		EXPECT_EQ(ConstructTime, 7);
		EXPECT_EQ(DestructTime, 7);
	}

}

