#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<algorithm>
using namespace std;

class UserAccount
{
private:
	string ID;
	double pin;
	vector<string> friendlyAccounts;
	double balance;
public:
	// default constructor
	UserAccount();
	//setter,getter to test each function
	void setID(string);
	string getID();
	//login
	bool login(UserAccount&);
	// function to interact with file:
	bool inputAccountData(const string&, UserAccount&);
	void createAccountFile(const UserAccount&);
	void updateFile(const string&, const UserAccount&);
	// function to generate random id
	string generateRandomID();
	//function to create new account
	void createAccount(UserAccount&);
	//function to exit the login menu of the ATM
	void exit();
	//function to display account information
	void AccountInformation(UserAccount&);
	//function to withdraw the money
	void withdraw(UserAccount&);
	//function to deposit the money
	void deposit(UserAccount&);
	//function to tranfer the money to friendly account
	void transfer(UserAccount&);
	void addFriendlyAccount(UserAccount& account, string);
	bool isNewFriendlyAccount(const UserAccount& , const string& );
	//function to exit the main menu of ATM
	void logOut();
	//MainMenu
	void MainMenu();
	//UserMenu
	void UserMenu(UserAccount&);
};