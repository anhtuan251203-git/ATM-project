#include "UserAccount.h"

// constructor
UserAccount::UserAccount()
{
    ID =  "";
    pin = 0;
    balance = 0.0;
}
// setter,getter
void UserAccount::setID(string _id)
{
    ID = _id;
}
string UserAccount::getID()
{
    return ID;
}

bool UserAccount::login(UserAccount& account)
{
    string inputID;
    double inputPin = 0;
    cout << "Enter your ID: ";
    cin >> inputID;
    if (inputAccountData(inputID, account))
    {
        cout << "Enter your PIN: ";
        cin >> inputPin;
        if (inputPin == account.pin)
        {
            cout << "Login successful!" << endl;
            return true;
        }
        else
        {
            cout << "Incorrect PIN. Please try again." << endl;
        }
    }
    else
    {
        cout << "Account not found. Please check your ID." << endl;
    }
    inputAccountData(inputID, account);
    return false;
}

// function to interact with file
bool UserAccount::inputAccountData(const string& _id, UserAccount& account)
{
    setID(_id);
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

void UserAccount::updateFile(const string& _id, const UserAccount& account) 
{
    setID(_id);
    ofstream file(account.ID + ".txt");
    file << account.pin << " " << account.balance << endl;
    for (const string& friendlyID : account.friendlyAccounts) {
        file << " " << friendlyID;
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
        cout << "5. Other " << endl;
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
            cout << "withdraw sucessfully!";
            break;
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
            cout << "withdraw sucessfully!";
            break;
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
            cout << "withdraw sucessfully!";
            break;
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
            cout << "withdraw sucessfully!";
            break;
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
                cout << "withdraw sucessfully!";
                break;
            }
        }
        }
        updateFile(ID, amount);
    } while (option > 0 && option <= 5);
}

//function to deposit the money
void UserAccount::deposit(UserAccount& account)
{
    cout << "Input the amount to deposit: ";
    double depAmount;
    cin >> depAmount;
    if (depAmount < 0)
    {
        cout << "Please input a positive number!" << endl;
        cin >> depAmount;
    }
    account.balance += depAmount;
    cout << "Success!";
    updateFile(ID, account);
}


void UserAccount::transfer(UserAccount& account)
{
    string inputID;
    double amount = 0;
    cout << "input the ID of the account you want to transfer: " << endl;
    cin >> inputID;
    addFriendlyAccount(account, inputID);
    cout << "input the amount you want to transfer: " << endl;
    cin >> amount;
    if (amount > account.balance)
        {
            cout << "not enough money!";
            return;
        }
    account.balance -= amount;
    updateFile(ID, account);
    inputAccountData(inputID, account);
    updateFile(inputID, account);
    cout << "transfer sucessfully! " << endl;
}


bool UserAccount::isNewFriendlyAccount(const UserAccount& user, const string& newFriendlyID) {
    for (const string& friendlyID : user.friendlyAccounts) {
        if (friendlyID == newFriendlyID) {
            cout << "This account is already in your friendly list." << endl;
            return false;
        }
    }
    return true;
}

void UserAccount::addFriendlyAccount(UserAccount& account, string newFriendlyID) 
{
    if (isNewFriendlyAccount(account, newFriendlyID)) 
    {
        char saveChoice;
        cout << "Do you want to save this account as a friendly account? (Y/N): ";
        cin >> saveChoice;

        if (saveChoice == 'Y' || saveChoice == 'y') 
        {
            account.friendlyAccounts.push_back(newFriendlyID);
            updateFile(ID, account);
            cout << "Friendly account added successfully!" << endl;
        }
        else 
        {
            cout << "Friendly account not saved." << endl;
        }
    }
}


//function to exit the main menu of ATM
void UserAccount::logOut()
{
    UserAccount u;
    u.MainMenu();
}

void UserAccount::MainMenu() {
    UserAccount u;
    int option = 0;

    const int login = 1;
    const int signin = 2;
    const int exit = 3;
    do {
        cout << "ATM" << endl;
        cout << login << ". Log in" << endl;
        cout << signin << ". Sign in" << endl;
        cout << exit << ". Exit" << endl;
        cout << "Please pick an option: ";
        cin >> option;
        switch (option) {
        case login:
            if (u.login(u)) {
                UserMenu(u);
            };
            break;
        case signin:
            createAccount(u);
            break;
        case exit:
        default:
            cout << "Please pick a valid option!!" << endl;
            break;
        }
    } while (option > 0 || option < 4);
}

void UserAccount::UserMenu(UserAccount& account) {
    UserAccount u;
    int option = 0;
    const int info = 1;
    const int withdraw = 2;
    const int deposit = 3;
    const int transfer = 4;
    const int logout = 5;
    do {
        cout << "ATM" << endl;
        cout << info << ". Account info" << endl;
        cout << withdraw << ". Withdraw" << endl;
        cout << deposit << ". Deposit" << endl;
        cout << transfer << ". Transfer" << endl;
        cout << logout << ". Logout" << endl;

        cout << "Please pick an option: ";
        cin >> option;
        switch (option) {
        case info:
            u.AccountInformation(account);
            break;
        case withdraw:
            u.withdraw(account);
            break;
        case deposit:
            u.deposit(account);
            break;
        case transfer:
            u.transfer(account);
        case logout:
            u.logOut();
        default:
            cout << "Please pick a valid option!!" << endl;
            break;
        }
    } while (option >= info || option <= logout);
}
