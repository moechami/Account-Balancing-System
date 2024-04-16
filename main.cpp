// main.cpp
#include <iostream>
#include <string>
#include "myHeader.h"
using namespace std;

int main() {
    // Gets the rates and balances from given txt files
    vector<AccountRate> rates = readRates("rates.txt");
    vector<AccountBalance> balances = readBalances("balances.txt");

    // Initialize accounts from loaded balances
    vector<Account> accounts;
    for (const auto& balance : balances) {
        // This finds the rate for each account type
        auto it = find_if(rates.begin(), rates.end(), [&](const AccountRate& rate) {
            return rate.accountType == balance.accountType;
        });
        double rate = (it != rates.end()) ? it->interestRate : 0; // Use 0 if no rate found
        accounts.push_back(Account(balance.accountType, balance.accountID, balance.accountBalance, rate));
    }

    bool running = true;
    while (running) {
        int choice = displayMenu();

        switch (choice) {
            case 1: // Deposit
                doDeposit(accounts, rates);
                break;
            case 2: // Withdraw
                doWithdrawal(accounts);
                break;
            case 3: // Check Balances
                doCheckBalances(accounts);
                break;
            case 4: // Review Transactions
                doReview(accounts);
                break;
            case 5: // Save
                doSave(accounts, "balances.txt");
                break;
            case 6: // Correct ID
                doCorrectID(accounts);
                break;
            case 7: // Quit
                cout << "Thank you for using my easy to use banking system. Goodbye!" << endl;
                running = false; // Exit so theres no infinite loop
                break;
            default:
                cout << "Invalid selection. Please try again." << endl;
                break;
        }
    }

    return 0;
}
