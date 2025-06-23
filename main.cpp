#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Lexer.h"
#include "Parser.h"
#include "SemanticAnalyzer.h"
#include "TACGenerator.h"
#include "Optimizer.h"
#include "utils.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./compiler <input_code.txt>" << endl;
        return 1;
    }
    string input_file = argv[1];

    // Lexical Analysis
    Lexer lexer(input_file);
    vector<Token> tokens = lexer.tokenize();
    vector<string> token_strs;
    for (const auto& t : tokens) token_strs.push_back(t.repr());
    write_to_file("tokens.txt", token_strs);

    // Syntax Analysis
    Parser parser(tokens);
    auto parse_tree = parser.parse();
    write_to_file("parse_tree.txt", parse_tree->repr());

    // Semantic Analysis
    SemanticAnalyzer semantic_analyzer(parse_tree);
    SymbolTable symbol_table = semantic_analyzer.analyze();
    write_to_file("symbol_table.txt", symbol_table.repr());

    // Intermediate Code Generation
    TACGenerator tac_generator(parse_tree, symbol_table);
    vector<string> tac = tac_generator.generate();
    cout << "TAC generated:" << endl;
    for (const auto& line : tac) cout << line << endl;
    write_to_file("tac.txt", tac);

    // Code Optimization
    Optimizer optimizer(tac);
    vector<string> optimized_code = optimizer.optimize();
    cout << "Optimized code:" << endl;
    for (const auto& line : optimized_code) cout << line << endl;
    cout << "[DIRECT WRITE] Writing to optimized_output.txt:" << endl;
    for (const auto& line : optimized_code) cout << line << endl;
    write_to_file("optimized_output.txt", optimized_code);
    cout << "[DIRECT WRITE] Done writing optimized_output.txt" << endl;

    cout << "Compilation complete. Outputs generated:" << endl;
    cout << "tokens.txt, parse_tree.txt, symbol_table.txt, tac.txt, optimized_output.txt" << endl;
    return 0;
} 