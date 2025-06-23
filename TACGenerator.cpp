#include "TACGenerator.h"
#include <iostream>
using namespace std;

TACGenerator::TACGenerator(const shared_ptr<ASTNode>& parse_tree_, const SymbolTable& symbol_table_)
    : parse_tree(parse_tree_), symbol_table(symbol_table_), temp_count(0), label_count(0) {}

string TACGenerator::new_temp() {
    temp_count++;
    return "t" + to_string(temp_count);
}

string TACGenerator::new_label() {
    label_count++;
    return "L" + to_string(label_count);
}

vector<string> TACGenerator::generate() {
    visit(parse_tree);
    return tac;
}

string TACGenerator::visit(const shared_ptr<ASTNode>& node) {
    if (!node) return "";
    if (node->type == "FUNCTION") {
        tac.push_back("function " + node->value + ":");
        for (const auto& child : node->children) {
            visit(child);
        }
        tac.push_back("end function " + node->value);
    } else if (node->type == "PROGRAM") {
        for (const auto& child : node->children) {
            visit(child);
        }
    } else if (node->type == "DECL") {
        string var = node->value;
        if (!node->children.empty()) {
            string res = visit(node->children[0]);
            tac.push_back(var + " = " + res);
        }
    } else if (node->type == "ASSIGN") {
        string var = node->value;
        auto expr = node->children[0];
        string res = visit(expr);
        tac.push_back(var + " = " + res);
    } else if (node->type == "BINOP") {
        string left = visit(node->children[0]);
        string right = visit(node->children[1]);
        string temp = new_temp();
        tac.push_back(temp + " = " + left + " " + node->value + " " + right);
        return temp;
    } else if (node->type == "RELOP") {
        string left = visit(node->children[0]);
        string right = visit(node->children[1]);
        string temp = new_temp();
        tac.push_back(temp + " = " + left + " " + node->value + " " + right);
        return temp;
    } else if (node->type == "WHILE") {
        string start_label = new_label();
        string end_label = new_label();
        tac.push_back(start_label + ":");
        string cond = visit(node->children[0]);
        tac.push_back("ifFalse " + cond + " goto " + end_label);
        if (node->children[1]->type == "BODY") {
            for (const auto& stmt : node->children[1]->children) {
                visit(stmt);
            }
        } else {
            visit(node->children[1]);
        }
        tac.push_back("goto " + start_label);
        tac.push_back(end_label + ":");
    } else if (node->type == "FOR") {
        visit(node->children[0]); // init
        visit(node->children[1]); // desugared while
    } else if (node->type == "IF") {
        string else_label = new_label();
        string end_label = new_label();
        string cond = visit(node->children[0]);
        tac.push_back("ifFalse " + cond + " goto " + else_label);
        visit(node->children[1]); // THEN
        tac.push_back("goto " + end_label);
        tac.push_back(else_label + ":");
        visit(node->children[2]); // ELSE
        tac.push_back(end_label + ":");
    } else if (node->type == "BODY" || node->type == "THEN" || node->type == "ELSE") {
        for (const auto& child : node->children) {
            visit(child);
        }
    } else if (node->type == "RETURN") {
        string res = visit(node->children[0]);
        tac.push_back("return " + res);
    } else if (node->type == "NUMBER" || node->type == "ID") {
        return node->value;
    } else {
        cout << "[TACGenerator] Unhandled node type: " << node->type << endl;
    }
    return "";
} 