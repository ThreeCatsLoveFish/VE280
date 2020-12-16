/**
 * @file cnf.cpp
 * @author Zhimin Sun
 * @date 2020-11-18
 * @course 2020FA VE280
 */
#include "cnf.h"
#include <cassert>
#include <iostream>

using namespace std;

CNF::CNF() : numClauses(0), numVars(0) {}

CNF::~CNF()
{
    numClauses = 0;
    numVars    = 0;
}

void
CNF::addClause(Clause cls)
{
    clauses[numClauses++] = cls;
}

void
CNF::eliminate(Literal literal)
{
    for (unsigned int i = 0; i < numClauses; i++) {
        clauses[i].eliminate(literal);
    }
}

int
CNF::evaluate(const int val[]) const
{
    int result = 1;

    for (unsigned int i = 0; i < numClauses; i++) {
        int eval = clauses[i].evaluate(val);
        if (eval == 0) {
            return 0;
        } else if (eval == -1) {
            result = -1;
        }
    }
    return result;
}

bool
CNF::hasUnit() const
{
    for (unsigned int i = 0; i < numClauses; i++) {
        if (clauses[i].getNumLiterals() == 1) {
            return true;
        }
    }
    return false;
}

Literal
CNF::getUnit() const
{
    for (unsigned int i = 0; i < numClauses; i++) {
        if (clauses[i].getNumLiterals() == 1) {
            return clauses[i].getLiteral(0);
        }
    }
    assert(false);
}

CNF
CNF::unitPropagate(Literal unit, int val[]) const
{
    if (unit.negative) {
        val[unit.ID] = 0;
    } else {
        val[unit.ID] = 1;
    }
    CNF result = *this;
    result.eliminate(unit);
    return result;
}

void
CNF::print() const
{
    for (unsigned int i = 0; i < numClauses; i++) {
        if (i > 0) {
            cout << " & ";
        }
        clauses[i].print();
    }
    cout << endl;
}

unsigned int
CNF::getNumVars() const
{
    return numVars;
}

unsigned int
CNF::getNumClauses() const
{
    return numClauses;
}

void
CNF::setNumVars(unsigned int n)
{
    numVars = n;
}
