/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tree.h
 * Author: Thomas Skinner
 * Purpose: implement the "Tree" class
 *
 * Created on October 24, 2017, 9:17 PM
 */

#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"

class Tree {
public:
//    constructors/destructors
    Tree(int degree);
    Tree(const Tree& orig);
    virtual ~Tree();
//    functions
    void insert(KeyType key, DataType data);
    void search(KeyType key);
    void search(KeyType startKey, KeyType endKey);
    void printTree();
    void printData();
private:
    //    properties
    TreeNode* root;
};

#endif /* TREE_H */

