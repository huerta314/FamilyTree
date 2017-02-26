#include "RuleBase.h"


RuleBase::RuleBase(){
    
    
}

RuleBase::~RuleBase(){
    
}
	
	
int RuleBase::AddRule(Query query){
    ruleContainer[query.name].push_back(query);
    
}
int RuleBase::RemoveRule(Query query){
    if(query.parameters.size() == 0){
        ruleContainer[query.name].clear();
        ruleContainer.erase(query.name);
    }
    else{
        for(int i = 0; i < ruleContainer[query.name].size(); i++){
            if(ruleContainer[query.name][i].parameters == query.parameters) 
                ruleContainer[query.name].erase(ruleContainer[query.name].begin()+(i-1));
        }
    }
    
}

bool RuleBase::doesRuleExist(Query query){
    
    map<string, deque<Query> >::iterator it;
    it = ruleContainer.find(query.name);
    if (it == ruleContainer.end() ){
        
        return false;
    }else {
        
        return true;
    }
}
int RuleBase::QueryRule(Query query){
    
    
}//Deduce aliases to facts and logical operations
