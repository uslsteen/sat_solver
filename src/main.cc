import sat;

#include <iostream>

int main() {
    sat::SAT sat_solver{{{1, -2, -3}, {2, 3, -1}}};
    sat_solver.try_solve();
    //
    sat_solver.dump(std::cout);
    return 0;
}