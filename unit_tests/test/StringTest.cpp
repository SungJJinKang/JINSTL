#include "test.h"

#include <jinstl/TString.h>

TEST(CharStringTest, StringConstruct1)
{
	jinstl::String str{ "abcd" };

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str.Length(), 4);
	//jinstl::String str{};
}

TEST(CharStringTest, StringConstruct2)
{
	const char* const testString = "abcdef";
	jinstl::String str{ testString, testString + 2 };

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str.Length(), 2);
	//jinstl::String str{};
}

TEST(CharStringTest, StringConstruct3)
{
	jinstl::String str{ "" };
	
	EXPECT_EQ(str.Length(), 0);
	//jinstl::String str{};
}

TEST(CharStringTest, StringConstruct4)
{
	jinstl::String str{ };

	EXPECT_EQ(str.Length(), 0);
	//jinstl::String str{};
}

TEST(CharStringTest, CopyConstruct1)
{
	jinstl::String str1{ "abcdefg" };
	jinstl::String str2{ str1 };

	EXPECT_EQ(str1.Length(), 7);

	EXPECT_EQ(str2[0], 'a');
	EXPECT_EQ(str2[1], 'b');
	EXPECT_EQ(str2[2], 'c');
	EXPECT_EQ(str2[3], 'd');
	EXPECT_EQ(str2[4], 'e');
	EXPECT_EQ(str2[5], 'f');
	EXPECT_EQ(str2[6], 'g');
	EXPECT_EQ(str2.Length(), 7);
	//jinstl::String str{};
}

TEST(CharStringTest, CopyConstruct2)
{
	jinstl::String str1{ };
	jinstl::String str2{ str1 };

	EXPECT_EQ(str1.Length(), 0);
	EXPECT_EQ(str2.Length(), 0);
	//jinstl::String str{};
}

TEST(CharStringTest, MoveConstruct)
{
	jinstl::String str1{ "abcdefg" };
	jinstl::String str2{ std::move(str1) };

	EXPECT_EQ(str1.Length(), 0);

	EXPECT_EQ(str2[0], 'a');
	EXPECT_EQ(str2[1], 'b');
	EXPECT_EQ(str2[2], 'c');
	EXPECT_EQ(str2[3], 'd');
	EXPECT_EQ(str2[4], 'e');
	EXPECT_EQ(str2[5], 'f');
	EXPECT_EQ(str2[6], 'g');
	EXPECT_EQ(str2.Length(), 7);
	//jinstl::String str{};
}

TEST(CharStringTest, CopyAssignment1)
{
	jinstl::String str1{ "abcdefg" };
	jinstl::String str2{ };
	str2 = str1;

	EXPECT_EQ(str1.Length(), 7);

	EXPECT_EQ(str2[0], 'a');
	EXPECT_EQ(str2[1], 'b');
	EXPECT_EQ(str2[2], 'c');
	EXPECT_EQ(str2[3], 'd');
	EXPECT_EQ(str2[4], 'e');
	EXPECT_EQ(str2[5], 'f');
	EXPECT_EQ(str2[6], 'g');
	EXPECT_EQ(str2.Length(), 7);
	//jinstl::String str{};
}

TEST(CharStringTest, CopyAssignment2)
{
	jinstl::String str1{ "abcdefg" };
	jinstl::String str2{ "abcdefghijklmn" };
	str2 = str1;

	EXPECT_EQ(str1.Length(), 7);

	EXPECT_EQ(str2[0], 'a');
	EXPECT_EQ(str2[1], 'b');
	EXPECT_EQ(str2[2], 'c');
	EXPECT_EQ(str2[3], 'd');
	EXPECT_EQ(str2[4], 'e');
	EXPECT_EQ(str2[5], 'f');
	EXPECT_EQ(str2[6], 'g');
	EXPECT_EQ(str2.Length(), 7);
	//jinstl::String str{};
}

TEST(CharStringTest, MoveAssignment1)
{
	jinstl::String str1{ "abcdefg" };
	jinstl::String str2{ };
	str2 = std::move(str1);

	EXPECT_EQ(str1.Length(), 0);
	EXPECT_EQ(str1.Capacity(), 0);

	EXPECT_EQ(str2[0], 'a');
	EXPECT_EQ(str2[1], 'b');
	EXPECT_EQ(str2[2], 'c');
	EXPECT_EQ(str2[3], 'd');
	EXPECT_EQ(str2[4], 'e');
	EXPECT_EQ(str2[5], 'f');
	EXPECT_EQ(str2[6], 'g');
	EXPECT_EQ(str2.Length(), 7);
}

