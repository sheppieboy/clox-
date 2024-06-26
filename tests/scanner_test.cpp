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

TEST(Scanner, BasicString)
{
    std::string source = "\"hello\"";
    Scanner scanner{source};
    auto tokens = scanner.scanTokens();
    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0].getType(), STRING);
}

struct ScannerExpectedInput
{   
    std::string test_case;
    std::string source;
    std::vector<Token> expected;
};

void PrintTo(const ScannerExpectedInput& sei, std::ostream* os)
{
     *os << sei.test_case;
}

//test case: SingleCharTokens
ScannerExpectedInput singleCharTokens
{   
    "SingleCharTokens",
    "(){},.-+;/\n*",
    {
        Token(LEFT_PAREN, "(", nullptr, 1),
        Token(RIGHT_PAREN, ")", nullptr, 1),
        Token(LEFT_BRACE, "{", nullptr, 1),
        Token(RIGHT_BRACE, "}", nullptr, 1),
        Token(COMMA, ",", nullptr, 1),
        Token(DOT, ".", nullptr, 1),
        Token(MINUS, "-", nullptr, 1),
        Token(PLUS, "+", nullptr, 1),
        Token(SEMICOLON, ";", nullptr, 1),
        Token(SLASH, "/", nullptr, 1),
        Token(STAR, "*", nullptr, 2)
    },
};

//test case: Comments
ScannerExpectedInput onlyComments
{   
    "OnlyComments",
    "//this is a comment \n //another comment",
    {
        Token(COMMENT, "//", nullptr, 1),
        Token(COMMENT, "//", nullptr, 2),
    },

};

//test case: Comments & Tokens
ScannerExpectedInput commentsAndTokens
{   
    "CommentsAndTokens",
    "(){} //comment",
    {
        Token(LEFT_PAREN, "(", nullptr, 1),
        Token(RIGHT_PAREN, ")", nullptr, 1),
        Token(LEFT_BRACE, "{", nullptr, 1),
        Token(RIGHT_BRACE, "}", nullptr, 1),
        Token(COMMENT, "//", nullptr, 1),
    },
};

//test case: String Literals
ScannerExpectedInput stringLiterals
{
    "OnlyStringLiterals",
    "\"hello\" \"another\" \n \"last\"",
    {
        Token(STRING, "hello", "hello", 1),
        Token(STRING, "another", "another", 1),
        Token(STRING, "last", "last", 2),
    },
};

//test case: number literals
ScannerExpectedInput onlyNumbers
{
    "OnlyNumbers",
    "1234 67 \n 27.456",
    {
        Token(NUMBER, "1234", static_cast<double>(1234), 1),
        Token(NUMBER, "67", static_cast<double>(67), 1),
        Token(NUMBER, "27.456", static_cast<double>(27.456), 2),
    }
};

//test case: identifiers
ScannerExpectedInput identifiers
{
    "OnlyIdentifiers",
    "funcCall anotherFuncCall \n call _CALL funcCall", //contains a repeat
    {
        Token(IDENTIFIER, "funcCall", "funcCall", 1),
        Token(IDENTIFIER, "anotherFuncCall", "anotherFuncCall", 1),
        Token(IDENTIFIER, "call", "call", 1),
        Token(IDENTIFIER, "_CALL", "_CALL", 2)
        Token(IDENTIFIER, "funcCall", "funcCall", 2)
    }
};

//test case: keywords

//test case: identifiers and keywords

//test case: Combination of Tokens 1

//test case: Combination of Tokens 2

using ::testing::TestWithParam;
using ::testing::Values;

class ScannerTest : public TestWithParam<ScannerExpectedInput>
{
    protected:
        std::vector<Token> scanned;
        std::vector<Token> expected;
        Scanner* scanner;

        void SetUp() override
        {   
            ScannerExpectedInput input = GetParam();
            const std::string source = input.source;
            expected = input.expected;
            scanner = new Scanner(source);
            scanned = scanner->scanTokens();
        }

        void TearDown() override
        {
            delete scanner;
            scanner = nullptr;
        }
};

TEST_P(ScannerTest, CorrectTokenNumer)
{   
    ASSERT_EQ(scanned.size() - 1, expected.size());
}

TEST_P(ScannerTest, ValidTypesForTokens)
{
    EXPECT_EQ(scanned[0].getType(), expected[0].getType());
}


INSTANTIATE_TEST_SUITE_P(ScannerTestParameters, ScannerTest,
Values(
    singleCharTokens, onlyComments
    )
);