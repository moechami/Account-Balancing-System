// myHeader.h
#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;

int displayMenu();

struct AccountRate {
    string accountType;
    double interestRate;
};

struct AccountBalance {
    string accountType;
    string accountID;
    double accountBalance;
};

vector<AccountRate> readRates(const string& filename);
vector<AccountBalance> readBalances(const string& filename);

class Account {
public:
    string accountType;
    string accountID;
    double balance;
    double interestRate;

    Account(string type, string ID, double initialBalance, double rate): accountType(type), accountID(ID), balance(initialBalance), interestRate(rate) {}

    void deposit(double amount);
    void withdraw(double amount);
    static void displayAccounts(const vector<Account>& accounts);
    static void updateInterest(vector<Account>& accounts, int day);
};

void doDeposit(vector<Account>& accounts, const vector<AccountRate>& rates);
void doWithdrawal(vector<Account>& accounts);
void doCheckBalances(const vector<Account>& accounts);
void doReview(const vector<Account>& accounts);
void doSave(vector<Account>& accounts, const string& filename);
void doCorrectID(vector<Account>& accounts);
