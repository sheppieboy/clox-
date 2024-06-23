#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include "Scanner.hpp"

Scanner::Scanner(std::string source) : source{std::move(source)}
{}

std::vector<Token>& Scanner::scanTokens()
{
   while(!isAtEnd())
   {
        start = current;
        scanToken();
   }
//    tokens.emplace_back(EOF, "", nullptr , line);
   return tokens;
}

bool Scanner::isAtEnd() const 
{
    return current >= source.length();
}

void Scanner::scanToken()
{
    switch(const char c = advance())
    {
        case '(':
        case ')':
        case '{':
        case '}':
        case ',':
        case '.':
        case '_':
        case '+':
        case ';':
        case '/':
        case '*':
    }
}

char Scanner::advance()
{
    return '(';
}

// void Scanner::addToken(const TokenType& type)
// {
//     addToken(type, nullptr);
// }

// void Scanner::addToken(const TokenType& type, const TokenLiteral& literal)
// {

// }

