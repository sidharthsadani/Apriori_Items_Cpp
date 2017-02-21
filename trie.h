// Header file for Trie class

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
