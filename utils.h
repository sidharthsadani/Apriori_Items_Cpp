// Utils.h

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

// Write Output To File
void writeToFile(std::string outF, std::map<std::string, int> &keys, int min_sup);

// Get Frequent Sets
std::map<std::string, int> getFreqSets(std::map<std::string, int> &, int);

//Insert first Gen Candidates into rootTrie
// void

#endif



/*
  // Displaying Counts
  tb = clock();
  int sum = 0;
  int key_ctr = 0;
  std::map<std::string, int>::iterator it = keys.begin();
  while (it != keys.end()) {
    key_ctr = key_ctr + 1;
    sum += it->second;
    if (it->second>=min_sup) {
      std::cout << it->first<<" : "<<it->second << '\n';
    }
    it++;
  }
  te = clock();
  et = (te-tb)/(float)CLOCKS_PER_SEC;
  std::cout << "Time Elapsed In Iteration Through Map: "<< et << '\n';
  std::cout << "Sum of Cts: "<< sum << '\n';
  std::cout << "Num Keys: "<< key_ctr << '\n';
*/
