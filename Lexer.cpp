#include "Lexer.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>
using namespace std;

Lexer::Lexer(const string& filename) : current_line(1) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Cannot open file: " + filename);
    }
    ostringstream ss;
    string line;
    while (getline(file, line)) {
        size_t pos = line.find("//");
        if (pos != string::npos) line = line.substr(0, pos);
        pos = line.find('#');
        if (pos != string::npos) line = line.substr(0, pos);
        ss << line << '\n';
    }
    code = ss.str();
}

vector<Token> Lexer::tokenize() {
    vector<pair<string, string> > token_specification = {
        make_pair("FOR",      "for"),
        make_pair("WHILE",    "while"),
        make_pair("IF",       "if"),
        make_pair("ELSE",     "else"),
        make_pair("INT",      "int"),
        make_pair("RETURN",   "return"),
        make_pair("NUMBER",   "\\d+"),
        make_pair("ID",       "[A-Za-z_]\\w*"),
        make_pair("ASSIGN",   "="),
        make_pair("END",      ";"),
        make_pair("COMMA",    ","),
        make_pair("OP",       "[-+*/]"),
        make_pair("LPAREN",   "\\("),
        make_pair("RPAREN",   "\\)"),
        make_pair("LBRACE",   "\\{"),
        make_pair("RBRACE",   "\\}"),
        make_pair("LE",       "<="),
        make_pair("GE",       ">="),
        make_pair("EQ",       "=="),
        make_pair("NE",       "!="),
        make_pair("LT",       "<"),
        make_pair("GT",       ">"),
        make_pair("SKIP",     "[ \\t]+"),
        make_pair("NEWLINE",  "\\n"),
        make_pair("MISMATCH", ".")
    };
    string::size_type pos = 0;
    while (pos < code.size()) {
        bool matched = false;
        for (size_t i = 0; i < token_specification.size(); ++i) {
            regex pattern("^" + token_specification[i].second);
            smatch m;
            string remaining = code.substr(pos);
            if (regex_search(remaining, m, pattern)) {
                if (m.position() == 0) {
                    string kind = token_specification[i].first;
                    string value = m.str();
                    if (kind == "NEWLINE") {
                        current_line++;
                    } else if (kind == "SKIP") {
                        // skip
                    } else if (kind == "MISMATCH") {
                        throw runtime_error("Unexpected character '" + value + "' on line " + to_string(current_line));
                    } else {
                        tokens.emplace_back(kind, value, current_line);
                    }
                    pos += m.length();
                    matched = true;
                    break;
                }
            }
        }
        if (!matched) {
            throw runtime_error("Lexer error at position " + to_string(pos));
        }
    }
    return tokens;
} 