#include <gtest/gtest.h>
#include "core/MessageParser.h"

TEST(MessageParserTest, ParsesCommandWithArguments)
{
        auto req = MessageParser::parse("WRITE file.txt;hello");

        ASSERT_TRUE(req.has_value());
        EXPECT_EQ(req->command, "WRITE");
        ASSERT_EQ(req->arguments.size(), 2);
        EXPECT_EQ(req->arguments[0], "file.txt");
        EXPECT_EQ(req->arguments[1], "hello");
}

TEST(MessageParserTest, ParsesCommandWithoutArguments)
{
        auto req = MessageParser::parse("READ");
        ASSERT_TRUE(req.has_value());
        EXPECT_EQ(req->command, "READ");
        EXPECT_TRUE(req->arguments.empty());
}

TEST(MessageParserTest, HandlesExtraWhitespace)
{
        auto req = MessageParser::parse("  WRITE   a.txt ;  hi  ");

        ASSERT_TRUE(req.has_value());
        EXPECT_EQ(req->command, "WRITE");
        ASSERT_EQ(req->arguments.size(), 2);
        EXPECT_EQ(req->arguments[0], "a.txt");
        EXPECT_EQ(req->arguments[1], "hi");
}

