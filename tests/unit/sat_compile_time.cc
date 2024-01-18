import sat_compile_time;

#include <gtest/gtest.h>

TEST(Naive, ExampleTask) {
    constexpr int ClauseNum = 2;
    constexpr int VarsNum = 3;
    constexpr std::array<std::tuple<int, int, int>, 2> clauses = {
        {{1, -2, -3}, {2, 3, -1}}};
    //
    sat::SAT<ClauseNum, VarsNum> sat{};
    auto res = sat.try_solve(clauses);

    EXPECT_TRUE(res.has_value());
}

TEST(Naive, False) {
    constexpr int ClauseNum = 2;
    constexpr int VarsNum = 3;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {
        {{2, 2, 2}, {-2, -2, -2}}};

    sat::SAT<ClauseNum, VarsNum> sat{};

    constexpr auto res = sat.try_solve(clauses);
    EXPECT_FALSE(res.has_value());
}

TEST(CompileTimeGen, TrueExample5_2) {
    constexpr int ClauseNum = 5;
    constexpr int VarsNum = 2;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {-1, -2, 2},
        {-1, 1, -1},
        {2, 2, 1},
        {-2, 1, -1},
        {-2, 2, -1},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    constexpr auto res = sat.try_solve(clauses);
    EXPECT_TRUE(res.has_value());
}

TEST(CompileTimeGen, FalseExample5_2) {
    constexpr int ClauseNum = 5;
    constexpr int VarsNum = 2;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {-2, 1, 1},
        {-1, -2, -1},
        {1, 2, 2},
        {-1, 2, -1},
        {1, 2, 1},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    constexpr auto res = sat.try_solve(clauses);
    EXPECT_FALSE(res.has_value());
}

TEST(CompileTimeGen, TrueExample10) {
    constexpr int ClauseNum = 10;
    constexpr int VarsNum = 4;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {4, 2, 2},
        {-1, -4, 4},
        {-1, 4, -3},
        {1, -2, 3},
        {-3, 2, -1},
        {3, -3, 1},
        {-2, 3, -2},
        {-2, -1, -3},
        {-3, 4, 2},
        {4, 4, -2},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};

    constexpr auto res = sat.try_solve(clauses);
    EXPECT_TRUE(res.has_value());
}

TEST(CompileTimeGen, FalseExample10) {
    constexpr int ClauseNum = 10;
    constexpr int VarsNum = 3;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {1, -3, -3},
        {-3, -1, -3},
        {2, -2, -1},
        {3, 1, 3},
        {-3, 1, 3},
        {-1, 2, -1},
        {-2, -2, 3},
        {1, 3, 1},
        {1, 2, 3},
        {-1, 1, -3},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};

    auto res = sat.try_solve(clauses);
    EXPECT_FALSE(res.has_value());
}

TEST(CompileTimeGen, TrueExample15) {
    constexpr int ClauseNum = 15;
    constexpr int VarsNum = 4;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {4, 2, 3},
        {1, -1, 3},
        {4, 3, -4},
        {1, -3, -3},
        {2, -3, 4},
        {-4, 1, -2},
        {2, -3, 4},
        {4, 2, 4},
        {2, -4, -2},
        {3, -3, -2},
        {4, -4, 1},
        {-4, -1, 2},
        {3, -2, -3},
        {1, 4, 4},
        {2, -2, 1},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    const auto res = sat.try_solve(clauses);

    EXPECT_TRUE(res.has_value());
}

TEST(CompileTimeGen, FalseExample15) {
    constexpr int ClauseNum = 15;
    constexpr int VarsNum = 4;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {-3, -2, -3},
        {-4, 4, -1},
        {-4, 1, 3},
        {-4, -1, 3},
        {1, -3, -3},
        {4, -4, 4},
        {-2, -4, -3},
        {3, 3, -2},
        {4, -1, -1},
        {3, 4, 2},
        {-2, -4, -1},
        {-3, 4, 3},
        {2, -1, -1},
        {-1, 3, 3},
        {-3, -1, -4},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    const auto res = sat.try_solve(clauses);

    EXPECT_FALSE(res.has_value());
}

