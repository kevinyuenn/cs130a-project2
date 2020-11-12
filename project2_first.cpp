#include "dictionary.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
    string line;
    ifstream infile;
    int index;
    int count = 0;
    infile.open(argv[1]);
    if (infile.is_open()){
        while (getline(infile,line)){
            count++;
        }
        infile.close();
    }
    string input = argv[1];
    Dictionary d1(input,count);
    string file = argv[2];
    d1.writeToFile(file);

    return 0;
}