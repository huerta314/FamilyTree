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

	vector<Edge*> myEdges;

public:


	int setName();
	string getName();
	
	void addEdge(Edge* edge);
	vector<Edge*>* getEdgeList();
	
	
	
	Node(); //Make sure to follow rule of 5
	~Node(); //Take care of Edge*
};
#endif
