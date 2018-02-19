/* 2017(c) Hangfeng Gong */

#include"PortfolioList.h"
#include"BankAccount.h"
#include"StockAccount.h"

#include<iostream>
#include <stdlib.h>     
#include <time.h>       

using std::cout;

int main() {

	BankAccount b;
	StockAccount s;

	//load account information
	b.loadCashBalance();
	s.loadPortfolio();


	while (true) {
		cout << "Welcome to the Account Management System.\n";
		cout << "Please select an amount to access:\n";
		cout << "1. Stock Portfolio Account\n";
		cout << "2. Bank Account\n";
		cout << "3. Exit\n\n";

		int option;
		bool menuflag;

		cin >> option;

		switch (option) {
		case 1: {

			menuflag = true;

			while (menuflag) {

				cout << "Please select an option:\n";
				cout << "1. Display the price for a stock symbol\n";
				cout << "2. Display the current portfolio\n";
				cout << "3. Buy shares\n";
				cout << "4. Sell shares\n";
				cout << "5. View a graph for the portfolio value\n";
				cout << "6. View transcation history\n";
				cout << "7. Return to previous menu\n\n";

				int option1;
				string tempSymbol;
				int tempShare;
				double tempPrice;

				cin >> option1;

				switch (option1) {
				case 1: {
					cout << "Please enter the stock symbol:\n";
					cin >> tempSymbol;
					cout << tempSymbol << ": $" << s.stockPrice(tempSymbol) << "\n\n";
					break;
				}

				case 2: {

					s.updatePortfolio();
					s.displayPortfolio(); // this function contains updating stock price and sorting the list.
					cout << "Total Value of the portfolio is " << s.portfolioValue() << "\n\n";
					break;
				}

				case 3: {
					cout << "Please enter the stock symbol you wish to purchase:\n";
					cin >> tempSymbol;
					cout << "Please enter the number of shares:\n";
					cin >> tempShare;
					cout << "Please enter the maximum amount you are willing to pay per share:\n";
					cin >> tempPrice;

					if (s.buy(tempSymbol, tempShare, tempPrice))
						cout << "\nYou have purchased " << tempShare << " shares of " << tempSymbol << " at $" << s.stockPrice(tempSymbol) << " each for a total of " << tempShare*s.stockPrice(tempSymbol) << "\n\n";

					cout << "\n";
					break;
				}

				case 4: {
					cout << "Please enter the stock symbol you wish to sell:\n";
					cin >> tempSymbol;
					cout << "Please enter the number of shares:\n";
					cin >> tempShare;
					cout << "Please enter the minimum amount you are willing to receive per share:\n";
					cin >> tempPrice;

					if (s.sell(tempSymbol, tempShare, tempPrice))
						cout << "You have sold " << tempShare << " shares of " << tempSymbol << " at $" << s.stockPrice(tempSymbol) << " each for a total of " << tempShare*s.stockPrice(tempSymbol) << "\n\n";

					cout << "\n";
					break;
				}

				case 5: {
					s.portfolioValueGraph();
					cout << "\n\n";
					break;
				}

				case 6: {
					s.history();
					break;
				}

				case 7: {
					menuflag = false;
					s.savePortfolio();
					break;
				}

				}// end switch

			}//end while

			break;

		}// end case 1

		case 2: {

			int option2;
			double amount;
			bool menuflag = true;


			while (menuflag) {

				cout << "Please select an option:\n";
				cout << "1. View account balance\n";
				cout << "2. Deposit money\n";
				cout << "3. Withdraw money\n";
				cout << "4. Print out history\n";
				cout << "5. Return to previous menu\n\n";

				cin >> option2;

				switch (option2) {

				case 1: {
					cout << "You have " << b.balance() << " in your bank account.\n\n";
					break;
				}

				case 2: {
					cout << "Please enter the amount you wish to deposit\n";
					cin >> amount;
					b.deposit(amount); break;
				}

				case 3: {
					cout << "Please enter the amount you wish to withdraw\n";
					cin >> amount;
					b.withdraw(amount); break;
				}
				case 4: {
					b.history();
					break;
				}

				case 5: {
					menuflag = false;
					break;
				}

				}//end switch
			}
			break;
		}

		case 3: return 0;
		}// end switch

	}


}