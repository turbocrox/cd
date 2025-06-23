#include "Parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens_)
    : tokens(tokens_), pos(0), current_token(tokens.empty() ? Token("", "", 0) : tokens[0]) {}

void Parser::advance() {
    pos++;
    if (pos < tokens.size())
        current_token = tokens[pos];
    else
        current_token = Token("", "", 0);
}

void Parser::eat(const std::string& token_type) {
    if (!current_token.type.empty() && current_token.type == token_type) {
        advance();
    } else {
        throw std::runtime_error("Expected " + token_type + ", got " + current_token.type);
    }
}

std::shared_ptr<ASTNode> Parser::parse() {
    if (!current_token.type.empty() && current_token.type == "INT") {
        return function_def();
    } else {
        return program();
    }
}

std::shared_ptr<ASTNode> Parser::function_def() {
    eat("INT");
    std::string func_name = current_token.value;
    eat("ID");
    eat("LPAREN");
    eat("RPAREN");
    eat("LBRACE");
    std::vector<std::shared_ptr<ASTNode>> body;
    while (!current_token.type.empty() && current_token.type != "RBRACE") {
        if (current_token.type == "ID" || current_token.type == "WHILE" || current_token.type == "IF" || current_token.type == "FOR" || current_token.type == "INT" || current_token.type == "RETURN") {
            body.push_back(statement());
        } else {
            advance();
        }
    }
    eat("RBRACE");
    return std::make_shared<ASTNode>("FUNCTION", func_name, body);
}

std::shared_ptr<ASTNode> Parser::program() {
    std::vector<std::shared_ptr<ASTNode>> stmts;
    while (!current_token.type.empty()) {
        if (current_token.type == "ID" || current_token.type == "WHILE" || current_token.type == "IF" || current_token.type == "FOR" || current_token.type == "INT" || current_token.type == "RETURN") {
            stmts.push_back(statement());
        } else {
            advance();
        }
    }
    return std::make_shared<ASTNode>("PROGRAM", "", stmts);
}

std::shared_ptr<ASTNode> Parser::statement() {
    if (current_token.type == "INT") {
        return declaration();
    } else if (current_token.type == "ID") {
        auto node = assignment();
        eat("END");
        return node;
    } else if (current_token.type == "WHILE") {
        return while_stmt();
    } else if (current_token.type == "FOR") {
        return for_stmt();
    } else if (current_token.type == "IF") {
        return if_stmt();
    } else if (current_token.type == "RETURN") {
        return return_stmt();
    } else {
        throw std::runtime_error("Invalid statement at " + current_token.type);
    }
}

std::shared_ptr<ASTNode> Parser::declaration() {
    eat("INT");
    std::string var = current_token.value;
    eat("ID");
    if (!current_token.type.empty() && current_token.type == "ASSIGN") {
        eat("ASSIGN");
        auto expr_node = expr();
        eat("END");
        return std::make_shared<ASTNode>("DECL", var, std::vector<std::shared_ptr<ASTNode>>{expr_node});
    } else {
        eat("END");
        return std::make_shared<ASTNode>("DECL", var);
    }
}

std::shared_ptr<ASTNode> Parser::for_stmt() {
    eat("FOR");
    eat("LPAREN");
    auto init = statement();
    auto cond = condition();
    eat("END");
    auto update = assignment();
    eat("RPAREN");
    eat("LBRACE");
    std::vector<std::shared_ptr<ASTNode>> body;
    while (!current_token.type.empty() && current_token.type != "RBRACE") {
        if (current_token.type == "ID" || current_token.type == "WHILE" || current_token.type == "IF" || current_token.type == "FOR" || current_token.type == "INT" || current_token.type == "RETURN") {
            body.push_back(statement());
        } else {
            advance();
        }
    }
    eat("RBRACE");
    body.push_back(update);
    return std::make_shared<ASTNode>("FOR", "", std::vector<std::shared_ptr<ASTNode>>{init, std::make_shared<ASTNode>("WHILE", "", std::vector<std::shared_ptr<ASTNode>>{cond, std::make_shared<ASTNode>("BODY", "", body)})});
}

std::shared_ptr<ASTNode> Parser::return_stmt() {
    eat("RETURN");
    auto expr_node = expr();
    eat("END");
    return std::make_shared<ASTNode>("RETURN", "", std::vector<std::shared_ptr<ASTNode>>{expr_node});
}

