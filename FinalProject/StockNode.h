/* 2017(c) Hangfeng Gong */

#pragma once
#include<iostream>
#include<string>

using std::string;

class StockNode
{
friend class PortfolioList;
friend class StockAccount;

private:
	StockNode *prevPtr;
	StockNode *nextPtr;

	int shares;
	double pps; // price per share when the transaction was made
	double cpps; // current price per share
	double value;

	string symbol;

public:
	StockNode(int, double, string);
	double getValue();

	void updateStockPrice(double); // update current stock price
	void updateStockShares(int);
};

