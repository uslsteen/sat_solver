import sat_hybrid;

#include <array>
#include <iostream>
#include <tuple>

int main() {
    //
    constexpr int ClauseNum = 2;
    constexpr int VarsNum = 3;
    constexpr std::array<sat::Clause, ClauseNum> clauses = {
        {{1, 1, 1}, {-1, -1, -1}}};

    sat::SAT<ClauseNum, VarsNum> sat{clauses};
    const auto res = sat.try_solve();

    std::cout << "Problem is ";
    if (res.has_value())
        std::cout << "satisfable\n";
    else
        std::cout << "unsatisfable\n";

    return 0;
}