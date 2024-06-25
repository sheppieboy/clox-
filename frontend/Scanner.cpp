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
   tokens.emplace_back(END, "", nullptr , line);
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
            addToken(LEFT_PAREN);
            break;
        case ')':
            addToken(RIGHT_PAREN);
            break;
        case '{':
            addToken(LEFT_BRACE);
            break;
        case '}':
            addToken(RIGHT_BRACE);
            break;
        case ',':
            addToken(COMMA);
            break;
        case '.':
            addToken(DOT);
            break;
        case '-':
            addToken(MINUS);
            break;
        case '+':
            addToken(PLUS);
            break;
        case ';':
            addToken(SEMICOLON);
            break;
        case '/':
            addToken(SLASH);
            break;
        case '*':
            addToken(STAR);
            break;
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
    }
}

std::string_view Scanner::getSubStringView()
{   
    return std::string_view(source).substr(start, current);
}

char Scanner::advance()
{
    return source[current++];
}

void Scanner::addToken(const TokenType& type)
{
    addToken(type, nullptr);
}

void Scanner::addToken(const TokenType& type, const TokenLiteral& literal)
{
    std::string_view lexeme = getSubStringView();
    tokens.emplace_back(type, lexeme, literal, line);
}

bool Scanner::match(char expected)
{
    if(isAtEnd()) return false;
    if(source[current] != expected) return false;

    current++;
    return true;
}

