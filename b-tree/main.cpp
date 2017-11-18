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

/* Define types for parsing commands */
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

/**
 * Reads input from an input file
 * @param inputFilename Name of file to read
 * @return Each line of 'inputFilename' in a pointer to a "StringList", or if the file 
 * cannot be read, 'NULL'
 */
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

/**
 * Splits 'str' by the delimeter 'delim' and trims leading and trailing 
 * spaces
 * @param str String to split
 * @param delim Delimeter to use for splitting
 * @return "StringList" with each part of 'str'
 */
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

/**
 * Gets the degree from 'input'
 * @param input Input read from file
 * @return Degree read from file
 */
int parseDegree(StringList* input) {
    int degree;
    std::istringstream(input->at(0)) >> degree;
    input->erase(input->begin());
    return degree;
}

/**
 * Parses commands from 'input' and puts them into a "CommandList"
 * @param input Input read from file
 * @return "CommandList" containing all valid commands
 */
CommandList* parseCommands(StringList* input) {
    if ( input->size() < 1 )
        return NULL;
    else {
        CommandList* commands = new CommandList;
        regex commandRegex("([A-Za-z]+)\\((.*?)\\)");
        Function func;
        for ( unsigned i = 0 ; i < input->size(); i++ ) {
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
        if ( commands->size() < 1 )
            return NULL;
        else
            return commands;
    }
}

/**
 * Converts a "Command" to string.
 * @param command Command to convert
 * @return command converted to string
 */
std::string getCommandString (Command command) {
    std::string commandString;
    std::stringstream stream;
    switch(command.func) {
        case Function::insert : stream << "insert"; break;
        case Function::search : stream << "search"; break;
        default : stream << "unkonwn"; break;
    }

    stream << "(";
    for ( unsigned j = 0; j < command.args.size(); j++ ){
        stream << command.args.at(j);
        if ( j != command.args.size()-1 )
            stream << ",";
    }
    stream << ")";
    stream >> commandString;
    return commandString;
}

/**
 * Prints the content of the valid commands read from the file to cerr
 * @param commands "CommandList" containing commands read from file
 */
void printCommands (CommandList* commands) {
    std::cerr << std::endl;
    std::cerr << "----------File Commands----------" << std::endl;
    std::cerr << std::endl;
    for ( unsigned i = 0; i < commands->size(); i++ )
    {
        std::cerr << getCommandString(commands->at(i)) << std::endl;
    }
    std::cerr << std::endl;
    std::cerr << "---------------------------------" << std::endl;
    std::cerr << std::endl;
}

/**
 * Compares 'startKey' and 'endKey' to determine whether the range is valid or
 * not.
 * @param startKey Beginning of range
 * @param endKey End of range
 * @return true if range is valid, false otherwise
 */
bool checkRangeKeys ( KeyType startKey, KeyType endKey )
{
    // do comparison of start and end keys here
    if ( startKey <= endKey ) return true;
    else return false;
}

/**
 * Processes the commands in 'commands' against 'tree'. Outputs errors to 
 * cerr.
 * @param commands Commands to run
 * @param tree Tree to run commands against
 */
void processCommands(CommandList* commands, Tree* tree) {
    Function f;
    StringList a;
    for ( unsigned i = 0; i < commands->size(); i++ ) {
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
                    if ( checkRangeKeys( startKey, endKey ) )
                        tree->search(startKey, endKey);
                    else {
                        std::cerr << "Bad start & end keys; startKey > " 
                            << "endKey for command \""
                            << getCommandString(commands->at(i))
                            << "\"; command not executed." << std::endl;
                    }
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


/**
 * Run commands passed in an input file against a B+-Tree with degree specified 
 * by the input file. All command results are output to std::cout, which has 
 * been redirected to the output file './output_file.txt'. An input file with valid 
 * degree and commands must be input for this program to successfully output 
 * data.
 * @return Any value other than '0' is considered an error. The following return
 * values are known errors:
 * 1) Input file not passed via command line or not the right number of 
 *    arguments passed
 * 2) Input file cannot be opened
 * 3) Input file is not formatted correctly (see error output)
 * 4) The output file cannot be opened
 * 5) The degree specified in the input file is too small
 * 6) No valid commands were specified in the input file
 */
int main(int argc, char** argv) {
    // check to make sure an input file was provided
    if ( argc != 2 ) {
        std::cerr << "Usage: " << argv[0] << " <inputFile>" << std::endl;
        return 1;
    }
    
    // read in file contents
    StringList* input = readInput(argv[1]);
    if ( input == NULL ){
        std::cerr << "Unable to open input file: \"" << argv[1] << "\"" << std::endl;
        return 2;
    }
    else if ( input->size() < 1 ) {
        std::cerr << "Input file not formatted correctly. File should have the format:" << std::endl;
        std::cerr << "inputFile.txt" << std::endl;
        std::cerr << "  <degreeOfTree>" << std::endl;
        std::cerr << "  <command>" << std::endl;
        std::cerr << "  [<command>]..." << std::endl;
        return 3;
    }
    
    // make sure we can touch the output file
    std::string outFilename = "./output_file.txt";
    std::ofstream output(outFilename);
    if ( output.is_open() ) {
        std::cout.rdbuf(output.rdbuf());
    }
    else {
        std::cerr << "Unable to open output file: \"" << outFilename << "\"" << std::endl;
        return 4;
    }
    
    // parse degree of tree from input
    int treeDegree = parseDegree(input);
    if ( treeDegree <= 0 ) {
        std::cerr << "Tree degree not specified or is invalid" << std::endl;
        return 5;
    }
    if ( treeDegree < 3 ) {
        std::cerr << "Tree degree \"" << treeDegree << "\" is less than the minimum \"3\"" << std::endl;
        return 5;
    }
    
    // parse commands from rest of input
    CommandList* commands = parseCommands(input);
    if ( commands == NULL ) {
        std::cerr << "No commands specified in the input file." << std::endl;
        return 6;
    }
//    printCommands(commands);
    
    // if we're here, everything checks out, and we can continue
    Tree* tree = new Tree(treeDegree);
    processCommands(commands, tree);
    
    //show output here
//    tree->printTree();
//    tree->printData();
    
    //cleanup here
    delete input;
    delete commands;
    delete tree;
    return 0;
}
