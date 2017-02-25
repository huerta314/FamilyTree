#ifndef QUERY_H_
#define QUERY_H_

#include <deque>
#include <queue>
#include <iostream>

using namespace std;

struct Query{
	
	int 					flag;			//Flag to check if a drop command has a variable to search
	string					command;		//Name of the command issued
	string					ident;			//Rule or fact identifier
	//For adding/removing/parsing
	string					name;			//Name of the rule or fact to add
	deque<string>			parameters;		//The parameters of a fact or rule
	string					ruleParamName[2];//The names of the facts that make up the rule and there will only be 2 of them
	deque<deque<string> >	ruleParams;		//A queue of a queue to hold the rule parameters
	string					ruleIdent;		//String to hold whether the rule is an AND or OR
	//For dumping/loading
	string					file;			//Name of the file to output/load
	
	Query():flag(0){}						//Default constructor to set the flag to 0
	friend ostream &operator<<( ostream &output, const Query query );
};



#endif

