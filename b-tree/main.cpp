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

#define NUM_TESTS 10

void printNode(TreeNode* node, int level);
std::string tabs(int count);
/*
 * 
 */
int main(int argc, char** argv) {
    Tree tree = Tree(4);
    srand(time(NULL));
    for ( int i = 0; i < NUM_TESTS; i++) {
        float random = (float)(rand() % 100 +1);
        cout << endl << "**Starting insert " << i << " (" << random << ")**" << endl;
        tree.insert(random, "data");
        cout << endl << "**Tree data**" << endl;
        printNode(tree.root, 0);
        cout << endl << "-------------------------------------" << endl;
    }
    return 0;
}

void printNode(TreeNode* node, int level) {
    for ( int j = 0; j < node->keys->size(); j++ )
        cout << tabs(level) << node->keys->getPairAt(j).key << endl;
    for ( int j = node->keys->size(); j < node->keys->maxSize(); j++ )
        cout << tabs(level) << "(empty)" << endl;
    for ( int j = 0; j < node->keys->maxSize()+1; j++ ) {
        TreeNode* child = node->children[j];
        if ( child != NULL ) {
            cout << tabs(level) << child << endl; 
            printNode(child, level+1);
        }
        else cout << tabs(level)<< "NULL" << endl;
    }
}

std::string tabs(int count) {
    std::string tabString = "";
    for ( int i = 0; i < count; i++)
        tabString += "  ";
    return tabString;
}