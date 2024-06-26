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
        case '/':
            if(match('/'))
            {
                while(peek() != '\n' && !isAtEnd()) 
                {
                    advance();
                }
                addToken(COMMENT);
            }
            else addToken(SLASH);
            break;
        case '\r':
        case '\t':
        case ' ':
            break;
        case '\n':
            line++;
            break;
        case '"':
            string();
            break;
    }
}

std::string_view Scanner::getSubStringView() const
{   
    return std::string_view(source).substr(start, current-start);
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

char Scanner::peek() const
{
    if(isAtEnd()) return '\0';
    return source[current];
}

void Scanner::string()
{   
    //break condition is ending " or end of file
    while(peek() != '"' && !isAtEnd())
    {
        if(peek() == '\n') line++;
        advance();
    }

    //the string does not have a closing ", exit early and report error
    if(isAtEnd())
    {
        //add error reporting
        return;

    }

    // closing "
    advance();


    //trim quotes
    std::string_view string_value = (source).substr(start + 1, current - 1);
    //add token
    addToken(STRING, string_value);
}

bool Scanner::isDigit(char c) const 
{
    return c >= '0' && c <= '9';
}

char Scanner::peekNext() const
{
    if(current + 1 >= source.length()) return '\0';
    return source[current+1];
}

void Scanner::number()
{
    while(isDigit(peek())) advance();

    //check for fraction
    if(peek() == '.'  && isDigit(peekNext()))
    {   
        //consume the '.';
        advance();

        while(isDigit(peek())) advance();
    }

    addToken(NUMBER);
}

void Scanner::identifier()
{
    while(isAlphaNumeric(peek())) advance();
    addToken(IDENTIFIER);
}

bool Scanner::isAlpha(char c) const
{
    return ( c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphaNumeric(char c) const
{
    return isAlpha(c) || isDigit(c);
}
