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

  /*// Experimenting with Trie
  Trie t1;
  t1.length = 5;
  t1.width = 4;
  t1.height = 6;
  Trie *tp;
  tp = &t1;

  std::cout<<tp->getVol()<<std::endl;
  return 0;
  */
  /*
  Trie t1("A", 5);
  std::cout<<t1.getName()<<" : "<<t1.getPathCount()<<std::endl;
  Trie t2("B", 6);
  t1.next_trie = &t2;
  std::cout<<t1.next_trie->getName()<<" : "<<t1.next_trie->getPathCount()<<std::endl;
  Trie t3("C", 7);
  t2.insertTrie(t3);
  std::cout<<t2.trie_Map["C"]->getName()<<" : "<<t2.trie_Map["C"]->getPathCount()<<std::endl;
  Trie t4("D", 8);
  int ctr = 1;
  while(ctr>0){
    // Do stuff
    Trie t4("D", 8);
    t2.insertTrie(t4);
    //t2.insertTrie("D", 8);
    ctr = ctr - 1;
  }
  std::cout<<t2.trie_Map["D"]->getName()<<" : "<<t2.trie_Map["D"]->getPathCount()<<std::endl;
  return 0;
  */


  /*
  // Creating New Hash Trie
  Trie rootTrie("ROOT", -1);
  std::cout<<"Root Trie Created"<<std::endl;
  std::cout<<rootTrie.Head->my_name<<" : "<<rootTrie.Head->path_count<<std::endl;
  std::cout<<"Inserting Node"<<std::endl;
  rootTrie.insertNode("A",5);
  std::cout<<rootTrie.Head->trie_Map["A"]->my_name<<" : "<<rootTrie.Head->trie_Map["A"]->path_count<<std::endl;

  trieNode* x = rootTrie.Head->trie_Map["A"];
  std::cout<<"Inserting Node"<<std::endl;
  rootTrie.insertNode(x, "B", 6);
  std::cout<<x->trie_Map["B"]->my_name<<" : "<<x->trie_Map["B"]->path_count<<std::endl;

  return 0;

  */

  //READ INPUT FILE FIRST TIME
  std::map<std::string, int> keys = readFileFirst(inF, k);

  // GET FREQ SETS FROM ALL SETS
  std::map<std::string, int> freqSet = getFreqSets(keys, min_sup);

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

  for(int level=2;level<=2;level++){
    genCand(inF, RT, level, k);
    std::cout << "Trie After L2 Cand Gen" << '\n';
    // rootTrie.display();
    candPrune(RT, level);
    std::cout << "Trie After L2 Cand Prune" << '\n';
  }

  rootTrie.display();


  return 0;


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
