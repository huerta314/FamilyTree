#ifndef KNOWLEDGE_BASE_H_
#define KNOWLEDGE_BASE_H_

#include "Node.h"
#include "Query.h"

class KnowledgeBase{

	friend class Node;

private:
	Node masterNode;
	
public:

	int AddFact(Query query);
	int RemoveFact();
	int QueryFact(Query query);
	
	KnowledgeBase();

	~KnowledgeBase();
	

};


#endif

