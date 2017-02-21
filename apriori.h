//Apriori.h

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
void candCheck(Trie*, trieNode*, trieNode*, std::vector<std::string>, int, int &);
// Pruning
void candPrune(Trie*, int, int);
void doPrune(Trie*, trieNode*, int, int, int, int);
// std::map<std::string, int> candPrune(std::vector<std::string> cands, int min_sup);

#endif
