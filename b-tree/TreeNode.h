/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TreeNode.h
 * Author: Thomas Skinner
 * Purpose: implement the "TreeNode" class
 *
 * Created on October 22, 2017, 5:50 PM
 */

#ifndef TREENODE_H
#define TREENODE_H

#include <cstdlib>
#include <vector>
#include <string>

/* Define types for node contents */
typedef struct keyPair KeyPair;
typedef float KeyType;
typedef std::string DataType;
struct keyPair {
    KeyType key;
    DataType data;
};
typedef std::vector<class TreeNode *> ChildContainer;
typedef std::vector<struct keyPair> KeyContainer;

class TreeNode {
public:
//    constructor destructor functions
    /**
     * Initializes a tree node with the order specified in 'order'
     * @param order Order of tree node to initialize
     */
    TreeNode(int order);
    
    /**
     * Destroys this TreeNode and its children (if there are any)
     */
    virtual ~TreeNode();
//    properties
    bool leaf; //whether or not this node is a leaf
    unsigned maxKeys; //maximum number of keys this node can hold
    KeyContainer keys; // keys in this node
    ChildContainer children; //children in this node
    TreeNode* siblingLeft; //left sibling of this node
    TreeNode* siblingRight; //right sibling of this node
//    functions
    /**
     * Finds the index of where the key should be inserted in the current node
     * @param key Key to insert into this node
     * @return Index of position where key should be inserted
     */
    unsigned findChildIndex(KeyType key);
    
    /**
     * Inserts a keyPair into this node
     * @param keyPair keyPair to insert into the node
     */
    void insertPair(KeyPair keyPair);
    
    /**
     * Splits the current node and inserts the split value and its pointer into 
     * the parent reference by 'parent'.
     * @param parent Parent of this node
     * @param index Index of the position where the split value should be 
     * inserted into the parent
     */
    void split(TreeNode* parent, int index);
    
    /**
     * Searches this node for a specified key
     * @param key Key to search for
     * @return Pointer to a "KeyContainer" holding the keyPairs found or 'NULL' 
     * if none are found
     */
    KeyContainer* search(KeyType key);
    
    /**
     * Searches this node for a specified key range
     * @param startKey Starting key to begin search
     * @param endKey Ending key of search
     * @return Pointer to KeyContainer holding the KeyPairs found between the 
     * 'startKey' and 'endKey' range, inclusive, or 'NULL' if none are found.
     */
    KeyContainer* search(KeyType startKey, KeyType endKey);
    
    /**
     * Prints this node and indents output depending on the value passed 
     * to 'level'
     * @param level Level to indent the output to
     */
    void printNode(int level);
    
    /**
     * Prints the doubly-linked list of nodes starting from this node and going 
     * right
     */
    void printNodeDataFromHere();
private:
};

#endif /* TREENODE_H */

