#include <gtest/gtest.h>
#include "Scanner.hpp"
#include "Token.hpp"

TEST(ScannerTest, SingleCharTokens)
{
    std::string source = "(){},.-+;/*";
    Scanner scanner{source};
    // auto tokens = scanner.scanTokens();

    std::string_view text = scanner.getSubStringView();

    EXPECT_EQ(text, "(){},");

}

// ASSERT_EQ(tokens.size(), 11);
    // EXPECT_EQ(tokens[0].getType(), LEFT_PAREN);
    // EXPECT_EQ(tokens[1].getType(), RIGHT_PAREN);
    // EXPECT_EQ(tokens[2].getType(), LEFT_BRACE);
    // EXPECT_EQ(tokens[3].getType(), RIGHT_BRACE);
