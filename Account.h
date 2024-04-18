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
    map<int, double> dailyBalances;  // Daily balances for each day of the month
};

class Account {
public:
    map<string, AccountDetail> accounts;  // Map of accounts by ID

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

#endif // ACCOUNT_H
