#include "dict.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(){
    Dictionary test("PA2_dataset_10000.txt",10000);
    test.writeToFile("test.txt");
    Dictionary test2;
    test2 = Dictionary::readFromFile("test.txt");
    if(test2.find("zusu")){
        cout<<"found zusu"<<endl;
    }
}