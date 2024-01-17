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

    auto calc(const table_type& data) const noexcept {
        auto literal_val = data.at(m_id);
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

    auto calc(const table_type& data) {
        bool res = true;

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

    auto calc(const table_type& data) {
        bool res = true;

        for (auto&& clause : m_clauses) {
            res &= clause.calc(data);
        }

        return res;
    }

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
    std::optional<table_type> m_sol{};

public:
    SAT() = default;
    SAT(std::vector<Clause> inp) : m_cnf{inp} {}

    void try_solve() const {}

    void dump(std::ostream& os) {
        os << m_cnf << std::endl;

        os << "Problem is ";

        if (m_sol == std::nullopt)
            os << "unsatisfiable";
        else
            os << "satisfable";
    }
};

}  // namespace sat
