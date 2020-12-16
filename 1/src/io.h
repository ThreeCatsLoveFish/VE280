#ifndef __IO_H__
#define __IO_H__

#include <string>
using namespace std;

double GetParam(string prompt, double min, double max);
//     EFFECTS: Prints the prompt, and reads a double from cin.
//              If the value is between min and max, inclusive, returns
//              it.  Otherwise, repeats.

void PrintHeader (void);
//     EFFECTS: prints out a nice header for the payment info table.
//     MODIFIES: cout

void PrintMonthlyData (int month, double principal, 
		       double interest, double loaned);
//     EFFECTS: prints out a row in the payment info table.
//     MODIFIES: standard output stream

#endif
