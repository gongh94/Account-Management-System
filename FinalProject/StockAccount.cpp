/* 2017(c) Hangfeng Gong */

#include "StockAccount.h"
#include <fstream>   
#include "mex.h"        
#include <engine.h>   

using std::ifstream;
using std::cout;
using std::endl;

double StockAccount::stockPrice(string tsymbl)
{
	string symbol, date;
	double price=0;

	srand(time(0));  

	int r = rand() % 2; 

	if (r == 0)
	{
		ifstream ifs("Result_1.txt", std::ios::in);

		if (!ifs.is_open())
		{
			cout << "Cannot retrieve stock inofromation\n" << endl;
			return 0;
		}

		while (ifs >> symbol >> price >> date)
		{
			if (symbol == tsymbl)
			{
				return price;
			}
		}
	}
	else {
		ifstream ifs("Result_2.txt", std::ios::in);

		if (!ifs.is_open())
		{
			cout << "Cannot retrieve stock inofromation\n" << endl;
			return 0;
		}

		while (ifs >> symbol >> price >> date)
		{
			if (symbol == tsymbl)
			{
				return price;
			}
		}
	}
	return 0;
}


bool StockAccount::buy(string tsymbl, int shares, double maxPrice)
{
	loadCashBalance();

	double sPrice = stockPrice(tsymbl);

	if (sPrice > maxPrice)
	{
		cout << "Transaction failed. " << tsymbl << " is $" << sPrice << "per share, higher than expectation\n\n";
		return false;
	}
	else if (sPrice == 0) {
		cout << "Transaction failed. This stock does not exist.\n\n";
		return false;

	}
	else {
		double stockValue = shares*sPrice;
		if (stockValue > cash_balance)
		{
			cout << "Transaction failed. Insufficient balance in the account.\n\n";
			return false;
		}
		else {

			/*Observer Patthern*/
			cash_balance -= stockValue;
			saveCashBalance();
			myPortfolio.insertAtBack(StockNode(shares, sPrice, tsymbl));
			updatePortfolio();//**
			savePortfolio();

			log_buy(tsymbl, shares, sPrice);
			log("StockBuy", shares*sPrice, cash_balance);
			return true;
		}
	}
}

bool StockAccount::sell(string tsymbl, int shares, double minPrice)
{
	loadCashBalance();

	double sPrice = stockPrice(tsymbl);
	int difference;

	if (sPrice < minPrice)
	{
		return false;
		cout << "Transaction failed. " << tsymbl << " is $" << sPrice << "per share, lower than expectation\n";
	}
	else {
		StockNode* tempPtr = myPortfolio.catchNode(tsymbl);

		if (tempPtr == 0)
		{
			
			cout << "Transaction failed as this stock is not in the portfolio\n\n";
			return false;
		}
		else
		{
			int shares_in_portfolio = tempPtr->shares;
			if (shares > shares_in_portfolio)
			{
				cout << "Transaction failed as shares in the account are not sufficient\n\n";
				return false;
			}
			else {

				/*Observer Pattern*/
				cash_balance += shares*sPrice;
				saveCashBalance();
				difference = shares_in_portfolio - shares;
				if (difference == 0) myPortfolio.removeNode(tsymbl);
				else tempPtr->updateStockShares(difference);
				updatePortfolio(); //**
				savePortfolio();

				log_sell(tsymbl,shares,sPrice);
				log("StockSell", shares*sPrice, cash_balance);
				return true;
			}
		}
		
	}
}

/* Facade Pattern */
double StockAccount::portfolioValue()
{
	return myPortfolio.totalValue();
}




void StockAccount::history()
{
	cout << left << setw(6) << "Event" << setw(20) << "CompanySymbol" << setw(11) << "Number" << setw(15) << "PricePerShare" << setw(11) << "TotalValue" << setw(26) << "Time" << endl;

	ifstream ifs("StockTransactionHistory.txt", ios::app); 

	string line;

	if (ifs.is_open())
	{
		while (!ifs.eof())
		{
			while (getline(ifs, line))
				cout << line << "\n";
		}
	}
	
	ifs.close();  // close the file
}

/* Facade Pattern */
void StockAccount::displayPortfolio()
{
	cout << "Cash balance = $" << cash_balance << "\n";
	myPortfolio.print();
	cout << "Total portfolio value: $" << cash_balance + portfolioValue()<<"\n\n";
}

void StockAccount::loadPortfolio()
{
	StockNode *p = myPortfolio.firstPtr;
	ifstream ifs("portfolio.txt", ios::in);
	
	string symbol;
	int shares;
	double pps;

	while (ifs >> symbol >> shares >> pps )
	{
		myPortfolio.insertAtBack(StockNode(shares, pps, symbol));
	}

	ifs.close();
	
}

