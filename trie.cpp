// TRIE FUNCTIONS
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "trie.h"

// Accessibility Functions
int Trie::getPathCount(){
  return this->path_count;
}

std::string Trie::getName(){
  return this->my_name;
}

// Creating and Destroying Nodes
Trie *Trie::createTrie(std::string s, int i){
  Trie *t2;
  return t2;
}

// Constructor
Trie::Trie(std::string s, int p){
  this->my_name = s;
  this->path_count = p;
}

// Insertion Functions
void Trie::insertTrie(Trie iT){
  // Insert an already existing trie
  this->trie_Map.insert(std::make_pair(iT.my_name, &iT));
}

void Trie::insertTrie(std::string name, int value ){
  // Check if Node Exists
  try{
    Trie *x = this->trie_Map.at(name);
  }
  catch(...){
    // Node did not previously exist
    // Create New Node
    // Update It's name and value
    // Add it's pointer to the hashmap
    std::cout<<"Created Node: "<<std::endl;
  }

  // If it does not, create it with initial count = freq
}
