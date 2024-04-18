// main.cpp
#include "Account.h"
#include <iostream>

using namespace std;

int main() {
    Account accountManager;
    accountManager.loadBalances();
    accountManager.loadRates();

    int choice;
    do {
        cout << "------------------------ Menu --------------------------\n";
        cout << "1. Deposit money\n";
        cout << "2. Withdraw money\n";
        cout << "3. Check balances\n";
        cout << "4. Review\n";
        cout << "5. Save\n";
        cout << "6. Correct ID\n";
        cout << "7. Quit\n";
        cout << "--------------------------------------------------------\n";
        cout << "Please Enter Your Choice (1-7): ";
        cin >> choice;

        switch (choice) {
            case 1:
                accountManager.depositMoney();
                break;
            case 2:
                accountManager.withdrawMoney();
                break;
            case 3:
                accountManager.checkBalances();
                break;
            case 4:
                accountManager.reviewTransactions();
                break;
            case 5:
                cout << "Enter the day of the month: ";
                int day;
                cin >> day;
                accountManager.calculateInterest(day);
                accountManager.saveBalances();
                break;
            case 6:
                accountManager.correctID();
                break;
            case 7:
                cout << "Thank you for using the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