void StockAccount::savePortfolio()
{
	StockNode *p = myPortfolio.firstPtr;
	ofstream ofs("portfolio.txt", ios::out);

	while (p != 0)
	{
		ofs << p->symbol << " " << p->shares << " " << p->pps << "\n";
		p = p->nextPtr;
	}

	ofs.close();

}


void StockAccount::portfolioValueGraph()
{
	
	engine *ep;                          
	ep = engOpen(NULL);
	if (ep == NULL)
	{
	std::cout << "Error: Not Found" << endl;
	exit(1);
	}


	string line;
	int count = 0;
	
	//count how many records here are
	ifstream ifs("historicPfValues.txt", ios::in);

	if (ifs.is_open()) {
		while (getline(ifs, line))
			count++;
	}
	else {
		cout << "Cannot retrieve history of portfolio values\n\n";
	}
	
	ifs.close();

	//reopen the file to get values
	ifstream ifss("historicPfValues.txt", ios::in);

	double* value = new double[count] {};
	double* time = new double[count] {};

		int i  = 0 ;
		double tempVb;

		while (!ifss.eof() && i<count)
		{
			ifss >> value[i] >> tempVb;
			time[i] = i;
			i++;
		}

	mxArray *mxa;     
	mxArray *mxb;       
	mxa = mxCreateDoubleMatrix(1, count, mxREAL);    
	mxb = mxCreateDoubleMatrix(1, count, mxREAL);    
	memcpy((void *)mxGetPr(mxa), (void *)value, sizeof(double)*count);   
	memcpy((void *)mxGetPr(mxb), (void *)time, sizeof(double)*count); 
	engPutVariable(ep, "v", mxa);  
	engPutVariable(ep, "t", mxb);   
	engEvalString(ep, "plot(t,v);");  
	engEvalString(ep, "xlabel('Time'),ylabel('Value'),title('Portfolio Value Variance over Time');");
	engEvalString(ep, "pause(15.0);");

	ifss.close();
	engClose(ep);  
	delete [] value;
	delete [] time;

}

void StockAccount::updatePortfolio()
{

	StockNode* currentPtr = myPortfolio.firstPtr;

	while (currentPtr != 0) {
		currentPtr->updateStockPrice(stockPrice(currentPtr->symbol));
		currentPtr = currentPtr->nextPtr;
	}

	myPortfolio.sort();

	//historic portfolio values
	ofstream ofs("historicPfValues.txt", ios::app);
	time_t seconds = time(NULL);

	if (ofs.is_open()) {
		ofs << myPortfolio.totalValue() << " " << seconds << endl;
	}

	ofs.close();

}


void StockAccount::log(string event, double amount, double balance)
{
	time_t seconds = time(NULL);
	struct tm timeinfo;
	localtime_s(&timeinfo, &seconds);
	char timebuff[26];
	asctime_s(timebuff, 26, &timeinfo);
	timebuff[24] = ' '; //exclude a newline

	ofstream ofs("BankAccountHistory.txt ", ios::app);
	ofs << left << setw(11) << event << setw(11) << amount << setw(26) << timebuff << setw(11) << balance << endl;

	ofs.close();
}


void StockAccount::log_buy(string symbl, int volumn, double finalPrice)
{

	time_t seconds = time(NULL);
	struct tm timeinfo;
	localtime_s(&timeinfo, &seconds);
	char timebuff[26];
	asctime_s(timebuff, 26, &timeinfo);
	timebuff[24] = ' ';//exclude a newline

	ofstream ofs("StockTransactionHistory.txt ", ios::app);
	ofs << left << setw(6) << "Buy" << setw(20) << symbl << setw(11) << volumn << setw(15) << finalPrice << setw(11) << volumn*finalPrice << setw(26) << timebuff << endl;
	ofs.close();
}

void StockAccount::log_sell(string symbl, int volumn, double finalPrice)
{
	time_t seconds = time(NULL);
	struct tm timeinfo;
	localtime_s(&timeinfo, &seconds);
	char timebuff[26];
	asctime_s(timebuff, 26, &timeinfo);
	timebuff[24] = ' '; //exclude a newline


	ofstream ofs("StockTransactionHistory.txt ", ios::app);
	ofs << left << setw(6) << "Sell" << setw(20) << symbl << setw(11) << volumn << setw(15) << finalPrice << setw(11) << volumn*finalPrice << setw(26) << timebuff << endl;

	ofs.close();
}

