#include <iostream>
#include <string>
#include "Interface.h"

using namespace std;

int main() {

    string transactionCommand, transaction;
    while (transactionCommand != "EXIT"){

        cout << "$> ";
        cin >> transactionCommand;
        getline(cin , transaction);

        cout << transactionCommand << transaction << endl;

    }

    return 0;
}