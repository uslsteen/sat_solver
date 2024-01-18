import sat_runtime;

#include <iostream>

int main() {
    sat::SAT sat_solver{{{1, -2, -3}, {2, 3, -1}}};
    const auto res = sat_solver.try_solve();
    //
    std::cout << "Problem is ";
    if (res.has_value())
        std::cout << "satisfable\n";
    else
        std::cout << "unsatisfable\n";

    return 0;
}