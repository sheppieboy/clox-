#include <string>
#include <vector>
#include "Token.hpp"

class Scanner
{
private:
    const std::string source;
    unsigned int start = 0;
    unsigned int current = 0;
    unsigned int line = 1;
    std::vector<Token> tokens = std::vector<Token>();

    bool isAtEnd() const;

    void scanToken();

    char advance();

    void addToken(const TokenType& type);

    void addToken(const TokenType& type, const TokenLiteral& literal);

    bool match(char expected);

    char peek() const;

    std::string_view getSubStringView() const;

    void string();

    bool isDigit(char c) const;

    void number();

    char peekNext() const;

    void identifier();

    bool isAlpha(char c) const;

    bool isAlphaNumeric(char c) const;
    

public:
    explicit Scanner(std::string source);

    std::vector<Token>& scanTokens();

};
