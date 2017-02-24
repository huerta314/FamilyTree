#ifndef QUERY_H_
#define QUERY_H_

#include <deque>
#include <queue>
#include <iostream>

using namespace std;

struct Query{
	
	//for parser and interface
	string command;		//add or remove
	string ruleOrFactIdentifier;	//rule or fact
	//
	
	//for adding or removing
	string factName;				//father
	queue<string> parameters;		//roger, bob, or x, y
	//
	
	//for dumping
	string file;						//Added a string file attribute so that we can just return a query object from parsing and pass this only for dumps and loads -Trevor
	//to perform inference query
	queue<string> inferenceQueue;	//father, $x, $y AND ....

};



#endif

