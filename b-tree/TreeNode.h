/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TreeNode.h
 * Author: thomas
 *
 * Created on October 22, 2017, 5:50 PM
 */

#ifndef TREENODE_H
#define TREENODE_H

#include <cstdlib>
#include "KeyContainer.h"

class TreeNode {
public:
    TreeNode(int _maxKeys);
    TreeNode(const TreeNode& orig);
    virtual ~TreeNode();
    static void insert(KeyPair _keyPair, TreeNode* _np);
    void insertNonFull(KeyPair _keyPair);
    void split(TreeNode* parent, int index);
    KeyContainer* keys;
    TreeNode** children; //array of pointers to children
    bool leaf; //whether of not tree is leaf
    TreeNode* siblingLeft;
    TreeNode* siblingRight;
    int findChildIndex(KeyPair _keyPair);
private:
};

#endif /* TREENODE_H */

