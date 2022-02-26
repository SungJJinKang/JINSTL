#include "test.h"

#include <jinstl/TString.h>

TEST(WideStringTest, StringConstruct1)
{
	jinstl::WideString str{ L"abcd" };

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str.Length(), 4);
	//jinstl::WideString str{};
}

TEST(WideStringTest, StringConstruct2)
{
	const wchar_t* const testString = L"abcdef";
	jinstl::WideString str{ testString, testString + 2 };

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str.Length(), 2);
	//jinstl::WideString str{};
}

TEST(WideStringTest, StringConstruct3)
{
	jinstl::WideString str{ L"" };
	
	EXPECT_EQ(str.Length(), 0);
	//jinstl::WideString str{};
}

TEST(WideStringTest, StringConstruct4)
{
	jinstl::WideString str{ };

	EXPECT_EQ(str.Length(), 0);
	//jinstl::WideString str{};
}

TEST(WideStringTest, CopyConstruct1)
{
	jinstl::WideString str1{ L"abcdefg" };
	jinstl::WideString str2{ str1 };

	EXPECT_EQ(str1.Length(), 7);

	EXPECT_EQ(str2[0], L'a');
	EXPECT_EQ(str2[1], L'b');
	EXPECT_EQ(str2[2], L'c');
	EXPECT_EQ(str2[3], L'd');
	EXPECT_EQ(str2[4], L'e');
	EXPECT_EQ(str2[5], L'f');
	EXPECT_EQ(str2[6], L'g');
	EXPECT_EQ(str2.Length(), 7);
	//jinstl::WideString str{};
}

TEST(WideStringTest, CopyConstruct2)
{
	jinstl::WideString str1{ };
	jinstl::WideString str2{ str1 };

	EXPECT_EQ(str1.Length(), 0);
	EXPECT_EQ(str2.Length(), 0);
	//jinstl::WideString str{};
}

TEST(WideStringTest, MoveConstruct)
{
	jinstl::WideString str1{ L"abcdefg" };
	jinstl::WideString str2{ std::move(str1) };

	EXPECT_EQ(str1.Length(), 0);

	EXPECT_EQ(str2[0], L'a');
	EXPECT_EQ(str2[1], L'b');
	EXPECT_EQ(str2[2], L'c');
	EXPECT_EQ(str2[3], L'd');
	EXPECT_EQ(str2[4], L'e');
	EXPECT_EQ(str2[5], L'f');
	EXPECT_EQ(str2[6], L'g');
	EXPECT_EQ(str2.Length(), 7);
	//jinstl::WideString str{};
}

TEST(WideStringTest, CopyAssignment1)
{
	jinstl::WideString str1{ L"abcdefg" };
	jinstl::WideString str2{ };
	str2 = str1;

	EXPECT_EQ(str1.Length(), 7);

	EXPECT_EQ(str2[0], L'a');
	EXPECT_EQ(str2[1], L'b');
	EXPECT_EQ(str2[2], L'c');
	EXPECT_EQ(str2[3], L'd');
	EXPECT_EQ(str2[4], L'e');
	EXPECT_EQ(str2[5], L'f');
	EXPECT_EQ(str2[6], L'g');
	EXPECT_EQ(str2.Length(), 7);
	//jinstl::WideString str{};
}

TEST(WideStringTest, CopyAssignment2)
{
	jinstl::WideString str1{ L"abcdefg" };
	jinstl::WideString str2{ L"abcdefghijklmn" };
	str2 = str1;

	EXPECT_EQ(str1.Length(), 7);

	EXPECT_EQ(str2[0], L'a');
	EXPECT_EQ(str2[1], L'b');
	EXPECT_EQ(str2[2], L'c');
	EXPECT_EQ(str2[3], L'd');
	EXPECT_EQ(str2[4], L'e');
	EXPECT_EQ(str2[5], L'f');
	EXPECT_EQ(str2[6], L'g');
	EXPECT_EQ(str2.Length(), 7);
	//jinstl::WideString str{};
}

