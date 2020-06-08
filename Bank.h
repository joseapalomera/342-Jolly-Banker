//
//  Bank.h
//  Program5
//
//  Created by Jose Palomera on 12/5/19.
//  Copyright © 2019 Jose Palomera. All rights reserved.
//

#ifndef Bank_h
#define Bank_h

#include <string>
#include <queue>
#include "Transaction.h"
#include "BSTree.h"
using namespace std;

class Bank{
    
public:
    Bank();
    ~Bank();
    
    void ReadTransactionFile(string textFile);
    void ProcessTransactions();
    void Display();
    
private:
    
    queue<Transaction> transactions;
    BSTree theAccounts;
    
};
#endif /* Bank_h */
