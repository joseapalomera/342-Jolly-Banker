//
//  Transaction.cpp
//  Program5
//
//  Created by Jose Palomera on 12/1/19.
//  Copyright © 2019 Jose Palomera. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Transaction.h"

using namespace std;

//Accessed when we want to open an account
Transaction::Transaction(char type, string lastName, string firstName, int accID){
    
    setTransaction(type);
    setFirstName(firstName);
    setLastName(lastName);
    setAccountNumber(accID);
    setAcceptance(true);
    
}

//Accessed when we want to deposit or withdraw from an account
Transaction::Transaction(char type, int accID, int amount){
    
    setTransaction(type);
    setAccountNumber(accID);
    setMoney(amount);
    setAcceptance(true);
    
}

//Accessed when we want to transfer money
Transaction::Transaction(char type, int accID, int amount, int toAcc){
    
    setTransaction(type);
    setAccountNumber(accID);
    setMoney(amount);
    setToAccount(toAcc);
    setAcceptance(true);
}

//Accessed when we want to view the history
Transaction::Transaction(char type, int accID){
    
    setTransaction(type);
    setAccountNumber(accID);
    setAcceptance(true);
}

Transaction::~Transaction(){
    
}

bool Transaction::setTransaction(char type){
    
    this->transactionType = type;
    return true;
}

bool Transaction::setAccountNumber(int accNum){
    
    this->accNum = accNum;
    return true;
}

bool Transaction::setMoney(int amount){
    
    this->money = amount;
    return true;
}

bool Transaction::setToAccount(int toAcc){
    
    this->toAcc = toAcc;
    return true;
}

bool Transaction::setFirstName(string firstName){
    
    this->firstName = firstName;
    return true;
}

bool Transaction::setLastName(string lastName){
    
    this->lastName = lastName;
    return true;
}

bool Transaction::setAcceptance(bool statement){
    
    this->accepted = statement;
    return true;
}

char Transaction::getTransaction()const{
    
    return this->transactionType;
}

int Transaction::getAccountNumber()const{
    
    return this->accNum;
}

int Transaction::getMoney()const{
    
    return this->money;
}

int Transaction::getToAccount()const{
    
    return this->toAcc;
}

string Transaction::getFirstName()const{
    
    return this->firstName;
}

string Transaction::getLastName()const{
    
    return this->lastName;
}

bool Transaction::getAcceptance()const{
    
    return this->accepted;
}

ostream& operator<<(ostream &out, const Transaction &trans){
    
    if(trans.getTransaction() == 'D' || trans.getTransaction() == 'W'){
        
        out << "   " << trans.getTransaction() << " " << trans.getAccountNumber() << " " << trans.getMoney();
    }
    else if(trans.getTransaction() == 'T'){
        
        out << "   " << trans.getTransaction() << " " << trans.getAccountNumber() << " " << trans.getMoney() << " " << trans.getToAccount();
    }
   
    //If the transaction didn't go through, then add the "(Failed)" at the end
    if(!trans.getAcceptance()){
        out << " (Failed)";
    }
        
    return out << endl;
}
