#include "dict.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(){
    // Dictionary test("PA2_dataset_10000.txt",10000);
    // if (test.find("dog"))
    //     cout<<"dog found\n";
    // else cout<<"dog not found\n";
    // if(test.find("milfhunter"))
    //     cout<<"milfhunter found\n";
    // else cout<<"milfhunter not found\n";
    // if(test.find("kevin"))
    //     cout<<"kevin found\n";
    // else cout<<"kevin not found\n";

    // test.writeToFile("writetest.txt");

    // cout<<endl;
    Dictionary test("PA2_dataset_10000.txt",10000);
    test.writeToFile("writetest.txt");
    Dictionary test2;
    test2.readFromFile("writetest.txt");
    
    return 0;
}