TEST(CharStringTest, MoveAssignment2)
{
	jinstl::String str1{ "abcdefg" };
	jinstl::String str2{ "abcdefghijklmn" };
	str2 = std::move(str1);

	EXPECT_EQ(str1.Length(), 0);
	EXPECT_EQ(str1.Capacity(), 0);

	EXPECT_EQ(str2[0], 'a');
	EXPECT_EQ(str2[1], 'b');
	EXPECT_EQ(str2[2], 'c');
	EXPECT_EQ(str2[3], 'd');
	EXPECT_EQ(str2[4], 'e');
	EXPECT_EQ(str2[5], 'f');
	EXPECT_EQ(str2[6], 'g');
	EXPECT_EQ(str2.Length(), 7);
}

TEST(CharStringTest, Reserve1)
{
	jinstl::String str{};
	str.Reserve(11);

	EXPECT_EQ(str.Length(), 0);
	EXPECT_EQ(str.Capacity(), 11);
}

TEST(CharStringTest, Reserve2)
{
	jinstl::String str{"sdfdsf"};
	str.Reserve(11);

	EXPECT_EQ(str.Length(), 6);
	EXPECT_EQ(str.Capacity(), 11);
}


TEST(CharStringTest, Append1)
{
	jinstl::String str{ };
	str.Append("sdfdsf");

	EXPECT_EQ(str[0], 's');
	EXPECT_EQ(str[1], 'd');
	EXPECT_EQ(str[2], 'f');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 's');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str.Length(), 6);
}

TEST(CharStringTest, Append2)
{
	jinstl::String str{"abc"};
	str.Append("sdfdsf");

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 's');
	EXPECT_EQ(str[4], 'd');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str[6], 'd');
	EXPECT_EQ(str[7], 's');
	EXPECT_EQ(str[8], 'f');
	EXPECT_EQ(str.Length(), 9);
}

TEST(CharStringTest, Append3)
{
	jinstl::String str{ "abc" };
	str.Append("s");

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 's');
	EXPECT_EQ(str.Length(), 4);
}

TEST(CharStringTest, Append4)
{
	jinstl::String str{  };
	jinstl::String str1{ "abc" };
	str.Append(str1);

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str.Length(), 3);
}

TEST(CharStringTest, Append5)
{
	jinstl::String str{ "a"};
	jinstl::String str1{ "bcd" };
	str.Append(str1);

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str.Length(), 4);
}

TEST(CharStringTest, Append6)
{
	jinstl::String str{ "abcdef" };
	jinstl::String str1{ "ghi" };
	str.Append(str1);

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 'e');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str[6], 'g');
	EXPECT_EQ(str[7], 'h');
	EXPECT_EQ(str[8], 'i');
	EXPECT_EQ(str.Length(), 9);
}

TEST(CharStringTest, Append7)
{
	jinstl::String str{ "abcdef" };
	jinstl::String str1{ "" };
	str.Append(str1);

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 'e');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str.Length(), 6);
}

TEST(CharStringTest, Append8)
{
	jinstl::String str{ };
	str.Append('g');

	EXPECT_EQ(str[0], 'g');
	EXPECT_EQ(str.Length(), 1);
}

TEST(CharStringTest, Append9)
{
	jinstl::String str{ "abcdef" };
	str.Append('g');

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 'e');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str[6], 'g');
	EXPECT_EQ(str.Length(), 7);
}

TEST(CharStringTest, Append10)
{
	jinstl::String str{ };
	str.Append("abc");

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str.Length(), 3);
}

TEST(CharStringTest, Append11)
{
	jinstl::String str{ "abcdef" };
	str.Append("ghi");

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 'e');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str[6], 'g');
	EXPECT_EQ(str[7], 'h');
	EXPECT_EQ(str[8], 'i');
	EXPECT_EQ(str.Length(), 9);
}

