//
//  Transaction.h
//  Program5
//
//  Created by Jose Palomera on 12/1/19.
//  Copyright © 2019 Jose Palomera. All rights reserved.
//

#ifndef Transaction_h
#define Transaction_h

#include <string>
using namespace std;
/*
 This class stores the info all of the trasactions
 */
class Transaction{
    
public:

    //Opens accounts
    Transaction(char type, string lastName, string firstName, int accNum);
    
    //Deposits/Withdrawls
    Transaction(char type, int accNum, int money);
    
    //Manages a transfer
    Transaction(char type, int accNum, int money, int toAcc);
    
    //View History
    Transaction(char type, int accNum);
    
    ~Transaction();
    
    //Basic getters and setters
    bool setTransaction(char type);
    bool setAccountNumber(int accNum);
    bool setMoney(int amount);
    bool setToAccount(int toAcc);
    bool setFirstName(string firstName);
    bool setLastName(string lastName);
    bool setAcceptance(bool statement);
    
    char getTransaction()const;
    int getAccountNumber()const;
    int getMoney()const;
    int getToAccount()const;
    string getFirstName()const;
    string getLastName()const;
    bool getAcceptance()const;
    
    friend ostream &operator<<(ostream &out, const Transaction &trans);
    
private:
    
    char transactionType;
    int accNum, money, toAcc;
    string firstName;
    string lastName;
    bool accepted = false;
    
};


#endif /* Transaction_h */
