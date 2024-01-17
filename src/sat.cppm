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

export module sat;

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
using table_type = std::unordered_map<int, bool>;

class Var final {
    int m_id = 0;

public:
    Var() = default;
    Var(int id) : m_id(id) {}

    auto id() const noexcept { return std::abs(m_id); }

    auto calc(const table_type& data) const {
        auto literal_val = data.at(id());
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

auto operator==(const Var& lhs, const Var& rhs) { return lhs.id() == rhs.id(); }
}  // namespace sat

namespace std {
template <>
struct hash<sat::Var> {
    size_t operator()(const sat::Var& obj) const {
        return hash<int>()(obj.id());
    }
};
}  // namespace std

namespace sat {

class Clause final {
    static constexpr int m_size = 3;
    std::array<Var, m_size> m_literals{};

public:
    Clause(const std::array<Var, m_size>& literals) : m_literals{literals} {}

    template <typename... Args>
    Clause(Args&&... args) : m_literals{std::forward<Args>(args)...} {
        static_assert(sizeof...(args) == 3,
                      "Every clause should have 3 literals");
    }

    auto calc(const table_type& data) const {
        // return std::ranges::any_of(
        bool res = false;

        for (auto&& lit : m_literals) {
            res |= lit.calc(data);
        }

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

// export class ConjNormalForm final {
class ConjNormalForm final {
    //
    std::vector<Clause> m_clauses{};

public:
    ConjNormalForm() = default;
    ConjNormalForm(const std::vector<Clause>& clauses) : m_clauses{clauses} {}

    auto calc(const table_type& data) const {
        //! NOTE: maybe ranges::any_of
        bool res = true;

        for (const auto& clause : m_clauses) {
            res &= clause.calc(data);
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

auto& operator<<(std::ostream& os, const ConjNormalForm& obj) {
    obj.dump(os);
    return os;
}

export class SAT final {
    //
    ConjNormalForm m_cnf{};
    std::unordered_set<Var> m_vars{};
    table_type m_sol{};
    bool m_is_sat = true;

public:
    SAT() = default;
    SAT(const std::vector<Clause>& clauses) : m_cnf{clauses} {
        set_vars(clauses);
    }

    std::optional<table_type> try_solve() noexcept {
        if (solve_step(m_vars.begin(), m_vars.end())) return m_sol;
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

            for (auto&& it : m_sol)
                std::cout << "x" << it.first << " = " << it.second << std::endl;
        }
    }

    bool calc(const table_type& data) {
        //! NOTE: maybe ranges::all_of
        bool res = true;
        for (const auto& clause : m_cnf) res &= clause.calc(data);
        return res;
    }

    bool is_sat() { return m_is_sat; }

private:
    void set_vars(const std::vector<Clause>& clauses) noexcept {
        for (auto&& clause : clauses)
            for (auto&& var : clause) m_vars.insert(var.id());
    }

    template <typename InputIt>
    bool solve_step(InputIt cur, InputIt last) {
        if (cur == last) return calc(m_sol);

        auto& val = m_sol[(*cur).id()];
        auto next = std::next(cur);

        val = true;
        if (solve_step(next, last)) return true;

        val = false;
        return solve_step(next, last);
    }
};

}  // namespace sat
