#include "SemanticAnalyzer.h"
#include <iostream>

SemanticAnalyzer::SemanticAnalyzer(const std::shared_ptr<ASTNode>& parse_tree_)
    : parse_tree(parse_tree_) {}

SymbolTable SemanticAnalyzer::analyze() {
    visit(parse_tree);
    return symbol_table;
}

void SemanticAnalyzer::visit(const std::shared_ptr<ASTNode>& node) {
    if (!node) return;
    if (node->type == "FUNCTION") {
        for (const auto& child : node->children) {
            visit(child);
        }
    } else if (node->type == "PROGRAM") {
        for (const auto& child : node->children) {
            visit(child);
        }
    } else if (node->type == "DECL") {
        std::string var = node->value;
        if (!node->children.empty()) {
            visit(node->children[0]);
        }
        symbol_table.table[var] = "int";
    } else if (node->type == "ASSIGN") {
        std::string var = node->value;
        auto expr = node->children[0];
        visit(expr);
        symbol_table.table[var] = "int"; // Assume all variables are int
    } else if (node->type == "BINOP") {
        visit(node->children[0]);
        visit(node->children[1]);
    } else if (node->type == "RELOP") {
        visit(node->children[0]);
        visit(node->children[1]);
    } else if (node->type == "WHILE" || node->type == "IF" || node->type == "FOR") {
        for (const auto& child : node->children) {
            visit(child);
        }
    } else if (node->type == "BODY" || node->type == "THEN" || node->type == "ELSE") {
        for (const auto& child : node->children) {
            visit(child);
        }
    } else if (node->type == "RETURN") {
        visit(node->children[0]);
    } else if (node->type == "NUMBER" || node->type == "ID") {
        // Nothing to do for leaves
    } else {
        std::cout << "[SemanticAnalyzer] Unhandled node type: " << node->type << std::endl;
    }
} 