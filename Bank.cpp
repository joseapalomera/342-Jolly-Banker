//
//  Bank.cpp
//  Program5
//
//  Created by Jose Palomera on 11/26/19.
//  Copyright © 2019 Jose Palomera. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Bank.h"
using namespace std;

Bank::Bank(){
    
}

Bank::~Bank(){
    
}

//This method will access the file and read each line
void Bank::ReadTransactionFile(string textFile){
    
    string line, fName, lName;
    
    ifstream file (textFile);
    
    //As long as there is a line in the file, keep running the loop
    while(getline(file, line)){
        
        //Allows us to read each word/character in the line of the file
        istringstream theLine(line);
        char type;
        //Reads the first thing in the line which is the transaction type
        theLine >> type;
        
        //If the first thing in the line is an O, try to open an account
        if(type == 'O'){
            int accId;
            //Assign the next characters/strings in the line
            //in the order of how they appear
            theLine >> lName >> fName >> accId;
            
            //Check to see if the Account Id is in range
            //if so, then make a transaction object that stores
            //the variables
            if(accId >= 1000 && accId <= 9999){
            Transaction temp(type, lName, fName, accId);
            transactions.push(temp);
            }
            else{
                cerr << "ERROR: Invalid Account id." << endl;
            }
            
        }
        //If the letter is either a D, or W then make a transaction object
        //that holds the deposit or withdraw
        else if(type == 'D' || type == 'W'){
            int accId, money;
            theLine >> accId >> money;
            Transaction temp(type, accId, money);
            transactions.push(temp);
        }
        //If the letter is a T,  then make a transaction object
        //that holds the transfer information
        else if(type == 'T'){
            int accId, money, toAcc;
            theLine >> accId >> money >> toAcc;
            Transaction temp(type, accId, money, toAcc);
            transactions.push(temp);
        }
        //If the letters is an H, then make a transaction object
        //that holds the account number to search the history for
        else if(type == 'H'){
            int accId;
            theLine >> accId;
            
            Transaction temp(type, accId);
            transactions.push(temp);
        }
        else{
            cerr << "ERROR: No transaction found" << endl;
        }
        
    }
    
    file.close();
    
}

