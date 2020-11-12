#include "dictionary.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(){
    
    Dictionary test2;
    test2 = Dictionary::readFromFile("test.txt");
    test2.find("milfhunter");
    return 0;
}