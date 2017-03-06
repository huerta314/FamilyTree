#include <iostream>
#include <string>
#include "Interface.h"

using namespace std;

int main() {
    
    Interface interface;

    string command;
    cout << "Type 'EXIT' to quit.";
    while (command != "EXIT"){

        cout << "$> ";

        getline(cin , command);
        interface.executeCommand(command);
        

    }

    return 0;
}