TEST(CharStringTest, Append12)
{
	jinstl::String str{ "abcdef" };
	str.Append("ghijklmnopqrstu");

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 'e');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str[6], 'g');
	EXPECT_EQ(str[7], 'h');
	EXPECT_EQ(str[8], 'i');
	EXPECT_EQ(str[9], 'j');
	EXPECT_EQ(str[10], 'k');
	EXPECT_EQ(str[11], 'l');
	EXPECT_EQ(str[12], 'm');
	EXPECT_EQ(str[13], 'n');
	EXPECT_EQ(str[14], 'o');
	EXPECT_EQ(str[15], 'p');
	EXPECT_EQ(str[16], 'q');
	EXPECT_EQ(str[17], 'r');
	EXPECT_EQ(str[18], 's');
	EXPECT_EQ(str[19], 't');
	EXPECT_EQ(str[20], 'u');
	EXPECT_EQ(str.Length(), 21);
}

TEST(CharStringTest, operatorAppend1)
{
	jinstl::String str{ };
	str += "sdfdsf";

	EXPECT_EQ(str[0], 's');
	EXPECT_EQ(str[1], 'd');
	EXPECT_EQ(str[2], 'f');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 's');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str.Length(), 6);
}

TEST(CharStringTest, operatorAppend2)
{
	jinstl::String str{ "abc" };
	str += "sdfdsf";

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 's');
	EXPECT_EQ(str[4], 'd');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str[6], 'd');
	EXPECT_EQ(str[7], 's');
	EXPECT_EQ(str[8], 'f');
	EXPECT_EQ(str.Length(), 9);
}

TEST(CharStringTest, operatorAppend3)
{
	jinstl::String str{ "abc" };
	str += "s";

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 's');
	EXPECT_EQ(str.Length(), 4);
}

TEST(CharStringTest, operatorAppend4)
{
	jinstl::String str{  };
	jinstl::String str1{ "abc" };
	str += str1;

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str.Length(), 3);
}

TEST(CharStringTest, operatorAppend5)
{
	jinstl::String str{ "a" };
	jinstl::String str1{ "bcd" };
	str += str1;

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str.Length(), 4);
}

TEST(CharStringTest, operatorAppend6)
{
	jinstl::String str{ "abcdef" };
	jinstl::String str1{ "ghi" };
	str += str1;

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 'e');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str[6], 'g');
	EXPECT_EQ(str[7], 'h');
	EXPECT_EQ(str[8], 'i');
	EXPECT_EQ(str.Length(), 9);
}

TEST(CharStringTest, operatorAppend7)
{
	jinstl::String str{ "abcdef" };
	jinstl::String str1{ "" };
	str += str1;

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 'e');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str.Length(), 6);
}

TEST(CharStringTest, operatorAppend8)
{
	jinstl::String str{ };
	str += 'g';

	EXPECT_EQ(str[0], 'g');
	EXPECT_EQ(str.Length(), 1);
}

TEST(CharStringTest, operatorAppend9)
{
	jinstl::String str{ "abcdef" };
	str += 'g';

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 'e');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str[6], 'g');
	EXPECT_EQ(str.Length(), 7);
}

TEST(CharStringTest, operatorAppend10)
{
	jinstl::String str{ };
	str += "abc";

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str.Length(), 3);
}

TEST(CharStringTest, operatorAppend11)
{
	jinstl::String str{ "abcdef" };
	str += "ghi";

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 'e');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str[6], 'g');
	EXPECT_EQ(str[7], 'h');
	EXPECT_EQ(str[8], 'i');
	EXPECT_EQ(str.Length(), 9);
}


TEST(CharStringTest, PopBack)
{
	jinstl::String str{ "abcdef" };
	str.PopBack();

	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 'e');
	EXPECT_EQ(str.Length(), 5);
}

TEST(CharStringTest, Empty1)
{
	jinstl::String str{ };
	EXPECT_EQ(str.Empty(), true);
}

TEST(CharStringTest, Empty2)
{
	jinstl::String str{ "df"};
	EXPECT_EQ(str.Empty(), false);
}

TEST(CharStringTest, CString)
{
	jinstl::String str{ "df" };
	EXPECT_EQ(str.CString()[0], 'd');
	EXPECT_EQ(str.CString()[1], 'f');
	EXPECT_EQ(std::strlen(str.CString()), 2);
}

