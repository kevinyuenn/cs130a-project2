#include "dict.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

Dictionary::Dictionary(string fname, int tsize) 
{
    string line;
    ifstream infile;
    int index;
    int count = 0;
    root = new firstHash;
    root->table.resize(tsize); //set root table to tsize 
    infile.open(fname);
    if (infile.is_open()){

        while (getline(infile,line)){
            index = root->hashFunc.hash(line)%tsize;
            root->table[index].words.push_back(line);
            // cout<<"initial insert: "<<line<<" at index: "<<index<<"\n";
            count++;
        }
        infile.close();
    }
    root->hashFunc.dump();
    cout<<"Number of words = "<<count<<"\n";
    cout<<"Table size = "<<tsize<<"\n";
    int maxcollisions;
    for (int i = 0; i <= 20; i++){
        int collisions = 0;
        for(int j = 0; j < root->table.size(); j++){
            if(root->table[j].words.size() == i){
                collisions++;
            }
        }
        if(collisions>0){
            maxcollisions=i;
        }
        cout<<"# of primary slots with "<<i
            <<" words = "<<collisions<<"\n";
    }
        cout<<"** Words in the slot with most collisions ***\n";
    for(int i = 0; i < root->table.size(); i++){
        if(root->table[i].words.size()==maxcollisions){
            for(int j = 0; j < root->table[i].words.size();j++){
                cout<<root->table[i].words[j]<<"\n";
            }
            break;
        }
    }
    for (int i = 0; i < root->table.size(); i++){
        if(root->table[i].words.size()>1){
            insertHelper(root->table[i]);
        }
    }
    
}

void Dictionary::insertHelper(Dictionary::firstHash::secondHash &secondHash) 
{
    firstHash *n = new firstHash;
    n->table.resize(pow(secondHash.words.size(),2));
    int index;
    for(int i = 0; i< secondHash.words.size();i++){
        index = n->hashFunc.hash(secondHash.words[i])%(n->table.size());
        n->table[index].words.push_back(secondHash.words[i]);
        // cout<<"inserted: "<<secondHash.words[i]<<" at index: "<<index<<"\n";
    }
    secondHash.next = n;
    for (int i = 0; i < n->table.size(); i++){
        if(n->table[i].words.size()>1){
            insertHelper(n->table[i]);
        }
    }
}

Dictionary::~Dictionary() 
{
    return;
}

bool Dictionary::find(string word) 
{
    return 0;
}

void Dictionary::writeToFile(string fName) 
{
    return;
}

Dictionary Dictionary::readFromFile(string fName) 
{
    Dictionary numtwo = Dictionary(fName, fName.length());
    return numtwo;
}



