//
//  Account.h
//  Program5
//
//  Created by Jose Palomera on 11/26/19.
//  Copyright © 2019 Jose Palomera. All rights reserved.
//

#ifndef Account_h
#define Account_h

#include <string>
#include <iostream>
#include "Fund.h"
#include <vector>
using namespace std;

class Account{
    
private:
    
    string firstName;
    string lastName;
    int clientID;
    Fund myFunds[10];
    bool insertCh;
    
public:
    
    Account(string lastName, string firstName, int ID);
    ~Account();
    
    void Deposit(int fundNumber, int depot);
    bool Withdraw(int fundNumber, int with);
    void viewHistory();
    void viewFundHistory(int fundID);
    void addTransaction(Transaction t, int fundNum);
    
    //Basic getters and setters
    string getFundName(int fundNum);
    Fund getFund(int fundNum);
    
    string getFirstName()const;
    string getLastName()const;
    
    int getClientID()const;
    bool getInsertCheck()const;
    
    void setFirstName(string fName);
    void setLastName(string lName);
    void setClientID(int clientID);
    
    friend ostream& operator<<(ostream &out, const Account &acc);
};

#endif /* Account_h */
