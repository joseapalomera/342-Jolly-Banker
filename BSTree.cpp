//
//  BSTree.cpp
//  Program5
//
//  Created by Jose Palomera on 11/26/19.
//  Copyright © 2019 Jose Palomera. All rights reserved.
//

#include <stdio.h>
#include "BSTree.h"
using namespace std;

BSTree::BSTree(){
    root = nullptr;
}

BSTree::~BSTree(){
    
}

bool BSTree::Insert(Account *client){

    return recursiveInsert(client, root);
    
}

bool BSTree::recursiveInsert(Account *acc, Node *&cur){
    
    //If root is null, then make the account the new root
    if(cur == nullptr){
        cur = new Node();
        cur->pAcct = acc;
        cur->left = nullptr;
        cur->right = nullptr;
        return true;
    }else{
        
        //If the Account id is more than the root...
        if(cur->pAcct->getClientID() < acc->getClientID()){
            //...then check to see if the right node is null
            if(cur->right == nullptr){
                Node *temp = new Node();
                temp->pAcct = acc;
                temp->left = nullptr;
                temp->right = nullptr;
                cur->right = temp;
                return true;
            }else{
                //If not, then we keep going right in the tree
                return recursiveInsert(acc, cur->right);
            }
            
        }
        //If the Account id is less than the root...
        else if(cur->pAcct->getClientID() > acc->getClientID()){
            //...then check to see if the left node is null
            if(cur->left == nullptr){
                Node *temp = new Node();
                temp->pAcct = acc;
                temp->left = nullptr;
                temp->right = nullptr;
                cur->left = temp;
                return true;
            }else{
                //If not, then we keep going left in the tree
                return recursiveInsert(acc, cur->left);
            }
            
        }
        else{
            return false;
        }
        
    }
    
}

bool BSTree::Retrieve(const int &clientID, Account *&acc)const{
    
    //If there is nothing in the tree, return false
    if(root == nullptr){
        return false;
    }
    //Otherwise, see if the account exitst
    return contains(clientID, acc, root);
}

bool BSTree::contains(const int &accID, Account *&acc, Node *theNode)const{
    
    //if the node is null, then the account doesn't exist
    if(theNode == nullptr){
        return false;
    }
    //If the nodes data equals the accounts data, then return true
    else if(accID == theNode->pAcct->getClientID()){
        acc = theNode->pAcct;
        return true;
    }
    //If the nodes data is more than the accounts data,
    //do the method again going left in the tree
    else if(accID < theNode->pAcct->getClientID()){
        return contains(accID, acc, theNode->left);
    }
    //Otherwise, do the method again but going right in the tree
    else{
        return contains(accID, acc, theNode->right);
    }
    
}

void BSTree::Empty(){
    
    helpEmpty(root);
}

//Helper method that deletes every node in the tree
void BSTree::helpEmpty(Node *node){
    
    if(node != nullptr){
        helpEmpty(node->left);
        helpEmpty(node->right);
        delete node->pAcct;
        delete node->left;
        delete node->right;
        delete node;
        node = nullptr;
    }
}

bool BSTree::isEmpty()const{
    
    if(root == nullptr){
        return true;
    }
    
    return false;
}

void BSTree::Display(){
    
    if(root != nullptr){
        printerHelper(root);
    }
    
}

//This helper method prints out the funds and their balances for the
//node's account
void BSTree::printerHelper(Node *node)const{
    
    if(node != nullptr){
        
        printerHelper(node->left);
        
        cout << *node->pAcct << endl;
        for(int i = 0; i < 10; i++){
            cout << "   " << node->pAcct->getFund(i);
        }
        cout << endl;
        
        printerHelper(node->right);
        
    }
    
}

//The next 4 methods are needed to remove a node in the tree
bool BSTree::Remove(Account *acc){
    
    return removeHelper(root, acc);
}

//This method checks to see if we need a helper method
//to delete a node, or if the account we want
//is already accessed
bool BSTree::removeHelper(Node *&root, Account *acc){
    
    if(root == nullptr){
        return false;
    }
    
    if(root->pAcct->getClientID() == acc->getClientID()){
        deleteAccount(root);
    }
    
    if(root->pAcct->getClientID() > acc->getClientID()){
        return removeHelper(root->left, acc);
    }
    else{
        return removeHelper(root->right, acc);
    }
    
}

//This method will delete a node if we want to
//delete the root, or the node that contains one child
//It accesses the deleteSmallestAcc method if
//we want to delete the root node that contains two children
void BSTree::deleteAccount(Node *&pNode){
    
    if(pNode->left == nullptr && pNode->right == nullptr){
        delete pNode;
        pNode = nullptr;
        return;
    }
    if(pNode->left == nullptr){
        Node *temp = pNode;
        pNode = pNode->right;
        delete temp;
        return;
    }
    if(pNode->right == nullptr){
        Node *temp = pNode;
        pNode = pNode->left;
        delete temp;
        return;
    }
    
    pNode->pAcct = deleteSmallestAcc(pNode->right);
    
}
//This method will find the node with the smallest Account
//id and delete that account
Account* BSTree::deleteSmallestAcc(Node *&pNode){
    
    if(pNode->left == nullptr){
        Node *temp = pNode;
        pNode = pNode->right;
        Account *acc = pNode->pAcct;
        delete temp;
        return acc;
    }
    
    return deleteSmallestAcc(pNode->left);
}
