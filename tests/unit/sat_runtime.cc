import sat;

#include <gtest/gtest.h>

TEST(Naive, ExampleTask) {
    sat::SAT sat{{{1, 2, -3}, {2, 3, -1}}};

    auto sol = sat.try_solve();
    EXPECT_TRUE(sat.is_sat());
}

TEST(Naive, False) {
    sat::SAT sat{{{2, 2, 2}, {-2, -2, -2}}};

    auto sol = sat.try_solve();
    EXPECT_FALSE(sol.has_value());
}