TEST(CharStringTest, ResizeLength1)
{
	jinstl::String str{ "df" };
	str.ResizeLength(5);
	EXPECT_EQ(str.CString()[0], 'd');
	EXPECT_EQ(str.CString()[1], 'f');
	EXPECT_EQ(str.Length(), 5);
}

TEST(CharStringTest, ResizeLength2)
{
	jinstl::String str{ "df" };
	str.ResizeLength(0);
	EXPECT_EQ(str.Length(), 0);
}

TEST(CharStringTest, ResizeLength3)
{
	jinstl::String str{  };
	str.ResizeLength(111);
	EXPECT_EQ(str.Length(), 111);
}

TEST(CharStringTest, ResizeLength4)
{
	jinstl::String str{  };
	str.ResizeLength(0);
	EXPECT_EQ(str.Length(), 0);
}

TEST(CharStringTest, ResizeLength5)
{
	jinstl::String str{ "dsfdsfkndsfkdsnfksdnfsdffdsfdsfds" };
	str.ResizeLength(2);
	EXPECT_EQ(str[0], 'd');
	EXPECT_EQ(str[1], 's');
	EXPECT_EQ(str.Length(), 2);
	EXPECT_EQ(str.Length(), 2);
}

TEST(CharStringTest, Clear1)
{
	jinstl::String str{  };
	str.Clear();
	EXPECT_EQ(str.Length(), 0);
}

TEST(CharStringTest, Clear2)
{
	jinstl::String str{ "sdfsdf"};

	const size_t originalCapacity = str.Capacity();

	str.Clear();
	EXPECT_EQ(str.Length(), 0);
	EXPECT_EQ(str.Capacity(), originalCapacity);
}

TEST(CharStringTest, Insert1)
{
	jinstl::String str{ };
	
	str.Insert(0, 'a');
	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str.Length(), 1);
}

TEST(CharStringTest, Insert2)
{
	jinstl::String str{ "df" };
	EXPECT_EQ(str[0], 'd');
	EXPECT_EQ(str[1], 'f');

	str.Insert(0, 'a');
	EXPECT_EQ(str.Length(), 3);
	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'd');
	EXPECT_EQ(str[2], 'f');
}

TEST(CharStringTest, Insert3)
{
	jinstl::String str{ "df" };

	str.Insert(0, "abcdefghijklm");
	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 'e');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str[6], 'g');
	EXPECT_EQ(str[7], 'h');
	EXPECT_EQ(str[8], 'i');
	EXPECT_EQ(str[9], 'j');
	EXPECT_EQ(str[10], 'k');
	EXPECT_EQ(str[11], 'l');
	EXPECT_EQ(str[12], 'm');
	EXPECT_EQ(str[13], 'd');
	EXPECT_EQ(str[14], 'f');
	EXPECT_EQ(str.Length(), 15);
}

