//
//  Fund.h
//  Program5
//
//  Created by Jose Palomera on 11/26/19.
//  Copyright © 2019 Jose Palomera. All rights reserved.
//

#ifndef Fund_h
#define Fund_h

#include <string>
#include <iostream>
#include <vector>
#include "Transaction.h"

using namespace std;

class Fund{
private:
    
    string fundName;
    int balance;
    vector<Transaction> myHistory;
    
public:
    
    Fund();
    Fund(string nameOfFund);
    ~Fund();
    
    //Deposit and withdraw methods are only needed. If we need to
    //transfer money, we can withdraw money from a fund
    //and then deposit to another one
    bool Deposit(int depot);
    bool Withdraw(int withD);
    bool addTransaction(Transaction transaction);
    //This method views the history of transactions for the fund
    void viewHistory()const;
    bool canWithdraw(int money);
    
    //Basic getters and setters
    void setFundName(string name);
    void setFundBalance(int bal);
    string getFundName()const;
    int getBalance()const;
    
    Fund operator=(const Fund &fund);
    friend ostream& operator<<(ostream &out, const Fund &f);
};

#endif /* Fund_h */
