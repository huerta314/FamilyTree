#ifndef KNOWLEDGE_BASE_H_
#define KNOWLEDGE_BASE_H_

#include <string>
#include <map>
#include <vector>


#include "Node.h"
#include "Query.h"

class KnowledgeBase{

	//friend class Node;
	
	//   father         roger          john, bob, ...
	//   apple         applesauce      applejuice, applepie, ....

	
private:
	map<string, map<string, vector<string> > > knowledgeContainer;
	
public:

	int AddFact(Query query);
	int RemoveFact(Query query);
	int QueryFact(Query query);
	
	KnowledgeBase();

	~KnowledgeBase();
	

};


#endif