TEST(WideStringTest, MoveAssignment1)
{
	jinstl::WideString str1{ L"abcdefg" };
	jinstl::WideString str2{ };
	str2 = std::move(str1);

	EXPECT_EQ(str1.Length(), 0);
	EXPECT_EQ(str1.Capacity(), 0);

	EXPECT_EQ(str2[0], L'a');
	EXPECT_EQ(str2[1], L'b');
	EXPECT_EQ(str2[2], L'c');
	EXPECT_EQ(str2[3], L'd');
	EXPECT_EQ(str2[4], L'e');
	EXPECT_EQ(str2[5], L'f');
	EXPECT_EQ(str2[6], L'g');
	EXPECT_EQ(str2.Length(), 7);
}

TEST(WideStringTest, MoveAssignment2)
{
	jinstl::WideString str1{ L"abcdefg" };
	jinstl::WideString str2{ L"abcdefghijklmn" };
	str2 = std::move(str1);

	EXPECT_EQ(str1.Length(), 0);
	EXPECT_EQ(str1.Capacity(), 0);

	EXPECT_EQ(str2[0], L'a');
	EXPECT_EQ(str2[1], L'b');
	EXPECT_EQ(str2[2], L'c');
	EXPECT_EQ(str2[3], L'd');
	EXPECT_EQ(str2[4], L'e');
	EXPECT_EQ(str2[5], L'f');
	EXPECT_EQ(str2[6], L'g');
	EXPECT_EQ(str2.Length(), 7);
}

TEST(WideStringTest, Reserve1)
{
	jinstl::WideString str{};
	str.Reserve(11);

	EXPECT_EQ(str.Length(), 0);
	EXPECT_EQ(str.Capacity(), 11);
}

TEST(WideStringTest, Reserve2)
{
	jinstl::WideString str{L"sdfdsf"};
	str.Reserve(11);

	EXPECT_EQ(str.Length(), 6);
	EXPECT_EQ(str.Capacity(), 11);
}


TEST(WideStringTest, Append1)
{
	jinstl::WideString str{ };
	str.Append(L"sdfdsf");

	EXPECT_EQ(str[0], L's');
	EXPECT_EQ(str[1], L'd');
	EXPECT_EQ(str[2], L'f');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L's');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str.Length(), 6);
}

TEST(WideStringTest, Append2)
{
	jinstl::WideString str{L"abc"};
	str.Append(L"sdfdsf");

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L's');
	EXPECT_EQ(str[4], L'd');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str[6], L'd');
	EXPECT_EQ(str[7], L's');
	EXPECT_EQ(str[8], L'f');
	EXPECT_EQ(str.Length(), 9);
}

TEST(WideStringTest, Append3)
{
	jinstl::WideString str{ L"abc" };
	str.Append(L"s");

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L's');
	EXPECT_EQ(str.Length(), 4);
}

TEST(WideStringTest, Append4)
{
	jinstl::WideString str{  };
	jinstl::WideString str1{ L"abc" };
	str.Append(str1);

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str.Length(), 3);
}

TEST(WideStringTest, Append5)
{
	jinstl::WideString str{ L"a"};
	jinstl::WideString str1{ L"bcd" };
	str.Append(str1);

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str.Length(), 4);
}

TEST(WideStringTest, Append6)
{
	jinstl::WideString str{ L"abcdef" };
	jinstl::WideString str1{ L"ghi" };
	str.Append(str1);

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L'e');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str[6], L'g');
	EXPECT_EQ(str[7], L'h');
	EXPECT_EQ(str[8], L'i');
	EXPECT_EQ(str.Length(), 9);
}

TEST(WideStringTest, Append7)
{
	jinstl::WideString str{ L"abcdef" };
	jinstl::WideString str1{ L"" };
	str.Append(str1);

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L'e');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str.Length(), 6);
}

TEST(WideStringTest, Append8)
{
	jinstl::WideString str{ };
	str.Append('g');

	EXPECT_EQ(str[0], L'g');
	EXPECT_EQ(str.Length(), 1);
}

