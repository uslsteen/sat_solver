module;

#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <numeric>
#include <optional>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

export module sat_hybrid;

namespace sat {

namespace detail {

template <typename T, typename InputIt>
std::string join_str(InputIt first, InputIt last,
                     const std::string& separator) {
    auto concat_fold = [&](std::string str, const T& var) {
        std::stringstream stream;
        stream << var;
        return str.empty() ? stream.str()
                           : std::move(str) + separator + stream.str();
    };
    //
    std::stringstream stream;
    stream << std::accumulate(first, last, stream.str(), concat_fold);
    //
    return stream.str();
}

}  // namespace detail

//! NOTE: bijection of literal and his value
template <std::semiregular T, int TableSize>
using table_type = std::array<T, TableSize>;

class Var final {
public:
    using data_type = int;

private:
    data_type m_id = 0;

public:
    constexpr Var() = default;
    constexpr Var(int id) : m_id(id) {}

    auto id() const noexcept { return std::abs(m_id); }
    auto val() const noexcept { return m_id; }

    template <int VarNum>
    auto calc(const table_type<int, VarNum>& data) const {
        auto literal_val = data.at(id() - 1);
        return m_id > 0 ? literal_val : !literal_val;
    }

    auto empty() const noexcept { return m_id == 0; }

    void dump(std::ostream& os) const {
        os << (m_id > 0 ? "" : "~") << "x" << id();
    }
};

auto& operator<<(std::ostream& os, const Var& obj) {
    obj.dump(os);
    return os;
}

}  // namespace sat

namespace sat {

export class Clause final {
    static constexpr int m_size = 3;
    std::array<Var, m_size> m_literals{};

public:
    constexpr Clause(const std::array<Var, m_size>& literals)
        : m_literals{literals} {}

    template <typename... Args>
    constexpr Clause(Args&&... args) : m_literals{std::forward<Args>(args)...} {
        static_assert(sizeof...(args) == 3,
                      "Every clause should have 3 literals");
    }

    template <int VarNum>
    auto calc(const table_type<int, VarNum>& data) const {
        bool res = false;

        for (auto&& lit : m_literals) res |= lit.calc<VarNum>(data);

        return res;
    }

    void dump(std::ostream& os) const {
        os << "(";
        os << detail::join_str<Var>(m_literals.begin(), m_literals.end(), "|");
        os << ")";
    }

    // Iterators
    auto begin() const noexcept { return m_literals.begin(); }
    auto begin() noexcept { return m_literals.begin(); }

    auto end() const noexcept { return m_literals.end(); }
    auto end() noexcept { return m_literals.end(); }
};

auto& operator<<(std::ostream& os, const Clause& obj) {
    obj.dump(os);
    return os;
}

template <int ClauseNum>
class ConjNormalForm final {
    //
    std::array<Clause, ClauseNum> m_clauses{};

public:
    constexpr ConjNormalForm(const std::array<Clause, ClauseNum>& clauses)
        : m_clauses{clauses} {}

    //
    template <int VarNum>
    auto calc(const std::array<int, VarNum>& data) const {
        bool res = true;

        for (const auto& clause : m_clauses) {
            res &= clause.calc<VarNum>(data);
        }

        return res;
    }

    // Iterators
    auto begin() const noexcept { return m_clauses.begin(); }
    auto begin() noexcept { return m_clauses.begin(); }

    auto end() const noexcept { return m_clauses.end(); }
    auto end() noexcept { return m_clauses.end(); }

    void dump(std::ostream& os) const {
        os << detail::join_str<Clause>(m_clauses.begin(), m_clauses.end(),
                                       "&\n");
    }
};

export template <int ClauseNum, int VarNum>
class SAT final {
    //
public:
    using SolutionTy = table_type<int, VarNum>;

private:
    ConjNormalForm<ClauseNum> m_cnf{};
    bool m_is_sat = true;

public:
    constexpr SAT(const std::array<Clause, ClauseNum>& clauses)
        : m_cnf{clauses} {}

    std::optional<SolutionTy> try_solve(const SolutionTy& reference = {}) noexcept {
        SolutionTy solution = reference;
        if (solve_step(solution)) return solution;
        //
        m_is_sat = false;
        return std::nullopt;
    }

    void dump(std::ostream& os) {
        os << m_cnf << std::endl;
        os << "Problem is ";
        if (!m_is_sat)
            os << "unsatisfiable";
        else {
            os << "satisfable\n";
            os << "The possible solution is:\n";
        }
    }

private:
    //
    bool calc(const SolutionTy& data) {
        bool res = true;
        for (const auto& clause : m_cnf)
            res &= clause.template calc<VarNum>(data);
        return res;
    }

    //
    bool solve_step(SolutionTy& solution, int id = 0) {
        if (id == VarNum) return calc(solution);

        auto& val = solution[id];

        val = 1;
        if (solve_step(solution, id + 1)) return true;

        val = 0;
        return solve_step(solution, id + 1);
    }
};
}  // namespace sat