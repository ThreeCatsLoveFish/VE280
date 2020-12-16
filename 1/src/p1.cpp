#include "io.h"

void Money()
//   EFFECTS: Prints the prompt, reads the data, and prints the detail
//            information of loan amount.
//   MODIFIES: standard output stream
{
    double  pay   = 0;
    double  rate  = 0;
    int     month = 0;

    pay = GetParam("Please enter the monthly payment: ",
                   /*min=*/1,
                   /*max=*/100000);
    rate = GetParam("Please enter the interest rate: ",
                    /*min=*/0,
                    /*max=*/1) / 12;
    month = GetParam("Please enter the duration of the loan, in years: ",
                     /*min=*/1,
                     /*max=*/100) * 12;
    PrintHeader();
    for (double prev_balance = 0, curr_balance = 0; month > 0; ) {
        prev_balance = curr_balance;
        curr_balance = (prev_balance + pay) / (1 + rate);
        PrintMonthlyData(month--,
                         curr_balance - prev_balance,
                         curr_balance * rate,
                         curr_balance);
    }
}

int main()
{
    Money();
    return 0;
}
