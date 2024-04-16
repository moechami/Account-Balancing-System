// myFunctions.cpp
#include "myHeader.h"
#include <algorithm>

// Display Menu and do User Input
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
        cout << "------------------------------------------------------" << endl;
        cout << "Please Enter Your Choice (1-7): ";

        cin >> userSelection;
        if (cin.fail() || userSelection > 7 || userSelection < 1) {
            cout << "Invalid input. Please try again.\n";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            validInput = true;
        }
    }
    return userSelection;
}

// Implement readRates
vector<AccountRate> readRates(const string& filename) {
    ifstream file(filename);
    vector<AccountRate> rates;
    string type;
    double rate;
    while (file >> type >> rate) {
        rates.push_back({type, rate});
    }
    file.close();
    return rates;
}

// Implement readBalances
vector<AccountBalance> readBalances(const string& filename) {
    ifstream file(filename);
    vector<AccountBalance> balances;
    string type, id;
    double balance;
    while (file >> type >> id >> balance) {
        balances.push_back({type, id, balance});
    }
    file.close();
    return balances;
}

// Deposit Method for Account
void Account::deposit(double amount) {
    this->balance += amount;
    cout << "Deposited: " << amount << " to ID: " << this->accountID << endl;
}

// Withdrawal Method for Account
void Account::withdraw(double amount) {
    if (this->balance >= amount) {
        this->balance -= amount;
        cout << "Withdrawn: " << amount << " from ID: " << this->accountID << endl;
    } else {
        cout << "Insufficient balance." << endl;
    }
}

// Display all accounts
void Account::displayAccounts(const vector<Account>& accounts) {
    for (const auto& account : accounts) {
        cout << "Type: " << account.accountType << ", ID: " << account.accountID
             << ", Balance: " << account.balance << ", Rate: " << account.interestRate << "%" << endl;
    }
}

// Update interest for all accounts
void Account::updateInterest(vector<Account>& accounts, int day) {
    for (auto& account : accounts) {
        double dailyInterest = (account.interestRate / 360) * account.balance;
        account.balance += dailyInterest;
        cout << "Interest for " << account.accountID << " on day " << day << " is " << dailyInterest << endl;
    }
}

// do deposit transactions
void doDeposit(vector<Account>& accounts, const vector<AccountRate>& rates) {
    Account::displayAccounts(accounts);
    cout << "Enter the day of the month (1-30): ";
    int day;
    cin >> day;

    cout << "Is this deposit into an existing account or a new account? (existing/new): ";
    string accountType;
    cin >> accountType;
    if (accountType == "existing") {
        string ID;
        double amount;
        cout << "Enter account ID and amount to deposit: ";
        cin >> ID >> amount;
        auto it = find_if(accounts.begin(), accounts.end(), [&](const Account& acc) { return acc.accountID == ID; });
        if (it != accounts.end()) {
            it->deposit(amount);
        } else {
            cout << "Account not found.\n";
        }
    } else if (accountType == "new") {
        string type, ID;
        double amount, rate;
        cin >> type;
        cout << "Enter new account ID: " << endl;
        cin >> ID;
        cout << "Enter initial balance (Ex. 35.86): " << endl;
        cin >> amount;
        cout << "Enter interest rate: " << endl;
        accounts.push_back(Account(type, ID, amount, rate));
        cout << "New account created.\n";
    }
}

// do withdrawal transactions
void doWithdrawal(vector<Account>& accounts) {
    Account::displayAccounts(accounts);
    cout << "Enter the day of the month (1-30): ";
    int day;
    cin >> day;

    string ID;
    double amount;
    cout << "Enter account ID and amount to withdraw: ";
    cin >> ID >> amount;
    auto it = find_if(accounts.begin(), accounts.end(), [&](const Account& acc) { return acc.accountID == ID; });
    if (it != accounts.end()) {
        it->withdraw(amount);
    } else {
        cout << "Account not found.\n";
    }
}

// do checking account balances
void doCheckBalances(const vector<Account>& accounts) {
    Account::displayAccounts(accounts);
}

// do reviewing account transactions
void doReview(const vector<Account>& accounts) {
    // This would require additional transaction tracking which is not currently implemented
    cout << "Transaction history feature not implemented.\n";
}

// do saving account balances
void doSave(vector<Account>& accounts, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Unable to open " << filename << endl;
        return;
    }
    for (const auto& account : accounts) {
        file << account.accountType << " " << account.accountID << " " << account.balance << endl;
    }
    file.close();
    cout << "Accounts saved successfully.\n";
}

// do correcting account IDs
void doCorrectID(vector<Account>& accounts) {
    string oldID, newID;
    cout << "Enter old ID and new ID: ";
    cin >> oldID >> newID;
    auto it = find_if(accounts.begin(), accounts.end(), [&](const Account& acc) { return acc.accountID == oldID; });
    if (it != accounts.end()) {
        it->accountID = newID;
        cout << "Account ID updated successfully.\n";
    } else {
        cout << "Account not found.\n";
    }
}
