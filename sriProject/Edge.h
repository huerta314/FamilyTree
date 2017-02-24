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

	int setFactName(string n); //set n to factName
	string getFactName(); //get factName
	
	void setNextName(Node* node);
	Node* getNextName();
	

	Edge();
	
	
	//copy constructor, move constructor, assignment operator
	/*Edge(Edge& other);
	Edge(string n, Node* np);*/
	

	~Edge();
		
};
#endif

