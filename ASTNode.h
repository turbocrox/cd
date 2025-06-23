#ifndef ASTNODE_H
#define ASTNODE_H
#include <string>
#include <vector>
#include <memory>

class ASTNode {
public:
    std::string type;
    std::string value;
    std::vector<std::shared_ptr<ASTNode>> children;
    ASTNode(const std::string& type_, const std::string& value_ = "", const std::vector<std::shared_ptr<ASTNode>>& children_ = {})
        : type(type_), value(value_), children(children_) {}
    std::string repr() const;
};

#endif // ASTNODE_H 