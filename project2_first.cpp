#include "dict.h"
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
    Dictionary d1(argv[1],count);
    d1.writeToFile(argv[2]);

    return 0;
}