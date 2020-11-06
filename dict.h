#include "hash24.h"
#include <string>

using namespace std;

class Dictionary {
    public:
        Dictionary();
        ~Dictionary();
        bool find(string word);
        void writeToFile(string fName);
        Dictionary readFromFile(string fName);
    private:
    
};