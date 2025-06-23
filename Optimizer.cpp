#include "Optimizer.h"
#include <regex>
#include <unordered_map>
#include <set>

std::set<std::string> global_used_vars;

Optimizer::Optimizer(const std::vector<std::string>& tac_) : tac(tac_) {}

std::vector<std::string> Optimizer::optimize() {
    std::vector<std::string> code = tac;
    bool changed = true;
    int max_passes = 10; // Prevent infinite loops
    int pass = 0;
    while (changed && pass < max_passes) {
        changed = false;
        std::vector<std::string> prev = code;
        code = constant_propagation_and_folding(code);
        code = constant_folding(code);
        code = algebraic_simplification(code);
        code = strength_reduction(code);
        code = induction_variable_simplification(code);
        code = loop_unrolling(code);
        code = common_subexpression_elimination(code);
        code = advanced_loop_invariant_code_motion(code);
        code = remove_redundant_copies(code);
        code = induction_variable_elimination(code);
        code = full_dead_code_elimination(code);
        if (code != prev) changed = true;
        pass++;
    }
    return code;
}

bool Optimizer::is_control_or_label(const std::string& line) const {
    std::regex label_regex("^L\\d+:");
    return (
        line.find("function") == 0 ||
        line.find("end function") == 0 ||
        std::regex_search(line, label_regex) ||
        line.find("ifFalse") == 0 ||
        line.find("goto") == 0 ||
        line.find("return") == 0
    );
}

std::vector<std::string> Optimizer::constant_folding(const std::vector<std::string>& code) const {
    std::vector<std::string> new_code;
    std::regex re("(t\\d+) = (\\w+) ([-+*/]) (\\w+)");
    std::unordered_map<std::string, int> const_vals;
    for (const auto& line : code) {
        if (is_control_or_label(line)) {
            new_code.push_back(line);
            continue;
        }
        std::smatch m;
        if (std::regex_match(line, m, re)) {
            std::string t = m[1];
            std::string a = m[2];
            std::string op = m[3];
            std::string b = m[4];
            // Mark both operands as used for folding, always
            global_used_vars.insert(a);
            global_used_vars.insert(b);
            // Try to parse a and b as constants
            bool a_is_const = false, b_is_const = false;
            int a_val = 0, b_val = 0;
            try { a_val = std::stoi(a); a_is_const = true; } catch (...) {}
            try { b_val = std::stoi(b); b_is_const = true; } catch (...) {}
            if (a_is_const && b_is_const) {
                int v = 0;
                if (op == "+") v = a_val + b_val;
                else if (op == "-") v = a_val - b_val;
                else if (op == "*") v = a_val * b_val;
                else if (op == "/") v = (b_val != 0) ? a_val / b_val : 0;
                new_code.push_back(t + " = " + std::to_string(v));
                continue;
            }
            if (const_vals.count(a) && const_vals.count(b)) {
                int v = 0;
                if (op == "+") v = const_vals[a] + const_vals[b];
                else if (op == "-") v = const_vals[a] - const_vals[b];
                else if (op == "*") v = const_vals[a] * const_vals[b];
                else if (op == "/") v = (const_vals[b] != 0) ? const_vals[a] / const_vals[b] : 0;
                new_code.push_back(t + " = " + std::to_string(v));
                const_vals[t] = v;
                continue;
            }
        }
        std::regex assign_const("(\\w+) = (\\d+)");
        std::smatch m2;
        if (std::regex_match(line, m2, assign_const)) {
            const_vals[m2[1]] = std::stoi(m2[2]);
        }
        new_code.push_back(line);
    }
    return new_code;
}

std::vector<std::string> Optimizer::algebraic_simplification(const std::vector<std::string>& code) const {
    std::vector<std::string> new_code;
    std::regex mul1("(\\w+) = (\\w+) \\* 1");
    std::regex add0("(\\w+) = (\\w+) \\+ 0");
    std::regex sub0("(\\w+) = (\\w+) \\- 0");
    std::regex mul0("(\\w+) = (\\w+) \\* 0");
    std::regex div1("(\\w+) = (\\w+) / 1");
    for (auto line : code) {
        if (is_control_or_label(line)) {
            new_code.push_back(line);
            continue;
        }
        line = std::regex_replace(line, mul1, "$1 = $2");
        line = std::regex_replace(line, add0, "$1 = $2");
        line = std::regex_replace(line, sub0, "$1 = $2");
        line = std::regex_replace(line, mul0, "$1 = 0");
        line = std::regex_replace(line, div1, "$1 = $2");
        new_code.push_back(line);
    }
    return new_code;
}

