// Header file for Trie class
/*
    **********************************************************************************
    Author:   Sidharth SADANI
    Date:     2/20/17
    File:     trie.h
    Comments: Header file for trie.cpp // Modified trie with Nodes containing hashmap
            : to pointers to children Nodes
    **********************************************************************************
*/
// This is the data structure utilised to generate itemsets. Trie tree with trieNodes, pointers to children hashed.
//Header guards

#ifndef TRIE_H
#define TRIE_H

#include<string>
#include<vector>
#include<map>

struct trieNode{
  std::string my_name;
  int path_count;
  std::map<std::string, trieNode*> trie_Map;
};

class Trie{
  public:
  // Variables
  trieNode* Head;
  // Create and Destroy Node Functions
  trieNode* createNode(std::string, int);
  void destroyNode(trieNode*);

  // Insertion and Deletion
  // Overloaded insertion, when no Node pointer provided, insert at head.
  void insertNode(std::string, int);
  void insertNode(trieNode*, std::string, int);

  // Displaying Nodes
  void display(std::string, int);
  void doPrint(std::string, trieNode*, std::vector<std::string>, int, int&, int);
  // Constructor
  Trie(std::string s, int p);
};

#endif
