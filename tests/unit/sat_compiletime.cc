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

TEST(GenTest, TrueExample10) {
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

TEST(GenTest, FalseExample10) {
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

TEST(GenTest, TrueExample50) {
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

TEST(GenTest, FalseExample50) {
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

TEST(GenTest, TrueExample70) {
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

TEST(GenTest, FalseExample70) {
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