#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <memory>
#include <string>
#include "Token.h"
#include "ASTNode.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::shared_ptr<ASTNode> parse();
private:
    std::vector<Token> tokens;
    size_t pos;
    Token current_token;
    void eat(const std::string& token_type);
    std::shared_ptr<ASTNode> function_def();
    std::shared_ptr<ASTNode> program();
    std::shared_ptr<ASTNode> statement();
    std::shared_ptr<ASTNode> declaration();
    std::shared_ptr<ASTNode> for_stmt();
    std::shared_ptr<ASTNode> return_stmt();
    std::shared_ptr<ASTNode> while_stmt();
    std::shared_ptr<ASTNode> if_stmt();
    std::shared_ptr<ASTNode> condition();
    std::shared_ptr<ASTNode> expr();
    std::shared_ptr<ASTNode> term();
    std::shared_ptr<ASTNode> factor();
    std::shared_ptr<ASTNode> assignment();
    void advance();
};

#endif // PARSER_H 