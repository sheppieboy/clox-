#include <string>
#include <vector>
#include "Token.h"

class Scanner
{
private:
    const std::string source;
    unsigned int start = 0;
    unsigned int current = 0;
    unsigned int line = 1;
    std::vector<lox::Token> tokens = std::vector<lox::Token>();

    bool isAtEnd() const;

    void scanToken();

public:
    explicit Scanner(std::string source);

    std::vector<lox::Token>& scanTokens();
};