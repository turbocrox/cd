#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>
#include "Token.h"

class Lexer {
public:
    Lexer(const std::string& filename);
    std::vector<Token> tokenize();
private:
    std::string code;
    int current_line;
    std::vector<Token> tokens;
    void strip_comments();
};

#endif // LEXER_H 