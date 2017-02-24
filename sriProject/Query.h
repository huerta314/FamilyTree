#ifndef QUERY_H_
#define QUERY_H_

#include <deque>
#include <queue>

using namespace std;

struct Query{
	string command;
	string ruleOrFactIdentifier;
	string parameters;
	queue<string> inferenceQueue;	

};



#endif

