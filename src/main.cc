import sat;

#include <iostream>

int main() {
    sat::SAT sat3_solver{{{1, -2, -3}, {2, 3, -1}}};
    sat3_solver.dump(std::cout);
    return 0;
}