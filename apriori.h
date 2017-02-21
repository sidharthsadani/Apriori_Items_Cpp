//Apriori.h
/*
    **********************************************************************************
    Author:   Sidharth SADANI
    Date:     2/20/17
    File:     Apriori.h
    Comments: Header File For Apriori.cpp
    **********************************************************************************
*/

// Header Guards
#ifndef APP_H
#define  APP_H

#include <string>
#include <map>
#include <vector>
#include "utils.h"
#include "trie.h"

// Candidate Generation,
// Return type = void in the hope that RT will come back updated.
void genCand(std::string, Trie*, int, int, int &);
/*
param: input file name
param: Pointer to the head of the trie
param: level of itemset Generation
param: k
param: pass by reference number of insertions
return:
*/
void candCheck(Trie*, trieNode*, trieNode*, std::vector<std::string>, int, int &);
/*
param: Pointer to the head of the trie
param: pointer to currentNode(which is being expanded)
param: pointer to parent Node
param: vector list of unprocessed item from line in file
param: level of itemset Generation
param: pass by reference number of insertions
return:
*/
// Pruning
void candPrune(Trie*, int, int);
/*
NOTE: min_sup is stored in the head of the Trie, so needn't be passed again
param: Pointer to the head of the trie
param: level of itemset Generation
param: k
return:
*/
void doPrune(Trie*, trieNode*, int, int, int, int);
/*
NOTE: min_sup is stored in the head of the Trie, so needn't be passed again
param: Pointer to the head of the trie
param: Pointer to the node being expanded, or the leaf
param: level of itemset Generation
param: min_sup
param: k
param: toplevel, highest level in the trie.
return:
*/
// std::map<std::string, int> candPrune(std::vector<std::string> cands, int min_sup);

#endif
