#include "ASTNode.h"
#include <sstream>
using namespace std;

string ASTNode::repr() const {
    ostringstream oss;
    oss << "ASTNode(" << type << ", " << value << ", [";
    for (size_t i = 0; i < children.size(); ++i) {
        if (children[i]) oss << children[i]->repr();
        if (i + 1 < children.size()) oss << ", ";
    }
    oss << "] )";
    return oss.str();
} 