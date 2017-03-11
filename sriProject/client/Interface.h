//Interface.h
// Created by kelvinsilva on 2/21/17.
//Provides the functions to execute commands for the user

#ifndef PROJECTTEMP_INTERFACE_H
#define PROJECTTEMP_INTERFACE_H

#include <string>
#include <iostream>
#include <fstream>

#include "Parser.h"
#include "QueryOperations.h"
#include "Query.h"

using namespace std;

class Interface {

private:

	Parser parser; //object of Parser class
 	QueryOperations ops; //object of querry operations class	
	int Load(Query query); //Loads a file and each line should just be a command so take each line and give it back to the execute command function
	void print(deque<Query> queries); //Prints results of inference command


public:

	Interface();
	~Interface();
	int executeCommand(string command);	//Executes Operation from Query Operations based on parsed string in query struct




};


#endif //PROJECTTEMP_INTERFACE_H
