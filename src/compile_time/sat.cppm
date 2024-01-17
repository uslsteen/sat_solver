module;

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <iterator>
#include <optional>
#include <tuple>
#include <vector>

export module sat_compile_time;

namespace sat {

namespace detail {

template <typename T>
consteval T compile_abs(T val) {
    return val > 0 ? val : -val;
}
}  // namespace detail

export template <int ClauseNum, int VarNum>
class SAT final {
public:
    using var_type = int;
    using clause_type = std::tuple<int, int, int>;
    //
public:
    constexpr SAT() = default;
    //
    consteval bool calc(const std::array<var_type, VarNum>& vars,
                        const std::array<clause_type, ClauseNum>& clauses) {
        for (const auto& clause : clauses) {
            var_type x1 = std::get<0>(clause);
            var_type x2 = std::get<1>(clause);
            var_type x3 = std::get<2>(clause);
            //
            bool val1 =
                x1 > 0 ? vars[x1 - 1] : !vars[detail::compile_abs(x1) - 1];
            //
            bool val2 =
                x2 > 0 ? vars[x2 - 1] : !vars[detail::compile_abs(x2) - 1];
            //
            bool val3 =
                x3 > 0 ? vars[x3 - 1] : !vars[detail::compile_abs(x3) - 1];
            //
            if (!(val1 || val2 || val3)) return false;
        }
        return true;
    }

    //
    template <int var_id>
    consteval std::optional<std::array<var_type, VarNum>> solve_iter(
        const std::array<var_type, VarNum>& vars,
        const std::array<clause_type, ClauseNum>& clauses) {
        const bool res = calc(vars, clauses);
        //
        if (res) return vars;
        //
        if constexpr (VarNum == var_id)
            return std::nullopt;
        else {
            auto cur_vars = vars;
            //
            cur_vars[var_id] = 1;
            const auto true_flow = solve_iter<var_id + 1>(cur_vars, clauses);
            if (true_flow.has_value()) return true_flow;
            //
            cur_vars[var_id] = 0;
            const auto false_flow = solve_iter<var_id + 1>(cur_vars, clauses);
            if (false_flow.has_value()) return false_flow;
        }
        //
        return std::nullopt;
    }

    //
    consteval std::optional<std::array<var_type, VarNum>> try_solve(
        const std::array<clause_type, ClauseNum>& clauses) {
        std::array<var_type, VarNum> vars{};
        return solve_iter<0>(vars, clauses);
    }
};
}  // namespace sat