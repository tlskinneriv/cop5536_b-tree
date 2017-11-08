/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: thomas
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

#define NUM_TESTS 100

void printNode(TreeNode* node, int level);
void printInorder(TreeNode* node);
std::string tabs(int count);
/*
 * 
 */
int main(int argc, char** argv) {
    Tree tree = Tree(4);
    srand(time(NULL));
    for ( int i = 0; i < NUM_TESTS; i++) {
        float random = (float)(rand() % 500 +1);
        cout << endl << "**Starting insert " << i << " (" << random << ")**" << endl;
        tree.insert(random, "data");
        cout << endl << "**Tree data**" << endl;
//        printNode(tree.root, 0);
        cout << endl << "-------------------------------------" << endl;
    }
    // print final tree in inorder
    printInorder(tree.root);
    return 0;
}

void printNode(TreeNode* node, int level) {
    for ( int j = 0; j < node->keys.size(); j++ )
        cout << tabs(level) << node->keys.at(j).key << endl;
    for ( int j = node->keys.size(); j < node->maxKeys; j++ )
        cout << tabs(level) << "(empty)" << endl;
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

std::string tabs(int count) {
    std::string tabString = "";
    for ( int i = 0; i < count; i++)
        tabString += "  ";
    return tabString;
}