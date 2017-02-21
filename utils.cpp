/*
    **********************************************************************************
    Author:   Sidharth SADANI
    Date:     2/20/17
    File:     utils.cpp
    Comments: Utility functions of this Module
    **********************************************************************************
*/

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "trie.h"

// PARSE EACH LINE OF FILE
std::vector<std::string> parseLine(std::string line){
  std::vector<std::string> Items;

  //TODO : Trim the line for escape characters at the end

  std::size_t found = line.find(" ");
  std::string subStr;
  // std::cout << "Finding Strings" << '\n';

  while (found!=std::string::npos) {
    subStr = line.substr(0,found);
    Items.push_back(subStr);
    line = line.substr(found+1);
    // std::cout << "Line: "<<line << '\n';
    found = line.find(" ");
  }
  Items.push_back(line);
  // std::cout << "At: "<< found <<" "<<line.substr(0,found-1)<< '\n';

  return Items;
}

// READ FILE FIRST TIME
std::map<std::string, int> readFileFirst(std::string inF, int k, int &maxLen){
  std::map<std::string, int> keys;
  std::map<int, int> distr;

  std::ifstream ifile(inF, std::ios::in);
  int count = 0;
  int num_lines=0;
  int num_tokens=0;

  clock_t tb = clock();

  if (ifile.is_open()) {
    std::string line;
    while (std::getline(ifile, line)) {
      // std::cout << line << '\n';
      num_lines++;
      std::vector<std::string> Items;
      Items = parseLine(line);

      int no_items = Items.size();

      if(no_items<k){
        continue;
      }

      if(no_items>maxLen){
        maxLen = no_items;
      }

      try{
        int x = distr.at(no_items);
        distr[no_items]++;
      }
      catch(...){
        distr.insert(std::make_pair(no_items,1));
      }

      while (!Items.empty()) {
        std::string key = Items.back();
        // std::cout << "Item: " <<key<<" ";

        if (keys.find(key) == keys.end()) {
          keys.insert(std::make_pair(key,1));
          //std::cout << "Doing This" << '\n';
        }
        else{
          keys[key]++;
        }
        num_tokens++;
        Items.pop_back();
      }

      count++;
      if (count==-1) {
        break;
      }
    }
    ifile.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
  clock_t te = clock();
  float et = (te-tb)/(float)CLOCKS_PER_SEC;
  std::cout << "Time Elapsed In Reading and Parsing File: "<< et << '\n';
  std::cout << "Num of Lines: "<< num_lines << '\n';
  std::cout << "Num of Tokens: "<< num_tokens << '\n';

  std::map<int, int>::iterator d_it = distr.begin();
  while(d_it != distr.end()){
    // std::cout<<d_it->first<<" : "<<d_it->second<<std::endl;
    d_it++;
  }

  return keys;
}


void writeToFile(std::string outF, std::map<std::string, int> &keys, int min_sup){
	// std::cout<<"Hello World";

  	std::ofstream ofile(outF, std::ios::out /*| std::ios::app*/);
    if (ofile.is_open()) {

  	clock_t tb = clock();
    	int sum = 0;
    	int key_ctr = 0;
    	std::map<std::string, int>::iterator it = keys.begin();
    	while (it != keys.end()) {
    	  key_ctr = key_ctr + 1;
    	  sum += it->second;
    	  if (it->second>=min_sup) {
    	    //std::cout << it->first<<" : "<<it->second << '\n';
    	    ofile << it->first <<" (" << it->second << ")" << '\n';
    	  }
    	  it++;
    	}
    	clock_t te = clock();
    	float et = (te-tb)/(float)CLOCKS_PER_SEC;
    	std::cout << "Time Elapsed In Iteration Through Map: "<< et << '\n';
    	std::cout << "Sum of Cts: "<< sum << '\n';
    	std::cout << "Num Keys: "<< key_ctr << '\n';

  	//  ofile << "This is a line.\n";
    	ofile.close();
    }
}

// OUT OF ALL ITEMS, GET FREQUENT ITEMS
std::map<std::string, int> getFreqSets(std::map<std::string ,int> &keys, int min_sup){
	std::map<std::string, int> freqSet;
	std::map<std::string, int>::iterator it = keys.begin();
	while(it != keys.end()){
		if(it->second >= min_sup){
			freqSet.insert(std::make_pair(it->first, it->second));
		}
		it++;
	}
	return freqSet;

}

///////////////////////////
// Move the below stuff to Apriori
