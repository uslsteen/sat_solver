import sat_compile_time;

#include <array>
#include <iostream>
#include <tuple>

int main() {
    //
    constexpr int ClauseNum = 2;
    constexpr int VarsNum = 3;
    constexpr std::array<std::tuple<int, int, int>, 2> clauses = {{{1, -2, -3},
                                                                  {2, 3, -1}}};
    //
    sat::ConjNormalForm<ClauseNum, VarsNum> cnf{clauses};
    cnf.try_solve();
};
