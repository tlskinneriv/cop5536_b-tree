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
#include <sstream>
#include <regex>
#include <time.h>
#include <fstream>
#include <algorithm>

using namespace std;
#include "TreeNode.h"
#include "Tree.h"


typedef std::vector<std::string> StringList;
typedef enum commandTypes {
    unknown = 0,
    insert,
    search
} Function;
typedef struct command {
    command(Function _func, StringList _args) : 
        func(_func), args(_args) {}
    Function func;
    StringList args;
} Command;
typedef std::vector<Command> CommandList;

StringList* readInput(std::string inputFilename)
{
    std::string line;
    std::ifstream in(inputFilename);
    if ( in.is_open() ) {
        StringList* input = new StringList;
        while ( getline(in, line) )
            input->push_back(line);
        in.close();
        return input;
    }
    else {
        return NULL;
    }
}

StringList splitString(const std::string& str, char delim){
    StringList subStrings;
    std::string subString;
    std::istringstream stream(str);
    while ( getline(stream, subString, delim) ) {
        remove(subString.begin(), subString.end(), ' ');
        subStrings.push_back(subString);
    }
    return subStrings;
}

int parseDegree(StringList* input) {
    int degree;
    std::istringstream(input->at(0)) >> degree;
    input->erase(input->begin());
    return degree;
}

CommandList* parseCommands(StringList* input) {
    if ( input->size() < 1 )
        return NULL;
    else {
        CommandList* commands = new CommandList;
        regex commandRegex("([A-Za-z]+)\\((.*?)\\)");
        Function func;
        for ( int i = 0 ; i < input->size(); i++ ) {
            smatch matches;
            regex_search(input->at(i), matches, commandRegex);
            if ( matches.size() == 3 ) { //matches at least contains full match, command, and args
                if ( matches[1] == "Insert" || matches[1] == "insert" )
                    func = Function::insert;
                else if ( matches[1] == "Search" || matches[1] == "search" )
                    func = Function::search;
                else {
                    func = Function::unknown;
                    std::cerr << "Unknown function/command \"" << matches[0] << "\" found in input file." << std::endl;
                }
                if ( func != Function::unknown )
                    commands->push_back(Command(func, splitString(matches[2], ',')));
            }
            else
                std::cerr << "Unknown function/command \"" << input->at(i) << "\" found in input file." << std::endl;
        }
        return commands;
    }
}

void processCommands(CommandList* commands, Tree* tree) {
    Function f;
    StringList a;
    for ( int i = 0; i < commands->size(); i++ ) {
        f = commands->at(i).func;
        a = commands->at(i).args;
        switch(f) {
            case Function::insert :
                if ( a.size() != 2 )
                    std::cerr << "Bad argument(s) for insert command.";
                else {
                    KeyType key;
                    DataType data;
                    std::istringstream(a.at(0)) >> key;
                    std::istringstream(a.at(1)) >> data;
                    tree->insert(key, data);
                }
                break;
            case Function::search :
                if ( a.size() == 1 ) {
                    KeyType key;
                    std::istringstream(a.at(0)) >> key;
                    tree->search(key);
                }
                else if ( a.size() == 2 ) {
                    KeyType startKey, endKey;
                    std::istringstream(a.at(0)) >> startKey;
                    std::istringstream(a.at(1)) >> endKey;
                    tree->search(startKey, endKey);
                }
                else 
                    std::cerr << "Bad argument(s) for search command.";
                break;
            default :
                // do nothing, unknown command
                break;
        }
    }
}

void printCommands (CommandList* commands) {
    std::cerr << std::endl;
    std::cerr << "----------File Commands----------" << std::endl;
    std::cerr << std::endl;
    for ( int i = 0; i < commands->size(); i++ )
    {
        switch(commands->at(i).func) {
            case Function::insert : std::cerr << "insert"; break;
            case Function::search : std::cerr << "search"; break;
            default : std::cerr << "unkonwn"; break;
        }
        
        std::cerr << "(";
        for ( int j = 0; j < commands->at(i).args.size(); j++ ){
            std::cerr << commands->at(i).args.at(j);
            if ( j != commands->at(i).args.size()-1 )
                std::cerr << ",";
        }
        std::cerr << ")" << std::endl;
    }
    std::cerr << std::endl;
    std::cerr << "---------------------------------" << std::endl;
    std::cerr << std::endl;
}
/*
 * 
 */
int main(int argc, char** argv) {
    int errNo = 1;
    // check to make sure an input file was provided
    if ( argc != 2 ) {
        std::cerr << "Usage: " << argv[0] << " <inputFile>" << std::endl;
        return errNo;
    }
    errNo++;
    
    // read in file contents
    StringList* input = readInput(argv[1]);
    if ( input == NULL ){
        std::cerr << "Unable to open input file: \"" << argv[1] << "\"" << std::endl;
        return errNo;
    }
    else if ( input->size() < 1 ) {
        std::cerr << "Input file not formatted correctly. File should have the format:" << std::endl;
        std::cerr << "[inputFile.txt]" << std::endl;
        std::cerr << "  <degreeOfTree>" << std::endl;
        std::cerr << "  [<command>]" << std::endl;
        std::cerr << "  [<command>]..." << std::endl;
        return errNo;
    }
    errNo++;
    
    // make sure we can touch the output file
    std::string outFilename = "./output.txt";
    std::ofstream cout(outFilename);
    if ( cout.is_open() ) {
        std::cout.rdbuf(cout.rdbuf());
    }
    else {
        std::cerr << "Unable to open output file: \"" << outFilename << "\"" << std::endl;
        return errNo;
    }
    errNo++;
    
    // parse degree of tree from input
    int treeDegree = parseDegree(input);
    if ( treeDegree < 3 ) {
        std::cerr << "Tree degree \"" << treeDegree << "\" is less than the minimum \"3\"" << std::endl;
        return errNo;
    }
    errNo++;
    
    // parse commands from rest of input
    CommandList* commands = parseCommands(input);
    if ( commands == NULL ) {
        std::cerr << "No commands specified in the input file." << std::endl;
        return errNo;
    }
    printCommands(commands);
    
    // if we're here, everything checks out, and we can continue
    Tree* tree = new Tree(treeDegree);
    processCommands(commands, tree);
    
    //show output here
    tree->printTree();
    tree->printData();
    
    //cleanup here
    input->~vector();
    commands->~vector();
    tree->~Tree();
    return 0;
}