#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <string>
#include <unordered_map>

class SymbolTable {
public:
    std::unordered_map<std::string, std::string> table;
    SymbolTable() = default;
    std::string repr() const;
};

#endif // SYMBOLTABLE_H 