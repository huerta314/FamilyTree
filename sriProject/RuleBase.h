#ifndef RULEBASE_H_
#define RULEBASE_H_

#include <map>
#include <deque>
#include <string>

#include "Query.h"

using std::map;
using std::string;
using std::vector;

class RuleBase{


private:
	map<string, deque<Query> > ruleContainer;

public:
	int AddRule(Query query);
	int RemoveRule(Query query);
	int QueryRule(Query query); //Deduce aliases to facts and logical operations

	RuleBase();
	~RuleBase();
};
#endif
