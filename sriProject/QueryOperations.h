#ifndef QUERY_OPERATIONS_H_
#define QUERY_OPERATIOSN_H_

#include "Dumper.h"
#include "KnowledgeBase.h"
#include "RuleBase.h"
#include "Query.h"

class QueryOperations{

private:
	Dumper dumper;
	KnowledgeBase kb;
	RuleBase rb;


public:
	QueryOperations();
	int Add(Query query);
	int Remove(Query query);

	int Inference(Query query);
	int Dump(string file);
	int Load(string file);
	~QueryOperations();
};
#endif
