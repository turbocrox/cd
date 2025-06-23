#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include <vector>
#include <string>

class Optimizer {
public:
    Optimizer(const std::vector<std::string>& tac);
    std::vector<std::string> optimize();
private:
    std::vector<std::string> tac;
    bool is_control_or_label(const std::string& line) const;
    std::vector<std::string> constant_folding(const std::vector<std::string>& code) const;
    std::vector<std::string> algebraic_simplification(const std::vector<std::string>& code) const;
    std::vector<std::string> common_subexpression_elimination(const std::vector<std::string>& code) const;
    std::vector<std::string> advanced_loop_invariant_code_motion(const std::vector<std::string>& code) const;
    std::vector<std::string> remove_useless_assignments(const std::vector<std::string>& code) const;
    std::vector<std::string> strength_reduction(const std::vector<std::string>& code) const;
    std::vector<std::string> induction_variable_elimination(const std::vector<std::string>& code) const;
    std::vector<std::string> full_dead_code_elimination(const std::vector<std::string>& code) const;
    std::vector<std::string> remove_redundant_copies(const std::vector<std::string>& code) const;
    std::vector<std::string> constant_propagation_and_folding(const std::vector<std::string>& code) const;
    std::vector<std::string> induction_variable_simplification(const std::vector<std::string>& code) const;
    std::vector<std::string> loop_unrolling(const std::vector<std::string>& code) const;
};

#endif // OPTIMIZER_H 