#include <iostream>
#include <string>
#include "Interface.h"
#include "socketInclude.h"

using namespace std;

int main() {
    
    Interface interface;

    string command;
    cout << "Type 'EXIT' to quit.\n";
    while (command != "EXIT"){

        cout << "$> ";

        getline(cin , command);
        interface.executeCommand(command);
        

    }

    return 0;
}