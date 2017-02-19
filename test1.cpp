#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <ctime>

//Compilation command g++ -pipe -O2 -std=c++14 <filename > -lm

// // Function Definitions
std::vector<std::string> parseLine(std::string);
// Write Output To File
// TODO: Enforce pass by reference
void writeToFile(std::string, std::map<std::string, int> &, int);
// Get Frequent Sets
std::map<std::string, int> getFreqSets(std::map<std::string, int> &, int);

int main(int argc, char const *argv[]){
  std::cout<<"Hello World"<<std::endl;
  if (argc!=5) {
    std::cout << "Insufficient Arguements" << '\n';
    return 0;
  }
  // Parse Input Parameters
  int min_sup = std::stoi(argv[1]);
  int k = std::stoi(argv[2]);
  std::string inF = argv[3];
  std::string outF = argv[4];

  std::map<std::string, int> keys;
  //READ INPUT FILE
  //std::ifstream afile("filename.txt", std::ios::in);
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

  // std::cout << "Clocks Per Sec: "<< CLOCKS_PER_SEC << '\n';
  std::map<std::string, int> freqSet = getFreqSets(keys, min_sup);
  // Write To File
  writeToFile(outF, freqSet, min_sup);
  return 0;
}


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

// WRITE OUTPUT TO FILE
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
		if(it->second > min_sup){
			freqSet.insert(std::make_pair(it->first, it->second));
		}
		it++;
	}
	return freqSet;
			
}

/*
  // Displaying Counts
  tb = clock();
  int sum = 0;
  int key_ctr = 0;
  std::map<std::string, int>::iterator it = keys.begin();
  while (it != keys.end()) {
    key_ctr = key_ctr + 1;
    sum += it->second;
    if (it->second>=min_sup) {
      std::cout << it->first<<" : "<<it->second << '\n';
    }
    it++;
  }
  te = clock();
  et = (te-tb)/(float)CLOCKS_PER_SEC;
  std::cout << "Time Elapsed In Iteration Through Map: "<< et << '\n';
  std::cout << "Sum of Cts: "<< sum << '\n';
  std::cout << "Num Keys: "<< key_ctr << '\n';
*/
