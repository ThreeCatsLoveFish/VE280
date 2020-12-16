/*
 * This is VE280 Project 4, FA2020.
 * Written by Changyuan Qiu & Chujie Ni.
 * Latest Update: 10/15/2020.
 * All rights reserved.
 */


/*
 * Attention: any content in this file are not allowed to be modified and should be implemented.
 */
#ifndef SOLVER_H
#define SOLVER_H

#include "cnf.h"

class Solver
/*
// Type: Solver
// ------------------
// The type Solver is an abstract base class that provides the SAT solver interface.
// You need to implement its 2 derived classes in solver.cpp.
*/
{
public:
    virtual void solve(const CNF &cnf) = 0;
    // EFFECTS: handle the "SAT" command (defined in the Driver Program section).
    // Solve if the CNF expression is satisfiable, or SAT;
    // and output corresponding solution info.

    virtual void evaluate(const CNF &cnf, const int val[]) = 0;
    // REQUIRES: value in array val[] is either 0, 1, or -1.
    // The length of val[] is equal to the number of variables.
    // EFFECTS: handle the "EVAL" command (defined in the Driver Program section).
    // Evaluate the value of the CNF expression given an assignment
    // and output the solution info.

    virtual ~Solver() {};
    // Added to suppress compiler warning.
    // If you do not need to do anything when destructing, just ignore it.
};


extern Solver *getEnum();
// EFFECTS: returns a pointer to a "enumerative solver"
// You should only declare one static global instance of EnumSolver

extern Solver *getDeduct();
// EFFECTS: returns a pointer to a "deductive solver"
// You should only declare one static global instance of DeductSolver

#endif // SOLVER_H
