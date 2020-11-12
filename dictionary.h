#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include "hash24.h"
using namespace std;

class Dictionary{

private:
struct DictionaryNode{
    struct sucessiveHash{
        vector<string> list;
        DictionaryNode* next;
    };
    vector<sucessiveHash> table;
    Hash24 hashfunct;
    int depth;
};

DictionaryNode* primary;
vector<int> depths;
vector<int> collisions;
vector<string> allwords;

public:
    Dictionary();
    Dictionary(string fname, int tsize);
    void insertHelper(DictionaryNode* nextHash, int index);
    bool find(string word);
    bool findHelper(string word, DictionaryNode* root);
    void writeToFile(string fName);
    static Dictionary readFromFile(string fName);
};

#endif