TEST(CompileTimeGen, TrueExample20) {
    constexpr int ClauseNum = 20;
    constexpr int VarsNum = 5;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {3, 4, -4},   {-4, -2, 3}, {4, -2, 3},  {2, -2, -2}, {2, -5, -3},
        {-5, -1, 5},  {-3, 3, -5}, {1, 2, 4},   {-5, 2, 1},  {-4, -1, 4},
        {-4, -1, -2}, {1, 3, 2},   {-2, -1, 5}, {-3, 3, -5}, {-3, 3, 3},
        {-3, 5, 4},   {-1, -4, 4}, {-2, -3, 5}, {-1, -5, 5}, {-1, -1, 4},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    const auto res = sat.try_solve(clauses);

    EXPECT_TRUE(res.has_value());
}

TEST(CompileTimeGen, FalseExample20) {
    constexpr int ClauseNum = 20;
    constexpr int VarsNum = 5;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {2, -2, 1},   {-5, 3, 1},   {2, 4, 5},    {-1, 1, -4}, {-4, -4, -4},
        {3, 3, -1},   {-1, -5, -5}, {4, 5, -1},   {-3, 5, 4},  {1, -2, -5},
        {-3, -3, -5}, {-1, 1, 5},   {-4, -2, -5}, {3, 4, -2},  {-5, 1, 2},
        {-5, 2, 1},   {2, -5, -4},  {-1, 3, 1},   {-2, 1, -2}, {-5, 5, -5},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    const auto res = sat.try_solve(clauses);

    EXPECT_FALSE(res.has_value());
}

TEST(CompileTimeGen, TrueExample20_10) {
    constexpr int ClauseNum = 20;
    constexpr int VarsNum = 10;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {5, -5, -6}, {4, -2, -8},  {8, -3, -7},  {-5, 2, 3},  {-2, 5, -7},
        {8, 5, -7},  {-2, -1, 2},  {-7, -5, -3}, {3, 9, -10}, {8, -10, 9},
        {-3, 7, 7},  {-9, -9, -1}, {8, -8, 9},   {-4, 6, -7}, {-6, 5, -8},
        {-6, -9, 3}, {9, 1, 6},    {-5, 10, -6}, {-8, 1, 8},  {-6, 8, 5},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    constexpr auto res = sat.try_solve(clauses);
    EXPECT_TRUE(res.has_value());
}

TEST(CompileTimeGen, TrueExample25) {
    constexpr int ClauseNum = 25;
    constexpr int VarsNum = 5;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {2, -4, 1},  {-2, 3, -2}, {-2, -3, 1}, {-2, -4, -1}, {-2, 3, -1},
        {1, 2, -5},  {1, 4, -5},  {-4, 4, 1},  {3, -2, 1},   {-1, -3, 3},
        {-2, -2, 2}, {-3, -3, 1}, {5, -4, -1}, {5, -5, -1},  {-4, -1, 4},
        {-2, 4, 4},  {2, 5, 5},   {4, -2, -2}, {-3, 3, 5},   {-3, -2, 2},
        {-4, 3, -4}, {3, -4, -4}, {-5, -4, 5}, {3, -3, -2},  {-5, -2, 2},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    const auto res = sat.try_solve(clauses);

    EXPECT_TRUE(res.has_value());
}

TEST(CompileTimeGen, FalseExample25) {
    constexpr int ClauseNum = 25;
    constexpr int VarsNum = 5;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {-2, -2, 5},  {-5, 5, 3},   {2, 2, -1}, {-2, 5, -1},  {1, 4, 4},
        {3, -2, -2},  {-4, 4, 5},   {4, 5, 5},  {1, -1, -2},  {-2, -1, -1},
        {-4, 4, -2},  {5, 2, -4},   {5, 1, 3},  {-3, -3, -4}, {-2, 4, 1},
        {-3, -4, -5}, {-3, -2, -5}, {-2, 5, 5}, {-1, -1, 5},  {3, -1, -2},
        {-3, 3, -3},  {-3, -5, 5},  {1, -2, 1}, {-5, -5, 3},  {-3, -4, -5},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    const auto res = sat.try_solve(clauses);

    EXPECT_FALSE(res.has_value());
}

TEST(CompileTimeGen, TrueExample30) {
    constexpr int ClauseNum = 30;
    constexpr int VarsNum = 5;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {-5, -3, -3}, {-3, -1, -4}, {-1, -2, -4}, {-3, 2, 5},  {-3, -3, -4},
        {-3, -1, -4}, {-5, 5, -2},  {4, 2, 2},    {3, -4, 4},  {2, -3, -3},
        {4, -3, -5},  {3, -1, 1},   {2, -1, -1},  {-5, 3, -5}, {1, -3, -1},
        {1, 1, -5},   {5, -1, -4},  {1, 2, -3},   {-1, 4, 4},  {3, -2, 4},
        {-4, -3, -4}, {3, -3, -4},  {-5, 4, -4},  {-5, 1, -3}, {3, -1, -3},
        {-3, 2, 5},   {-1, 3, -2},  {4, -1, -5},  {4, 2, 2},   {3, -1, -4},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    const auto res = sat.try_solve(clauses);

    EXPECT_TRUE(res.has_value());
}

