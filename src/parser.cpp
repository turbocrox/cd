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