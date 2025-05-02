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