std::vector<std::string> Optimizer::common_subexpression_elimination(const std::vector<std::string>& code) const {
    std::unordered_map<std::string, std::string> expr_map;
    std::vector<std::string> new_code;
    std::regex re("(t\\d+) = (.+)");
    for (const auto& line : code) {
        if (is_control_or_label(line)) {
            new_code.push_back(line);
            continue;
        }
        std::smatch m;
        if (std::regex_match(line, m, re)) {
            std::string t = m[1];
            std::string expr = m[2];
            if (expr_map.count(expr)) {
                new_code.push_back(t + " = " + expr_map[expr]);
            } else {
                expr_map[expr] = t;
                new_code.push_back(line);
            }
        } else {
            new_code.push_back(line);
        }
    }
    return new_code;
}

std::vector<std::string> Optimizer::advanced_loop_invariant_code_motion(const std::vector<std::string>& code) const {
    std::vector<std::string> new_code;
    std::vector<std::string> loop_body;
    bool in_loop = false;
    std::regex label_regex("^L\\d+:");
    std::regex word_re("\\b\\w+\\b");
    std::size_t last_label_pos = 0;
    for (std::size_t i = 0; i < code.size(); ++i) {
        const std::string& line = code[i];
        if (std::regex_search(line, label_regex)) {
            in_loop = true;
            loop_body.clear();
            last_label_pos = i;
        } else if (in_loop && line.find("goto") == 0) {
            // Analyze loop body
            std::regex assign_re("(\\w+) = (.+)");
            std::set<std::string> loop_assigned;
            std::vector<std::pair<std::string, std::string>> assignments;
            for (const auto& l : loop_body) {
                std::smatch m;
                if (std::regex_match(l, m, assign_re)) {
                    loop_assigned.insert(m[1]);
                    assignments.push_back({m[1], m[2]});
                }
            }
            // Find invariants: assignments whose RHS only uses variables not assigned in the loop or already invariant
            std::set<std::string> invariants;
            bool changed = true;
            while (changed) {
                changed = false;
                for (const auto& a : assignments) {
                    if (invariants.count(a.first)) continue;
                    bool rhs_invariant = true;
                    for (std::sregex_iterator it(a.second.begin(), a.second.end(), word_re), end; it != end; ++it) {
                        std::string v = it->str();
                        if (loop_assigned.count(v) && !invariants.count(v)) {
                            rhs_invariant = false;
                            break;
                        }
                    }
                    if (rhs_invariant) {
                        invariants.insert(a.first);
                        changed = true;
                    }
                }
            }
            // Move invariant assignments before the loop label
            std::vector<std::string> invariants_code;
            for (const auto& l : loop_body) {
                std::smatch m;
                if (std::regex_match(l, m, assign_re)) {
                    if (invariants.count(m[1])) {
                        invariants_code.push_back(l);
                    }
                }
            }
            for (const auto& inv : invariants_code) {
                new_code.push_back(inv);
            }
            // Add rest of loop body
            for (const auto& l : loop_body) {
                std::smatch m;
                if (std::regex_match(l, m, assign_re)) {
                    if (invariants.count(m[1])) continue;
                }
                new_code.push_back(l);
            }
            new_code.push_back(line);
            in_loop = false;
        } else if (in_loop) {
            loop_body.push_back(line);
        } else {
            new_code.push_back(line);
        }
    }
    return new_code;
}

std::vector<std::string> Optimizer::remove_useless_assignments(const std::vector<std::string>& code) const {
    std::vector<std::string> new_code;
    std::regex assign_re("(\w+) = (.+)");
    for (size_t i = 0; i < code.size(); ++i) {
        std::smatch m1, m2;
        if (i + 1 < code.size() &&
            std::regex_match(code[i], m1, assign_re) &&
            std::regex_match(code[i+1], m2, assign_re) &&
            m1[1] == m2[1]) {
            // Assignment is immediately overwritten, skip the first
            continue;
        }
        new_code.push_back(code[i]);
    }
    return new_code;
}

std::vector<std::string> Optimizer::strength_reduction(const std::vector<std::string>& code) const {
    std::vector<std::string> new_code;
    std::regex mul2("(\\w+) = (\\w+) \\* 2");
    std::regex mul4("(\\w+) = (\\w+) \\* 4");
    for (const auto& line : code) {
        if (is_control_or_label(line)) {
            new_code.push_back(line);
            continue;
        }
        std::smatch m;
        if (std::regex_match(line, m, mul2)) {
            std::string x = m[1];
            std::string y = m[2];
            new_code.push_back(x + " = " + y + " + " + y);
        } else if (std::regex_match(line, m, mul4)) {
            std::string x = m[1];
            std::string y = m[2];
            new_code.push_back(x + " = " + y + " + " + y + " + " + y + " + " + y);
        } else {
            new_code.push_back(line);
        }
    }
    return new_code;
}

