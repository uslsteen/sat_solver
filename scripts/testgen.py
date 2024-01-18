import argparse

from pysat.formula import CNF
from pysat.solvers import Solver

import numpy as np

from argparse_range import range_action
import textwrap

MAX_VARS = 10000
MAX_CLAUSES = 100000
CLAUSE_SIZE = 3

def gen_hybrid(clauses_num : int, 
                vars_num : int, 
                clauses : str, 
                is_sat : bool):
    
    is_SAT = "True" if is_sat else "False"
    
    
    return textwrap.dedent(
f"""
TEST(HybridGen, {is_SAT}Example{clauses_num}_{vars_num}) {{
    constexpr int ClauseNum = {clauses_num};
    constexpr int VarsNum = {vars_num};

    constexpr std::array<sat::Clause, ClauseNum> clauses = {{{{
        {clauses}
    }}}};

    sat::SAT<ClauseNum, VarsNum> sat{{clauses}};
    const auto res = sat.try_solve();

    EXPECT_{"TRUE" if is_sat else "FALSE"}(res.has_value());
}}
""")

def gen_compile_time(clauses_num : int, 
                    vars_num : int, 
                    clauses : str, 
                    is_sat : bool):
    
    is_SAT = "True" if is_sat else "False"
    
    
    return textwrap.dedent(
f"""
TEST(CompileTimeGen, {is_SAT}Example{clauses_num}_{vars_num}) {{
    constexpr int ClauseNum = {clauses_num};
    constexpr int VarsNum = {vars_num};

    constexpr std::array<std::tuple<int, int, int>, ClauseNum> clauses = {{{{
        {clauses}
    }}}};

    sat::SAT<ClauseNum, VarsNum> sat{{}};
    constexpr auto res = sat.try_solve(clauses);
    EXPECT_{"TRUE" if is_sat else "FALSE"}(res.has_value());
}}
""")

def gen_runtime(clauses_num : int, 
                vars_num : int, 
                clauses : str, 
                is_sat : bool):
    
    is_SAT = "True" if is_sat else "False"
    
    return textwrap.dedent(
f"""
TEST(RuntimeTimeGen, {is_SAT}Example{clauses_num}_{vars_num}) {{
    sat::SAT sat{{{{
        {clauses}
    }}}};

    const auto res = sat.try_solve();
    EXPECT_{"TRUE" if is_sat else "FALSE"}(res.has_value());
}}
""")

def main():
    parser = argparse.ArgumentParser(
        description="Script for generating SAT systems"
    )

    parser.add_argument(
        "-c",
        "--clauses",
        type=int,
        required=True,
        action=range_action(1, MAX_CLAUSES + 1),
        help="Amount of clauses",
    )
    parser.add_argument(
        "-v",
        "--vars",
        required=True,
        type=int,
        action=range_action(2, MAX_VARS + 1),
        help="Amount of vars",
    )

    args = parser.parse_args()

    cnf_sizes: tuple[int, int] = (args.clauses, CLAUSE_SIZE)
    clauses = (
        np.random.randint(1, args.vars + 1, size=cnf_sizes)
        * np.random.choice([-1, 1], size=cnf_sizes)
    ).tolist()

    clauses2str = str()
    for clause in clauses:
        clauses2str += f'{{{", ".join(map(str, clause))}}},'
    # 
    
    with open('test_gen.cc', 'w') as f:
        with Solver(bootstrap_with=CNF(from_clauses=clauses)) as solver:
            is_sat = solver.solve()
            print(gen_runtime(args.clauses, args.vars, 
                  clauses2str, is_sat), file=f)
            print(gen_compile_time(args.clauses, args.vars, 
                  clauses2str, is_sat), file=f)
            print(gen_hybrid(args.clauses, args.vars,
                  clauses2str, is_sat), file=f)


if __name__ == "__main__":
    main()