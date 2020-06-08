//
//  Fund.cpp
//  Program5
//
//  Created by Jose Palomera on 11/26/19.
//  Copyright © 2019 Jose Palomera. All rights reserved.
//

#include <stdio.h>

#include "Fund.h"
#include <string>
using namespace std;

Fund::Fund(){
    this->balance = 0;
}

Fund::Fund(string nameOfFund){
    
    this->fundName = nameOfFund;
    this->balance = 0;
}

Fund::~Fund(){

}

bool Fund::Deposit(int money){
    
    this->balance += money;
    return true;
}

bool Fund::Withdraw(int money){
    
    //Checks to see if we can first withdraw money or not
    if(canWithdraw(money)){
        this->balance -= money;
        return true;
    }
    
    return false;
}

bool Fund::addTransaction(Transaction transaction){
   
    //Adds a transaction to the Funds history
    myHistory.push_back(transaction);
    return true;
}

void Fund::viewHistory()const{
    
    //Shows the transaction history of the fund
    if(myHistory.size() != 0){
        
        cout << this->fundName << ": $" << balance << endl;
        
        for(int i = 0; i < myHistory.size(); i++){
            cout << " " << myHistory[i];
        }
    }
    
}

bool Fund::canWithdraw(int money){
    
    //Checks to see if the amount of money we want doesn't exceed
    //the balance
    if(this->balance >= money){
        return true;
    }
    
    return false;
}

void Fund::setFundName(string name){
        
    this->fundName = name;
}

void Fund::setFundBalance(int bal){
    
    this->balance = bal;
}

string Fund::getFundName()const{
    
    return this->fundName;
}

int Fund::getBalance()const{
    
    return this->balance;
}

//Overloaded equals operator
Fund Fund::operator=(const Fund &fund){
    
    Fund temp;
    temp.myHistory = fund.myHistory;
    temp.fundName = fund.fundName;
    temp.balance = fund.balance;
    return temp;
}

ostream& operator<<(ostream &out, const Fund &f){
    
    out << f.getFundName() << ": $" << f.getBalance() << endl;
    return out;
}
