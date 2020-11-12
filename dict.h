#ifndef DICT_H
#define DICT_H

#include "hash24.h"
#include <string>
#include <vector>
#include <set>

using namespace std;

class Dictionary {
    public:
        Dictionary();
        Dictionary(string fname, int tsize);
        bool find(string word);
        void writeToFile(string fName);
        static Dictionary readFromFile(string fName);
    private:
        // Dictionary(vector<string> list, int tsize);
        vector<int> secondary;
        struct firstHash{
            struct secondHash{
                vector<string> words;
                firstHash* next;
                secondHash() : next(0){}
            };
            int depth;
            Hash24 hashFunc;
            vector<secondHash> table;
            firstHash() : hashFunc(), depth(0) {}
        };
        firstHash* root;
        void insertHelper(firstHash *firstHash, int index);
        bool findHelper(string word, firstHash *firstHash);
        // void writeToFileHelper( vector <Dictionary::firstHash> *firstObj,
                                // vector <vector<string>> *tableWords, 
                                // vector <Hash24> *hashObj,
                                // vector <bool> *next,
                                // vector <int> *tableSize,
                                // firstHash *firstHash, int size);
        vector<string> initialList;
};      

#endif