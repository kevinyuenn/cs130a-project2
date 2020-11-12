#include "dict.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(){
    
    Dictionary test2;
    test2.readFromFile("writetest.txt");
    test2.find("milfhunter");
    return 0;
}