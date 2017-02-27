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

bool RuleBase::setRuleIdent(Query& query, string name){
    map<string, deque<Query> >::iterator it;
    deque<string> temp = query.parameters;
    it = ruleContainer.find(name);
    if (it == ruleContainer.end() ){
        return false;
    }else {
        query = ruleContainer[name][0]; // For now assume there is only one rule per name
        return true;
    }
}

bool RuleBase::setSecondIdent(Query& query, string name){
    map<string, deque<Query> >::iterator it;
    deque<string> temp = query.parameters;
    it = ruleContainer.find(name);
    if (it == ruleContainer.end() ){
        return false;
    }else {
        query.ruleIdent = ruleContainer[name][0].ruleIdent; // For now assume there is only one rule per name
        query.ruleParamName[0] = ruleContainer[name][0].ruleParamName[0];
        query.ruleParamName[1] = ruleContainer[name][0].ruleParamName[1];
        query.ruleParams.push_back(temp);
        query.ruleParams.push_back(temp);
        return true;
    }
}

bool RuleBase::setORRule(Query& query, string name){
    map<string, deque<Query> >::iterator it;
    deque<string> temp = query.parameters;
    it = ruleContainer.find(name);
    if (it == ruleContainer.end() ){
        return false;
    }else {
        query = ruleContainer[name][0]; // For now assume there is only one rule per name
        query.parameters = temp;        //Technically only works for ORs
        query.ruleParams[0] = temp;
        query.ruleParams[1] = temp;
        return true;
    }
}

Query RuleBase::createFactQuery(string name, deque<string> parameters){
    Query query;
    query.name = name;
    query.parameters = parameters;
    for(int i = 0; i < parameters.size(); i++){
        if (parameters[i][0] == '$') {
            query.flag = 1; 
            break;
        }
    }
    return query;
}

map<string, varPairT> RuleBase::setParamIndex(Query query){
    map<string,varPairT > varmap;
    for(int i = 0; i < query.ruleParams[0].size(); i++){
        varmap[query.ruleParams[0][i]].origParam = i;
    }
    for(int i = 0; i < query.ruleParams[1].size(); i++){
        auto it = varmap.find(query.ruleParams[1][i]);
        if(it != varmap.end())
            varmap[query.ruleParams[1][i]].newParam = i;
    }
    return varmap;
}

int RuleBase::QueryRule(Query query, deque<Query>& output,KnowledgeBase kb){
    //OR operator idea
    //Check if its the OR operator
    Query paramQuery;
    deque<Query> tempOutput;
    deque<Query> result;
    int count = 0;
    int spot = 0;
    if(query.ruleIdent.compare("OR") == 0){
    //Take first parameter and check if it exists in the rulebase
        if(setORRule(paramQuery, query.ruleParamName[0]))
        //If yes then call QueryRule on that query object
            QueryRule(paramQuery,output, kb);
        else
            kb.QueryFact(createFactQuery(query.ruleParamName[0], query.ruleParams[0]),output);
        if(setORRule(paramQuery, query.ruleParamName[1]))
            QueryRule(paramQuery,output, kb);
        else
            kb.QueryFact(createFactQuery(query.ruleParamName[1], query.ruleParams[1]),output);
        //If no then return everything that matches from the knowledge base

    }
    else if(query.ruleIdent.compare("AND")==0){
        if(setRuleIdent(paramQuery, query.ruleParamName[0]))
        //If yes then call QueryRule on that query object
            QueryRule(paramQuery,output, kb);
        else
            kb.QueryFact(createFactQuery(query.ruleParamName[0], query.ruleParams[0]),output);
        /*  
        for(int i = 0; i < output.size(); i++){
            Query q;
            q.name = query.name;
            q.parameters.push_back(output[i].parameters[1]);
            result.push_back(q);
        }*/
        
        
        map<string,varPairT> varmap = setParamIndex(query);
        count = output.size();
        for(int i = 0; i < count; i++){
            Query constructedSecondParam;
            constructedSecondParam.name = query.ruleParamName[1];
            constructedSecondParam.parameters = query.ruleParams[1];
            constructedSecondParam.flag = 1;
            for(int j = 0; j < query.ruleParams[1].size(); j++){
                auto it = varmap.find(query.ruleParams[1][j]);
                if(it != varmap.end())
                    constructedSecondParam.parameters[j] = output[i].parameters[varmap[query.ruleParams[1][j]].origParam];
            }
            if(setSecondIdent(constructedSecondParam, constructedSecondParam.name)){
                QueryRule(constructedSecondParam, tempOutput, kb);
            }
            else
                kb.QueryFact(constructedSecondParam,tempOutput);
        }
        for(auto it=tempOutput.begin(); it != tempOutput.end(); it++){
            for(auto ij = output.begin(); ij != output.end(); ij++){
                for(int i = 0; i < it->parameters.size(); i++){
                    for(int j = 0; j < ij->parameters.size(); j++){
                        if(it->parameters[i].compare(ij->parameters[j]) == 0){
                            Query q;
                            q.name = query.name;
                            q.parameters.push_back(ij->parameters[0]);
                            q.parameters.push_back(it->parameters[1]);
                            result.push_back(q);
                            break;
                        }
                    }
                }
            }
        }
        output = result;
        
    }
    
}//Deduce aliases to facts and logical operations