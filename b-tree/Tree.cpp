/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tree.cpp
 * Author: Thomas Skinner
 * Purpose: implement the "Tree" class
 * 
 * Created on October 24, 2017, 9:17 PM
 */

#include "Tree.h"
#include <iostream>

Tree::Tree(int degree) {
    if ( degree < 3 ) {
        std::cout << "Degree " << degree << " is less than the minimum degree 3. Aborting." << std::endl;
        std::exit(5); //exit code 5 is wrong degree; minimum degree 3 for B-Tree
        root = NULL;
    }
    else
        root = new TreeNode(degree);
}

Tree::~Tree() {
    delete root;
}

void Tree::insert(KeyType key, DataType data) 
{
    KeyPair pair = { .key = key, .data = data };
    TreeNode* existingRoot = root;
    //there = where keyPair should go in this node
    existingRoot->insertPair(pair);
    if(existingRoot->keys.size() > existingRoot->maxKeys)
    {    
        TreeNode* newRoot = new TreeNode(existingRoot->maxKeys+1);
        newRoot->leaf = false;
        newRoot->children.insert(newRoot->children.begin(), existingRoot);
        //make a new node split the original root
        existingRoot->split(newRoot, 0);
        root = newRoot;
    }
}

void Tree::search(KeyType key) {
    KeyContainer* results = root->search(key);
    if ( results != NULL )
        for ( unsigned i = 0; i < results->size(); i++ )
            if ( i == results->size()-1 )
                std::cout << results->at(i).data << std::endl;
            else
                std::cout << results->at(i).data << ", ";
    else
        std::cout << "Null" << std::endl;
    delete results;
}

void Tree::search(KeyType startKey, KeyType endKey) {
    KeyContainer* results = root->search(startKey,endKey);
    if ( results != NULL )
        for ( unsigned i = 0; i < results->size(); i++ )
            if ( i == results->size()-1 )
                std::cout << "(" << results->at(i).key << "," << results->at(i).data << ")" << std::endl;
            else
                std::cout << "(" << results->at(i).key << "," << results->at(i).data << "), ";
    else
        std::cout << "Null" << std::endl;
    delete results;
}

void Tree::printTree() {
    std::cerr << std::endl;
    std::cerr << "----------Tree Structure----------" << std::endl;
    std::cerr << std::endl;
    root->printNode(0);
    std::cerr << std::endl;
    std::cerr << "----------------------------------" << std::endl;
    std::cerr << std::endl;
}

void Tree::printData() {
    std::cerr << std::endl;
    std::cerr << "----------Tree Data----------" << std::endl;
    std::cerr << std::endl;
    root->printNodeDataFromHere();
    std::cerr << std::endl;
    std::cerr << "-----------------------------" << std::endl;
    std::cerr << std::endl;
}


