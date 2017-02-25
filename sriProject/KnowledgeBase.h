#ifndef KNOWLEDGE_BASE_H_
#define KNOWLEDGE_BASE_H_



#include "Node.h"
#include "Query.h"

class KnowledgeBase{

	//friend class Node;
	map<string, map<string, vector<string> > > knowledgeContainer;
	//   father         roger          john, bob, ...
	//   apple         applesauce      applejuice, applepie, ....

	
private:
	
	
public:

	int AddFact(Query query);
	int RemoveFact(Query query);
	int QueryFact(Query query);
	
	KnowledgeBase();

	~KnowledgeBase();
	

};


#endif