TEST(CompileTimeGen, FalseExample30) {
    constexpr int ClauseNum = 30;
    constexpr int VarsNum = 5;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {-1, -4, 4}, {-2, 5, 5},   {3, -1, 5},   {1, -5, -4},  {1, 1, -5},
        {1, -1, 2},  {1, 2, -2},   {-3, 2, -1},  {-1, 4, -3},  {3, 2, 1},
        {3, -5, 5},  {-5, -2, 3},  {-4, -4, -5}, {-5, -3, 4},  {3, 2, -2},
        {2, -2, 5},  {3, -2, 2},   {-2, 2, 5},   {-2, -4, -2}, {-5, 4, 4},
        {5, 2, -5},  {-2, -1, -1}, {-2, -1, -3}, {1, -4, 2},   {-5, 4, -3},
        {5, 5, -4},  {4, -4, 2},   {2, 5, -3},   {1, -2, 2},   {-1, 2, 4},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    const auto res = sat.try_solve(clauses);

    EXPECT_FALSE(res.has_value());
}

TEST(CompileTimeGen, TrueExample33_11) {
    constexpr int ClauseNum = 33;
    constexpr int VarsNum = 11;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {8, 9, 10},    {-8, -9, 2},   {5, 7, 5},    {-5, 11, 1}, {-11, -1, -9},
        {10, -11, 7},  {1, -1, -11},  {-7, -8, -6}, {9, 7, 3},   {-4, -4, -1},
        {2, 6, 2},     {-1, -10, -3}, {-4, 11, -6}, {-5, 6, -3}, {7, 1, 4},
        {-2, 11, -11}, {10, -7, 9},   {4, -10, -2}, {7, 2, 4},   {6, 8, -10},
        {6, 9, 9},     {-3, -2, -5},  {8, -1, 2},   {9, -6, 8},  {-11, 4, 4},
        {-1, 7, 5},    {-4, 2, 10},   {-10, 2, -8}, {3, -8, 10}, {9, -2, 1},
        {4, -8, -10},  {3, 10, 8},    {-9, -7, -4},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    constexpr auto res = sat.try_solve(clauses);
    EXPECT_TRUE(res.has_value());
}

TEST(CompileTimeGen, TrueExample50) {
    constexpr int ClauseNum = 50;
    constexpr int VarsNum = 10;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {9, 6, 1},    {3, -9, 7},     {-6, -1, 5},  {-6, -5, 3}, {10, -2, -10},
        {5, -3, 7},   {6, -8, 6},     {2, -7, -1},  {2, 7, 6},   {-7, -1, -7},
        {5, 6, -4},   {-3, -2, 7},    {2, 3, 2},    {-6, 4, 5},  {-8, -2, -6},
        {-3, 9, 1},   {-10, -8, -2},  {-8, -4, -6}, {-5, 7, -9}, {-6, 3, -2},
        {7, 6, -10},  {10, 7, -2},    {2, 10, 3},   {9, 9, -4},  {5, -4, -10},
        {-8, 8, 10},  {-10, 3, 2},    {8, 2, 2},    {-1, 5, -3}, {6, -6, 4},
        {10, 4, 8},   {-8, -4, 7},    {-5, -8, -5}, {10, 4, 10}, {-1, -10, 5},
        {-9, -3, 2},  {-10, -3, -10}, {3, 6, -8},   {10, 6, 2},  {-7, 10, -1},
        {-3, 5, -6},  {-5, 7, -2},    {-6, 10, 2},  {5, -6, 2},  {2, -8, 3},
        {-8, -7, -2}, {10, 3, 7},     {-3, 1, -8},  {10, 8, 8},  {-8, -5, 2},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    auto res = sat.try_solve(clauses);
    EXPECT_TRUE(res.has_value());
}

