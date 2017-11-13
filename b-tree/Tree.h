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
    /**
     * Initializes a tree with the degree specified in 'degree'
     * @param degree Degree of tree to initialize
     */
    Tree(int degree);
    
    /**
     * Destroys this tree
     */
    virtual ~Tree();
//    functions
    /**
     * Inserts a key pair into the tree
     * @param key Key to insert into tree
     * @param data Data associated with the key to insert into tree
     */
    void insert(KeyType key, DataType data);
    
    /**
     * Searches for a key in the tree. Outputs all search data to 'cout' as 
     * comma-separated list unless nothing is found, then outputs "Null"
     * @param key Key value to search for
     */
    void search(KeyType key);
    
    /**
     * Searches for a range of keys in the tree beginning at 'starKey' and 
     * ending at 'endKey', inclusive. Outputs all search data to 'cout' 
     * as a comma-separated list of (key, value) pairs unless nothing is found, 
     * then outputs "Null"
     * @param startKey Starting key of range to search for
     * @param endKey Ending key of range to search for
     */
    void search(KeyType startKey, KeyType endKey);
    
    /**
     * Prints the structure of the tree to 'cerr'
     */
    void printTree();
    
    /**
     * Prints all data in the doubly-linked list of nodes starting from the 
     * left-most node
     */
    void printData();
private:
    //    properties
    TreeNode* root; // root node of the tree
};

#endif /* TREE_H */

