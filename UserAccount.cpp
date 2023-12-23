#include "UserAccount.h"

// constructor
UserAccount::UserAccount()
{

}

//login
bool UserAccount::logIn(UserAccount& account)
{
    string _userInputId;
    double _userInputPin;
    cout << "please input your ID (10 characters): " << endl;
    cin.ignore(10);
    getline(cin, _userInputId);
    cout << "please input your pin (6 characters): ";
    cin >> _userInputPin;
    _userInputId = account.ID;
    if (!(inputAccountData(account)) || account.pin != _userInputPin)
    {
        cout << "incorrect pin code !" << endl;
        cout << "returning to menu" << endl;
        return 0;
    }
    else 
    {
        cout << "login sucessfully";
        inputAccountData(account);
        return 1;
    }
}

// function to interact with file
bool UserAccount::inputAccountData(UserAccount& account)
{
    ifstream file(account.ID + ".txt");
    if (!file)
    {
        cout << "Error: Account not found." << endl;
        return false;
    }

    file >> account.pin >> account.balance;
    string friendlyAccounts;
    while (file >> friendlyAccounts)
    {
        account.friendlyAccounts.push_back(friendlyAccounts);
    }

    file.close();
    return true;
}

void UserAccount::createAccountFile(const UserAccount& account)
{
    ofstream file(account.ID + ".txt");
    if (!file)
    {
        cout << "account creation failed" << endl;
    }
    else
    {
        cout << "account created sucessfully" << endl;
    }
    cout << "return to menu" << endl;
    file << account.pin << " " << account.balance;
    for (const string& friendlyID : account.friendlyAccounts)
    {
        file << " " << friendlyID;
    }
    file.close();
}

void UserAccount::updateFile(UserAccount& account)
{
    ofstream file;
    file.open(account.ID + ".txt");
    file << account.pin << account.balance;
    string friendlyAccounts;
    while (file << friendlyAccounts)
    {
        account.friendlyAccounts.push_back(friendlyAccounts);
    }
    file.close();
}

// function to generate random ID
string UserAccount::generateRandomID()
{
    // generate the character to random
    const string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    // set maximum length of the ID
    const int idLength = 10;
    string randomID;
    srand(time(0));

    for (int i = 0; i < idLength; ++i)
    {
        // set random ID
        randomID += charset[rand() % charset.length()];
    }

    return randomID;
}

//function to create new account:
void UserAccount::createAccount(UserAccount& account)
{
    account.ID = generateRandomID();
    cout << "your ID is: " << account.ID << endl;
    double userPin;
    cout << "Set your PIN (6 digits): " << endl;;
    cin >> userPin;
    while (userPin < 100000 || userPin > 1000000)
    {
        cout << "error, please set a 6 digits password: ";
        cout << "Set your PIN (6 digits): " << endl;
        cin >> userPin;
    }
    account.pin = userPin;
    account.balance = 0.0;
    createAccountFile(account);
}

// function to exit the login menu
void exit()
{
    return;
}

//function to display account information
void UserAccount::AccountInformation(UserAccount& account)
{
        cout << "Account ID: " << account.ID << endl;
        cout << "Balance: $" << account.balance << endl;
        cout << "Friendly account: " << endl;
        for (const string& friendlyID : account.friendlyAccounts)
        {
            cout << friendlyID << " ";
        }
        cout << endl;
}

//function to withdraw the money
void UserAccount::withdraw(UserAccount& amount)
{
    const int opt1 = 10, opt2 = 20, opt3 = 50, opt4 = 100;
    int option = 0;
    do
    {
        cout << "input the amount to withdraw: " << endl;
        cout << "1. " << opt1 << endl;
        cout << "2. " << opt2 << endl;
        cout << "3. " << opt3 << endl;
        cout << "4. " << opt4 << endl;
        cout << "5. Other "  << endl;
        cin >> option;
        switch (option)
        {
        case(1):
        {
            if (opt1 > amount.balance)
            {
                cout << "not enough money!";
                break;
            }
            else
            amount.balance -= 10;
        }
        case(2):
        {
            if (opt2 > amount.balance)
            {
                cout << "not enough money!";
                break;
            }
            else
            amount.balance -= 20;
        }
        case(3):
        {
            if (opt3 > amount.balance)
            {
                cout << "not enough money!";
                break;
            }
            else
            amount.balance -= 50;
        }
        case(4):
        {
            if (opt4 > amount.balance)
            {
                cout << "not enough money!";
                break;
            }
            else
            amount.balance -= 100;
        }
        case(5):
        {
            int otherAmount;
            cout << "amount you want to withdraw: ";
            cin >> otherAmount;
            if (otherAmount > amount.balance)
            {
                cout << "not enough money!";
                break;
            }
            else
            {
                amount.balance -= otherAmount;
            }
        }
        }
            updateFile(amount);
    } while (option > 0 && option <= 5);
}

//function to deposit the money
void UserAccount::deposit()
{

}

//function to tranfer the money to friendly account
void UserAccount::transfer()
{

}

//function to exit the main menu of ATM
void UserAccount::logOut()
{
    return;
}
