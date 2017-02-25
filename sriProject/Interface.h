//
// Created by kelvinsilva on 2/21/17.
//

#ifndef PROJECTTEMP_INTERFACE_H
#define PROJECTTEMP_INTERFACE_H

#include <string>
#include <iostream>

#include "Parser.h"
#include "QueryOperations.h"
#include "Query.h"

using namespace std;

class Interface {

private:

	Parser parser;
 	QueryOperations ops;	
	int Load(Query query);


public:

	Interface();
	~Interface();
	//returns int : error value 
	int executeCommand(string command);	




};


#endif //PROJECTTEMP_INTERFACE_H
