#include <iostream>
#include <fstream>
#include <string>
#include "hash24.h"
using namespace std;

int main(int argc, char *argv[]){

    ofstream writer;
    writer.open("tester.txt", ios::out | ios::trunc);
    Hash24 h;
    writer.write((char*)&h, sizeof(h));
    h.dump();
    writer.close();

    cout << endl;

    ifstream reader;
    reader.open("tester.txt", ios::in | ios:: binary);
    Hash24 h1;
    reader.read((char*)&h1, sizeof(h1));

    h1.dump();
    reader.close();

    return 0;
}