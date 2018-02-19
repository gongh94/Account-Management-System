/* 2017(c) Hangfeng Gong */

#pragma once

#include"StockNode.h"

class PortfolioList {

friend class StockAccount;

public:
	PortfolioList();
	~PortfolioList();
	void insertAtFront(const StockNode&);
	void insertAtBack(const StockNode&);
	bool removeFromFront();
	bool removeFromBack();
	bool isEmpty() const;
	void print() const;
	void removeNode(string);
	StockNode* catchNode(string);

	double totalValue();
	void sort();
	void swap(StockNode*, StockNode*);

private:
	StockNode *firstPtr;
	StockNode *lastPtr;
	StockNode *getNewNode(const StockNode&);

};