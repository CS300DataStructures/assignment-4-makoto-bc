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

TEST(SLLString, findSubstring) {
	struct Test {
		SLLString s;
		SLLString substring;
		int expected;
	};

	std::vector<Test> tests {
		{ // 0
			{""},
			{""},
			0,
		},
		{ // 1
			{"a"},
			{""},
			0,
		},
		{ // 2
			{"a"},
			{"a"},
			0,
		},
		{ // 3
			{""},
			{"a"},
			-1,
		},
		{ // 4
			{"a"},
			{"b"},
			-1,
		},
		{ // 5
			{"aa"},
			{"a"},
			0,
		},
		{ // 6
			{"ab"},
			{"b"},
			1,
		},
		{ // 7
			{"abc"},
			{"c"},
			2,
		},
		{ // 8
			{"abc"},
			{"ab"},
			0,
		},
		{ // 9
			{"abc"},
			{"bc"},
			1,
		},
		{ // 10
			{"abc"},
			{"cd"},
			-1,
		},
		{ // 11
			{"abc"},
			{"ba"},
			-1,
		},
		{ // 12
			{"ab"},
			{""},
			0,
		},
		{ // 13
			{""},
			{"ab"},
			-1,
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		EXPECT_EQ(tests[i].s.findSubstring(tests[i].substring), tests[i].expected) << i;
	}
}

TEST(SLLString, remove) {
	struct Test {
		SLLString s;
		size_t index;
		SLLString expected;
	};

	std::vector<Test> tests {
		{
			{"a"},
			0,
			{""},
		},
		{
			{"ab"},
			0,
			{"b"},
		},
		{
			{"ab"},
			1,
			{"a"},
		},
	};

	for (size_t i = 0; i < tests.size(); ++i) {
		tests[i].s.remove(tests[i].index);
		EXPECT_EQ(tests[i].s, tests[i].expected) << i;
	}

	EXPECT_THROW(SLLString().remove(0), std::out_of_range);
	EXPECT_THROW(SLLString("a").remove(2), std::out_of_range);
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