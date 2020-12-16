/*
 * This is VE280 Project 4, FA2020.
 * Written by Changyuan Qiu & Chujie Ni.
 * Latest Update: 10/15/2020.
 * All rights reserved.
 */


/*
 * Attention: any content in this file are not allowed to be modified and should be implemented.
 */
#ifndef CNF_H
#define CNF_H

#include "clause.h"

/* Constants */
// Max number of clauses in a CNF expression
const unsigned int MAX_CLAUSES = 100;

// Max number of variables in a CNF expression
const unsigned int MAX_VARS = 50;

class CNF
/*
// Type: CNF
// ------------------
// The type CNF is used to represent the conjunctive normal form of a Boolean expression.
// Its attributes consist of:
// * clauses: an array of clauses.
// * numClauses: number of clauses in the CNF expression,
//   e.g. numClauses = 2 for CNF expression (x0 | -x1) & (x0).
// * numVars: number of variables in the CNF expression,
//   e.g. numVars = 2 for CNF expression (x0 | -x1) & (-x0 | x1)
*/
{
    Clause clauses[MAX_CLAUSES];
    unsigned int numClauses;
    unsigned int numVars;

public:
    CNF();
    // EFFECTS: construct an empty CNF expression.

    void addClause(Clause cls);
    // MODIFIES: this
    // EFFECTS: add a clause to the current CNF expression.

    void eliminate(Literal literal);
    // MODIFIES: this
    // EFFECTS: given a literal, simplify the current CNF expression
    // by assuming that this literal is true.


    int evaluate(const int val[]) const;
    // REQUIRES: the i-th element in val[] represents the value of the
    // i-th variable: 1 (true), 0 (false), or -1 (unknown).
    // The length of val[] should be exactly equal to the number of variables.
    // EFFECTS: given an assignment of variables, evaluate and return the value of the CNF expression:
    // 1: the CNF expression evaluates to true,
    // e.g. for cnf.clauses = (x0 | -x1 | x2) & (x0 | x1 | -x2), if val = [0,0,0], cnf.evaluate(val) = 1
    // 0: the CNF expression evaluates to false,
    // e.g. for cnf.clauses = (x0 | -x1 | x2) & (x0 | x1 | -x2), if val = [0,0,1], cnf.evaluate(val) = 0
    // -1: the value of CNF expression is unknown,
    // e.g. for cnf.clauses = (x0 | -x1 | x2) & (x0 | x1 | -x2), if val = [0,0,-1], cnf.evaluate(val) = -1

    bool hasUnit() const;
    // EFFECTS: check whether there exists a unit clause in this CNF expression.

    Literal getUnit() const;
    // REQUIRES: the current CNF expression has at least one unit clause.
    // EFFECTS: return the only literal of the leftmost unit clause.

    CNF unitPropagate(Literal unit, int val[]) const;
    // MODIFIES: val
    // EFFECTS: given a literal and assuming it to be true, infer the value of its variable,
    // and then return a simplified CNF expression with that variable eliminated from "this" CNF
    // expression. Note that "this" CNF expression is not changed.
    // E.g. cnf.clauses = (-x0) & (x1 | x2), val=[-1,-1,-1], you should first set val=[0,-1,-1],
    // and return a simplified CNF expression with variable x0 eliminated from the current CNF expression.

    void print() const;
    // EFFECTS: print the CNF in form like: (-x0) & (x1 | x2) & (1).
    // See Section Driver Program for details on the output format.

    unsigned int getNumVars() const;
    // EFFECTS: return the number of variables in the CNF expression.

    unsigned int getNumClauses() const;
    // EFFECTS: return the number of clauses in the CNF expression.

    void setNumVars(unsigned int n);
    // MODIFIES: this
    // EFFECTS: modify number of variables of the CNF expression.

    ~CNF();
    // EFFECTS: destruct a CNF instance. If there's no extra operation needed,
    // just leave it empty.
};

#endif // CNF_H
