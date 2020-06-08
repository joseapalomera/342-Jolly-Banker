//
//  Driver.cpp
//  Program5
//
//  Created by Jose Palomera on 12/2/19.
//  Copyright © 2019 Jose Palomera. All rights reserved.
//

#include <stdio.h>
#include "Bank.h"
#include <iostream>

int main(int argc, char *argv[]){
    
    if(argc == 2){
        
        Bank jollyBanker;
        jollyBanker.ReadTransactionFile(argv[1]);
        jollyBanker.ProcessTransactions();
        jollyBanker.Display();
            
    }
    else{
        cerr << "ERROR: USAGE" << endl;
    }
    
    return 0;
}