TEST(WideStringTest, Append9)
{
	jinstl::WideString str{ L"abcdef" };
	str.Append('g');

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L'e');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str[6], L'g');
	EXPECT_EQ(str.Length(), 7);
}

TEST(WideStringTest, Append10)
{
	jinstl::WideString str{ };
	str.Append(L"abc");

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str.Length(), 3);
}

TEST(WideStringTest, Append11)
{
	jinstl::WideString str{ L"abcdef" };
	str.Append(L"ghi");

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L'e');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str[6], L'g');
	EXPECT_EQ(str[7], L'h');
	EXPECT_EQ(str[8], L'i');
	EXPECT_EQ(str.Length(), 9);
}

TEST(WideStringTest, Append12)
{
	jinstl::WideString str{ L"abcdef" };
	str.Append(L"ghijklmnopqrstu");

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L'e');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str[6], L'g');
	EXPECT_EQ(str[7], L'h');
	EXPECT_EQ(str[8], L'i');
	EXPECT_EQ(str[9], L'j');
	EXPECT_EQ(str[10], L'k');
	EXPECT_EQ(str[11], L'l');
	EXPECT_EQ(str[12], L'm');
	EXPECT_EQ(str[13], L'n');
	EXPECT_EQ(str[14], L'o');
	EXPECT_EQ(str[15], L'p');
	EXPECT_EQ(str[16], L'q');
	EXPECT_EQ(str[17], L'r');
	EXPECT_EQ(str[18], L's');
	EXPECT_EQ(str[19], L't');
	EXPECT_EQ(str[20], L'u');
	EXPECT_EQ(str.Length(), 21);
}


TEST(WideStringTest, operatorAppend1)
{
	jinstl::WideString str{ };
	str += L"sdfdsf";

	EXPECT_EQ(str[0], L's');
	EXPECT_EQ(str[1], L'd');
	EXPECT_EQ(str[2], L'f');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L's');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str.Length(), 6);
}

TEST(WideStringTest, operatorAppend2)
{
	jinstl::WideString str{ L"abc" };
	str += L"sdfdsf";

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L's');
	EXPECT_EQ(str[4], L'd');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str[6], L'd');
	EXPECT_EQ(str[7], L's');
	EXPECT_EQ(str[8], L'f');
	EXPECT_EQ(str.Length(), 9);
}

TEST(WideStringTest, operatorAppend3)
{
	jinstl::WideString str{ L"abc" };
	str += L"s";

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L's');
	EXPECT_EQ(str.Length(), 4);
}

TEST(WideStringTest, operatorAppend4)
{
	jinstl::WideString str{  };
	jinstl::WideString str1{ L"abc" };
	str += str1;

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str.Length(), 3);
}

TEST(WideStringTest, operatorAppend5)
{
	jinstl::WideString str{ L"a" };
	jinstl::WideString str1{ L"bcd" };
	str += str1;

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str.Length(), 4);
}

TEST(WideStringTest, operatorAppend6)
{
	jinstl::WideString str{ L"abcdef" };
	jinstl::WideString str1{ L"ghi" };
	str += str1;

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L'e');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str[6], L'g');
	EXPECT_EQ(str[7], L'h');
	EXPECT_EQ(str[8], L'i');
	EXPECT_EQ(str.Length(), 9);
}

TEST(WideStringTest, operatorAppend7)
{
	jinstl::WideString str{ L"abcdef" };
	jinstl::WideString str1{ L"" };
	str += str1;

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L'e');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str.Length(), 6);
}

TEST(WideStringTest, operatorAppend8)
{
	jinstl::WideString str{ };
	str += L'g';

	EXPECT_EQ(str[0], L'g');
	EXPECT_EQ(str.Length(), 1);
}

TEST(WideStringTest, operatorAppend9)
{
	jinstl::WideString str{ L"abcdef" };
	str += L'g';

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L'e');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str[6], L'g');
	EXPECT_EQ(str.Length(), 7);
}

