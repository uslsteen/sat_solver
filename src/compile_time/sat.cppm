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
class ConjNormalForm final {
public:
    using var_type = int;
    using clause_type = std::tuple<int, int, int>;
    //
private:
    std::array<clause_type, ClauseNum> m_clauses{};
    std::array<var_type, VarNum> m_vars{};

public:
    constexpr ConjNormalForm(const std::array<clause_type, ClauseNum>& clauses)
        : m_clauses(clauses) {}

    //
    template <int var_id>
    consteval std::optional<std::array<var_type, VarNum>> solve_iter() {
        return std::nullopt;
    }

    //
    consteval std::optional<std::array<var_type, VarNum>> try_solve() {
        return solve_iter<0>();
    }
};
}  // namespace sat