/*
 * This is VE280 Project 4, FA2020.
 * Written by Changyuan Qiu & Chujie Ni.
 * Latest Update: 10/15/2020.
 * All rights reserved.
 */


/*
 * Attention: any content in this file are not allowed to be modified and should be implemented.
 */
#ifndef CLAUSE_H
#define CLAUSE_H


/* Constants */
// Max number of literals in a clause
const unsigned int MAX_LITERALS = 50;

struct Literal
/*
// Type: Literal
// ------------------
// The type Literal is used to represent a literal.
// Its attributes consist of:
// * ID: variable ID of the literal, e.g., 0 for literals x0 and -x0, 1 for literals x1 and -x1, etc.
// * negative: represent the form of the literal in the clause,
//   i.e., 'true' for negative form, e.g., -x0;
//         'false' for positive form, e.g., x0.
*/
{
    unsigned int ID;
    bool negative;
};

class Clause
/*
// Type: Clause
// ------------------
// The type Clause is used to represent a clause.
// Its attributes consist of:
// * literals: an array of literals.
// * numLiterals: number of literals in the clause, e.g. numLiterals = 3 for a clause = (x0 | x1 | -x2).
// * value: used to represent 2 special states of a clause: (0) and (1).
//   When clause = (0), numLiterals = 0 and value = 0.
//   When clause = (1), numLiterals = 0 and value = 1.
//   Otherwise, numLiterals > 0 and value = -1.
*/
{
    Literal literals[MAX_LITERALS];
    unsigned int numLiterals;
    int value;

public:
    Clause();
    // EFFECTS: constructs an empty clause.

    void addLiteral(Literal literal);
    // MODIFIES: this
    // EFFECTS: add a literal to the current clause.

    int evaluate(const int val[]) const;
    // REQUIRES: the i-th element in val[] represents the value of the i-th variable:
    // 1 (true), 0 (false), or -1 (unknown) in sequence of variable ID.
    // The length of val[] should be exactly equal to the number of variables (represented by CNF::numVars).
    // EFFECTS: given an assignment of variables, evaluate and return the value of the clause:
    // 1: the clause evaluates to true,
    // e.g. for clause = (x0 | -x1 | x2), if val = [0,0,0], clause.evaluate(val) = 1
    // 0: the clause evaluates to false,
    // e.g. for clause = (x0 | -x1 | x2), if val = [0,1,0], clause.evaluate(val) = 0
    // -1: the value of the clause is unknown,
    // e.g. for clause = (x0 | -x1 | x2), if val = [0,1,-1], clause.evaluate(val) = -1

    void eliminate(Literal literal);
    // MODIFIES: this
    // EFFECTS: given a literal, simplify the current clause by assuming that this literal is true.
    // The order of the other literals in the clause keeps unchanged.

    void print() const;
    // EFFECTS: print the clause in the following form:
    // If numLiterals = 0, simply print (0) or (1) according to the "value" attribute.
    // Otherwise, print the CNF in form like: (-x0 | x1 | -x2).
    // Note that there should be a white space between every literal and “|”, but
    // there should be no space between a literal and a parenthesis.
    // If there is only a single literal, print like: (x0). 

    unsigned int getNumLiterals() const;
    // EFFECTS: return numLiterals of the Clause instance.

    Literal getLiteral(unsigned int i) const;
    // EFFECTS: return the i-th literal of the Clause instance (this->literals[i]).

    ~Clause();
    // EFFECTS: destruct a Clause instance. If there's no extra operations needed,
    // just leave it empty.
};


#endif // CLAUSE_H
