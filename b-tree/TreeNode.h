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
#include <vector>
#include <string>

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
    TreeNode(int degree);
    TreeNode(const TreeNode& orig);
    virtual ~TreeNode();
//    properties
    bool leaf; //whether of not tree is leaf
    int maxKeys;
    KeyContainer keys;
    ChildContainer children;
    TreeNode* siblingLeft;
    TreeNode* siblingRight;
//    functions
    int findChildIndex(KeyPair _keyPair);
    void insertPair(KeyPair _keyPair);
    void split(TreeNode* parent, int index);
private:
//    static void insert(KeyPair _keyPair, TreeNode* _np);
//    void insertNonFull(KeyPair _keyPair);
//    void checkOverfull(TreeNode* _parent);
//    void newSplit();
};

#endif /* TREENODE_H */

