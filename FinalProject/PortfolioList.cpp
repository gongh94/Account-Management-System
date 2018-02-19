/* 2017(c) Hangfeng Gong */

#include "StockNode.h"
#include "PortfolioList.h"
#include<iostream>
#include <iomanip> 

using std::cout;
using std::setw;
using std::left;

PortfolioList::PortfolioList() :firstPtr(0), lastPtr(0) {

};

PortfolioList::~PortfolioList() {

	if(!isEmpty()){
	 StockNode *currentPtr = firstPtr;
	 StockNode *tempPtr;
		while (currentPtr != 0) {  
		 tempPtr = currentPtr;
		 currentPtr = currentPtr->nextPtr;
		 delete tempPtr;} 
	 } 
};

void PortfolioList::insertAtFront(const StockNode& snode) {
	
	StockNode* newPtr = getNewNode(snode);
	
	if (isEmpty()) {
		firstPtr = lastPtr = newPtr;
	}
	else {
		newPtr->nextPtr = firstPtr;
		firstPtr->prevPtr = newPtr;
		firstPtr = newPtr;
	}
}

void PortfolioList::insertAtBack(const StockNode& snode) {

	StockNode* newPtr = getNewNode(snode);

	if (isEmpty()) {
		firstPtr = lastPtr = newPtr;
	}
	else {
		lastPtr->nextPtr = newPtr;
		newPtr->prevPtr = lastPtr;
		lastPtr = newPtr;
	}
}

bool PortfolioList::removeFromFront() {

	if (isEmpty())
		return false;
	else {
		StockNode *tempPtr = firstPtr;

		if (firstPtr == lastPtr)
			firstPtr = lastPtr = 0;
		else
			firstPtr = firstPtr->nextPtr;
			firstPtr->prevPtr = 0;

		delete tempPtr;
		return true;
	}
}

bool PortfolioList::removeFromBack()
{
	if (isEmpty()) {
		return false;
	}
	else {
		StockNode *tempPtr = lastPtr;

		if (firstPtr == lastPtr)
			firstPtr = lastPtr = 0;
		else {
			lastPtr = tempPtr->prevPtr;
			lastPtr->nextPtr = 0;
		}

		delete tempPtr;
	}
	return false;
}

bool PortfolioList::isEmpty() const{
	return firstPtr == 0;
}

StockNode* PortfolioList::getNewNode(const StockNode& snode) {
	return new StockNode(snode);
}

void PortfolioList::print() const
{
	if (isEmpty()) {
		cout << "The portfolio is empty\n\n";
		return;
	}

	StockNode *currentPtr = firstPtr;

	cout << setw(17) << left << "CompanySymbol";

	cout << setw(10) << left << "Number";

	cout << setw(17) << left << "PricePerShare";

	cout << setw(13) << left << "TotalValue"<<"\n";

	while (currentPtr != 0) {
		cout << setw(17) << left << currentPtr->symbol;

		cout << setw(10) << left << currentPtr->shares;

		cout << setw(17) << left << currentPtr->cpps;

		cout << setw(13) << left << currentPtr->value<< "\n";

		currentPtr = currentPtr->nextPtr;
	}

}

void PortfolioList::removeNode(string s)
{
	if (isEmpty()) cout << "Stock Symbol Not Found\n";
	else {
		StockNode* tempPtr = firstPtr;

		//locate the target element
		while (tempPtr->symbol.compare(s) != 0 && tempPtr != lastPtr) tempPtr = tempPtr->nextPtr;

		if (tempPtr == lastPtr) {
			if (tempPtr->symbol.compare(s) != 0) cout << "Stock Symbol Not Found\n";
			else removeFromBack();
		}
		else if (tempPtr == firstPtr) removeFromFront();
		else {
			tempPtr->prevPtr->nextPtr = tempPtr->nextPtr;
			tempPtr->nextPtr->prevPtr = tempPtr->prevPtr;
			delete tempPtr;
		}


	}
}

StockNode * PortfolioList::catchNode(string s)
{
	if (isEmpty()) return 0;

	StockNode* tempPtr = firstPtr;

	while (tempPtr->symbol != s && tempPtr != lastPtr) tempPtr = tempPtr->nextPtr;

		if (tempPtr == lastPtr) {
			if (tempPtr->symbol != s) return 0;
			else return lastPtr;
		} else return tempPtr;

}

double PortfolioList::totalValue()
{
	if (isEmpty()) {
		return 0;
	}

	StockNode *currentPtr = firstPtr;

	double totalValue = 0;

	while (currentPtr != 0) {

		totalValue += currentPtr->value;

		currentPtr = currentPtr->nextPtr;
	}
	return totalValue;
}

void PortfolioList::sort()
{
	StockNode *curr,*endsign;

	endsign = lastPtr;

	while (endsign != firstPtr) {

		curr = firstPtr;
		
		while (curr != endsign) {

			if (curr->value < curr->nextPtr->value) swap(curr, curr->nextPtr);

			curr = curr->nextPtr;
		}

		endsign = endsign->prevPtr;
	}

}

//auxiliary function for sorting; only swap the data
void PortfolioList::swap(StockNode* left, StockNode* right) {
	//swap
	string t_symbol = left->symbol;
	int t_shares = left->shares;
	double t_pps = left->pps, t_cpps = left->cpps, t_value = left->value;

	left->symbol = right->symbol;
	left->shares = right->shares;
	left->pps = right->pps;
	left->cpps = right->cpps;
	left->value = right->value;

	right->symbol = t_symbol;
	right->shares = t_shares;
	right->pps = t_pps;
	right->cpps = t_cpps;
	right->value = t_value;
	
}