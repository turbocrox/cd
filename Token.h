#ifndef TOKEN_H
#define TOKEN_H
#include <string>

class Token {
public:
    std::string type;
    std::string value;
    int line;
    Token(const std::string& type_, const std::string& value_, int line_)
        : type(type_), value(value_), line(line_) {}
    std::string repr() const {
        return "Token(" + type + ", " + value + ", line=" + std::to_string(line) + ")";
    }
};

#endif // TOKEN_H 