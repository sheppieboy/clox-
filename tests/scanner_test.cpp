#include <gtest/gtest.h>
#include "Scanner.hpp"
#include "Token.hpp"

TEST(ScannerTest, SingleCharTokens)
{
    std::string source = "(){},.-+;/*";
    Scanner scanner{source};
    auto tokens = scanner.scanTokens();

    ASSERT_EQ(tokens.size(), 12);
    EXPECT_EQ(tokens[0].getType(), LEFT_PAREN);
    EXPECT_EQ(tokens[1].getType(), RIGHT_PAREN);
    EXPECT_EQ(tokens[2].getType(), LEFT_BRACE);
    EXPECT_EQ(tokens[3].getType(), RIGHT_BRACE);
    EXPECT_EQ(tokens[4].getType(), COMMA);
    EXPECT_EQ(tokens[5].getType(), DOT);
    EXPECT_EQ(tokens[6].getType(), MINUS);
    EXPECT_EQ(tokens[7].getType(), PLUS);
    EXPECT_EQ(tokens[8].getType(), SEMICOLON);
    EXPECT_EQ(tokens[9].getType(), SLASH);
    EXPECT_EQ(tokens[10].getType(), STAR);
    EXPECT_EQ(tokens[11].getType(), END);
}

TEST(ScannerTest, Comments)
{
  Scanner scanner{"//this is a comment"};
  auto tokens = scanner.scanTokens();
  ASSERT_EQ(tokens.size(), 2);
  ASSERT_EQ(tokens[0].getType(), COMMENT);
}

TEST(Scanner, SingleCharAndComment)
{
  std::string source = "(){} //comment is here";
  Scanner scanner{source};
  auto tokens = scanner.scanTokens();
  ASSERT_EQ(tokens.size(), 6);
  EXPECT_EQ(tokens[0].getType(), LEFT_PAREN);
  EXPECT_EQ(tokens[1].getType(), RIGHT_PAREN);
  EXPECT_EQ(tokens[2].getType(), LEFT_BRACE);
  EXPECT_EQ(tokens[3].getType(), RIGHT_BRACE);
  EXPECT_EQ(tokens[4].getType(), COMMENT);
  EXPECT_EQ(tokens[5].getType(), END);
}

