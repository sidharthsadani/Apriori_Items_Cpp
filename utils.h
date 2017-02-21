// Utils.h
// This file contains all the utility functions used in this program
/*
    **********************************************************************************
    Author:   Sidharth SADANI
    Date:     2/20/17
    File:     utils.h
    Comments: Header for utility functions of this module
    **********************************************************************************
*/

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <map>
#include "trie.h"

// Parse Each Line of File
std::vector<std::string> parseLine(std::string line);

// Read File First Time
std::map<std::string, int> readFileFirst(std::string inF, int k, int&);

// Write Output To File, NOTE:
//NOTE: Writing output has been moved to Trie::display(args)
void writeToFile(std::string outF, std::map<std::string, int> &keys, int min_sup);

// Get Frequent Sets L1
std::map<std::string, int> getFreqSets(std::map<std::string, int> &, int);

#endif
