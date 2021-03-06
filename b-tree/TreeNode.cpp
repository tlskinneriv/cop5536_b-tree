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

TreeNode::TreeNode(int order) {
    leaf = true; // start node as leaf
    keys.clear();
    keys.reserve(order-1);
    children.clear();
    children.reserve(order);
    siblingLeft = NULL;
    siblingRight = NULL;
    maxKeys = (unsigned)order-1;
}

TreeNode::~TreeNode() {
    // delete all this nodes children before deleting itself
    for ( unsigned i = 0; i < children.size(); i++ )
        delete children[i];
}

unsigned TreeNode::findChildIndex(KeyType key) {
    unsigned i = 0;
    // go down the key list to find where key should go
    while ( i < keys.size() && key > keys.at(i).key ) {
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
    newNode->keys = KeyContainer(keys.begin()+middle,keys.end());
    //oldNode has 0 to middle-2
//    keys = KeyContainer(keys.begin(),keys.begin()+middle-1); 
    //get middle-1 key as well for B+-tree structure
    keys = KeyContainer(keys.begin(),keys.begin()+middle); 
    //check if not a leaf
    if(!leaf) {
        //copy children from old node half to new node
        newNode->children = ChildContainer(children.begin()+middle,children.end());
        children = ChildContainer(children.begin(), children.begin()+middle);
    }
    //assign sibling pointers to this and newNode if they are leaves
    if (leaf)
    {
        if(siblingRight != NULL)
        {
            siblingRight->siblingLeft = newNode;
            newNode->siblingRight = siblingRight;
        }
        siblingRight = newNode;
        newNode->siblingLeft = this;
    }
    //insert middle-1 into parent
    parent->keys.insert(parent->keys.begin()+index, parentPair);
    //insert new node into parent
    parent->children.insert(parent->children.begin()+index+1, newNode);
}

void TreeNode::insertPair(KeyPair keyPair) {
    //there = where keyPair should go in this node
    int there = findChildIndex(keyPair.key);
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

KeyContainer* TreeNode::search(KeyType key) {
    //there = where keyPair should be in this node
    unsigned there = findChildIndex(key);
    //if this node is a leaf, try to find it here
    if (leaf) {
        if(there < keys.size() && keys.at(there).key == key)
        {
            //make a new keyContainer
            KeyContainer* foundKeys = new KeyContainer;
            //stick the found key in it
            foundKeys->push_back(keys.at(there));
            there++;
            //check rest of the keys down from there
            while (there < keys.size() && keys.at(there).key == key )
            {
                foundKeys->push_back(keys.at(there));
                there++;
            }
            if ( there == keys.size() && siblingRight != NULL ) {
                // if there is a sibling, check it too
                KeyContainer* siblingKeys = siblingRight->search(key);
                if ( siblingKeys != NULL )
                    foundKeys->insert(foundKeys->end(), siblingKeys->begin(), siblingKeys->end());
                delete siblingKeys;
            }
            return foundKeys;
        }
        else {
            return NULL;
        }
    }
    else {
        // if not a leaf, continue down the tree
        TreeNode* child = children.at(there);
        return child->search(key);
    }
}

KeyContainer* TreeNode::search(KeyType startKey, KeyType endKey) {
    //there = where keyPair should be in this node
    unsigned there = findChildIndex(startKey);
    //if this node is a leaf, try to find it here
    if (leaf) {
        if(there < keys.size() && keys.at(there).key >= startKey && keys.at(there).key <= endKey)
        {
            //make a new keyContainer
            KeyContainer* foundKeys = new KeyContainer;
            //stick the found key in it
            foundKeys->push_back(keys.at(there));
            there++;
            //check rest of the keys down from there
            while (there < keys.size() && keys.at(there).key <= endKey)
            {
                foundKeys->push_back(keys.at(there));
                there++;
            }
            if ( there == keys.size() && siblingRight != NULL ) {
                // if there is a sibling, check it, too
                KeyContainer* siblingKeys = siblingRight->search(keys.at(there-1).key, endKey);
                if ( siblingKeys != NULL )
                    foundKeys->insert(foundKeys->end(), siblingKeys->begin(), siblingKeys->end());
                delete siblingKeys;
            }
            return foundKeys;
        }
        else {
            return NULL;
        }
    }
    else {
        // move down the tree if not at a leaf
        TreeNode* child = children.at(there);
        return child->search(startKey, endKey);
    }
}

/**
 * Generates string with a number of spaces for print at different levels 
 * (for debug)
 * @param count Number of spaces to generate
 * @return String with spaces in it
 */
std::string tabs(int count) {
    std::string tabString = "";
    for ( int i = 0; i < count; i++)
        tabString += "  ";
    return tabString;
}

void TreeNode::printNode(int level) {
    // print all the keys in this node
    for ( unsigned j = 0; j < keys.size(); j++ )
        std::cerr << tabs(level) << keys.at(j).key << ":" << keys.at(j).data << std::endl;
    // notate all the rest as empty
    for ( unsigned j = keys.size(); j < maxKeys; j++ )
        std::cerr << tabs(level) << "(empty)" << std::endl;
    // print the left sibling
    std::cerr << tabs(level) << "ls:" << siblingLeft << std::endl;
    // print the righ tsibling
    std::cerr << tabs(level) << "rs:" << siblingRight << std::endl;
    // print all of this nodes children recursively, increasing the indentaiton 
    // level
    for ( unsigned j = 0; j < children.size(); j++ ) {
        TreeNode* child = children[j];
        if ( child != NULL ) {
            std::cerr << tabs(level) << child << std::endl; 
            child->printNode(level+1);
        }
    }
    // if some children aren't used, mark them as NULL
    for ( unsigned j = children.size(); j < maxKeys+1; j++ )
        std::cerr << tabs(level) << "NULL" << std::endl;
}

void TreeNode::printNodeDataFromHere() {
    // get to the leftmost node
    if ( children.size() > 0 ) {
        children.at(0)->printNodeDataFromHere();
    }
    // print its contents and all of its siblings contents
    else {
        for ( unsigned i = 0; i < keys.size(); i++ )
            std::cerr << keys.at(i).key << ":" << keys.at(i).data << std::endl;
        if ( siblingRight != NULL )
            siblingRight->printNodeDataFromHere();
    }
}