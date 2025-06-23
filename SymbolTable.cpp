#include "SymbolTable.h"
#include <sstream>
using namespace std;

string SymbolTable::repr() const {
    ostringstream oss;
    oss << "{";
    bool first = true;
    for (const auto& kv : table) {
        if (!first) oss << ", ";
        oss << kv.first << ": " << kv.second;
        first = false;
    }
    oss << "}";
    return oss.str();
} 