//This method will do the actual processing of opening, depositing, and etc.
//in the accounts. We work with our list of tranasactions and create/retrieve
//account objects when needed to do.
void Bank::ProcessTransactions(){
   
    //As long as our list of transactions isn't empty, we keep working with
    //one transaction at a time
    while(!transactions.empty()){
        
        //Accesses the first transaction in our list
        Transaction temp = transactions.front();
        
        //If the char in our transaction is an O, then we create a new account
        if(temp.getTransaction() == 'O'){
            
            Account *acc = new Account(temp.getLastName(), temp.getFirstName(), temp.getAccountNumber());
            //If we can't insert the new account, then print out the error.
            if(!theAccounts.Insert(acc)){
                cerr << "ERROR: Account " << acc->getClientID() << " is already open. Transaction refused" << endl;
            }
            
        }
        //If the char is a D, we retrive the desired account from the BSTree
        else if(temp.getTransaction() == 'D'){
            
            int fundId = temp.getAccountNumber() % 10;
            int accId = temp.getAccountNumber() / 10;
            
            Account *acc;
            //If we can access the account, then we deposit the desired amount
            //and add the transaction the specific fund's history
            if(theAccounts.Retrieve(accId, acc)){
                acc->Deposit(fundId, temp.getMoney());
                acc->addTransaction(temp, fundId);
            }
            else{
                cerr << "ERROR: No account found. Deposit refused" << endl;
            }
            
        }
        //If the char is a W, we retrieve the desired account from the BSTree
        else if(temp.getTransaction() == 'W'){
            
            int fId = temp.getAccountNumber() % 10;
            int accId = temp.getAccountNumber() / 10;
            
            Account *acc;
            //if we access the account, we must still check if we can withdraw from it
            if(theAccounts.Retrieve(accId, acc)){
        
                if(acc->Withdraw(fId, temp.getMoney())){
                    temp.setAcceptance(true);
                }
                else{
                    //If we are not able to withdraw, we still add the transaction
                    //but we indicate that the transaction failed
                    temp.setAcceptance(false);
                    cerr << "ERROR: Not enough funds to withdraw " << temp.getMoney() << " from"
                    << temp.getFirstName() << " " << temp.getLastName() << " "
                    << acc->getFundName(fId) << endl;
                }
                if(!acc->getInsertCheck()){
                    acc->addTransaction(temp, fId);
                }
                
            }
            else{
                cerr << "ERROR: No account found. Withdraw refused" << endl;
            }
            
        }
        //If the char is a T, then we must retrieve the two accounts that we are
        //trying to do transfers with
        else if(temp.getTransaction() == 'T'){
            
            int fundFrom = temp.getAccountNumber() % 10;
            int accountFrom = temp.getAccountNumber() / 10;
            
            int fundTo = temp.getToAccount() % 10;
            int accountTo = temp.getToAccount() / 10;
            
            int moneyTransfer = temp.getMoney();
            
            Account *accFrom, *accTo;
            //Checks to see if both accounts exist in our BSTree
            if(theAccounts.Retrieve(accountFrom, accFrom)){
                
                if(theAccounts.Retrieve(accountTo, accTo)){
                    
                    //Now we must check to see if we can withdraw money from the account
                    //we are transferring from
                    if(accFrom->Withdraw(fundFrom, moneyTransfer)){
                        //Add the money to the desired transferTo acocunt
                        //and record that the transaction happened
                        accTo->Deposit(fundTo, moneyTransfer);
                        accTo->addTransaction(temp, fundTo);
                        accFrom->addTransaction(temp, fundFrom);
                        
                    }
                    else{
                        
                        cerr << "ERROR: Unsufficient funds to transfer $"
                        << moneyTransfer << " from Account: " << accFrom->getClientID() << " Fund: "
                        << accFrom->getFundName(fundFrom) << " to Account: " << accTo->getClientID()
                        << " Fund: " << accTo->getFundName(fundTo) << endl;
                    }
                    
                }
                else{
                    cerr << "ERROR: Account " << accountTo << " not found. Transferal refused" << endl;
                }
                
            }
            else{
                cerr << "ERROR: Account " << accountFrom << " not found. Transferal refused" << endl;
            }
            
        }
        //If the char is an H, then we must first see if the Account id is within
        //range to be able to see if we can retrieve it
        else if(temp.getTransaction() == 'H'){
            
            //If there is a 5 digit number, then view the history for the specific fund
            if(temp.getAccountNumber() >= 10000 && temp.getAccountNumber() <= 99999){
                
                Account *acc;
                //Separates the fund id from the account number
                int fundId = temp.getAccountNumber() % 10;
                int accId = temp.getAccountNumber() / 10;
                
                //If we can retrieve the account, then print out the history for that fund
                if(theAccounts.Retrieve(accId, acc)){
                    cout << "Transaction History for " << acc->getFirstName() << " " << acc->getLastName()
                    << acc->getFundName(fundId) << endl;
                    acc->viewFundHistory(fundId);
                }
                else{
                    cerr << "ERROR: Account " << accId << " not found. Transaction refused" << endl;
                }
                
            }
            //If there is a 4 digit number, then view the history for all the funds
            else if(temp.getAccountNumber() >= 1000 && temp.getAccountNumber() <= 9999){
                
                Account *acc;
                //Print out the history for the entire account if we can retrieve it
                if(theAccounts.Retrieve(temp.getAccountNumber(), acc)){
                    cout << "Transaction History for " << acc->getFirstName() << " " << acc->getLastName()
                    << " by fund." << endl;
                    acc->viewHistory();
                }
                else{
                    cerr << "ERROR: Account " << temp.getAccountNumber() <<  "not found. Transaction refused" << endl;
                }
                
            }
            else{
                cerr << "ERROR: Cannot display history. Account not found." << endl;
            }
            
        }
        //Once we're done working with the transaction, pop it from our list
        transactions.pop();
    }
    
    
}

void Bank::Display(){
    
    cout << "\nProcessing Done. Final Balances:" << endl;
    theAccounts.Display();
}

