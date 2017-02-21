#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include<queue>
#include <ctime>

#include "utils.h"
#include "apriori.h"
#include "trie.h"
//Compilation command g++ -pipe -O2 -std=c++14 <filename > -lm

// // Function Definitions
// std::vector<std::string> parseLine(std::string);
// Write Output To File
// TODO: Enforce pass by reference
// void writeToFile(std::string, std::map<std::string, int> &, int);

int main(int argc, char const *argv[]){
  std::cout<<"Hello World"<<std::endl;
  clock_t global_start = clock();
  // Check Input Parameters
  if (argc!=5) {
    std::cout << "Insufficient Arguements" << '\n';
    return 0;
  }
  // Parse Input Parameters
  int min_sup = std::stoi(argv[1]);
  int k = std::stoi(argv[2]);
  std::string inF = argv[3];
  std::string outF = argv[4];

  //out_s=3_k=4+.txt
  outF = outF + "_s=" + std::to_string(min_sup) + "_k=" + std::to_string(k) + "+.txt";

  int maxLen = 0;

  //READ INPUT FILE FIRST TIME
  std::map<std::string, int> keys = readFileFirst(inF, k, maxLen);
  std::cout << "Max Line Len" <<maxLen<< '\n';
  // GET FREQ SETS FROM ALL SETS
  std::map<std::string, int> freqSet = getFreqSets(keys, min_sup);

  std::cout << keys[""] << '\n';

  // Create Trie
  Trie rootTrie("ROOT", min_sup);
  Trie* RT = &rootTrie;
  std::map<std::string, int>::iterator it = freqSet.begin();
  while(it!=freqSet.end()){
    // std::cout<<"Inserting Node: "<<it->first<<" : "<<it->second<<std::endl;
    rootTrie.insertNode(it->first, it->second);
    it++;
  }

  std::cout << "Trie After L1" << '\n';
  // rootTrie.display();
  // int level = 2;

  for(int level=2;level<=maxLen;level++){
    clock_t tb = clock();
    int num_inserted = 0;
    genCand(inF, RT, level, k, num_inserted);
    std::cout << "Trie After Level: "<<level<<" Cand Gen" << '\n';
    std::cout << "NUM INSERTED: " <<num_inserted<< '\n';
    // rootTrie.display();
    candPrune(RT, level, k);
    std::cout << "Trie After Level: "<<level<<" Cand Prune" << '\n';

    clock_t te = clock();
    float et = (te-tb)/(float)CLOCKS_PER_SEC;
    std::cout << "Time Elapsed In Level: "<<level<<" : "<< et << '\n';

    std::cout << '\n';
    //TODO: Requires Update
    if(num_inserted==0){
      break;
    }
  }

  std::cout << "Results: " << '\n';
  // Display some details on terminal, and print the results into the file
  rootTrie.display(outF, k);

  clock_t global_end = clock();
  float global_et = (global_end-global_start)/(float)CLOCKS_PER_SEC;
  std::cout << std::endl << "Total Time Elapsed: "<< global_et << " seconds"<< '\n';


  // WRITE OUTPUT TO FILE
  // writeToFile(outF, freqSet, min_sup);
  return 0;
}
