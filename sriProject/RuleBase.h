#ifndef RULEBASE_H_
#define RULEBASE_H_
#include <map>
#include <vector>
#include <string>

using std::map;
using std::string;
using std::vector;

class RuleBase{


private:
	map<string, vector<string> > ruleContainer;

public:
	int AddRule(Query query);
	int RemoveRule(Query query);
	int QueryRule(Query query); //Deduce aliases to facts and logical operations

	RuleBase();
	~RuleBase();
};
#endif
