#include "dict.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <iomanip>

using namespace std;

Dictionary::Dictionary(){
    root = 0;
}

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
            initialList.push_back(line);
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
    string filename = fName;
    ofstream file(filename, ios::out|ios::binary);
    int size = this->initialList.size();
    file.write((char*)&size, sizeof(size));  //write size once
    vector<int> currLen;
    for(int i = 0; i < size; i++){
        currLen.push_back(initialList[i].length());
    }
        // cout<<initialList[size-1]<<endl;
        // cout<<currLen[size-1]<<endl;
    for(int i = 0; i < size; i++){
        string temp;
        file.write((char*)&currLen[i], sizeof(currLen[i])); //write size of string
        temp = initialList[i];
        file.write((char*)&temp, currLen[i]);  //write string
        // if(i == size-1){
        //     cout<<"\""<<temp<<"\""<<endl;
        // }
    }
    
    file.close();

    // sample read test
    ifstream file2(filename, ios::in|ios::binary);
    int sizetest;
    file2.read((char*)&sizetest, sizeof(sizetest));
    // cout<<sizetest<<endl;
    vector<string> v;
    for(int i=0; i < size; i++){
        int strLen;
        file2.read((char*)&strLen, sizeof(strLen));

        char* stringData = new char[strLen];
        file2.read((char*)stringData, strLen*sizeof(char));
        string temp(stringData);
        v.push_back(temp.substr(0,strLen));
        // if (i == size-1){
        //     cout<<strLen<<endl;
        //     cout<<temp<<endl;
        // }

    }
    file2.close();
}

Dictionary Dictionary::readFromFile(string fName) 
{
    int size;
    vector<string> v;
    ifstream file;
    firstHash *n = new firstHash;
    file.open(fName, ios::in);
    file.read((char*)&size, sizeof(size));
    for(int i = 0; i < size; i++){
        int strLen;
        file.read((char*)&strLen, sizeof(strLen));

        char* stringData = new char[strLen];
        file.read(stringData, strLen);
        string temp(stringData);
        v.push_back(temp.substr(0,strLen));
        if (i == 0){
            cout<<strLen<<endl;
        }
    }
    // cout<<v[150]<<endl;
    // cout<<"made it 0.5 \n";
    file.close();



    Dictionary d;
    d.secondary.resize(20);
    for(int i = 0; i < 20; i++){
        d.secondary[i] = 0;
    }
    d.root = n;
    n->table.resize(size); //set root table to tsize 
    // cout<<"made it 1 \n";
    // cout<<v[150]<<endl;
    int index;
    for(int i = 0; i < size; i++){
        d.initialList.push_back(v[i]);
        index = n->hashFunc.hash(v[i])%size;
        n->table[index].words.push_back(v[i]);
        // cout<<"initial insert: "<<line<<" at index: "<<index<<"\n";
    }
    // cout<<"made it 2 \n";
    // cout<<n->table.size()<<endl;
    for (int i = 0; i < n->table.size(); i++){
        if(n->table[i].words.size()>1){
            cout<<n->table[i].words.size();
            d.insertHelper(n, i);
        }
    }
    // cout<<"made it 3 \n";
    // if(d.find("zus"))
    //     cout<<"zus found\n";
    // else cout<<"zus not found\n";
    return d;
}



