#include <gtest/gtest.h>
#include "../SLLString.h"

TEST(SLLString, stringConstructorAndInsert) {
	{
		SLLString str;
		EXPECT_EQ(str, SLLString(""));
		EXPECT_THROW(str.insert(1, 'a'), std::out_of_range);
	}
	{
		SLLString str;
		str.insert(0, 'a');
		EXPECT_EQ(str, SLLString("a"));
	}
	{
		SLLString str;
		str.insert(0, 'a');
		str.insert(1, 'b');
		EXPECT_EQ(str, SLLString("ab"));
	}
	{
		SLLString str;
		str.insert(0, 'a');
		str.insert(0, 'b');
		EXPECT_EQ(str, SLLString("ba"));
	}
	{
		SLLString str("ab");
		str.insert(1, 'c');
		EXPECT_EQ(str, SLLString("acb"));
	}
}

TEST(SLLString, copyConstructor) {
	{
		SLLString str;
		EXPECT_EQ(SLLString(str), SLLString());
	}
	{
		SLLString str("a");
		EXPECT_EQ(SLLString(str), SLLString("a"));
	}
	{
		SLLString str("ab");
		EXPECT_EQ(SLLString(str), SLLString("ab"));
	}
}

TEST(SLLString, moveConstructor) {
	SLLString original("a");
	SLLString newStr = std::move(original);
	EXPECT_EQ(newStr, SLLString("a"));
	EXPECT_EQ(original, SLLString()); // NOLINT(bugprone-use-after-move)
}

TEST(SLLString, nodeAt) {
	{
		SLLString s;
		EXPECT_THROW(s.nodeAt(0), std::out_of_range);
	}
	{
		SLLString s("a");
		EXPECT_EQ(s.nodeAt(0).value, 'a');
	}
	{
		SLLString s("ab");
		EXPECT_EQ(s.nodeAt(0).value, 'a');
		EXPECT_EQ(s.nodeAt(1).value, 'b');
	}
}

TEST(SLLString, getter) {
	{
		SLLString s;
		EXPECT_THROW(s[0], std::out_of_range);
	}
	{
		SLLString s("a");
		EXPECT_EQ(s[0], 'a');
	}
	{
		SLLString s("ab");
		EXPECT_EQ(s[0], 'a');
		EXPECT_EQ(s[1], 'b');
	}
}

TEST(SLLString, concatenate) {
	struct Test {
		SLLString a;
		SLLString b;
		SLLString expected;
	};

	std::vector<Test> tests {
		{
			{""},
			{""},
			{""},
		},
		{
			{"a"},
			{""},
			{"a"},
		},
		{
			{""},
			{"a"},
			{"a"},
		},
		{
			{"a"},
			{"b"},
			{"ab"},
		},
		{
			{"ab"},
			{"cd"},
			{"abcd"},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		tests[i].a += tests[i].b;
		EXPECT_EQ(tests[i].a, tests[i].expected) << i;
	}
}