#include <iostream>
#include <iomanip>
#include "io.h"

double GetParam(string prompt, double min, double max)
{
    double result = min-1.0;
    bool done = false;

    do {
	cout << prompt;
	cin >> result;
	if ((result >= min) && (result <= max)) {
	    done = true;
	}
    } while (!done);
    
    return result;
}

void PrintHeader (void)
{
    cout << endl;
    cout << "Month\tPrincipal\t Interest\t  Balance" << endl;
    cout << "-----\t---------\t---------\t---------" << endl;
}

void PrintMonthlyData (int month, double principal, 
		       double interest, double loaned)
{
    cout << month << "\t" << fixed << setprecision(2) 
	 << setw(9) << principal << "\t" 
	 << setw(9) << interest << "\t" 
	 << setw(9) << loaned << endl;
}

