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

bool RuleBase::doesRuleExist(Query& query, string name){
    map<string, deque<Query> >::iterator it;
    it = ruleContainer.find(name);
    if (it == ruleContainer.end() ){
        return false;
    }else {
        query = ruleContainer[name][0]; // For now assume there is only one rule per name
        return true;
    }
}

Query RuleBase::createFactQuery(string name, deque<string> parameters){
    Query query;
    query.name = name;
    query.parameters = parameters;
    for(int i = 0; i < parameters.size(); i++){
        if (parameters[i][0] == '$') query.flag = 1; break;
    }
    return query;
}

int RuleBase::QueryRule(Query query, deque<Query>& output,KnowledgeBase kb){
    //OR operator idea
    //Check if its the OR operator
    Query paramQuery;
    if(query.ruleIdent.compare("OR") == 0){
    //Take first parameter and check if it exists in the rulebase
        if(doesRuleExist(paramQuery, query.ruleParamName[0]))
        //If yes then call QueryRule on that query object
            QueryRule(paramQuery,output, kb);
        else
            kb.QueryFact(createFactQuery(query.ruleParamName[0], query.ruleParams[0]),output);
        if(doesRuleExist(paramQuery, query.ruleParamName[1]))
            QueryRule(paramQuery,output, kb);
        else
            kb.QueryFact(createFactQuery(query.ruleParamName[1], query.ruleParams[1]),output);
        //If no then return everything that matches from the knowledge base
        
    //Repeat for the second parameter
    }
    //This way it recursively checks the rules for more rules in order
    
    //Need a recursive AND operator call
    //Check if its the AND operator
    
}//Deduce aliases to facts and logical operations
