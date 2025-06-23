#ifndef SEMANTICANALYZER_H
#define SEMANTICANALYZER_H
#include "ASTNode.h"
#include "SymbolTable.h"
#include <memory>

class SemanticAnalyzer {
public:
    SemanticAnalyzer(const std::shared_ptr<ASTNode>& parse_tree);
    SymbolTable analyze();
private:
    std::shared_ptr<ASTNode> parse_tree;
    SymbolTable symbol_table;
    void visit(const std::shared_ptr<ASTNode>& node);
};

#endif // SEMANTICANALYZER_H 