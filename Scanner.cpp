#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include "Scanner.h"

Scanner::Scanner(std::string source) : source{std::move(source)}
{}

std::vector<lox::Token>& Scanner::scanTokens()
{
   while(!isAtEnd())
   {
        start = current;
        scanToken();
   }
//    tokens.emplace_back(EOF, "", , line);
    return tokens;
}

bool Scanner::isAtEnd() const 
{
    return current >= source.length();
}

void scanToken()
{
    // switch(const char c = advance())
    // {
    //     case '(':
    //     case ')':
    //     case '{':
    //     case '}':
    //     case ',':
    //     case '.':
    //     case '_':
    //     case '+':
    //     case ';':
    //     case '/':
    //     case '*':
    // }
}
