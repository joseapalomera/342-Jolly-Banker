//
//  BSTree.h
//  Program5
//
//  Created by Jose Palomera on 11/26/19.
//  Copyright © 2019 Jose Palomera. All rights reserved.
//

#ifndef BSTree_h
#define BSTree_h

#include <iostream>
#include "Account.h"

using namespace std;

class BSTree{
private:
    
    struct Node{
        Account *pAcct;
        Node *right;
        Node *left;
    };
    
    Node *root;
    //The user does not need to know about how the recursion
    //works to see if the account exists or not. They also don't
    //need to know how the account is being inserted
    bool recursiveInsert(Account *acc, Node *&cur);
    bool contains(const int &accID, Account *&acc, Node *pointer)const;
    
public:
    BSTree();
    ~BSTree();
    
    bool Insert(Account *client);
    bool Retrieve(const int &clientID, Account* &acc)const;
    
    void Empty();
    void helpEmpty(Node *node);
    
    bool isEmpty()const;
    void Display();
    void printerHelper(Node *node)const;
    
    //These methods are used to help remove an account in the tree
    bool Remove(Account *acc);
    bool removeHelper(Node *&root, Account *acc);
    void deleteAccount(Node *&pNode);
    Account* deleteSmallestAcc(Node *&pNode);
};

#endif /* BSTree_h */
