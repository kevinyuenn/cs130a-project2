#include "dict.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
    string line;
    ifstream infile;
    int index;
    int count = 0;
    string inputs = argv[2];
    int start = 0;
    vector<string> in;
    for(int i = 0; i < inputs.length(); i++){
        if (inputs[i] == ' '){
            in.push_back(inputs.substr(start, i-start));
            start = i + 1;
            i = start;
        }
        if (inputs[i] == ','){
            in.push_back(inputs.substr(start, i-start));
            start = i + 2;
            i = start;
        }
        if (i == inputs.length()-1){
            in.push_back(inputs.substr(start, i-start+1));
        }
    }
    string file = argv[1];
    Dictionary d;
    d = Dictionary::readFromFile(file);
    for(int i = 0; i<in.size(); i++){
        if(d.find(in[i])){
            cout<<in[i]<<" found \n";
        }
        else{
            cout<<in[i]<<" not found \n";
        }
    }
    return 0;
}