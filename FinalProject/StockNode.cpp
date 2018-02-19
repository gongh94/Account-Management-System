/* 2017(c) Hangfeng Gong */

#include"StockNode.h"

StockNode::StockNode(int shrs, double price_per_share, string symbl) {
	prevPtr = 0;
	nextPtr = 0;
	shares = shrs;
	symbol = symbl;
	pps = price_per_share;
	cpps = price_per_share;
	value = price_per_share*shrs;
}

double StockNode::getValue() {
	return value;
}

void StockNode::updateStockPrice(double sp)
{
	cpps = sp;
	value = sp*shares;
}

void StockNode::updateStockShares(int ss)
{
	shares = ss;
	value = cpps*ss;
}
