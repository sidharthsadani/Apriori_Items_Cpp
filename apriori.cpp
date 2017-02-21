#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "utils.h"
#include "trie.h"
#include "apriori.h"

void genCand(std::string inF, Trie* RT, int level, int k, int &num_ins){
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
    // Read Each Line From File
    while (std::getline(iFile, line)) {
      line_ct++;
      // std::cout << line_ct<<" : "<< line << '\n';
      std::vector<std::string> Items;
      Items = parseLine(line);
      sort(Items.begin(), Items.end());
      int no_items = Items.size();
      // If line contains less than k items, it cannot contribute to K+ itemsets
      if(no_items<k){
        continue;
      }

      // if no items > k, start building candidates
      candCheck(RT, HNode, HNode, Items, level, num_ins);

    }
    iFile.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
}

void candCheck(Trie* RT, trieNode* TN, trieNode* parN, std::vector<std::string> iList, int level, int &num_insert){

  if(level==1){
    //Edge case updates
    //std::cout << "Entering Gen Edge Case:" << '\n';
    std::vector<std::string>::iterator it3 = iList.begin();
    while(it3!=iList.end()){
      //std::cout << "Here" << '\n';
      try{
        // if child of parent, append to child (increase ctr by 1 or create Node)
        trieNode* checkNode = parN->trie_Map.at(*it3);
        num_insert = num_insert + 1;
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
            candCheck(RT, nxtNode, TN, tList, level-1, num_insert);
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



void candPrune(Trie* RT, int level, int k){
  std::cout<<"Starting Pruning"<<std::endl;
  trieNode* headN = RT->Head;
  int min_sup = headN->path_count;
  int toplevel = level;
  doPrune(RT, headN, level, min_sup, k, toplevel);
}

void doPrune(Trie* RT, trieNode* TN, int level, int min_sup, int k, int toplevel){

  //std::cout << "Do Prune" << '\n';
  // First Remove all leaves at higher height


  if(toplevel<=k&&level>1){
    //std::cout << "Yes 1" << '\n';
    std::map<std::string, trieNode*>::iterator k_it = TN->trie_Map.begin();
    while(k_it!=TN->trie_Map.end()){
      if(k_it->second->trie_Map.empty()){
        // Delete Node k_it->second
        trieNode* dNode = k_it->second;
        std::string dName = k_it->first;
        k_it++;
        RT->destroyNode(dNode);
        TN->trie_Map.erase(dName);
      }
      else{
        k_it++;
      }
    }
  }


  // std::cout << "Here 1" << '\n';

  if(toplevel>k&&level>toplevel-k+1){
    std::map<std::string, trieNode*>::iterator k_it = TN->trie_Map.begin();
    while(k_it!=TN->trie_Map.end()){
      if(k_it->second->trie_Map.empty()){
        // Delete Node k_it
        trieNode* dNode = k_it->second;
        std::string dName = k_it->first;
        k_it++;
        RT->destroyNode(dNode);
        TN->trie_Map.erase(dName);
      }
      else{
        k_it++;
      }
    }
  }

  // std::cout << "Here 2" << '\n';


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
      doPrune(RT, cit->second, level-1, min_sup, k, toplevel);
      cit++;
    }
  }
}
