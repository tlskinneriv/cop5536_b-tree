/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tree.cpp
 * Author: thomas
 * 
 * Created on October 24, 2017, 9:17 PM
 */

#include "Tree.h"
#include <iostream>

Tree::Tree(int degree) {
    root = new TreeNode(degree);
}

Tree::Tree(const Tree& orig) {
}

Tree::~Tree() {
}

//void Tree::insert(KeyType key, DataType data) {
//    KeyPair pair = { .key = key, .data = data };
//    TreeNode* existingNode = root;
//    if ( root->keys->size() == root->keys->maxSize() ) {
//        std::cout << "Root is full, so split!" << std::endl;
//        TreeNode* newNode = new TreeNode(root->keys->maxSize());
//        root = newNode;
//        newNode->leaf = false;
//        newNode->children[0] = existingNode;
//        std::cout << "Splitting root..." << std::endl;
//        newNode->children[0]->split(newNode, 0);
//        std::cout << "Inserting into new root..." << std::endl;
//        newNode->insertNonFull(pair);
//    }
//    else {
//        std::cout << "Root not full, insert normally" << std:: endl;
////        existingNode->insertNonFull(pair);
//        TreeNode* newNode = new TreeNode(root->keys->maxSize());
//        existingNode->insertPair(newNode, pair);
//    }
//}

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