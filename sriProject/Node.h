#ifndef NODE_H_
#define NODE_H_


#include <string>
#include <vector>
#include "Edge.h"

using std::vector;
using std::string;

class Node{

private:

	string name;

	vector<Edge*> edges;

public:


	int setName();
	string getName();
	
	Node(); //Make sure to follow rule of 5
	~Node(); //Take care of Edge*
};
#endif
