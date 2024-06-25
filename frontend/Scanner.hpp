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
    

public:
    explicit Scanner(std::string source);

    std::vector<Token>& scanTokens();

    std::string_view getSubStringView();
};
