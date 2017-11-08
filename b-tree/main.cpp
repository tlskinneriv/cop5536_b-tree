/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Thomas Skinner
 * Purpose: call and test the "Tree" class
 *
 * Created on October 22, 2017, 5:47 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>

#include "TreeNode.h"
#include "Tree.h"
using namespace std;

#define NUM_TESTS 500

void printNode(TreeNode* node, int level);
void printInorder(TreeNode* node);
void printAlongLinkedList(TreeNode* node);
std::string tabs(int count);
/*
 * 
 */
int main(int argc, char** argv) {
    Tree tree = Tree(4);
    srand(time(NULL));
    for ( int i = 0; i < NUM_TESTS; i++) {
        float random = (float)(rand() % 93 +33);
        string randData(1,(char)random);
        cout << endl << "**Starting insert " << i << " (" << random << ")**" << endl;
        tree.insert(random, randData);
//        cout << endl << "**Tree data**" << endl;
//        printNode(tree.root, 0);
//        cout << endl << "-------------------------------------" << endl;
    }
    // print final tree in inorder
//    cout << "\nContent of all nodes in inorder:" << endl;
//    printInorder(tree.root);
    printAlongLinkedList(tree.root);
    return 0;
}

void printNode(TreeNode* node, int level) {
    for ( int j = 0; j < node->keys.size(); j++ )
        cout << tabs(level) << node->keys.at(j).key << ":" << node->keys.at(j).data << endl;
    for ( int j = node->keys.size(); j < node->maxKeys; j++ )
        cout << tabs(level) << "(empty)" << endl;
    cout << tabs(level) << "ls:" << node->siblingLeft << endl;
    cout << tabs(level) << "rs:" << node->siblingRight << endl;
    for ( int j = 0; j < node->children.size(); j++ ) {
        TreeNode* child = node->children[j];
        if ( child != NULL ) {
            cout << tabs(level) << child << endl; 
            printNode(child, level+1);
        }
        else cout << tabs(level)<< "NULL" << endl;
    }
}

void printInorder(TreeNode* node) {
    for ( int i = 0; i < node->keys.size(); i++ )
    {
        if ( node->children.size() > 0 )
            printInorder(node->children.at(i));
        std::cout << node->keys.at(i).key << " ";
    }
    if ( node->children.size() > 0 )
            printInorder(node->children.at(node->keys.size()));
}

void printAlongLinkedList(TreeNode* node) {
    if ( node->children.size() > 0 )
        printAlongLinkedList(node->children.at(0));
    else {
        while ( node != NULL )
        {
            for ( int i = 0; i < node->keys.size(); i++ )
                std::cout << node->keys.at(i).key << ":" << node->keys.at(i).data << endl;
            node = node->siblingRight;
        }
    }
}

std::string tabs(int count) {
    std::string tabString = "";
    for ( int i = 0; i < count; i++)
        tabString += "  ";
    return tabString;
}