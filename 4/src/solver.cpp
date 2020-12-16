/**
 * @file solver.cpp
 * @author Zhimin Sun
 * @date 2020-11-21
 * @course 2020FA VE280
 */
#include "solver.h"
#include <iostream>

using namespace std;

/*******************************************************************************
 *                            Constant variables                               *
 ******************************************************************************/
/* Prompt for EVAL result. */
static const char *EVAL[] = {
    "Unknown",
    "False",
    "True",
};

/* Prompt for bool result. */
static const char *VAL = "The value of the Boolean expression is: ";

/* Prompt for SAT result. */
static const char *SAT[] = {
    "The expression is SAT with one solution:\n",
    "The expression is SAT!\n",
    "The expression is unSAT!\n",
};

/* Prompt for decisions. */
static const char *DEC[] = {
    "Make decision x",
    "Reverse previous decision x",
};

/*******************************************************************************
 *                             Class Definition                                *
 ******************************************************************************/
class EnumSolver : public Solver
{
private:
    /**
     * @brief Helper function for solving CNF problem
     *
     * @param cnf CNF object
     * @param val An array of values
     * @param pos Index of value that will be changed
     * @return true  Solution Found
     * @return false Solution not found
     */
    bool
    solveHelper(const CNF &cnf, int val[], const unsigned int pos)
    // EFFECT: Helper function for solving CNF problem
    // MODIFIES: val
    {
        if (pos == cnf.getNumVars()) {
            return cnf.evaluate(val) == 1;
        }
        val[pos] = 0;
        if (solveHelper(cnf, val, pos + 1)) {
            return true;
        }
        val[pos] = 1;
        if (solveHelper(cnf, val, pos + 1)) {
            return true;
        }
        return false;
    }

public:
    void
    solve(const CNF &cnf)
    {
        unsigned int var = cnf.getNumVars();
        int *        val = new int[var];
        if (solveHelper(cnf, val, 0)) {
            cout << SAT[0];
            for (unsigned int i = 0; i < var; i++) {
                if (i > 0) {
                    cout << " ";
                }
                cout << val[i];
            }
            cout << "\n";
        } else {
            cout << SAT[2];
        }
        delete[] val;
    }

    void
    evaluate(const CNF &cnf, const int val[])
    {
        cout << VAL << EVAL[cnf.evaluate(val) + 1] << "\n";
    }
};

class DeductSolver : public Solver
{
private:
    /**
     * @brief Recursively find the unit clause in the CNF
     *
     * @param cnf CNF object
     * @param val An array of values
     * @return CNF New CNF object
     */
    CNF
    findUnit(const CNF &cnf, int val[])
    // EFFECT: Recursively find the unit clause in the CNF
    // MODIFIES: val
    {
        CNF tmp = cnf;
        while (tmp.hasUnit()) {
            Literal unit = tmp.getUnit();
            val[unit.ID] = unit.negative ? 0 : 1;
            cout << "Unit propagate x" << unit.ID << " = " << val[unit.ID]
                 << ":\n";
            tmp = tmp.unitPropagate(unit, val);
            tmp.print();
        }
        return tmp;
    }

    /**
     * @brief Copy values in array
     *
     * @param to   To this array
     * @param from From this array
     * @param size size of array
     */
    void
    copyValue(int to[], const int from[], const unsigned int size)
    // EFFECT: Copy values in array
    // MODIFIES: to
    {
        for (unsigned int i = 0; i < size; i++) {
            to[i] = from[i];
        }
    }

    /**
     * @brief Helper function for solving CNF problem
     *
     * @param cnf CNF object
     * @param val An array of values
     */
    bool
    solveHelper(const CNF &cnf, int val[])
    // EFFECT: Helper function for solving CNF problem
    // MODIFIES: val
    {
        unsigned int var = cnf.getNumVars();
        int          copyVal[MAX_VARS];
        copyValue(copyVal, val, var);
        CNF tmpCNF = findUnit(cnf, copyVal);

        if (tmpCNF.evaluate(copyVal) == 1) {
            copyValue(val, copyVal, var);
            return true;
        }
        if (tmpCNF.evaluate(copyVal) == 0) {
            return false;
        }
        for (unsigned int i = 0; i < var; i++) {
            if (copyVal[i] != -1) {
                continue;
            }
            CNF newCNF;
            int tmp[MAX_VARS];

            copyValue(tmp, copyVal, var);
            newCNF = tmpCNF.unitPropagate({i, true}, tmp);
            cout << DEC[0] << i << " = 0:\n";
            newCNF.print();
            if (solveHelper(newCNF, tmp)) {
                copyValue(val, tmp, var);
                return true;
            }
            copyValue(tmp, copyVal, var);
            newCNF = tmpCNF.unitPropagate({i, false}, tmp);
            cout << DEC[1] << i << " = 1:\n";
            newCNF.print();
            if (solveHelper(newCNF, tmp)) {
                copyValue(val, tmp, var);
                return true;
            }
            break;
        }
        return false;
    }

public:
    void
    solve(const CNF &cnf)
    {
        unsigned int var = cnf.getNumVars();
        int *        val = new int[var];

        for (unsigned int i = 0; i < var; i++) {
            val[i] = -1;
        }
        cout << "Start deductive solver for:\n";
        cnf.print();
        if (solveHelper(cnf, val)) {
            cout << SAT[1];
        } else {
            cout << SAT[2];
        }
        delete[] val;
    }

    void
    evaluate(const CNF &cnf, const int val[])
    {
        cout << VAL << EVAL[cnf.evaluate(val) + 1] << "\n";
    }
};

Solver *
getEnum()
{
    static Solver *solver;

    if (solver == nullptr) {
        solver = new EnumSolver();
    }
    return solver;
}

Solver *
getDeduct()
{
    static Solver *solver;

    if (solver == nullptr) {
        solver = new DeductSolver();
    }
    return solver;
}
