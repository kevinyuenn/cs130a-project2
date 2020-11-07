#include "dict.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <iomanip>

using namespace std;

Dictionary::Dictionary(): tsize(0), root(0){}

Dictionary::Dictionary(string fname, int tsize) 
{
    string line;
    ifstream infile;
    int index;
    int count = 0;
    secondary.resize(20);
    for(int i = 0; i < 20; i++){
        secondary[i] = 0;
    }
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
        // cout<<"# of primary slots with "<<i
        //     <<" words = "<<collisions<<"\n";
    }
    cout<<"Max collisions = "<<maxcollisions<<"\n";
    
    for (int i = 0; i <= 20; i++){
        int collisions = 0;
        for(int j = 0; j < root->table.size(); j++){
            if(root->table[j].words.size() == i){
                collisions++;
            }
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
            insertHelper(root, i);
        }
    }
    int weight = 0;
    int max = 0;
    for(int i = 1; i < 21; i++){
        cout<<"# of secondary hash tables trying "<<i<<" hash functions = "<<secondary[i-1]<<"\n";
        max += secondary[i-1];
        weight += i * secondary[i-1];
    }
    float average = (float)weight/(float)max;
    cout<<fixed;
    cout<<setprecision(7);
    cout<<"Average # of hash functions tried = "<<average<<"\n";

}


void Dictionary::insertHelper(Dictionary::firstHash *first, int index){
    firstHash *n = new firstHash;
    first->table[index].next = n;
    n->depth = first->depth+1;
    n->table.resize(pow(first->table[index].words.size(),2));
    int hashIndex;
    for(int i = 0; i < first->table[index].words.size();i++){
        hashIndex = n->hashFunc.hash(first->table[index].words[i])%(n->table.size());
        n->table[hashIndex].words.push_back(first->table[index].words[i]);
    }
    int nextHash;
    for(int i = 0; i < n->table.size(); i++){
        if(n->table[i].words.size()>1){
            insertHelper(n, i);
            return;
        }
        
    }

    bool test = true;
    for(int i = 0; i < n->table.size(); i++){
        if(n->table[i].words.size()>1){
            test = false;
        }
    }
    if(test)
        secondary[first->depth]++;
}

// void Dictionary::insertHelper(Dictionary::firstHash::secondHash &secondHash) 
// {
//     firstHash *n = new firstHash;
//     secondHash.next = n;
//     n->table.resize(pow(secondHash.words.size(),2));
//     int index;
//     for(int i = 0; i< secondHash.words.size();i++){
//         index = n->hashFunc.hash(secondHash.words[i])%(n->table.size());
//         n->table[index].words.push_back(secondHash.words[i]);
//         // cout<<"inserted: "<<secondHash.words[i]<<" at index: "<<index<<"\n";
//     }

//     for (int i = 0; i < n->table.size(); i++){
//         if(n->table[i].words.size()>1){
//             insertHelper(n->table[i]);
//         }
//     }
// }




Dictionary::~Dictionary() 
{
    return;
}

bool Dictionary::find(string word) {
    return findHelper(word, root);
}

bool Dictionary::findHelper(string word, Dictionary::firstHash *firstHash){
    if(!firstHash){
        return false;
    }
    int hashIndex = firstHash->hashFunc.hash(word)%(firstHash->table.size());
    if (firstHash->table[hashIndex].words.size() > 1){
        return findHelper(word, firstHash->table[hashIndex].next);
    }
    else if(firstHash->table[hashIndex].words.size() == 1){
        if(word == firstHash->table[hashIndex].words[0]){
            return true;
        }
    }
    return false;
}


void Dictionary::writeToFile(string fName) 
{
    ofstream file1;
    file1.open(fName, ios::out | ios::trunc);
    file1.write((char*)this, sizeof(this));
    file1.close();
}

Dictionary Dictionary::readFromFile(string fName) 
{
    Dictionary d1;
    fstream file2;
    file2.open(fName, ios::in | ios:: binary);
    file2.read((char*)&d1, sizeof(d1));
    file2.close();
    return d1;
}



