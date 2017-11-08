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

TreeNode::TreeNode(int degree) {
    leaf = true; // start node as leaf
    keys.clear();
    keys.reserve(degree-1);
    children.clear();
    children.reserve(degree);
    siblingLeft = NULL;
    siblingRight = NULL;
    maxKeys = degree-1;
}

TreeNode::TreeNode(const TreeNode& orig) {
}

TreeNode::~TreeNode() {
    keys.clear();
    children.clear();
}

int TreeNode::findChildIndex(KeyPair _keyPair) {
    std::cout << "starting find child" << std::endl;
    std::cout << "size of keys " << keys.size() << std::endl;
    int i = 0;
    while ( i < keys.size() && _keyPair.key > keys.at(i).key ) {
        i++;
    }
    return i;
}

//void TreeNode::insertNonFull(KeyPair _keyPair) {
//    std::cout << "Start nonfull..." << std::endl; 
//    if ( leaf ) {// if a leaf, just add the key
//        std::cout << "insertNonFull on leaf" << std::endl;
//        keys->add(_keyPair);
//    }
//    else { //if not, put it in a child
//        std::cout << "insertNonFull on nonleaf" << std::endl;
//        int i = this->findChildIndex(_keyPair); //find the child to put it into
//        std::cout << "Index of childNode to insert into is " << i << std::endl;
//        if ( children[i]->keys->size() == children[i]->keys->maxSize() ) { //check if full0
//            children[i]->split(this, i); //if so, split it, and insert the split back into this node
//            children[i+1]->insertNonFull(_keyPair);
//        }
//        else children[i]->insertNonFull(_keyPair);
//    }
//}

//void TreeNode::split(TreeNode* parent, int index) {
//    int splitIndex = (int)floor(keys->maxSize()/2); // t
//    std::cout << "--split index: " << splitIndex << std::endl;
//    KeyPair splitKey = keys->getPairAt(splitIndex);
//    TreeNode* newNode = new TreeNode(keys->maxSize()); // z<- allocate-node
//    std::cout << "--old node pointer: " << this << std::endl;
//    std::cout << "--new node pointer: " << newNode << std::endl;
//    newNode->leaf = leaf; // leaf[z] = leaf[y]
//    std::cout << "--getting keys for new node " << splitIndex+1 << " - " << keys->maxSize()-1 << std::endl;
//    newNode->keys->setKeys(keys->getKeys(splitIndex+1, keys->maxSize()-1)); //put the last half of keys in it
//    std::cout << "--new node start keys" << (newNode->keys->getPairAt(0).key) << std::endl;
//    if ( !leaf ) {// if not leaf[y]
//        std::cout << "--Node splitting isnt leaf" << std::endl;
//        for (int j = 0; j < splitIndex; j++) // then for j <- 1 to t
//            newNode->children[j] = children[j+splitIndex]; // do c_(j)[z] <- c_(j+t)[y]
//    }
//    for (int j = parent->keys->size(); j >= index+1; j--) // shift parent pointers to the right
//        parent->children[j+1] = parent->children[j];
//    parent->children[index+1] = newNode; // copy new child pointer into parent
//    parent->keys->add(splitKey);// copy new key into parent
//    keys->setKeys(keys->getKeys(0, splitIndex-1)); // delete keys to the right from this child
//}

void TreeNode::split(TreeNode* parent, int index) {
    //split down the middle = (floor(maxSize()/2))
    int middle = floor(maxKeys+1/2);
    KeyPair parentPair = keys.at(middle-1);
    std::cout << "  in split parent pair key = " << parentPair.key << std::endl;
    //new node has middle to maxSize-1
    TreeNode* newNode = new TreeNode(maxKeys+1);
    newNode->leaf = leaf;
    std::cout << "  in split new node is leaf? " << newNode->leaf << std::endl;
    std::cout << "  in split after setting leaf" << std::endl;
    newNode->keys = KeyContainer(keys.begin()+middle,keys.end());
    std::cout << "  in split after setting new node keys" << std::endl;
    //oldNode has 0 to middle-2
    keys = KeyContainer(keys.begin(),keys.begin()+middle-1);
    std::cout << "  in split after setting old node keys" << std::endl;
    //check if not a leaf
    if(!leaf) {
        //copy children from old node half to new node
        newNode->children = ChildContainer(children.begin()+middle,children.end());
        children = ChildContainer(children.begin(), children.begin()+middle);
    }
    //insert middle-1 into parent
    parent->keys.insert(parent->keys.begin()+index, parentPair);
    //insert new node into parent
    parent->children.insert(parent->children.begin()+index+1, newNode);
}

void TreeNode::insertPair(KeyPair keyPair) {
    //there = where keyPair should go in this node
    int there = findChildIndex(keyPair);
    std::cout << "there = " << there << std::endl;
    //if this node is a leaf, insert it there
    if (leaf) keys.insert(keys.begin()+there, keyPair);
    //else
    else {
        //insert it into the node at the children[there]
        TreeNode* child = children.at(there);
        child->insertPair(keyPair);
        //if children[there] is now overfull
        if(child->keys.size() > child->maxKeys)
            //split that child by giving it this and there
            child->split(this, there);
    }
}