TEST(WideStringTest, operatorAppend10)
{
	jinstl::WideString str{ };
	str += L"abc";

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str.Length(), 3);
}

TEST(WideStringTest, operatorAppend11)
{
	jinstl::WideString str{ L"abcdef" };
	str += L"ghi";

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L'e');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str[6], L'g');
	EXPECT_EQ(str[7], L'h');
	EXPECT_EQ(str[8], L'i');
	EXPECT_EQ(str.Length(), 9);
}


TEST(WideStringTest, PopBack)
{
	jinstl::WideString str{ L"abcdef" };
	str.PopBack();

	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L'e');
	EXPECT_EQ(str.Length(), 5);
}

TEST(WideStringTest, Empty1)
{
	jinstl::WideString str{ };
	EXPECT_EQ(str.Empty(), true);
}

TEST(WideStringTest, Empty2)
{
	jinstl::WideString str{ L"df"};
	EXPECT_EQ(str.Empty(), false);
}

TEST(WideStringTest, CString)
{
	jinstl::WideString str{ L"df" };
	EXPECT_EQ(str.CString()[0], L'd');
	EXPECT_EQ(str.CString()[1], L'f');
	EXPECT_EQ(std::wcslen(str.CString()), 2);
}

TEST(WideStringTest, ResizeLength1)
{
	jinstl::WideString str{ L"df" };
	str.ResizeLength(5);
	EXPECT_EQ(str.CString()[0], L'd');
	EXPECT_EQ(str.CString()[1], L'f');
	EXPECT_EQ(str.Length(), 5);
}

TEST(WideStringTest, ResizeLength2)
{
	jinstl::WideString str{ L"df" };
	str.ResizeLength(0);
	EXPECT_EQ(str.Length(), 0);
}

TEST(WideStringTest, ResizeLength3)
{
	jinstl::WideString str{  };
	str.ResizeLength(111);
	EXPECT_EQ(str.Length(), 111);
}

TEST(WideStringTest, ResizeLength4)
{
	jinstl::WideString str{  };
	str.ResizeLength(0);
	EXPECT_EQ(str.Length(), 0);
}

TEST(WideStringTest, ResizeLength5)
{
	jinstl::WideString str{ L"dsfdsfkndsfkdsnfksdnfsdffdsfdsfds" };
	str.ResizeLength(2);
	EXPECT_EQ(str[0], L'd');
	EXPECT_EQ(str[1], L's');
	EXPECT_EQ(str.Length(), 2);
	EXPECT_EQ(str.Length(), 2);
}

TEST(WideStringTest, Clear1)
{
	jinstl::WideString str{  };
	str.Clear();
	EXPECT_EQ(str.Length(), 0);
}

TEST(WideStringTest, Clear2)
{
	jinstl::WideString str{ L"sdfsdf"};

	const size_t originalCapacity = str.Capacity();

	str.Clear();
	EXPECT_EQ(str.Length(), 0);
	EXPECT_EQ(str.Capacity(), originalCapacity);
}

TEST(WideStringTest, Insert1)
{
	jinstl::WideString str{ };
	
	str.Insert(0, L'a');
	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str.Length(), 1);
}

TEST(WideStringTest, Insert2)
{
	jinstl::WideString str{ L"df" };
	EXPECT_EQ(str[0], L'd');
	EXPECT_EQ(str[1], L'f');

	str.Insert(0, L'a');
	EXPECT_EQ(str.Length(), 3);
	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'd');
	EXPECT_EQ(str[2], L'f');
}

TEST(WideStringTest, Insert3)
{
	jinstl::WideString str{ L"df" };

	str.Insert(0, L"abcdefghijklm");
	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L'e');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str[6], L'g');
	EXPECT_EQ(str[7], L'h');
	EXPECT_EQ(str[8], L'i');
	EXPECT_EQ(str[9], L'j');
	EXPECT_EQ(str[10], L'k');
	EXPECT_EQ(str[11], L'l');
	EXPECT_EQ(str[12], L'm');
	EXPECT_EQ(str[13], L'd');
	EXPECT_EQ(str[14], L'f');
	EXPECT_EQ(str.Length(), 15);
}

