#include "dict.h"
#include <iostream>

using namespace std;

int main(){
    Dictionary test2 = Dictionary::readFromFile("write.txt");
    cout<<"1\n";
    if (test2.find("dog"))
        cout<<"dog found\n";
    else cout<<"dog not found\n";
    if(test2.find("milfhunter"))
        cout<<"milfhunter found\n";
    else cout<<"milfhunter not found\n";
    if(test2.find("kevin"))
        cout<<"kevin found\n";
    else cout<<"kevin not found\n";
}