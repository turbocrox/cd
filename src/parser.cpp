#include "parser.hpp"
#include <stdexcept>
#include <iostream>

char Parser::peek() const {
    return pos < source.length() ? source[pos] : '\0';
}

char Parser::advance() {
    return pos < source.length() ? source[pos++] : '\0';
}

void Parser::skipWhitespace() {
    while (peek() == ' ' || peek() == '\t' || peek() == '\n' || peek() == '\r') {
        advance();
    }
}
bool Parser::match(char expected) {
    if (peek() == expected) {
        advance();
        return true;
    }
    return false;
}

bool Parser::isDigit(char c) const {
    return c >= '0' && c <= '9';
}

bool Parser::isAlpha(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Parser::isAlphaNumeric(char c) const {
    return isAlpha(c) || isDigit(c);
}

std::string Parser::parseIdentifier() {
    std::string result;
    while (isAlphaNumeric(peek())) {
        result += advance();
    }
    return result;
}

int Parser::parseNumber() {
    int result = 0;
    while (isDigit(peek())) {
        result = result * 10 + (advance() - '0');
    }
    return result;
}
.ExpressionPtr Parser::parseFactor() {
    skipWhitespace();
    if (isDigit(peek())) {
        return std::make_shared<Constant>(parseNumber());
    } else if (peek() == '(') {
        advance();
        auto expr = parseExpression();
        if (!match(')')) {
            throw std::runtime_error("Expected ')'");
        }
        return expr;
    } else if (isAlpha(peek())) {
        return std::make_shared<VariableReference>(parseIdentifier());
    }
    throw std::runtime_error("Unexpected token in factor: " + std::string(1, peek()));
}