TEST(CompileTimeGen, FalseExample50) {
    constexpr int ClauseNum = 50;
    constexpr int VarsNum = 10;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {-6, 5, -7},  {-7, -8, -2}, {9, -2, 6},    {10, 1, 5},  {5, 1, -5},
        {4, 8, 7},    {2, -5, 1},   {-8, -4, -3},  {3, -5, -7}, {-3, 1, 2},
        {-7, 5, -2},  {5, -5, -2},  {-9, -10, 10}, {6, 8, -8},  {8, 2, 10},
        {-1, -6, 7},  {-2, -9, -2}, {-9, -8, 1},   {1, 8, -9},  {-1, -10, 10},
        {6, -6, 3},   {-2, -8, 2},  {-1, -7, 8},   {-3, -5, 6}, {-3, 7, -6},
        {-2, 7, -9},  {6, -10, -8}, {-9, -4, -10}, {6, -1, 6},  {-4, 1, 8},
        {-3, -10, 5}, {-1, -8, 9},  {-10, 3, -10}, {-6, 8, -8}, {-4, -5, 6},
        {6, 10, 9},   {-6, -5, 3},  {7, 8, -8},    {-4, 1, -6}, {8, 6, 2},
        {-2, -9, -8}, {9, 8, -5},   {2, 8, 9},     {8, -5, 8},  {-4, -9, -3},
        {10, 4, 6},   {-5, -3, 4},  {-8, 9, -2},   {1, -9, -1}, {7, 3, -3},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};

    constexpr auto res = sat.try_solve(clauses);
    EXPECT_FALSE(res.has_value());
}

TEST(CompileTimeGen, TrueExample70) {
    constexpr int ClauseNum = 70;
    constexpr int VarsNum = 11;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {-9, -8, -7}, {-11, 3, 2},  {-3, -5, 6},  {3, 2, -7},    {5, 8, -6},
        {10, 6, -8},  {-6, -9, -2}, {-11, 1, -8}, {2, -6, -2},   {-5, -2, 6},
        {10, -4, -3}, {-7, 7, -2},  {-7, 1, 10},  {6, -3, -5},   {3, -8, -10},
        {4, -3, 4},   {-5, -6, 6},  {9, -8, -2},  {-7, -3, 11},  {-6, 9, 1},
        {2, -9, 11},  {-1, -7, 5},  {-1, 7, -6},  {-1, -5, 1},   {-2, 10, -7},
        {-2, -2, 3},  {2, -2, 1},   {-5, 10, 2},  {-11, -3, 5},  {4, -5, 2},
        {8, -6, 1},   {5, 8, 1},    {-6, 8, -10}, {-2, 2, 8},    {-11, -8, 7},
        {2, -7, 3},   {-1, 8, -4},  {8, 8, -5},   {-6, 6, -10},  {10, -10, 9},
        {3, 5, -11},  {10, -2, 11}, {-3, 8, -1},  {3, -3, -1},   {11, -7, -9},
        {6, -10, 9},  {9, 9, -1},   {-8, 3, 5},   {6, -11, 4},   {-4, -5, 6},
        {-6, -7, -5}, {-7, -3, -5}, {-1, 4, 6},   {3, -1, -9},   {7, -9, -7},
        {11, -7, -6}, {10, 10, 7},  {-9, 4, -1},  {-11, -6, -1}, {-10, -3, 9},
        {-9, 10, 8},  {6, -9, -11}, {4, -3, -4},  {2, -8, -2},   {-4, 1, -7},
        {9, 7, -5},   {-11, -6, 7}, {9, 11, -11}, {7, -5, -10},  {-5, -10, -2},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    constexpr auto res = sat.try_solve(clauses);
    EXPECT_TRUE(res.has_value());
}

