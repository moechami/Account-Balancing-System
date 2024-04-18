// Account.h - holds classes
/*********************************************
Name: Mohammad El-Chami
Creation Date: 4/10/2024
Modification Date: 4/10/2024 - 4/18/2024
Purpose: Header file for the Account class.
*********************************************/
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <map>
#include <vector>

using namespace std;

struct AccountDetail {
    string type;
    double balance;
    double interestRate;
    map<int, double> dailyBalances;  // balances for each day of the month
};

class Account {

private:
    map<string, AccountDetail> accounts;  // storage of accounts by ID

public:

    void loadBalances();
    void loadRates();
    void saveBalances();
    void displayAccounts();
    void depositMoney();
    void withdrawMoney();
    void checkBalances();
    void reviewTransactions();
    void calculateInterest(int day);
    void correctID();
};

#endif
