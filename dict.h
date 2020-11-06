#ifndef DICT_H
#define DICT_H

#include "hash24.h"
#include <string>
#include <vector>


using namespace std;

class Dictionary {
    public:
        Dictionary();
        Dictionary(string fname, int tsize);
        ~Dictionary();
        bool find(string word);
        void writeToFile(string fName);
        Dictionary readFromFile(string fName);
    private:
        
        int tsize;
        struct firstHash{
            struct secondHash{
                vector<string> words;
                firstHash* next;
                secondHash() : next(0){}
            };
            Hash24 hashFunc;
            vector<secondHash> table;
            firstHash() : hashFunc() {}
        };
        firstHash* root;
        void insertHelper(firstHash::secondHash &secondHash);
};

#endif