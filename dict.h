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
        static Dictionary readFromFile(string fName);
    private:
        vector<int> secondary;
        int tsize;
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
        // void insertHelper(firstHash::secondHash &secondHash);
        void insertHelper(firstHash *firstHash, int index);
        bool findHelper(string word, firstHash *firstHash);
};

#endif