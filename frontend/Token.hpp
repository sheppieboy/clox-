#pragma once
#include <string>
#include <variant>


enum TokenType
{
    //Single-char tokens
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    //one, or two char tokens
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    COMMENT,

    //literal
    IDENTIFIER,
    STRING,
    NUMBER,

    //keywords,
    AND,
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,

    END
};

using TokenLiteral = std::variant<std::string_view, double, bool, std::nullptr_t>;

class Token
{
private:
    TokenType type;
    std::string_view lexeme;
    TokenLiteral literal;
    unsigned int line;
public:
    explicit Token(const TokenType& type, const std::string_view& lexeme, const TokenLiteral& literal, const unsigned int& line)
    : type{type}, lexeme{lexeme}, literal{literal}, line{line}
    {}

    const TokenType& getType() const
    {
        return type;
    }

    const std::string_view getLexeme() const
    {
        return lexeme;
    }

    //inexpensive to copy as the TokenLiteral is either string_view, double, bool, nullptr
    const TokenLiteral getTokenLiteral()
    {
        return literal;
    }

    const unsigned int getLine()
    {
        return line;
    }
};

