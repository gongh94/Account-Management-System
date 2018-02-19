/* 2017(c) Hangfeng Gong */

#pragma once
#include"Account.h"
#include<string>
#include<ctime>
#include<fstream>
#include<iomanip>

using namespace std;

class BankAccount : public Account {


public:
	void deposit(double);
	void withdraw(double);
	void log(string, double, double);
	void history();
};