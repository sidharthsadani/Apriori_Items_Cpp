# APRIORI ALGORITHM FOR FREQ ITEMSETS IN C++

Compile Command:
g++ -pipe -O2 -std=c++14 main.cpp apriori.cpp utils.cpp trie.cpp -lm -o TR

Usage:
./TR min_sup k inFile outPrefix

NOTE: outPrefix in this case should just be "out", it will be appended by minsup, k

Sample Usage:
./TR 3 8 transactionDB.txt out

Approach:
Efficient Tree Structre, where each node contains a hashmap to pointers of it's child nodes.
