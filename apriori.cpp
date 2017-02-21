#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "utils.h"
#include "trie.h"
#include "apriori.h"

void genCand(std::string inF, Trie* RT, int level, int k){
  std::cout<<"Database File: "<<inF<<std::endl;
  std::cout<<"Root Trie Details: "<<std::endl;
  std::cout << "Name: " << RT->Head->my_name << '\n';
  std::cout << "Min_Sup: " << RT->Head->path_count<< '\n';

  // Retrieving the head node of Trie
  trieNode* HNode = RT->Head;

  int line_ct = 0;
  std::ifstream iFile(inF, std::ios::in);
  if (iFile.is_open()) {
    std::string line;
    while (std::getline(iFile, line)) {
      line_ct++;
      std::cout << line_ct<<" : "<< line << '\n';
      std::vector<std::string> Items;
      Items = parseLine(line);
      int no_items = Items.size();

      if(no_items<k){
        continue;
      }
      // std::cout<<"Running"<<std::endl;
      //std::vector<std::string>::iterator it = Items.begin();

      // std::cout<<"Level: "<<level<<std::endl;
      candCheck(RT, HNode, HNode, Items, level);
      // std::cout << "On The Other Side" << '\n';

    }
    iFile.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
}

void candCheck(Trie* RT, trieNode* TN, trieNode* parN, std::vector<std::string> iList, int level){
  /*
  std::cout << "Min_Sup: " << RT->Head->my_name<< '\n';
  std::cout << "Name: " << TN->my_name<< '\n';
  std::cout << "Name: " << parN->my_name<< '\n';
  std::cout<<"Level: "<<level<<std::endl;
  std::vector<std::string>::iterator itx = iList.begin();
  while(itx!=iList.end()){
    std::cout << "Element: "<<*itx<< '\n';
    itx++;
  }
  */

  if(level==1){
    //Edge case updates
    //std::cout << "Entering Gen Edge Case:" << '\n';
    std::vector<std::string>::iterator it3 = iList.begin();
    while(it3!=iList.end()){
      //std::cout << "Here" << '\n';
      try{
        // if child of parent, append to child (increase ctr by 1 or create Node)
        trieNode* checkNode = parN->trie_Map.at(*it3);
        try{
          TN->trie_Map.at(*it3)->path_count++;
        }
        catch(...){
          // Create Node at TN with inital value = 1
          RT->insertNode(TN, *it3, 1);
          //it3++
        }
      }
      catch(...){
        it3++;
        continue;
      }
      it3++;
    }
    // std::cout<<"Have Fun"<<std::endl;
  }
  else{
    std::vector<std::string>::iterator it2 = iList.begin();
    int start_item = 1;
    // std::cout << "List Size: "<<iList.size() << '\n';
    while(it2!=iList.end()){
      // add early termination if itemNo+level-1<no of left elements
      if(start_item + level-1 > iList.size()){
        // Not enough search items left to find itemset of level = level
        break;
      }

      try{
        trieNode* nxtNode = TN->trie_Map.at(*it2);
        // Get New Vector fron it2++ to end
        std::vector<std::string>::iterator it3 = it2;
        it3++;
        std::vector<std::string> tList;
        while(it3!=iList.end()){
          tList.push_back(*it3);
          it3++;
        }
        if(tList.size()>0){
            candCheck(RT, nxtNode, TN, tList, level-1);
        }
      }
      catch(...){
        // If it blows up, do nothing, skip to the next iteration
      }
      it2++;
      start_item++;
    }
  }
}

void candPrune(Trie* RT, int level){
  std::cout<<"Starting Pruning"<<std::endl;
  trieNode* headN = RT->Head;
  int min_sup = headN->path_count;
  doPrune(RT, headN, level, min_sup);
}

void doPrune(Trie* RT, trieNode* TN, int level, int min_sup){
  if(level==1){
    std::map<std::string, trieNode*>::iterator cit = TN->trie_Map.begin();
    while(cit!=TN->trie_Map.end()){
      if(cit->second->path_count<min_sup){
        //Prune Away the node.
        trieNode* dNode = cit->second;
        std::string dName = cit->first;
        cit++;
        //std::cout << "I'm Here" << '\n';
        RT->destroyNode(dNode);
        // std::cout << "Pruning Node: "<<dName<<" Has Parent: " << TN->my_name << " W/ Count: "<< dNode->path_count<<'\n';
        TN->trie_Map.erase(dName);
        //std::cout << "I'm Here" << '\n';
      }
      else{
          cit++;
      }
    }
    //std::cout << "Exited This Loop" << '\n';
  }
  else{
    std::map<std::string, trieNode*>::iterator cit = TN->trie_Map.begin();
    while(cit!=TN->trie_Map.end()){
      doPrune(RT, cit->second, level-1, min_sup);
      cit++;
    }
  }
}

/*
int start_item=1;
while(it!=Items.end()){
  if(start_item+level-1>no_items){
    // Not enough elements left in transaction to form LEVEL = level itemset
    break;
  }

  // Check if this item is an L1 freq Item
  trieNode* nxtNode;
  try{
    trieNode* nxtNode = HNode->trie_Map.at(*it);
  }
  catch(...){
    ++it;
    ++start_item;
    continue;
  }

  // Iterator over the items to the left of the selected item
  std::vector<std::string>::iterator nx_it = it;
  while(nx_it!=Items.end()){
    nx_it = it;
    nx_it++;

  }
  nx_it++;
  //break;

  //nxtNode is already at level 1
  // Now go down from level 2 to level = level-1
  for(int i=2; i<=level-1;i++){
    try{
      nxtNode = nxtNode->trie_Map.at(*nx_it);
    }
    catch(...){
      continue;
    }
  }

  ++it;
  ++start_item;

  */
