/* 2017(c) Hangfeng Gong */

#pragma once
#include<string>

using namespace std;

class Account {

protected:
	double cash_balance;

public:
	double balance();
	void loadCashBalance(); // retrieve balance from local file
	void saveCashBalance(); // save current balance to local space
	virtual void log(string, double, double)=0; //track money fluid
	virtual void history()=0;
	//virtual void loadInfo();
	//virtual void log();
};