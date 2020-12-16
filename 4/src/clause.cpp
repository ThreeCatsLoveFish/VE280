/**
 * @file clause.cpp
 * @author Zhimin Sun
 * @date 2020-11-16
 * @course 2020FA VE280
 */
#include "clause.h"
#include <iostream>

using namespace std;

Clause::Clause() : numLiterals(0), value(-1) {}

Clause::~Clause() { numLiterals = 0; }

void
Clause::addLiteral(Literal literal)
{
    literals[numLiterals++] = literal;
}

int
Clause::evaluate(const int val[]) const
{
    if (numLiterals == 0) {
        return value;
    }
    int result = 0;
    for (unsigned int i = 0; i < numLiterals; i++) {
        if (val[literals[i].ID] == -1) {
            result = -1;
        }
        if ((!literals[i].negative && val[literals[i].ID] == 1) ||
            (literals[i].negative && val[literals[i].ID] == 0)) {
            return 1;
        }
    }
    return result;
}

void
Clause::eliminate(Literal literal)
{
    for (unsigned int i = 0; i < numLiterals;) {
        if (literal.ID == literals[i].ID) {
            if (literal.negative == literals[i].negative) {
                value       = 1;
                numLiterals = 0;
                break;
            }
            if (numLiterals == 1) {
                value       = 0;
                numLiterals = 0;
                break;
            }
            for (unsigned int j = i; j < numLiterals - 1; j++) {
                literals[j] = literals[j + 1];
            }
            numLiterals--;
        } else {
            i++;
        }
    }
}

void
Clause::print() const
{
    if (numLiterals == 0) {
        cout << "(" << value << ")";
    } else {
        cout << "(";
        for (unsigned int i = 0; i < numLiterals; i++) {
            if (i > 0) {
                cout << " | ";
            }
            if (literals[i].negative) {
                cout << "-";
            }
            cout << "x" << literals[i].ID;
        }
        cout << ")";
    }
}

unsigned int
Clause::getNumLiterals() const
{
    return numLiterals;
}

Literal
Clause::getLiteral(unsigned int i) const
{
    return literals[i];
}