TEST(CompileTimeGen, FalseExample70) {
    constexpr int ClauseNum = 70;
    constexpr int VarsNum = 10;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {-7, -4, -4}, {-2, 7, -7},   {7, -8, -10}, {-3, 1, 10},  {10, -8, 9},
        {5, 10, 5},   {-1, 7, -9},   {-9, 4, -2},  {-5, 5, 6},   {7, -2, -6},
        {-2, 6, 5},   {1, 5, 5},     {10, -4, 8},  {6, -4, -7},  {-3, 3, 5},
        {5, 10, 4},   {3, -5, -4},   {-7, 3, -10}, {7, 8, -5},   {-3, -2, 1},
        {6, 10, -8},  {5, -2, -7},   {4, -7, -9},  {-2, -6, 3},  {2, 5, -6},
        {-2, 5, -9},  {-3, 9, -10},  {1, 2, 1},    {-5, 6, 1},   {8, 4, -1},
        {7, 6, -7},   {-4, 9, 2},    {-10, -1, 5}, {9, -1, -1},  {9, -7, 1},
        {7, -9, -6},  {-9, -6, 2},   {-8, 2, -7},  {6, -10, -6}, {6, -1, 8},
        {-4, -7, 1},  {-10, -8, -1}, {-5, 2, 7},   {-9, 9, 3},   {10, 4, -3},
        {7, 3, 6},    {-7, -7, 10},  {2, -4, -7},  {8, 8, -5},   {-10, 7, -3},
        {-9, -6, -5}, {-6, -9, -6},  {6, 8, 9},    {-4, 6, -6},  {8, -7, 4},
        {-5, 7, -1},  {3, 3, -4},    {-8, 3, -10}, {9, 9, -4},   {3, -10, 10},
        {2, -6, 7},   {-9, -3, -2},  {7, 10, 9},   {-5, -9, 2},  {10, 4, -2},
        {-5, -9, 10}, {5, -2, -8},   {-3, 10, 5},  {4, 8, -7},   {-8, 1, -10},
    }};

    sat::SAT<ClauseNum, VarsNum> sat{};
    constexpr auto res = sat.try_solve(clauses);
    EXPECT_FALSE(res.has_value());
}

//! NOTE: Compilation failed due constexpr evaluation hit maximum step limit
#if 0
TEST(CompileTimeGen, TrueExample100) {
    constexpr int ClauseNum = 100;
    constexpr int VarsNum = 20;

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{
        {16, -8, -17},  {-3, 13, 14},   {5, -5, -8},    {-16, -8, 6},
        {-15, -1, 5},   {16, -1, 8},    {-11, 14, -14}, {-7, -18, 11},
        {-15, -11, 4},  {-1, 12, -3},   {-1, 19, 12},   {-8, -4, -18},
        {-10, -4, -12}, {-6, -17, 15},  {-19, 14, 15},  {2, -12, -5},
        {-11, 11, -20}, {8, -7, 7},     {-2, -6, -4},   {-3, -4, 6},
        {5, -16, -7},   {-13, 1, 3},    {-16, -7, 3},   {15, -17, -2},
        {4, 3, 18},     {-16, -6, 12},  {-18, -14, 18}, {-6, 20, 18},
        {-15, -1, -18}, {16, 1, -7},    {-7, -5, -6},   {-13, -16, -1},
        {7, -1, 14},    {-10, 2, 7},    {-6, 17, -8},   {-19, 11, -19},
        {-2, 18, -15},  {-17, -14, 7},  {19, 13, 19},   {-10, -20, -16},
        {-13, -10, 15}, {1, -4, -1},    {2, -6, -10},   {-1, 6, -14},
        {8, -4, 7},     {15, -4, 2},    {19, 20, 3},    {-10, 17, 14},
        {-2, 16, -15},  {-19, -6, 12},  {-19, 9, -2},   {-5, -2, 6},
        {-2, -17, -9},  {-16, 12, -4},  {-7, -12, 13},  {-16, 8, -14},
        {12, 20, 9},    {9, 2, 2},      {-5, -19, -20}, {-7, 2, -20},
        {3, -12, -8},   {-4, 7, -14},   {-9, -2, 18},   {1, -4, 12},
        {12, 7, -16},   {20, 18, 14},   {-3, -19, -9},  {-19, 9, -18},
        {-13, -8, 10},  {-9, 15, 20},   {15, 16, 13},   {-20, -3, -10},
        {8, 18, 3},     {-19, 19, 10},  {-1, -5, 20},   {3, 14, 3},
        {18, 9, -7},    {20, -12, 6},   {2, -17, -3},   {-13, 5, 18},
        {-13, -10, 4},  {-6, 12, 2},    {11, 16, -3},   {-5, -12, 7},
        {20, -14, -3},  {-17, 10, 1},   {20, -7, -5},   {2, -8, 4},
        {-3, 18, 6},    {6, -10, 19},   {13, 8, 4},     {2, 20, -17},
        {10, 19, -7},   {-16, 7, 14},   {9, 18, 11},    {3, -5, 13},
        {9, -6, 6},     {-13, 15, -20}, {13, -12, -5},  {-9, 4, -12},

    }};

    sat::SAT<ClauseNum, VarsNum> sat{};

    constexpr auto sol = sat.try_solve(clauses);
    EXPECT_TRUE(sol.has_value());
}
#endif