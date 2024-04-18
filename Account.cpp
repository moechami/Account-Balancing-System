// Account.cpp - Implementation of the Account class
#include "Account.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

string numberToWords(int num) {
    if (num == 0) return "zero";

    vector<string> below20 = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
                              "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    vector<string> tens = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    vector<string> thousands = {"", "thousand", "million", "billion"};

    string words = "";
    int index = 0;

    while (num > 0) {
        if (num % 1000 != 0) {
            string part = "";
            int hundred = num % 1000 / 100;
            int rest = num % 100;
            if (hundred > 0) {
                part = below20[hundred] + " hundred ";
            }
            if (rest < 20) {
                part += below20[rest];
            } else {
                part += tens[rest / 10] + (rest % 10 ? (" " + below20[rest % 10]) : "");
            }
            words = part + (index > 0 ? " " + thousands[index] + " " : "") + words;
        }
        index++;
        num /= 1000;
    }

    return words;
}

string amountToWords(double amount) {
    int dollars = (int)amount;
    int cents = round((amount - dollars) * 100);
    string result = numberToWords(dollars) + " dollars";
    if (cents > 0) {
        result += " and " + numberToWords(cents) + " cents";
    }
    return result;
}

void Account::loadBalances() {
    ifstream file("balances.txt");
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string type, id;
        double balance;
        if (!(iss >> type >> id >> balance)) { // Ensuring the correct order and types are read
            cerr << "Failed to parse line: " << line << endl;
            continue;  // Skip to the next line on error
        }
        accounts[id] = {type, balance, 0.0, {}};  // Correct initialization of the struct
    }
    file.close();
}

void Account::loadRates() {
    ifstream file("rates.txt");
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string type;
        double rate;
        if (!(iss >> type >> rate)) {
            cerr << "Failed to parse line: " << line << endl;
            continue;  // Skip to the next line on error
        }
        for (auto& account : accounts) {
            if (account.second.type == type) {
                account.second.interestRate = rate;
            }
        }
    }
    file.close();
}

void Account::saveBalances() {
    ofstream file("balances.txt");
    for (const auto& account : accounts) {
        file << account.second.type << " " << account.first << " " << account.second.balance << endl;
    }
    file.close();
}

void Account::displayAccounts() {
    cout << "Account Type, ID, Current Balance, Interest Rate\n";
    for (const auto& account : accounts) {
        cout << account.second.type << ", " << account.first << ", " << account.second.balance
             << ", " << account.second.interestRate << "%\n";
    }
}

void Account::depositMoney() {
    cout << "Current accounts and balances:\n";
    displayAccounts();

    int day;
    cout << "Enter day of the month (1-30): ";
    cin >> day;

    string choice;
    cout << "Deposit into (N)ew or (E)xisting account? (N/E): ";
    cin >> choice;

    string id, type;
    double amount, rate;
    if (choice == "N" || choice == "n") {
        cout << "Enter new account type (Cash, Checking, Savings, CDs): ";
        cin >> type;
        cout << "Enter new account ID: ";
        cin >> id;
        cout << "Enter initial deposit amount: ";
        cin >> amount;
        cout << "Enter interest rate for new account: ";
        cin >> rate;

        // Create and initialize the new account correctly
        AccountDetail newAccount = {type, amount, rate, {}};  // Initialize with empty dailyBalances
        accounts[id] = newAccount;
        accounts[id].dailyBalances[day] = amount;
    } else {
        cout << "Enter account ID for deposit: ";
        cin >> id;
        cout << "Enter deposit amount: ";
        cin >> amount;

        if (accounts.find(id) != accounts.end()) {
            accounts[id].balance += amount;
            accounts[id].dailyBalances[day] = accounts[id].balance;
        } else {
            cout << "Account ID does not exist!\n";
            return;
        }
    }
}

void Account::withdrawMoney() {
    cout << "Current accounts and balances:\n";
    displayAccounts();

    int day;
    cout << "Enter day of the month (1-30): ";
    cin >> day;

    string id, method;
    double amount;
    cout << "Enter account ID for withdrawal: ";
    cin >> id;
    cout << "Enter withdrawal amount: ";
    cin >> amount;
    cout << "Withdraw as (C)ash or (C)heck? (C/H): ";
    cin >> method;

    if (accounts.find(id) == accounts.end()) {
        cout << "Account ID does not exist!\n";
        return;
    }

    if (accounts[id].balance >= amount) {
        accounts[id].balance -= amount;
        accounts[id].dailyBalances[day] = accounts[id].balance;

        if (method == "H" || method == "h") {
            string amountInWords = amountToWords(amount);
            cout << "Check amount: " << amountInWords << endl;
        }
    } else {
        cout << "Insufficient balance for this withdrawal.\n";
    }
}


void Account::checkBalances() {
    displayAccounts();
}

void Account::reviewTransactions() {
    cout << "Review of transactions:\n";
    for (const auto& account : accounts) {
        cout << "Account " << account.first << " transactions:\n";
        for (const auto& balance : account.second.dailyBalances) {
            cout << "Day " << balance.first << ": Balance " << balance.second << "\n";
        }
    }
}

void Account::calculateInterest(int day) {
    for (auto& account : accounts) {
        double totalBalance = 0;
        for (const auto& balance : account.second.dailyBalances) {
            totalBalance += balance.second;
        }
        double averageBalance = totalBalance / account.second.dailyBalances.size();
        double monthlyInterest = averageBalance * (account.second.interestRate / 360 * 30);
        account.second.balance += monthlyInterest;
    }
}

void Account::correctID() {
    string oldId, newId;
    cout << "Enter current ID to correct: ";
    cin >> oldId;
    cout << "Enter new ID: ";
    cin >> newId;

    if (accounts.find(oldId) != accounts.end()) {
        AccountDetail details = accounts[oldId];
        accounts.erase(oldId);
        accounts[newId] = details;
    } else {
        cout << "ID not found!\n";
    }
}
