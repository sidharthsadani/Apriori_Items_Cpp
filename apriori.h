//Apriori.h

// Header Guards
#ifndef APP_H
#define  APP_H

#include <string>
#include <map>
#include <vector>

// Candidate Generation
std::vector<std::string> genCand(std::vector<std::string> prevCands);
// Pruning
std::map<std::string, int> candPrune(std::vector<std::string> cands, int min_sup);

#endif
