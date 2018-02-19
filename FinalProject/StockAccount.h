/* 2017(c) Hangfeng Gong */

#pragma once
#include "Account.h"
#include "PortfolioList.h"
#include<cmath>
#include<time.h>
#include<fstream>
#include<iomanip> 

using namespace std;

class StockAccount : public Account {


public:
	double stockPrice(string); // return current price per share for a stock
	bool buy(string, int, double);
	bool sell(string, int, double);
	double portfolioValue();
	void portfolioValueGraph();
	void history(); // display stock transactions 
	void displayPortfolio();
	void updatePortfolio(); // update stock price in the portfolio and sort them
	
	/*functions for localization*/
	void loadPortfolio();
	void savePortfolio();

protected:
	void log(string, double, double); //inherented from class Account; shared with bank account
	void log_buy(string, int, double); // record a selling transcation
	void log_sell(string, int, double); // record a buying transcation
	//void sortPortfolio();
	

private: //temporary for testing
	PortfolioList myPortfolio;
};