std::vector<std::string> Optimizer::induction_variable_simplification(const std::vector<std::string>& code) const {
    std::vector<std::string> new_code;
    std::regex inc_re("(\\w+) = (\\w+) \\+ 1");
    std::set<std::string> used;
    // Find all used variables
    std::regex word_re("\\b\\w+\\b");
    for (const auto& line : code) {
        for (std::sregex_iterator it(line.begin(), line.end(), word_re), end; it != end; ++it) {
            used.insert(it->str());
        }
    }
    for (size_t i = 0; i < code.size(); ++i) {
        std::smatch m;
        if (std::regex_match(code[i], m, inc_re)) {
            std::string t = m[1];
            // If t is only used for incrementing i, skip it
            bool only_for_inc = true;
            for (size_t j = i + 1; j < code.size(); ++j) {
                if (code[j].find(t) != std::string::npos && code[j].find("i = " + t) == std::string::npos) {
                    only_for_inc = false;
                    break;
                }
            }
            if (only_for_inc) continue;
        }
        new_code.push_back(code[i]);
    }
    return new_code;
}

std::vector<std::string> Optimizer::loop_unrolling(const std::vector<std::string>& code) const {
    std::vector<std::string> new_code;
    std::regex loop_start("(\\w+) = 0");
    std::regex loop_cond("(\\w+) = (\\w+) LT (\\d+)");
    std::regex inc_re("(\\w+) = (\\w+) \\+ 1");
    for (size_t i = 0; i < code.size(); ++i) {
        if (i + 7 < code.size() &&
            std::regex_match(code[i], loop_start) &&
            std::regex_match(code[i+2], loop_cond) &&
            std::regex_match(code[i+8], inc_re)) {
            // Try to unroll
            std::smatch m_start, m_cond, m_inc;
            std::regex_match(code[i], m_start, loop_start);
            std::regex_match(code[i+2], m_cond, loop_cond);
            std::regex_match(code[i+8], m_inc, inc_re);
            std::string var = m_start[1];
            int limit = std::stoi(m_cond[3]);
            // Unroll only if limit is small
            if (limit <= 8) {
                // Copy code before loop
                for (size_t k = 0; k < i; ++k) new_code.push_back(code[k]);
                // Unroll loop body
                for (int iter = 0; iter < limit; ++iter) {
                    for (size_t k = i + 4; k < i + 8; ++k) {
                        std::string body_line = code[k];
                        // Replace i with iter
                        size_t pos = 0;
                        while ((pos = body_line.find(var, pos)) != std::string::npos) {
                            if ((pos == 0 || !isalnum(body_line[pos-1])) && (pos + var.size() == body_line.size() || !isalnum(body_line[pos+var.size()]))) {
                                body_line.replace(pos, var.size(), std::to_string(iter));
                                pos += std::to_string(iter).size();
                            } else {
                                pos += var.size();
                            }
                        }
                        new_code.push_back(body_line);
                    }
                }
                // Skip the original loop
                i += 8;
                continue;
            }
        }
        new_code.push_back(code[i]);
    }
    return new_code;
}

std::vector<std::string> Optimizer::remove_redundant_copies(const std::vector<std::string>& code) const {
    std::vector<std::string> new_code;
    std::regex assign_re("(\\w+) = (\\w+)");
    for (size_t i = 0; i + 1 < code.size(); ++i) {
        std::smatch m1, m2;
        if (std::regex_match(code[i], m1, assign_re) &&
            std::regex_match(code[i+1], m2, assign_re)) {
            std::string lhs1 = m1[1], rhs1 = m1[2];
            std::string lhs2 = m2[1], rhs2 = m2[2];
            if (lhs2 == rhs1 && rhs2 == lhs1) {
                // t4 = constant; constant = t4 pattern, remove both
                ++i; // skip next line too
                continue;
            }
        }
        new_code.push_back(code[i]);
    }
    // Add last line if not handled
    if (!code.empty() && (new_code.empty() || new_code.back() != code.back())) {
        new_code.push_back(code.back());
    }
    return new_code;
}

