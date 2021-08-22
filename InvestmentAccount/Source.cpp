#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <iomanip>
#include <conio.h>
#include "InvestmentAccount.h"
using namespace std;

// print results stored in passed in vector.  Display passed in title initially
void printResults(string title, const vector<tuple<float,float>> &data) {
	cout << title << endl;
	cout << "========================================================" << endl;
	// display data in 3 columns
	cout << left
		<< setw(8) << "  Year"
		<< setw(20) << "  Year End Balance"
		<< setw(28) << "  Year End Earned Interest"
		<< endl
		<< "--------------------------------------------------------" << endl;
	// loop through vector to display yearly results in 3 columns
	for (int i = 0; i < data.size(); i++) {
		cout << left
			<< setw(4) << "   " << setw(4) << i + 1
			<< std::fixed << std::setprecision(2)
			<< setw(8) << "       $" << setw(12) << get<0>(data.at(i))
			<< setw(12) << "           $" << setw(16) << get<1>(data.at(i))
			<< endl;
	}
}

// function that prompts user for info to create an InvestmentAccount
InvestmentAccount getInvestmentAccount() {
	// variables to store user input
	float initial, monthly, interest;
	int years;
	cout << "********************************************" << endl;
	cout << "*****************Data Input*****************" << endl;
	cout << "Initial Investment Amount: $";
	// get initial investment
	cin >> initial;
	// if passed in value isn't float or is less than 0 throw error
	if (cin.fail() || initial < 0) {
		throw runtime_error("Invalid initial investment.");
	}
	cout << "Monthly Deposit: $";
	// get monthly deposit amount
	cin >> monthly;
	// if passed in value isn't float or is less than 0 throw error
	if (cin.fail() || monthly < 0) {
		throw runtime_error("Invalid monthly deposit.");
	}
	cout << "Anual Interest: %";
	// get interest rate
	cin >> interest;
	// if passed in value isn't float or is less than 0 throw error
	if (cin.fail() || interest < 0) {
		throw runtime_error("Invalid interest.");
	}
	cout << "Number of years: ";
	// get number of years
	cin >> years;
	// if passed in value isn't int or is less than 0 throw error
	// note float will not fail as it is passed in as int
	// for example 5.9 will not fail as it is passed in as 5
	if (cin.fail() || years < 1) {
		throw runtime_error("Invalid years entry.");
	}
	cout << endl;
	// create and return InvestmentAccount with user inputs
	return InvestmentAccount(initial, monthly, interest, years);
	
}

// function that stores year end balance and interest as tuple per year in passed in vector for passed in account
// adds monthlyDeposit amount in account monthly if monthlyInvestment is true
void getInvestmentData(vector<tuple<float, float>> &data, InvestmentAccount account, bool monthlyInvestment) {
	// local variables to store totals while calculating year results 
	float yearlyBalance;
	float yearlyInterest;
	// initialize monthlyDeposit to 0 but change to account's monthly deposit if monthlyInvesment is true
	float monthlyDeposit = 0;
	if (monthlyInvestment) {
		monthlyDeposit = account.monthlyDeposit();
	}
	// initialize yearlyBalance with initial investment from account
	yearlyBalance = account.initialInvestment();
	// loop through every month adding interest and monthly deposit amount (0 if monthlyInvestment is false)
	for (int i = 0; i < 12; i++) {
		yearlyBalance += monthlyDeposit;
		yearlyBalance += yearlyBalance * (account.interestRate() / 100) / 12;
	}
	// calculate yearly interest based on initialInvestment and monthlyDeposit from account
	yearlyInterest = yearlyBalance - account.initialInvestment() - monthlyDeposit * 12;
	// store as tuple in first entry of data
	data.push_back(make_tuple(yearlyBalance, yearlyInterest));
	// loop through every year in account to calculate year end balance and interest
	for (int i = 1; i < account.numYears(); i++) {
		// initialize with last years end balance
		yearlyBalance = get<0>(data.at(i - 1));
		// loop through every month adding interest and monthly deposit amount (0 if monthlyInvestment is false)
		for (int j = 0; j < 12; j++) {
			yearlyBalance += monthlyDeposit;
			yearlyBalance += yearlyBalance * (account.interestRate() / 100) / 12;
		}
		// calculate yearly interest based on initialInvestment and monthlyDeposit from account
		yearlyInterest = yearlyBalance - get<0>(data.at(i - 1)) - monthlyDeposit * 12;
		//store as tuple in data
		data.push_back(make_tuple(yearlyBalance, yearlyInterest));
	}
}


int main() {
	// variable to store accountData
	vector<tuple<float, float>> accountData;
	char userReentry = 'y';
	// try block to insure proper user entry
	try {
		while (userReentry != 'n' && userReentry != 'N') {
			// clear accountData in case prior use
			accountData.clear();
			// create new account
			InvestmentAccount investmentAccount = getInvestmentAccount();
			// get account data without monthly deposit
			getInvestmentData(accountData, investmentAccount, false);
			// Pause for user entry to display results
			cin.clear();
			cout << "Press any key to continue...";
			_getch();
			cout << endl;
			// print account data without monthly deposit to screen
			printResults("Balance and Interest Without Additional Monthly Deposits", accountData);
			// clear accountData for reuse
			accountData.clear();
			// get account data with monthly deposit
			getInvestmentData(accountData, investmentAccount, true);
			// print account data with monthly deposit to screen
			printResults("Balance and Interest With Monthly Deposits", accountData);
			cout << endl;
			// prompt user for reentry
			cout << "Would you like to try different values? (Y/y or N/n):";
			cin >> userReentry;
			// if user doesn't enter n or y prompt for entry again
			while (userReentry != 'y' && userReentry != 'Y' && userReentry != 'n' && userReentry != 'N') {
				cout << "Please enter 'y' for yes or 'n' for no" << endl;
				cout << "Would you like to try different valuse? (Y/y or N/n):";
				cin >> userReentry;
			}
		}
		}
		// catch and handle input errors
		catch (runtime_error& excpt) {
			cout << excpt.what() << endl;
			cout << "Unable to create account." << endl;
		}
	
	return 0;
}