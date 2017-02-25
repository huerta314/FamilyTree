#include <iostream>
#include <string>
#include "Interface.h"

using namespace std;

int main() {
    
    Interface interface;

    string command;
    while (command != "EXIT"){
        //string transaction;
        //cout << "$> ";
        getline(cin , command);
        interface.executeCommand(command);
        

    }

    return 0;
}