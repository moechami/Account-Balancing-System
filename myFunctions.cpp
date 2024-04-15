//myFunctions.cpp
#include "myHeader.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int displayMenu() {

    bool validInput = false;
    int userSelection;

    while (!validInput) {
        cout << "------------------------ Menu ------------------------" << endl;
        cout << "1. Deposit Money" << endl;
        cout << "2. Withdraw Money" << endl;
        cout << "3. Check Balances" << endl;
        cout << "4. Review" << endl;
        cout << "5. Save" << endl;
        cout << "6. Correct ID" << endl;
        cout << "7. Quit" << endl;
        cout << "------------------------------------------------------ " << endl;
        cout << "Please Enter Your Choice (1-7): " << endl;

        cin >> userSelection;
        if (cin.fail() || userSelection > 7 || userSelection < 1 ) {
            cout << "Invalid input. Please try again. \n";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            validInput = true;
        }

    }

    return userSelection;
}