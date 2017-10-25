/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeyContainer.h
 * Author: thomas
 *
 * Created on October 24, 2017, 4:17 PM
 */

#ifndef KEYCONTAINER_H
#define KEYCONTAINER_H

#include <string>
#include <algorithm>
#include <vector>

typedef struct keyPair KeyPair;
typedef float KeyType;
typedef std::string DataType;
struct keyPair {
    KeyType key;
    DataType data;
};

class KeyContainer {
public:
    KeyContainer(int maxSize);
    KeyContainer(const KeyContainer& orig);
    virtual ~KeyContainer();
    int size();
    int maxSize();
    void add(KeyPair i);
    KeyPair removePairAt(int index);
    KeyPair getPairAt(int index);
    std::vector<KeyPair> getKeys(int indexBegin, int indexEnd);
    void setKeys(std::vector<KeyPair> keys);
    void setSize(int newSize);
    std::vector<KeyPair> _keys; // vector of keys
private:
    int _size;
    int _maxSize;
    void sort();
    static bool compareKeys(KeyPair i, KeyPair j);
};

#endif /* KEYCONTAINER_H */

