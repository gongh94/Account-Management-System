/* 2017(c) Hangfeng Gong */

#include "Account.h"
#include <fstream>
using namespace std;


void Account::saveCashBalance()
{
	ofstream ofs("CashBalance.txt", ios::out);
	ofs << cash_balance;
	ofs.close();
}

void Account::loadCashBalance()
{
	ifstream ifs("CashBalance.txt", ios::in);

	if (ifs.peek() == EOF) {
		ofstream ofs("CashBalance.txt", ios::out);
		ofs << 10000;
		ofs.close();
		cash_balance = 10000;
	}
	else
	{
		ifs >> cash_balance;
	}

	ifs.close();
}

double Account::balance() {

	loadCashBalance();
	return cash_balance;
}