std::shared_ptr<ASTNode> Parser::while_stmt() {
    eat("WHILE");
    eat("LPAREN");
    auto cond = condition();
    eat("RPAREN");
    eat("LBRACE");
    std::vector<std::shared_ptr<ASTNode>> body;
    while (!current_token.type.empty() && current_token.type != "RBRACE") {
        if (current_token.type == "ID" || current_token.type == "WHILE" || current_token.type == "IF" || current_token.type == "FOR" || current_token.type == "INT" || current_token.type == "RETURN") {
            body.push_back(statement());
        } else {
            advance();
        }
    }
    eat("RBRACE");
    return std::make_shared<ASTNode>("WHILE", "", std::vector<std::shared_ptr<ASTNode>>{cond, std::make_shared<ASTNode>("BODY", "", body)});
}

std::shared_ptr<ASTNode> Parser::if_stmt() {
    eat("IF");
    eat("LPAREN");
    auto cond = condition();
    eat("RPAREN");
    eat("LBRACE");
    std::vector<std::shared_ptr<ASTNode>> then_body;
    while (!current_token.type.empty() && current_token.type != "RBRACE") {
        if (current_token.type == "ID" || current_token.type == "WHILE" || current_token.type == "IF" || current_token.type == "FOR" || current_token.type == "INT" || current_token.type == "RETURN") {
            then_body.push_back(statement());
        } else {
            advance();
        }
    }
    eat("RBRACE");
    std::vector<std::shared_ptr<ASTNode>> else_body;
    if (!current_token.type.empty() && current_token.type == "ELSE") {
        eat("ELSE");
        eat("LBRACE");
        while (!current_token.type.empty() && current_token.type != "RBRACE") {
            if (current_token.type == "ID" || current_token.type == "WHILE" || current_token.type == "IF" || current_token.type == "FOR" || current_token.type == "INT" || current_token.type == "RETURN") {
                else_body.push_back(statement());
            } else {
                advance();
            }
        }
        eat("RBRACE");
    }
    return std::make_shared<ASTNode>("IF", "", std::vector<std::shared_ptr<ASTNode>>{
        cond,
        std::make_shared<ASTNode>("THEN", "", then_body),
        std::make_shared<ASTNode>("ELSE", "", else_body)
    });
}

std::shared_ptr<ASTNode> Parser::condition() {
    auto left = expr();
    if (!current_token.type.empty() && (current_token.type == "LT" || current_token.type == "GT" || current_token.type == "LE" || current_token.type == "GE" || current_token.type == "EQ" || current_token.type == "NE")) {
        std::string op = current_token.type;
        eat(op);
        auto right = expr();
        return std::make_shared<ASTNode>("RELOP", op, std::vector<std::shared_ptr<ASTNode>>{left, right});
    } else {
        return left;
    }
}

std::shared_ptr<ASTNode> Parser::expr() {
    auto node = term();
    while (!current_token.type.empty() && current_token.type == "OP" && (current_token.value == "+" || current_token.value == "-")) {
        std::string op = current_token.value;
        eat("OP");
        node = std::make_shared<ASTNode>("BINOP", op, std::vector<std::shared_ptr<ASTNode>>{node, term()});
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::term() {
    auto node = factor();
    while (!current_token.type.empty() && current_token.type == "OP" && (current_token.value == "*" || current_token.value == "/")) {
        std::string op = current_token.value;
        eat("OP");
        node = std::make_shared<ASTNode>("BINOP", op, std::vector<std::shared_ptr<ASTNode>>{node, factor()});
    }
    return node;
}

std::shared_ptr<ASTNode> Parser::factor() {
    Token token = current_token;
    if (token.type == "NUMBER") {
        eat("NUMBER");
        return std::make_shared<ASTNode>("NUMBER", token.value);
    } else if (token.type == "ID") {
        eat("ID");
        return std::make_shared<ASTNode>("ID", token.value);
    } else if (token.type == "LPAREN") {
        eat("LPAREN");
        auto node = expr();
        eat("RPAREN");
        return node;
    } else {
        throw std::runtime_error("Invalid factor at " + token.type);
    }
}

std::shared_ptr<ASTNode> Parser::assignment() {
    std::string var = current_token.value;
    eat("ID");
    eat("ASSIGN");
    auto expr_node = expr();
    return std::make_shared<ASTNode>("ASSIGN", var, std::vector<std::shared_ptr<ASTNode>>{expr_node});
} 