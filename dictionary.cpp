#include "dictionary.h"
#include<string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include<iomanip>

using namespace std;
Dictionary::Dictionary(){
    primary = 0;
}

Dictionary::Dictionary(string fname, int tsize){
    primary = new DictionaryNode;
    depths.resize(21);
    collisions.resize(21);
    primary->table.resize(tsize);
    string word;
    fstream infile;
    int index;
    infile.open(fname);
    int count = 0;
    if(infile.is_open()){
        while(getline(infile,word)){
            index = primary->hashfunct.hash(word)%tsize;
            primary->table[index].list.push_back(word);
            allwords.push_back(word);
            count++;
        }
        infile.close();
    }
    for(int i = 0;i<primary->table.size();i++){
        //1 b/c if it just has 1 element, no need to expand it
        if(primary->table[i].list.size()>1){
            insertHelper(primary,i);
        }
    }
    for(int i = 0;i<primary->table.size();i++){
        collisions[primary->table[i].list.size()]++;
    }
    int maxCollisions = 0;
    for(int i = 0;i <21; i++){
        if(collisions[i]>0 && i>maxCollisions){
            maxCollisions = i;
        }

    }
    
    
    primary->hashfunct.dump();
    cout<<"Number of words = "<<count<<endl;
    cout<<"Table Size = "<<count<<endl;
    cout<<"Max collisions = "<<maxCollisions<<endl;


    for(int i = 1;i<21;i++){
        cout<<"# of primary slots with "<<i<<" words = "<<collisions[i]<<endl;
    }
    for(int i = 0;i<primary->table.size();i++){
        if(primary->table[i].list.size()==maxCollisions){
            for(int k = 0; k < primary->table[i].list.size();k++){
                cout<<primary->table[i].list[k]<<endl;
            }
            break;
        }
    }
    int sum = 0;
    int weightedsum = 0;
    for(int i = 1;i<21;i++){
        cout<<"# of secondary hash tables trying "<<i<<" hash functions = "<<depths[i]<<endl;
        sum += depths[i];
        weightedsum += i*depths[i];
    }
    float average = (float)weightedsum/(float)sum;
    cout<<fixed;
    cout<<setprecision(7);
    cout<<"Average # of hash functions tried = "<<average<<endl;

}

void Dictionary::insertHelper(Dictionary::DictionaryNode* nextHash,int ind){
    DictionaryNode* newNode = new DictionaryNode();
    nextHash->table[ind].next = newNode;
    int newSize = pow(nextHash->table[ind].list.size(),2);
    newNode->table.resize(newSize);
    newNode->depth = nextHash->depth + 1;
    for(int i = 0;i < nextHash->table[ind].list.size();i++){
        int index = newNode->hashfunct.hash(nextHash->table[ind].list[i])%newSize;
        newNode->table[index].list.push_back(nextHash->table[ind].list[i]);

    }
    bool test = true;
    for(int i = 0;i<newNode->table.size();i++){
        if(newNode->table[i].list.size()>1){
            test = false;
        }
    }
    if(test){
        depths[newNode->depth]++;
    }


    for(int i = 0; i < newNode->table.size();i++){
        //1 b/c if it just has 1 element, no need to expand it
        if(newNode->table[i].list.size()>1){
            insertHelper(newNode,i);
            return;
        }
    }

}

bool Dictionary::find(string word){
    return findHelper(word,primary);
}
bool Dictionary::findHelper(string word, Dictionary::DictionaryNode* root){
    if(root== nullptr){
        return false;
    }
    int index = root->hashfunct.hash(word)%root->table.size();
    if(root->table[index].list.size() == 1){
        if(root->table[index].list[0]==word){
             return true;
        }
    }
    else if(root->table[index].list.size() > 1){
        return findHelper(word, root->table[index].next);
    }
    return false;
}
void Dictionary::writeToFile(string fName){
    string filename = fName;
    ofstream file(filename, ios::out|ios::binary);
    int size = this->allwords.size();
    file.write((char*)&size,sizeof(int));
    file.write((char*)&this->allwords[0],allwords.size()*sizeof(string));
    file.close();
}

Dictionary Dictionary::readFromFile(string fName){
    Dictionary d;
    vector<string> v;
    int size;
    fstream file;
    file.open(fName, ios::in);
    file.read((char*)&size, sizeof(int));
    v.resize(size);
    file.read((char*)&v[0], size*sizeof(string));
    file.close();

    DictionaryNode* prim = new DictionaryNode;
    d.depths.resize(21);
    d.collisions.resize(21);
    d.primary = prim;
    prim->table.resize(size);

    int index;
    for(int i = 0;i<v.size();i++){
            index = prim->hashfunct.hash(v[i])%size;
            prim->table[index].list.push_back(v[i]);
            d.allwords.push_back(v[i]);
    }
    for(int i = 0;i<prim->table.size();i++){
        //1 b/c if it just has 1 element, no need to expand it
        if(prim->table[i].list.size()>1){
            d.insertHelper(prim,i);
        }
    }
    for(int i = 0;i<prim->table.size();i++){
        d.collisions[prim->table[i].list.size()]++;
    }
    int maxCollisions = 0;
    for(int i = 0;i <21; i++){
        if(d.collisions[i]>0 && i>maxCollisions){
            maxCollisions = i;
        }

    } 
    return d;
}