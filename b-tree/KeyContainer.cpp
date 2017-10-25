/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeyContainer.cpp
 * Author: thomas
 * 
 * Created on October 24, 2017, 4:17 PM
 */

#include "KeyContainer.h"
#include <iostream>

KeyContainer::KeyContainer(int maxSize) {
    _keys.clear();
    _maxSize = maxSize;
}

KeyContainer::KeyContainer(const KeyContainer& orig) {
}

KeyContainer::~KeyContainer() {
}

void KeyContainer::add(KeyPair i) {
    _keys.push_back(i);
    sort();
}

void KeyContainer::sort() {
    std::sort(_keys.begin(), _keys.end(), compareKeys);
}

bool KeyContainer::compareKeys(KeyPair i, KeyPair j) {
    return i.key < j.key;
}

int KeyContainer::maxSize() {
    return _maxSize;
}

int KeyContainer::size() {
    return _keys.size();
}

KeyPair KeyContainer::getPairAt(int index) {
    return _keys[index];    
}

KeyPair KeyContainer::removePairAt(int index) {
    KeyPair temp;
    temp = _keys[index];
    _keys.erase(_keys.begin()+index);
    return temp;
}

std::vector<KeyPair> KeyContainer::getKeys(int indexBegin, int indexEnd) {
    if ( indexBegin == indexEnd ) {
        std::vector<KeyPair> temp;
        temp.push_back(_keys[indexBegin]);
        return temp;
    }
    else return std::vector<KeyPair>(_keys.begin()+indexBegin, _keys.begin()+indexEnd+1);
}

void KeyContainer::setKeys(std::vector<KeyPair> keys) {
    _keys = keys;
}