TEST(WideStringTest, Insert4)
{
	jinstl::WideString str1{ L"df" };
	jinstl::WideString str2{ L"gh" };

	str1.Insert(0, str2);
	EXPECT_EQ(str1[0], L'g');
	EXPECT_EQ(str1[1], L'h');
	EXPECT_EQ(str1[2], L'd');
	EXPECT_EQ(str1[3], L'f');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(WideStringTest, Insert5)
{
	jinstl::WideString str1{ L"gh" };

	str1.Insert(0, L"df");
	EXPECT_EQ(str1[0], L'd');
	EXPECT_EQ(str1[1], L'f');
	EXPECT_EQ(str1[2], L'g');
	EXPECT_EQ(str1[3], L'h');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(WideStringTest, Insert6)
{
	jinstl::WideString str{ };

	str.Insert(0, L'a');
	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str.Length(), 1);
}

TEST(WideStringTest, Insert7)
{
	jinstl::WideString str{ L"df" };
	EXPECT_EQ(str[0], L'd');
	EXPECT_EQ(str[1], L'f');

	str.Insert(1, L'a');
	EXPECT_EQ(str.Length(), 3);
	EXPECT_EQ(str[0], L'd');
	EXPECT_EQ(str[1], L'a');
	EXPECT_EQ(str[2], L'f');
}

TEST(WideStringTest, Insert8)
{
	jinstl::WideString str{ L"df" };

	str.Insert(1, L"abcdefghijklm");
	EXPECT_EQ(str[0], L'd');
	EXPECT_EQ(str[1], L'a');
	EXPECT_EQ(str[2], L'b');
	EXPECT_EQ(str[3], L'c');
	EXPECT_EQ(str[4], L'd');
	EXPECT_EQ(str[5], L'e');
	EXPECT_EQ(str[6], L'f');
	EXPECT_EQ(str[7], L'g');
	EXPECT_EQ(str[8], L'h');
	EXPECT_EQ(str[9], L'i');
	EXPECT_EQ(str[10], L'j');
	EXPECT_EQ(str[11], L'k');
	EXPECT_EQ(str[12], L'l');
	EXPECT_EQ(str[13], L'm');
	EXPECT_EQ(str[14], L'f');
	EXPECT_EQ(str.Length(), 15);
}

TEST(WideStringTest, Insert9)
{
	jinstl::WideString str1{ L"df" };
	jinstl::WideString str2{ L"gh" };

	str1.Insert(1, str2);
	EXPECT_EQ(str1[0], L'd');
	EXPECT_EQ(str1[1], L'g');
	EXPECT_EQ(str1[2], L'h');
	EXPECT_EQ(str1[3], L'f');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(WideStringTest, Insert10)
{
	jinstl::WideString str1{ L"gh" };

	str1.Insert(1, L"df");
	EXPECT_EQ(str1[0], L'g');
	EXPECT_EQ(str1[1], L'd');
	EXPECT_EQ(str1[2], L'f');
	EXPECT_EQ(str1[3], L'h');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(WideStringTest, Insert11)
{
	jinstl::WideString str{ };

	str.Insert(0, L'a');
	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str.Length(), 1);
}

TEST(WideStringTest, Insert12)
{
	jinstl::WideString str{ L"df" };
	EXPECT_EQ(str[0], L'd');
	EXPECT_EQ(str[1], L'f');

	str.Insert(2, L'a');
	EXPECT_EQ(str.Length(), 3);
	EXPECT_EQ(str[0], L'd');
	EXPECT_EQ(str[1], L'f');
	EXPECT_EQ(str[2], L'a');
}

TEST(WideStringTest, Insert13)
{
	jinstl::WideString str{ L"df" };

	str.Insert(2, L"abcdefghijklm");
	EXPECT_EQ(str[0], L'd');
	EXPECT_EQ(str[1], L'f');
	EXPECT_EQ(str[2], L'a');
	EXPECT_EQ(str[3], L'b');
	EXPECT_EQ(str[4], L'c');
	EXPECT_EQ(str[5], L'd');
	EXPECT_EQ(str[6], L'e');
	EXPECT_EQ(str[7], L'f');
	EXPECT_EQ(str[8], L'g');
	EXPECT_EQ(str[9], L'h');
	EXPECT_EQ(str[10], L'i');
	EXPECT_EQ(str[11], L'j');
	EXPECT_EQ(str[12], L'k');
	EXPECT_EQ(str[13], L'l');
	EXPECT_EQ(str[14], L'm');
	EXPECT_EQ(str.Length(), 15);
}

TEST(WideStringTest, Insert14)
{
	jinstl::WideString str1{ L"df" };
	jinstl::WideString str2{ L"gh" };

	str1.Insert(2, str2);
	EXPECT_EQ(str1[0], L'd');
	EXPECT_EQ(str1[1], L'f');
	EXPECT_EQ(str1[2], L'g');
	EXPECT_EQ(str1[3], L'h');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(WideStringTest, Insert15)
{
	jinstl::WideString str1{ L"gh" };

	str1.Insert(2, L"df");
	EXPECT_EQ(str1[0], L'g');
	EXPECT_EQ(str1[1], L'h');
	EXPECT_EQ(str1[2], L'd');
	EXPECT_EQ(str1[3], L'f');
	EXPECT_EQ(str1.Length(), 4);
}



TEST(WideStringTest, Insert16)
{
	jinstl::WideString str{ };
	str.Reserve(100);

	str.Insert(0, L'a');
	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str.Length(), 1);
}

TEST(WideStringTest, Insert17)
{
	jinstl::WideString str{ L"df" };
	str.Reserve(100);
	EXPECT_EQ(str[0], L'd');
	EXPECT_EQ(str[1], L'f');

	str.Insert(0, L'a');
	EXPECT_EQ(str.Length(), 3);
	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'd');
	EXPECT_EQ(str[2], L'f');
}

TEST(WideStringTest, Insert18)
{
	jinstl::WideString str{ L"df" };
	str.Reserve(100);

	str.Insert(0, L"abcdefghijklm");
	EXPECT_EQ(str[0], L'a');
	EXPECT_EQ(str[1], L'b');
	EXPECT_EQ(str[2], L'c');
	EXPECT_EQ(str[3], L'd');
	EXPECT_EQ(str[4], L'e');
	EXPECT_EQ(str[5], L'f');
	EXPECT_EQ(str[6], L'g');
	EXPECT_EQ(str[7], L'h');
	EXPECT_EQ(str[8], L'i');
	EXPECT_EQ(str[9], L'j');
	EXPECT_EQ(str[10], L'k');
	EXPECT_EQ(str[11], L'l');
	EXPECT_EQ(str[12], L'm');
	EXPECT_EQ(str[13], L'd');
	EXPECT_EQ(str[14], L'f');
	EXPECT_EQ(str.Length(), 15);
}

TEST(WideStringTest, Insert19)
{
	jinstl::WideString str1{ L"df" };
	str1.Reserve(100);
	jinstl::WideString str2{ L"gh" };

	str1.Insert(0, str2);
	EXPECT_EQ(str1[0], L'g');
	EXPECT_EQ(str1[1], L'h');
	EXPECT_EQ(str1[2], L'd');
	EXPECT_EQ(str1[3], L'f');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(WideStringTest, Insert20)
{
	jinstl::WideString str1{ L"gh" };
	str1.Reserve(100);

	str1.Insert(0, L"df");
	EXPECT_EQ(str1[0], L'd');
	EXPECT_EQ(str1[1], L'f');
	EXPECT_EQ(str1[2], L'g');
	EXPECT_EQ(str1[3], L'h');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(WideStringTest, Remove1)
{
	jinstl::WideString str1{ L"abc" };

	const size_t originalCapacity = str1.Capacity();

	str1.Remove(0);

	EXPECT_EQ(str1[0], L'b');
	EXPECT_EQ(str1[1], L'c');
	EXPECT_EQ(str1.Length(), 2);
	EXPECT_EQ(str1.Capacity(), originalCapacity);
}

TEST(WideStringTest, Remove2)
{
	jinstl::WideString str1{ L"abc" };

	const size_t originalCapacity = str1.Capacity();

	str1.Remove(1);

	EXPECT_EQ(str1[0], L'a');
	EXPECT_EQ(str1[1], L'c');
	EXPECT_EQ(str1.Length(), 2);
	EXPECT_EQ(str1.Capacity(), originalCapacity);
}

TEST(WideStringTest, Remove3)
{
	jinstl::WideString str1{ L"abc" };

	const size_t originalCapacity = str1.Capacity();

	str1.Remove(2);

	EXPECT_EQ(str1[0], L'a');
	EXPECT_EQ(str1[1], L'b');
	EXPECT_EQ(str1.Length(), 2);
	EXPECT_EQ(str1.Capacity(), originalCapacity);
}

TEST(WideStringTest, Substring1)
{
	jinstl::WideString str1{ L"abcdfg" };

	const size_t originalCapacity = str1.Capacity();

	jinstl::WideString str2 = str1.SubString(0);

	EXPECT_EQ(str2[0], L'a');
	EXPECT_EQ(str2[1], L'b');
	EXPECT_EQ(str2[2], L'c');
	EXPECT_EQ(str2[3], L'd');
	EXPECT_EQ(str2[4], L'f');
	EXPECT_EQ(str2[5], L'g');
	EXPECT_EQ(str2.Length(), 6);
}

TEST(WideStringTest, Substring2)
{
	jinstl::WideString str1{ L"abcdfg" };

	const size_t originalCapacity = str1.Capacity();

	jinstl::WideString str2 = str1.SubString(3);

	EXPECT_EQ(str2[0], L'd');
	EXPECT_EQ(str2[1], L'f');
	EXPECT_EQ(str2[2], L'g');
	EXPECT_EQ(str2.Length(), 3);
}


TEST(WideStringTest, Find1)
{
	jinstl::WideString str1{ L"abcdefg" };
	

	EXPECT_EQ(str1.Find('a'), 0);
	EXPECT_EQ(str1.Find('b'), 1);
	EXPECT_EQ(str1.Find('c'), 2);
	EXPECT_EQ(str1.Find('d'), 3);
	EXPECT_EQ(str1.Find('e'), 4);
	EXPECT_EQ(str1.Find('f'), 5);
	EXPECT_EQ(str1.Find('g'), 6);

	EXPECT_EQ(str1.Find('3'), str1.Length());
	EXPECT_EQ(str1.Find('2'), str1.Length());
}

TEST(WideStringTest, Find2)
{
	jinstl::WideString str1{ };

	EXPECT_EQ(str1.Find('a'), str1.Length());
	EXPECT_EQ(str1.Find('b'), str1.Length());
	EXPECT_EQ(str1.Find('c'), str1.Length());
	EXPECT_EQ(str1.Find('d'), str1.Length());
	EXPECT_EQ(str1.Find('e'), str1.Length());
	EXPECT_EQ(str1.Find('f'), str1.Length());
	EXPECT_EQ(str1.Find('g'), str1.Length());
	EXPECT_EQ(str1.Find('3'), str1.Length());
	EXPECT_EQ(str1.Find('2'), str1.Length());
}

TEST(WideStringTest, FirstString1)
{
	jinstl::WideString str1{ L"sd" };
	EXPECT_EQ(str1.FirstCharacter(), L's');
}

TEST(WideStringTest, FirstString2)
{
	const jinstl::WideString str1{ L"sd" };
	EXPECT_EQ(str1.FirstCharacter(), L's');
}

TEST(WideStringTest, LastString1)
{
	jinstl::WideString str1{ L"sd" };
	EXPECT_EQ(str1.LastCharacter(), L'd');
}

TEST(WideStringTest, LastString2)
{
	const jinstl::WideString str1{ L"sd" };
	EXPECT_EQ(str1.LastCharacter(), L'd');
}

TEST(WideStringTest, Contain1)
{
	const jinstl::WideString str1{ L"sd" };
	EXPECT_EQ(str1.Contain('s'), true);
	EXPECT_EQ(str1.Contain('d'), true);
	EXPECT_EQ(str1.Contain('1'), false);
	EXPECT_EQ(str1.Contain('2'), false);
}

TEST(WideStringTest, Contain2)
{
	const jinstl::WideString str1{  };
	EXPECT_EQ(str1.Contain('s'), false);
	EXPECT_EQ(str1.Contain('d'), false);
	EXPECT_EQ(str1.Contain('1'), false);
	EXPECT_EQ(str1.Contain('2'), false);
}

TEST(WideStringTest, Compare1)
{
	const jinstl::WideString str1{ L"ef" };
	const jinstl::WideString str2{ L"ef" };
	EXPECT_EQ(str1.Compare(str2), 0);
}

TEST(WideStringTest, Compare2)
{
	const jinstl::WideString str1{ L"a" };
	const jinstl::WideString str2{ L"b" };
	EXPECT_LT(str1.Compare(str2), 0);
}

TEST(WideStringTest, EqualWith1)
{
	const jinstl::WideString str1{ L"ef" };
	const jinstl::WideString str2{ L"ef" };
	EXPECT_EQ(str1.EqualWith(str2), true);
}

TEST(WideStringTest, EqualWith2)
{
	const jinstl::WideString str1{ L"a" };
	const jinstl::WideString str2{ L"b" };
	EXPECT_EQ(str1.EqualWith(str2), false);
}

TEST(WideStringTest, EqualWith3)
{
	const jinstl::WideString str1{ L"a" };
	const jinstl::WideString str2{ L"afdsf" };
	EXPECT_EQ(str1.EqualWith(str2), false);
}

TEST(WideStringTest, EqualWith4)
{
	const jinstl::WideString str1{ L"afdsf" };
	const jinstl::WideString str2{ L"afdsf" };
	EXPECT_EQ(str1.EqualWith(str2), true);
}

TEST(WideStringTest, Concate1)
{
	const jinstl::WideString str1{ L"abc" };
	const jinstl::WideString str2{ L"defghijklmn" };

	const jinstl::WideString ConcatedString = str1 + str2;
	EXPECT_EQ(ConcatedString[0], L'a');
	EXPECT_EQ(ConcatedString[1], L'b');
	EXPECT_EQ(ConcatedString[2], L'c');
	EXPECT_EQ(ConcatedString[3], L'd');
	EXPECT_EQ(ConcatedString[4], L'e');
	EXPECT_EQ(ConcatedString[5], L'f');
	EXPECT_EQ(ConcatedString[6], L'g');
	EXPECT_EQ(ConcatedString[7], L'h');
	EXPECT_EQ(ConcatedString[8], L'i');
	EXPECT_EQ(ConcatedString[9], L'j');
	EXPECT_EQ(ConcatedString[10], L'k');
	EXPECT_EQ(ConcatedString[11], L'l');
	EXPECT_EQ(ConcatedString[12], L'm');
	EXPECT_EQ(ConcatedString[13], L'n');
	EXPECT_EQ(ConcatedString.Length(), 14);
}

TEST(WideStringTest, Concate2)
{
	const jinstl::WideString str1{ L"abc" };
	const jinstl::WideString str2{ };

	const jinstl::WideString ConcatedString = str1 + str2;
	EXPECT_EQ(ConcatedString[0], L'a');
	EXPECT_EQ(ConcatedString[1], L'b');
	EXPECT_EQ(ConcatedString[2], L'c');
	EXPECT_EQ(ConcatedString.Length(), 3);
}