TEST(CharStringTest, Insert4)
{
	jinstl::String str1{ "df" };
	jinstl::String str2{ "gh" };

	str1.Insert(0, str2);
	EXPECT_EQ(str1[0], 'g');
	EXPECT_EQ(str1[1], 'h');
	EXPECT_EQ(str1[2], 'd');
	EXPECT_EQ(str1[3], 'f');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(CharStringTest, Insert5)
{
	jinstl::String str1{ "gh" };

	str1.Insert(0, "df");
	EXPECT_EQ(str1[0], 'd');
	EXPECT_EQ(str1[1], 'f');
	EXPECT_EQ(str1[2], 'g');
	EXPECT_EQ(str1[3], 'h');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(CharStringTest, Insert6)
{
	jinstl::String str{ };

	str.Insert(0, 'a');
	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str.Length(), 1);
}

TEST(CharStringTest, Insert7)
{
	jinstl::String str{ "df" };
	EXPECT_EQ(str[0], 'd');
	EXPECT_EQ(str[1], 'f');

	str.Insert(1, 'a');
	EXPECT_EQ(str.Length(), 3);
	EXPECT_EQ(str[0], 'd');
	EXPECT_EQ(str[1], 'a');
	EXPECT_EQ(str[2], 'f');
}

TEST(CharStringTest, Insert8)
{
	jinstl::String str{ "df" };

	str.Insert(1, "abcdefghijklm");
	EXPECT_EQ(str[0], 'd');
	EXPECT_EQ(str[1], 'a');
	EXPECT_EQ(str[2], 'b');
	EXPECT_EQ(str[3], 'c');
	EXPECT_EQ(str[4], 'd');
	EXPECT_EQ(str[5], 'e');
	EXPECT_EQ(str[6], 'f');
	EXPECT_EQ(str[7], 'g');
	EXPECT_EQ(str[8], 'h');
	EXPECT_EQ(str[9], 'i');
	EXPECT_EQ(str[10], 'j');
	EXPECT_EQ(str[11], 'k');
	EXPECT_EQ(str[12], 'l');
	EXPECT_EQ(str[13], 'm');
	EXPECT_EQ(str[14], 'f');
	EXPECT_EQ(str.Length(), 15);
}

TEST(CharStringTest, Insert9)
{
	jinstl::String str1{ "df" };
	jinstl::String str2{ "gh" };

	str1.Insert(1, str2);
	EXPECT_EQ(str1[0], 'd');
	EXPECT_EQ(str1[1], 'g');
	EXPECT_EQ(str1[2], 'h');
	EXPECT_EQ(str1[3], 'f');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(CharStringTest, Insert10)
{
	jinstl::String str1{ "gh" };

	str1.Insert(1, "df");
	EXPECT_EQ(str1[0], 'g');
	EXPECT_EQ(str1[1], 'd');
	EXPECT_EQ(str1[2], 'f');
	EXPECT_EQ(str1[3], 'h');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(CharStringTest, Insert11)
{
	jinstl::String str{ };

	str.Insert(0, 'a');
	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str.Length(), 1);
}

TEST(CharStringTest, Insert12)
{
	jinstl::String str{ "df" };
	EXPECT_EQ(str[0], 'd');
	EXPECT_EQ(str[1], 'f');

	str.Insert(2, 'a');
	EXPECT_EQ(str.Length(), 3);
	EXPECT_EQ(str[0], 'd');
	EXPECT_EQ(str[1], 'f');
	EXPECT_EQ(str[2], 'a');
}

TEST(CharStringTest, Insert13)
{
	jinstl::String str{ "df" };

	str.Insert(2, "abcdefghijklm");
	EXPECT_EQ(str[0], 'd');
	EXPECT_EQ(str[1], 'f');
	EXPECT_EQ(str[2], 'a');
	EXPECT_EQ(str[3], 'b');
	EXPECT_EQ(str[4], 'c');
	EXPECT_EQ(str[5], 'd');
	EXPECT_EQ(str[6], 'e');
	EXPECT_EQ(str[7], 'f');
	EXPECT_EQ(str[8], 'g');
	EXPECT_EQ(str[9], 'h');
	EXPECT_EQ(str[10], 'i');
	EXPECT_EQ(str[11], 'j');
	EXPECT_EQ(str[12], 'k');
	EXPECT_EQ(str[13], 'l');
	EXPECT_EQ(str[14], 'm');
	EXPECT_EQ(str.Length(), 15);
}

TEST(CharStringTest, Insert14)
{
	jinstl::String str1{ "df" };
	jinstl::String str2{ "gh" };

	str1.Insert(2, str2);
	EXPECT_EQ(str1[0], 'd');
	EXPECT_EQ(str1[1], 'f');
	EXPECT_EQ(str1[2], 'g');
	EXPECT_EQ(str1[3], 'h');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(CharStringTest, Insert15)
{
	jinstl::String str1{ "gh" };

	str1.Insert(2, "df");
	EXPECT_EQ(str1[0], 'g');
	EXPECT_EQ(str1[1], 'h');
	EXPECT_EQ(str1[2], 'd');
	EXPECT_EQ(str1[3], 'f');
	EXPECT_EQ(str1.Length(), 4);
}



TEST(CharStringTest, Insert16)
{
	jinstl::String str{ };
	str.Reserve(100);

	str.Insert(0, 'a');
	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str.Length(), 1);
}

TEST(CharStringTest, Insert17)
{
	jinstl::String str{ "df" };
	str.Reserve(100);
	EXPECT_EQ(str[0], 'd');
	EXPECT_EQ(str[1], 'f');

	str.Insert(0, 'a');
	EXPECT_EQ(str.Length(), 3);
	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'd');
	EXPECT_EQ(str[2], 'f');
}

TEST(CharStringTest, Insert18)
{
	jinstl::String str{ "df" };
	str.Reserve(100);

	str.Insert(0, "abcdefghijklm");
	EXPECT_EQ(str[0], 'a');
	EXPECT_EQ(str[1], 'b');
	EXPECT_EQ(str[2], 'c');
	EXPECT_EQ(str[3], 'd');
	EXPECT_EQ(str[4], 'e');
	EXPECT_EQ(str[5], 'f');
	EXPECT_EQ(str[6], 'g');
	EXPECT_EQ(str[7], 'h');
	EXPECT_EQ(str[8], 'i');
	EXPECT_EQ(str[9], 'j');
	EXPECT_EQ(str[10], 'k');
	EXPECT_EQ(str[11], 'l');
	EXPECT_EQ(str[12], 'm');
	EXPECT_EQ(str[13], 'd');
	EXPECT_EQ(str[14], 'f');
	EXPECT_EQ(str.Length(), 15);
}

TEST(CharStringTest, Insert19)
{
	jinstl::String str1{ "df" };
	str1.Reserve(100);
	jinstl::String str2{ "gh" };

	str1.Insert(0, str2);
	EXPECT_EQ(str1[0], 'g');
	EXPECT_EQ(str1[1], 'h');
	EXPECT_EQ(str1[2], 'd');
	EXPECT_EQ(str1[3], 'f');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(CharStringTest, Insert20)
{
	jinstl::String str1{ "gh" };
	str1.Reserve(100);

	str1.Insert(0, "df");
	EXPECT_EQ(str1[0], 'd');
	EXPECT_EQ(str1[1], 'f');
	EXPECT_EQ(str1[2], 'g');
	EXPECT_EQ(str1[3], 'h');
	EXPECT_EQ(str1.Length(), 4);
}

TEST(CharStringTest, Remove1)
{
	jinstl::String str1{ "abc" };

	const size_t originalCapacity = str1.Capacity();

	str1.Remove(0);

	EXPECT_EQ(str1[0], 'b');
	EXPECT_EQ(str1[1], 'c');
	EXPECT_EQ(str1.Length(), 2);
	EXPECT_EQ(str1.Capacity(), originalCapacity);
}

TEST(CharStringTest, Remove2)
{
	jinstl::String str1{ "abc" };

	const size_t originalCapacity = str1.Capacity();

	str1.Remove(1);

	EXPECT_EQ(str1[0], 'a');
	EXPECT_EQ(str1[1], 'c');
	EXPECT_EQ(str1.Length(), 2);
	EXPECT_EQ(str1.Capacity(), originalCapacity);
}

TEST(CharStringTest, Remove3)
{
	jinstl::String str1{ "abc" };

	const size_t originalCapacity = str1.Capacity();

	str1.Remove(2);

	EXPECT_EQ(str1[0], 'a');
	EXPECT_EQ(str1[1], 'b');
	EXPECT_EQ(str1.Length(), 2);
	EXPECT_EQ(str1.Capacity(), originalCapacity);
}

TEST(CharStringTest, Substring1)
{
	jinstl::String str1{ "abcdfg" };

	const size_t originalCapacity = str1.Capacity();

	jinstl::String str2 = str1.SubString(0);

	EXPECT_EQ(str2[0], 'a');
	EXPECT_EQ(str2[1], 'b');
	EXPECT_EQ(str2[2], 'c');
	EXPECT_EQ(str2[3], 'd');
	EXPECT_EQ(str2[4], 'f');
	EXPECT_EQ(str2[5], 'g');
	EXPECT_EQ(str2.Length(), 6);
}

TEST(CharStringTest, Substring2)
{
	jinstl::String str1{ "abcdfg" };

	const size_t originalCapacity = str1.Capacity();

	jinstl::String str2 = str1.SubString(3);

	EXPECT_EQ(str2[0], 'd');
	EXPECT_EQ(str2[1], 'f');
	EXPECT_EQ(str2[2], 'g');
	EXPECT_EQ(str2.Length(), 3);
}


TEST(CharStringTest, Find1)
{
	jinstl::String str1{ "abcdefg" };
	

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

TEST(CharStringTest, Find2)
{
	jinstl::String str1{ };

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

TEST(CharStringTest, FirstString1)
{
	jinstl::String str1{ "sd" };
	EXPECT_EQ(str1.FirstCharacter(), 's');
}

TEST(CharStringTest, FirstString2)
{
	const jinstl::String str1{ "sd" };
	EXPECT_EQ(str1.FirstCharacter(), 's');
}

TEST(CharStringTest, LastString1)
{
	jinstl::String str1{ "sd" };
	EXPECT_EQ(str1.LastCharacter(), 'd');
}

TEST(CharStringTest, LastString2)
{
	const jinstl::String str1{ "sd" };
	EXPECT_EQ(str1.LastCharacter(), 'd');
}

TEST(CharStringTest, Contain1)
{
	const jinstl::String str1{ "sd" };
	EXPECT_EQ(str1.Contain('s'), true);
	EXPECT_EQ(str1.Contain('d'), true);
	EXPECT_EQ(str1.Contain('1'), false);
	EXPECT_EQ(str1.Contain('2'), false);
}

TEST(CharStringTest, Contain2)
{
	const jinstl::String str1{  };
	EXPECT_EQ(str1.Contain('s'), false);
	EXPECT_EQ(str1.Contain('d'), false);
	EXPECT_EQ(str1.Contain('1'), false);
	EXPECT_EQ(str1.Contain('2'), false);
}

TEST(CharStringTest, Compare1)
{
	const jinstl::String str1{ "ef" };
	const jinstl::String str2{ "ef" };
	EXPECT_EQ(str1.Compare(str2), 0);
}

TEST(CharStringTest, Compare2)
{
	const jinstl::String str1{ "a" };
	const jinstl::String str2{ "b" };
	EXPECT_LT(str1.Compare(str2), 0);
}

TEST(CharStringTest, EqualWith1)
{
	const jinstl::String str1{ "ef" };
	const jinstl::String str2{ "ef" };
	EXPECT_EQ(str1.EqualWith(str2), true);
}

TEST(CharStringTest, EqualWith2)
{
	const jinstl::String str1{ "a" };
	const jinstl::String str2{ "b" };
	EXPECT_EQ(str1.EqualWith(str2), false);
}

TEST(CharStringTest, EqualWith3)
{
	const jinstl::String str1{ "a" };
	const jinstl::String str2{ "afdsf" };
	EXPECT_EQ(str1.EqualWith(str2), false);
}

TEST(CharStringTest, EqualWith4)
{
	const jinstl::String str1{ "afdsf" };
	const jinstl::String str2{ "afdsf" };
	EXPECT_EQ(str1.EqualWith(str2), true);
}

TEST(CharStringTest, Concate1)
{
	const jinstl::String str1{ "abc" };
	const jinstl::String str2{ "defghijklmn" };

	const jinstl::String ConcatedString = str1 + str2;
	EXPECT_EQ(ConcatedString[0], 'a');
	EXPECT_EQ(ConcatedString[1], 'b');
	EXPECT_EQ(ConcatedString[2], 'c');
	EXPECT_EQ(ConcatedString[3], 'd');
	EXPECT_EQ(ConcatedString[4], 'e');
	EXPECT_EQ(ConcatedString[5], 'f');
	EXPECT_EQ(ConcatedString[6], 'g');
	EXPECT_EQ(ConcatedString[7], 'h');
	EXPECT_EQ(ConcatedString[8], 'i');
	EXPECT_EQ(ConcatedString[9], 'j');
	EXPECT_EQ(ConcatedString[10], 'k');
	EXPECT_EQ(ConcatedString[11], 'l');
	EXPECT_EQ(ConcatedString[12], 'm');
	EXPECT_EQ(ConcatedString[13], 'n');
	EXPECT_EQ(ConcatedString.Length(), 14);
}

TEST(CharStringTest, Concate2)
{
	const jinstl::String str1{ "abc" };
	const jinstl::String str2{ };

	const jinstl::String ConcatedString = str1 + str2;
	EXPECT_EQ(ConcatedString[0], 'a');
	EXPECT_EQ(ConcatedString[1], 'b');
	EXPECT_EQ(ConcatedString[2], 'c');
	EXPECT_EQ(ConcatedString.Length(), 3);
}