// TRIE FUNCTIONS
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "trie.h"


// Constructor
Trie::Trie(std::string s, int p){
  struct trieNode *TN;
  TN = new(struct trieNode);
  this->Head = TN;
  this->Head->my_name = s;
  this->Head->path_count = p;
}

// Create Node
trieNode* Trie::createNode(std::string name, int ct){
  struct trieNode *TN;
  TN = new(struct trieNode);
  TN->my_name = name;
  TN->path_count = ct;
  // std::cout<<"Node Created"<<std::endl;
  return TN;
}

void Trie::destroyNode(trieNode* delNode){
  try{
    std::string name = delNode->my_name;
    free(delNode);
    // std::cout << "Element Deleted" << '\n';
  }
  catch(...){
    // std::cout << "Element Did Not Exist" << '\n';
  }
}

// Insert Node
void Trie::insertNode(std::string name, int ct){
  try{
    trieNode* x = this->Head->trie_Map.at(name);
    // x->path_count += 1;
  }
  catch(...){
    trieNode* temp = createNode(name,ct);
    this->Head->trie_Map.insert(std::make_pair(name, temp));
  }

}

void Trie::insertNode(trieNode* parent, std::string name, int ct){
  try{
    trieNode* x = parent->trie_Map.at(name);
  }
  catch(...){
    trieNode* temp = createNode(name,ct);
    parent->trie_Map.insert(std::make_pair(name, temp));
  }
}

// Display Functions
void Trie::display(){
  std::cout<<"My Size is: "<<this->Head->trie_Map.size()<<std::endl;
  trieNode* H = this->Head;
  std::cout<<"Name: "<<this->Head->my_name<<" Count: "<<this->Head->path_count<<std::endl;

  std::map<std::string, trieNode*>::iterator it = H->trie_Map.begin();
  while(it!=H->trie_Map.end()){
    // std::cout << "Name: " << it->first << " Count : "<< it->second->path_count<< " Size : "<< it->second->trie_Map.size() << '\n';

    trieNode* cNode = it->second;
    // Iterating Through child
    std::map<std::string, trieNode*>::iterator cit = cNode->trie_Map.begin();
    while(cit!=cNode->trie_Map.end()){
      std::cout <<"Parent Name: "<<cNode->my_name<< " Name: " << cit->first << " Count : "<< cit->second->path_count<< '\n';
      cit++;
    }

    it++;
  }
}

/*
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
*/
