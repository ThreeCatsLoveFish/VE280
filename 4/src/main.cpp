/**
 * @file main.cpp
 * @author Zhimin Sun
 * @date 2020-11-21
 * @course 2020FA VE280
 */
#include "solver.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/* Two types of solver. */
static const char *TYPE[2] = {
    "ENUM",
    "DEDUCT",
};

/* Four types of user commands. */
static const char *CMD[4] = {
    "EXIT",
    "PRINT",
    "EVAL",
    "SAT",
};

/**
 * @brief Build a CNF object with the given arguments
 *
 * This function handel the Input and create the instance of CNF.
 *
 * @param variable Number of variables
 * @param clause Number of clauses
 * @return CNF A CNF object
 */
static CNF
CNFBuilder()
// EFFECT: Build a CNF object with the given arguments
{
    CNF          cnfIns;
    unsigned int variable = 0;
    unsigned int clause   = 0;

    cin >> variable >> clause;
    cin.get();
    cnfIns.setNumVars(variable);
    for (unsigned int i = 0; i < clause; i++) {
        Clause clauseIns;
        string tmp;

        getline(cin, tmp);
        while (true) {
            if (tmp.size() == 0) {
                break;
            }
            Literal input;
            if (tmp[0] == '-') {
                istringstream data(tmp.substr(2));

                data >> input.ID;
                input.negative = true;
            } else {
                istringstream data(tmp.substr(1));

                data >> input.ID;
                input.negative = false;
            }
            clauseIns.addLiteral(input);

            size_t pos = tmp.find('|');
            if (pos >= tmp.size()) {
                break;
            } else {
                tmp = tmp.substr(pos + 2);
            }
        }
        cnfIns.addClause(clauseIns);
    }
    return cnfIns;
}

int
main(int argc, char const *argv[])
{
    CNF     cnf;
    Solver *solver;

    assert(argc == 2);
    if (strcmp(argv[1], TYPE[0]) == 0) {
        solver = getEnum();
    } else if (strcmp(argv[1], TYPE[1]) == 0) {
        solver = getDeduct();
    } else {
        assert(false);
    }
    cnf = CNFBuilder();

    while (true) {
        string cmd;

        cin >> cmd;
        if (strncmp(cmd.data(), CMD[0], 4) == 0) {
            cout << "Bye!" << endl;
            delete solver;
            return 0;
        } else if (strncmp(cmd.data(), CMD[1], 5) == 0) {
            cnf.print();
        } else if (strncmp(cmd.data(), CMD[2], 4) == 0) {
            unsigned int size = cnf.getNumVars();
            int *        data = new int[size];
            for (unsigned int i = 0; i < size; i++) {
                cin >> data[i];
            }
            solver->evaluate(cnf, data);
            delete[] data;
        } else if (strncmp(cmd.data(), CMD[3], 3) == 0) {
            solver->solve(cnf);
        } else {
            assert(false);
        }
    }
}
