#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
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

  // Experimenting with Trie
  /*
  Trie t1;
  t1.length = 5;
  t1.width = 4;
  t1.height = 6;

  std::cout<<t1.getVol(t1.length, t1.width, t1.height)<<std::endl;
  return 0;
  */

  //READ INPUT FILE FIRST TIME
  std::map<std::string, int> keys = readFileFirst(inF, k);

  // GET FREQ SETS FROM ALL SETS
  std::map<std::string, int> freqSet = getFreqSets(keys, min_sup);

  // Extract Only Keys


  //
  // DO APRIORI
  // for(int i=0; i<k; i++){
    // Candidate Generation
    // Pruning
  // }


  // WRITE OUTPUT TO FILE
  writeToFile(outF, freqSet, min_sup);
  return 0;
}
