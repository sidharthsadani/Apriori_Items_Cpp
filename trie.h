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
  void display();
  // Constructor
  Trie(std::string s, int p);
};

/*
class Trie{
  public:
    std::string my_name;
    int path_count;
    Trie *next_trie;
    std::map<std::string, Trie*> trie_Map;
    // PUBLIC FUNCTIONS
    // Access Functions
    int getPathCount();
    std::string getName();
    // Insert Functinos
    void insertTrie(Trie);
    void insertTrie(std::string, int);
    Trie* createTrie(std::string, int);

    // Constructor
    Trie(std::string s, int p);
};
*/
#endif