std::vector<std::string> Optimizer::constant_propagation_and_folding(const std::vector<std::string>& code) const {
    std::unordered_map<std::string, int> consts;
    std::vector<std::string> new_code;
    std::regex assign_const("(\\w+) = (\\d+)");
    std::regex binop("(\\w+) = (\\w+) ([-+*/]) (\\w+)");
    for (const auto& line : code) {
        std::smatch m;
        if (std::regex_match(line, m, assign_const)) {
            consts[m[1]] = std::stoi(m[2]);
            new_code.push_back(line);
        } else if (std::regex_match(line, m, binop)) {
            std::string lhs = m[1];
            std::string v1 = m[2];
            std::string op = m[3];
            std::string v2 = m[4];
            if (consts.count(v1) && consts.count(v2)) {
                int a = consts[v1];
                int b = consts[v2];
                int v = 0;
                if (op == "+") v = a + b;
                else if (op == "-") v = a - b;
                else if (op == "*") v = a * b;
                else if (op == "/") v = (b != 0) ? a / b : 0;
                new_code.push_back(lhs + " = " + std::to_string(v));
                consts[lhs] = v;
            } else {
                new_code.push_back(line);
                consts.erase(lhs);
            }
        } else {
            new_code.push_back(line);
        }
    }
    return new_code;
}

std::vector<std::string> Optimizer::induction_variable_elimination(const std::vector<std::string>& code) const {
    std::vector<std::string> new_code;
    std::regex inc_re("(\\w+) = (\\w+) \\+ 1");
    std::set<std::string> used;
    // Find all used variables
    std::regex word_re("\\b\\w+\\b");
    for (const auto& line : code) {
        for (std::sregex_iterator it(line.begin(), line.end(), word_re), end; it != end; ++it) {
            used.insert(it->str());
        }
    }
    for (size_t i = 0; i < code.size(); ++i) {
        std::smatch m;
        if (std::regex_match(code[i], m, inc_re)) {
            std::string t = m[1];
            // If t is only used for incrementing i, skip it
            bool only_for_inc = true;
            for (size_t j = i + 1; j < code.size(); ++j) {
                if (code[j].find(t) != std::string::npos && code[j].find("i = " + t) == std::string::npos) {
                    only_for_inc = false;
                    break;
                }
            }
            if (only_for_inc) continue;
        }
        new_code.push_back(code[i]);
    }
    return new_code;
}

std::vector<std::string> Optimizer::full_dead_code_elimination(const std::vector<std::string>& code) const {
    std::vector<std::string> new_code;
    std::regex assign_re("(\\w+) = (.+)");
    std::set<std::string> used;
    // First pass: collect all used variables (on RHS, in control flow, etc.)
    for (const auto& line : code) {
        if (line.empty() || line.back() == ':' || line.find("goto") == 0 || line.find("ifFalse") == 0 || line.find("return") == 0) {
            std::regex word_re("\\b\\w+\\b");
            for (std::sregex_iterator it(line.begin(), line.end(), word_re), end; it != end; ++it) {
                used.insert(it->str());
            }
            continue;
        }
        std::smatch m;
        if (std::regex_match(line, m, assign_re)) {
            std::string expr = m[2];
            std::regex word_re("\\b\\w+\\b");
            for (std::sregex_iterator it(expr.begin(), expr.end(), word_re), end; it != end; ++it) {
                used.insert(it->str());
            }
        }
    }
    // Add variables used in constant folding
    used.insert(global_used_vars.begin(), global_used_vars.end());
    // Second pass: keep only assignments whose LHS is used or are control/label lines
    for (size_t i = 0; i < code.size(); ++i) {
        const auto& line = code[i];
        if (line.empty() || line.back() == ':' || line.find("goto") == 0 || line.find("ifFalse") == 0 || line.find("return") == 0) {
            new_code.push_back(line);
            continue;
        }
        std::smatch m;
        if (std::regex_match(line, m, assign_re)) {
            std::string lhs = m[1];
            bool is_increment = false;
            for (int j = (int)i - 1; j >= 0; --j) {
                if (!code[j].empty() && code[j].back() == ':') {
                    std::string label = code[j].substr(0, code[j].size() - 1);
                    for (size_t k = i + 1; k < code.size(); ++k) {
                        if (code[k].find("goto " + label) == 0) {
                            is_increment = true;
                            break;
                        }
                        if (!code[k].empty() && code[k].back() == ':') break;
                    }
                    break;
                }
            }
            if (used.count(lhs) || is_increment) {
                new_code.push_back(line);
            }
        } else {
            new_code.push_back(line);
        }
    }
    return new_code;
} 