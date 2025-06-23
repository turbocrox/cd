#ifndef TACGENERATOR_H
#define TACGENERATOR_H
#include "ASTNode.h"
#include "SymbolTable.h"
#include <vector>
#include <string>
#include <memory>

class TACGenerator {
public:
    TACGenerator(const std::shared_ptr<ASTNode>& parse_tree, const SymbolTable& symbol_table);
    std::vector<std::string> generate();
private:
    std::shared_ptr<ASTNode> parse_tree;
    SymbolTable symbol_table;
    std::vector<std::string> tac;
    int temp_count;
    int label_count;
    std::string new_temp();
    std::string new_label();
    std::string visit(const std::shared_ptr<ASTNode>& node);
};

#endif // TACGENERATOR_H 