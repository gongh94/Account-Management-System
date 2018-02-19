/* 2017(c) Hangfeng Gong */

#include "BankAccount.h"
#include<iostream>

using std::cout;

void BankAccount::deposit(double d)
{
	loadCashBalance();
	cash_balance += d;
	saveCashBalance();
	cout << "$" << d << " has been deposited to the account\n\n";

	log("Deposit", d, cash_balance);
}

void BankAccount::withdraw(double w)
{
	loadCashBalance();
	if (w > cash_balance) {
		cout << "The balance is not sufficient!\n";
	}
	else {
		cash_balance -= w;
		cout << "$" << w << " has been withdrawn from the account\n\n";
		saveCashBalance();
	}

	log("Withdraw", w, cash_balance);
}

void BankAccount::log(string event, double amount, double balance)
{
	time_t seconds = time(NULL);
	struct tm timeinfo;
	localtime_s(&timeinfo, &seconds);
	char timebuff[26];
	asctime_s(timebuff, 26, &timeinfo);
	timebuff[24] = ' ';//exclude a newline

	ofstream ofs("BankAccountHistory.txt ", ios::app);
	ofs << left << setw(11) << event << setw(11) << amount << setw(26)<< timebuff << setw(11) << balance<<endl;

	ofs.close();

}

void BankAccount::history()
{
	
	cout << left << setw(11) << "Event" << setw(11) << "Amount" << setw(26) << "Date" << setw(11) << "Balance"<<endl;

	ifstream ifs("BankAccountHistory.txt", ios::app);

	string line;

	if (ifs.is_open())
	{
		while (!ifs.eof())
		{
			while (getline(ifs, line))
				cout << line << "\n";
		}
	}

	cout << "\n";

	ifs.close();  
}
