// TRIE FUNCTIONS

/*
    **********************************************************************************
    Author:   Sidharth SADANI
    Date:     2/20/17
    File:     trie.cpp
    Comments: Functions to operate the trie + hashmap node pointer data structure
    **********************************************************************************
*/

#include <string>
#include <vector>
//#include <queue>
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
void Trie::display(std::string outF, int k){
  int ct = 0;
  std::cout<<"My Size is: "<<this->Head->trie_Map.size()<<std::endl;
  trieNode* H = this->Head;
  std::cout<<"Name: "<<this->Head->my_name<<" Count: "<<this->Head->path_count<<std::endl;

  std::vector<std::string> prevList;
  int dispCt = 0;

  // Empty the output file
  std::ofstream oFile(outF, std::ios::out);
  if (oFile.is_open()) {
    oFile.close();
  }

  int min_sup = H->path_count;
  doPrint(outF, H, prevList, k, dispCt, min_sup);

  std::cout << "No of Items: "<< dispCt << '\n';
}

void Trie::doPrint(std::string outF, trieNode* TN, std::vector<std::string> prevList, int k, int &dCt, int min_sup){

  if(TN->trie_Map.empty()&&k<=0){
    //if(k<=0){
    //if(TN->trie_Map.empty())
    // std::cout << "HERE" << '\n';

    std::ofstream oFile(outF, std::ios::app);
    if (oFile.is_open()) {
      std::vector<std::string>::iterator it3 = prevList.begin();
      while(it3!=prevList.end()){
        oFile<<*it3<<" ";
        it3++;
      }
      //std::cout<<TN->my_name<<" : "<<TN->path_count<<std::endl;
      oFile << "(" << TN->path_count <<")"<< '\n';
      dCt++;

      oFile.close();
    }
  }
  else{
    std::map<std::string, trieNode*>::iterator cit = TN->trie_Map.begin();
    while(cit!=TN->trie_Map.end()){
      prevList.push_back(cit->first);
      doPrint(outF, cit->second, prevList, k-1, dCt, min_sup);
      prevList.pop_back();
      cit++;
    }
    if(k<=0&&TN->path_count>=min_sup){
      std::ofstream oFile(outF, std::ios::app);
      if (oFile.is_open()) {
        std::vector<std::string>::iterator it3 = prevList.begin();
        while(it3!=prevList.end()){
          oFile<<*it3<<" ";
          it3++;
        }
        //std::cout<<TN->my_name<<" : "<<TN->path_count<<std::endl;
        oFile << "(" << TN->path_count <<")"<< '\n';
        dCt++;

        oFile.close();
      }
    }
  }

}
