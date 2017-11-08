/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TreeNode.cpp
 * Author: Thomas Skinner
 * Purpose: implement the "TreeNode" class
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
    int i = 0;
    while ( i < keys.size() && _keyPair.key > keys.at(i).key ) {
        i++;
    }
    return i;
}

void TreeNode::split(TreeNode* parent, int index) {
    //split down the middle = (floor(maxSize()/2))
    int middle = floor(maxKeys+1/2);
    KeyPair parentPair = keys.at(middle-1);
    //parent pair will include key only
    parentPair.data = "";
    //new node has middle to maxSize-1
    TreeNode* newNode = new TreeNode(maxKeys+1);
    newNode->leaf = leaf;
//    newNode->keys = KeyContainer(keys.begin()+middle,keys.end());
    //get middle-1 key as well for B+-tree structure
    newNode->keys = KeyContainer(keys.begin()+middle-1,keys.end()); 
    //oldNode has 0 to middle-2
    keys = KeyContainer(keys.begin(),keys.begin()+middle-1); 
    //check if not a leaf
    if(!leaf) {
        //copy children from old node half to new node
        newNode->children = ChildContainer(children.begin()+middle,children.end());
        children = ChildContainer(children.begin(), children.begin()+middle);
    }
    //assign sibling pointers to this and newNode
    if(siblingRight != NULL)
    {
        siblingRight->siblingLeft = newNode;
        newNode->siblingRight = siblingRight;
    }
    siblingRight = newNode;
    newNode->siblingLeft = this;
    //insert middle-1 into parent
    parent->keys.insert(parent->keys.begin()+index, parentPair);
    //insert new node into parent
    parent->children.insert(parent->children.begin()+index+1, newNode);
}

void TreeNode::insertPair(KeyPair keyPair) {
    //there = where keyPair should go in this node
    int there = findChildIndex(keyPair);
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
