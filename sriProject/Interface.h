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
 	QueryOperations queryOperations;	


	int Add(Query query);
	int Remove(Query query);

	int Dump(Query query); //dumper object called here		
	int Load(Query query);
	int Inference(Query query); //Worry about it last


public:

	Interface();
	~Interface();


	//returns int : error value 
	int executeCommand(string command);	




};


#endif //PROJECTTEMP_INTERFACE_H
