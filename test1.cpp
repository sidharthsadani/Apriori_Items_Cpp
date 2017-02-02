#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

//Compilation command g++ -pipe -O2 -std=c++14 <filename > -lm

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

  //READ INPUT FILE
  //std::ifstream afile("filename.txt", std::ios::in);
  std::ifstream ifile(inF, std::ios::in);
  int count = 0;
  if (ifile.is_open()) {
    std::string line;
    while (std::getline(ifile, line)) {
      std::cout << line << '\n';
      count++;
      if (count==10) {
        break;
      }
    }
    ifile.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }

  // WRITE TO OUTPUT FILE
  std::ofstream ofile(outF, std::ios::out /*| std::ios::app*/);
  if (ofile.is_open()) {
    ofile << "This is a line.\n";
    ofile.close();
  }
  return 0;
}
