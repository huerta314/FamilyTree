#ifndef KNOWLEDGE_BASE_H_
#define KNOWLEDGE_BASE_H_

#include <string>
#include <map>
#include <deque>


#include "Node.h"
#include "Query.h"

class KnowledgeBase{

	//friend class Node;
	
	//   father         roger          john, bob, ...
	//   apple         applesauce      applejuice, applepie, ....

	
private:
//	map<string, map<string, vector<string> > > knowledgeContainer;

	map<string, deque<Query> > knowledgeContainer;
	
public:

	int AddFact(Query query);
	int RemoveFact(Query query);
	int QueryFact(Query query);
	bool doesFactExist(Query query);
	
	KnowledgeBase();

	~KnowledgeBase();
	

};


#endif

