//
//  Account.cpp
//  Program5
//
//  Created by Jose Palomera on 11/26/19.
//  Copyright © 2019 Jose Palomera. All rights reserved.
//

#include <stdio.h>

#include <string>
#include <iostream>
#include "Fund.h"
#include "Account.h"
#include <vector>


using namespace std;

Account::Account(string lastName, string firstName, int ID){
    
    this->insertCh = false;
    this->lastName = lastName;
    this->firstName = firstName;
    this->clientID = ID;
    
    //Array of strings that holds the names for every fund so we can
    //initialize them in the appropriate order
    //for our list of funds
    string fundNames[] = {
        "Money Market", "Prime Money Market",
        "Long-Term Bond", "Short-Term Bond",
        "500 Index Fund", "Capital Value Fund",
        "Growth Equity Fund", "Growth Index Fund",
        "Value Fund", "Value Stock Index"
    };
    
    //For loop that helps set the fund object with a balance
    //and a name
    for(int i = 0; i < 10; i++){
        myFunds[i].setFundName(fundNames[i]);
        myFunds[i].setFundBalance(0);
    }
    
}

Account::~Account(){
    
}

void Account::Deposit(int fundNumber, int depot){
    //Will access the fund directly to deposit into it
    myFunds[fundNumber].Deposit(depot);
    
}

bool Account::Withdraw(int fundNumber, int with){
    
    //If the fund has enough money to withdraw, then access the fund
    //directly and withdraw from it
    if(myFunds[fundNumber].canWithdraw(with)){
        
        myFunds[fundNumber].Withdraw(with);
        return true;
    }
    //If the fund does not have enough money to withdraw, see if the other funds can help out
    else{
        
        //Money Market Fund
        if(fundNumber == 0){
            //Checks to see if the other fund can help out pay the withdraw amount
            if(myFunds[fundNumber].getBalance() + myFunds[1].getBalance() >= with){
                
                int leftOver = with - myFunds[fundNumber].getBalance();
                
                //Withdraws from both funds that add up to the desired amount
                myFunds[fundNumber].Withdraw(with);
                myFunds[1].Withdraw(leftOver);
                
                Transaction *firstFund = new Transaction('W', getClientID() * 10 + fundNumber, with);
                Transaction *secondFund = new Transaction('W', getClientID() * 10 + 1, leftOver);
                
                myFunds[fundNumber].addTransaction(*firstFund);
                myFunds[1].addTransaction(*secondFund);
                return true;
                
            }
        }
        //Prime Money Market Fund
        else if(fundNumber == 1){
            //Checks to see if the other fund can help out pay the withdraw amount
            if(myFunds[fundNumber].getBalance() + myFunds[0].getBalance() >= with){
                
                int leftOver = with - myFunds[fundNumber].getBalance();
                
                //Withdraws from both funds that add up to the desired amount
                myFunds[fundNumber].Withdraw(with);
                myFunds[0].Withdraw(with);
                
                //Makes new transactions that have the new information and adds it to the appropriate fund history
                Transaction *firstFund = new Transaction('W', getClientID() * 10 + fundNumber, with);
                Transaction *secondFund = new Transaction('W', getClientID() * 10, leftOver);
                
                myFunds[fundNumber].addTransaction(*firstFund);
                myFunds[0].addTransaction(*secondFund);
                return true;
                
            }
        }
        //Long-Term Bond Fund
        else if(fundNumber == 2){
            //Checks to see if the other fund can help out pay the withdraw amount
            if(myFunds[fundNumber].getBalance() + myFunds[fundNumber+1].getBalance() >= with){
                
                int leftOver = with - myFunds[fundNumber].getBalance();
                
                //Withdraws from both funds that add up to the desired amount
                myFunds[fundNumber].Withdraw(with);
                myFunds[3].Withdraw(with);
                
                //Makes new transactions that have the new information and adds it to the appropriate fund history
                Transaction *firstFund = new Transaction('W', getClientID() * 10 + fundNumber, with);
                Transaction *secondFund = new Transaction('W', getClientID() * 10 + 3, leftOver);
                
                myFunds[fundNumber].addTransaction(*firstFund);
                myFunds[3].addTransaction(*secondFund);
                return true;
                
            }
            
        }
        //Short-Term Bond Fund
        else if(fundNumber == 3){
            //Checks to see if the other fund can help out pay the withdraw amount
            if(myFunds[fundNumber].getBalance() + myFunds[fundNumber-1].getBalance() >= with){
                
                int leftOver = with - myFunds[fundNumber].getBalance();
                
                //Withdraws from both funds that add up to the desired amount
                myFunds[fundNumber].Withdraw(with);
                myFunds[2].Withdraw(with);
                
                //Makes new transactions that have the new information and adds it to the appropriate fund history
                Transaction *firstFund = new Transaction('W', getClientID() * 10 + fundNumber, with);
                Transaction *secondFund = new Transaction('W', getClientID() * 10 + 2, leftOver);
                
                myFunds[fundNumber].addTransaction(*firstFund);
                myFunds[2].addTransaction(*secondFund);
                return true;
            }
            
        }
        
    }
    
    //If no withdraw has happened then return false
    return false;
    
}

void Account::viewHistory(){
    //Views the history of all the funds for the current Account
    for(int i = 0; i < 10; i++){
        myFunds[i].viewHistory();
    }
}

void Account::viewFundHistory(int fundID){
    //Views the history for a specific fund in the current Account
    myFunds[fundID].viewHistory();
}

void Account::addTransaction(Transaction t, int fundNum){
    //Adds a transaction to the desired fund history 
    myFunds[fundNum].addTransaction(t);
    
}

bool Account::getInsertCheck()const{
    return this->insertCh;
}

string Account::getFirstName()const{
    
    return this->firstName;
}

string Account::getLastName()const{
    
    return this->lastName;
}

int Account::getClientID()const{
    
    return this->clientID;
}

Fund Account::getFund(int fundNum){
    return myFunds[fundNum];
}

string Account::getFundName(int fundNum){
    return myFunds[fundNum].getFundName();
}

ostream& operator<<(ostream &out, const Account &acc){
    
    out << acc.getFirstName() << " " << acc.getLastName() << " Account ID: "
    << acc.getClientID();
    return out;
}
