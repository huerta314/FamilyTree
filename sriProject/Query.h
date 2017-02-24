#ifndef QUERY_H_
#define QUERY_H_

#include <deque>
#include <queue>
#include <iostream>

using namespace std;

struct Query{
	string command;
	string ruleOrFactIdentifier;
	string parameters;
	string file;						//Added a string file attribute so that we can just return a query object from parsing and pass this only for dumps and loads -Trevor
	queue<string> inferenceQueue;	

};



#endif

