#ifndef EDGE_H_
#define EDGE_H_

#include <string>
#include "Node.h"

class Node;

using std::string;

class Edge{

private:
	string factName;// Father, or Apple, etc
	Node* nextName;


public:

	int setName(string n); //set n to factName
	string getName(); //get factName

	Edge();
	Edge(string n, Node* np);
	//copy constructor, move constructor, assignment operator
	Edge(Edge& other);

	~Edge();
		
};
#endif

