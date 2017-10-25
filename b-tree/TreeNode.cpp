/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TreeNode.cpp
 * Author: thomas
 * 
 * Created on October 22, 2017, 5:50 PM
 */

#include "TreeNode.h"
#include <algorithm>
#include <iostream>
#include <math.h>

TreeNode::TreeNode(int _maxKeys) {
    children = new TreeNode*[_maxKeys+1];
    leaf = true; // start node as leaf
    keys = new KeyContainer(_maxKeys);
    for ( int i = 0; i < _maxKeys+1; i++ ) {
        children[i] = NULL;
    }
    siblingLeft = NULL;
    siblingRight = NULL;
}

TreeNode::TreeNode(const TreeNode& orig) {
}

TreeNode::~TreeNode() {
    delete keys;
}

int TreeNode::findChildIndex(KeyPair _keyPair) {
    std::cout << "starting find child" << std::endl;
    std::cout << "size of keys " << keys->size() << std::endl;
    int i = 0;
    while ( i < keys->size() && _keyPair.key > keys->getPairAt(i).key ) {
        i++;
    }
    return i;
}

void TreeNode::insertNonFull(KeyPair _keyPair) {
    std::cout << "Start nonfull..." << std::endl; 
    if ( leaf ) {// if a leaf, just add the key
        std::cout << "insertNonFull on leaf" << std::endl;
        keys->add(_keyPair);
    }
    else { //if not, put it in a child
        std::cout << "insertNonFull on nonleaf" << std::endl;
        int i = this->findChildIndex(_keyPair); //find the child to put it into
        std::cout << "Index of childNode to insert into is " << i << std::endl;
        if ( children[i]->keys->size() == children[i]->keys->maxSize() ) { //check if full0
            children[i]->split(this, i); //if so, split it, and insert the split back into this node
            children[i+1]->insertNonFull(_keyPair);
        }
        else children[i]->insertNonFull(_keyPair);
    }
}

void TreeNode::split(TreeNode* parent, int index) {
    int splitIndex = (int)floor(keys->maxSize()/2); // t
    std::cout << "--split index: " << splitIndex << std::endl;
    KeyPair splitKey = keys->getPairAt(splitIndex);
    TreeNode* newNode = new TreeNode(keys->maxSize()); // z<- allocate-node
    std::cout << "--old node pointer: " << this << std::endl;
    std::cout << "--new node pointer: " << newNode << std::endl;
    newNode->leaf = leaf; // leaf[z] = leaf[y]
    std::cout << "--getting keys for new node " << splitIndex+1 << " - " << keys->maxSize()-1 << std::endl;
    newNode->keys->setKeys(keys->getKeys(splitIndex+1, keys->maxSize()-1)); //put the last half of keys in it
    std::cout << "--new node start keys" << (newNode->keys->getPairAt(0).key) << std::endl;
    if ( !leaf ) {// if not leaf[y]
        std::cout << "--Node splitting isnt leaf" << std::endl;
        for (int j = 0; j < splitIndex; j++) // then for j <- 1 to t
            newNode->children[j] = children[j+splitIndex]; // do c_(j)[z] <- c_(j+t)[y]
    }
    for (int j = parent->keys->size(); j >= index+1; j--) // shift parent pointers to the right
        parent->children[j+1] = parent->children[j];
    parent->children[index+1] = newNode; // copy new child pointer into parent
    parent->keys->add(splitKey);// copy new key into parent
    keys->setKeys(keys->getKeys(0, splitIndex-1)); // delete keys to the right from this child
}
