#include "RuleBase.h"


RuleBase::RuleBase(){
    
    
}

RuleBase::~RuleBase(){
    
}
	
/*
Adds a rule if it doesn't exist with the name in the rule base yet.
*/
int RuleBase::AddRule(Query query){
    if(!doesRuleExist(query))
        ruleContainer[query.name].push_back(query);
    
}

/*
Removes a rule from the rulebase if found.
*/
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

/*
Returns whether a rule is found or not.
*/
bool RuleBase::doesRuleExist(Query query){
    
    map<string, deque<Query> >::iterator it;
    it = ruleContainer.find(query.name);
    if (it == ruleContainer.end() ){
        return false;
    }else {
        return true;
    }
}

/*
Searches the rule base for the rule name. If found it
sets the query object to be the rule found.
*/
bool RuleBase::setRuleIdent(Query& query, string name){
    map<string, deque<Query> >::iterator it;
    deque<string> temp = query.parameters;
    it = ruleContainer.find(name);
    if (it == ruleContainer.end() ){
        return false;
    }
    else if(query.command.compare("INFERENCE") == 0){
        query = ruleContainer[name][0];
        query.parameters = temp;
        return true;
    }
    else {
        query = ruleContainer[name][0];
        query.parameters[0] = temp[0];
        return true;
    }
}

/*
Searches for a rule if it exists after the 2nd half of the AND operator of a rule query.
If a rule is found set the query object to have the rule identifier set and the rule parameters.
Does not copy the complete rule found into the query object.
*/
bool RuleBase::setSecondIdent(Query& query, string name){
    map<string, deque<Query> >::iterator it;
    deque<string> temp = query.parameters;
    it = ruleContainer.find(name);
    if (it == ruleContainer.end() ){
        return false;
    }else {
        query.ruleIdent = ruleContainer[name][0].ruleIdent;
        query.ruleParamName[0] = ruleContainer[name][0].ruleParamName[0];
        query.ruleParamName[1] = ruleContainer[name][0].ruleParamName[1];
        query.ruleParams.push_back(temp);
        query.ruleParams.push_back(temp);
        return true;
    }
}

/*
Creates a rule query to be searched if the rule is found in the rule database.
The rule is made specifically for the OR operator in which the name of the rule to
search is copied in and the parameters are copied over from the original rule parameters
and the query object is returned.
*/
bool RuleBase::setORRule(Query& query, string name){
    map<string, deque<Query> >::iterator it;
    deque<string> temp = query.parameters;
    it = ruleContainer.find(name);
    if (it == ruleContainer.end() ){
        return false;
    }else {
        query = ruleContainer[name][0];
        query.parameters = temp;        //Technically only works for ORs
        query.ruleParams[0] = temp;
        query.ruleParams[1] = temp;
        return true;
    }
}

/*
Creates a query object that can be used by the knowledge based to query for a fact
setting the name parameter to be searched for and the list of parameters that need
to be matched.
*/
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

/*
Creates a map of the string variables in the left rule as the key and
the right rule is matched to a key, if a key is found it wil insert the index
the matching variable was found in and storing it in a map.
*/
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
    
    Query paramQuery;           //Temporary query used by OR to search for more rules
    deque<Query> tempOutput;    //Temporary output of the second half of the AND operator
    deque<Query> result;        //Temporary output of AND operator
    int count = 0;
    deque<string> tempOR;
    /*OR operator for a rule
    Either half of the rule needs to return true for the result to be outputted. Check first if the 
    name of the parameter is a rule and if it is recursively call the function again to break that one down.
    If it's a fact then search the knowledge base to output all of the facts that match the query
    */
    if(query.ruleIdent.compare("OR") == 0){
        if(setORRule(paramQuery, query.ruleParamName[0]))
            QueryRule(paramQuery,output, kb);
        else
            kb.QueryFact(createFactQuery(query.ruleParamName[0], query.parameters),output);
        if(setORRule(paramQuery, query.ruleParamName[1]))
            QueryRule(paramQuery,output, kb);
        else
            kb.QueryFact(createFactQuery(query.ruleParamName[1], query.parameters),output);

    }
    /*AND operator for a rule
    The left half of the AND rule is the start of breaking down the rule. Just call it similar to the OR operator and return its output
    Loop through the output of the first half of the rule and replace the matching variable between both parameters with the output and check
    if it's a rule or a fact.If it's a rule recursively call it with the parameters set to the narrowed result. If it's a fact search the knowledgebase
    with the narrowed results. Compare both output and tempOutput and concatenate the results into the name of the rule and the differing variables.
    */
    else if(query.ruleIdent.compare("AND")==0){
        //First half of the AND operator is the same as the OR operator just call it searching for either a rule or fact
        if(setRuleIdent(paramQuery, query.ruleParamName[0]))
            QueryRule(paramQuery,output, kb);
        else
            //Queries the rule base with the same first parameter of the inference
            tempOR.push_back(query.parameters[0]);
            tempOR.push_back(query.ruleParams[0][1]);
            kb.QueryFact(createFactQuery(query.ruleParamName[0], tempOR),output);
        
        map<string,varPairT> varmap = setParamIndex(query);
        
        map<int,vector<int> > tracker;
        int n = 0;
        //Constructs a second query object with the name of the second half of the rule and the matching parameter between
        //both subrules and replaces it with the result of the left half of the expression. Then queries it into the rule/fact base
        for(int i = 0; i < output.size(); i++){
            
            Query constructedSecondParam;
            constructedSecondParam.name = query.ruleParamName[1];
            constructedSecondParam.parameters = query.ruleParams[1];
            constructedSecondParam.flag = 1;
            
            for(int j = 0; j < query.ruleParams[1].size(); j++){
                auto it = varmap.find(query.ruleParams[1][j]);
                if(it != varmap.end()){
                    constructedSecondParam.parameters[j] = output[i].parameters[varmap[query.ruleParams[1][j]].origParam];
                }
            }
            constructedSecondParam.parameters[1] = query.parameters[1];
            count = tempOutput.size();
            if(setSecondIdent(constructedSecondParam, constructedSecondParam.name)){
                QueryRule(constructedSecondParam, tempOutput, kb);
            }
            else
                kb.QueryFact(constructedSecondParam,tempOutput);
                
            //Keeps track of the index of the narrowed down search results
            vector<int> tempvec;
            if(count < tempOutput.size()){
                while(n < tempOutput.size()){
                    tempvec.push_back(n++);
                }
                tracker[i] = tempvec;
            }
            tempvec.clear();
        }
        //More efficient searching for the complete result
        //Keep track of the results in output that match in tempOutput using the tracker map
        //the tracker map stores the output index with the matching fact as the key and
        //a vector of matching indices in tempOutput that match with the key index in output
        //Can switch one variable now with 2 parameters.
        int a = 0;
        int r = 0;
        query = ruleContainer[query.name][0];
        for(int i = 0; i < query.parameters.size(); i++){
            if(query.parameters[0].compare(query.ruleParams[0][i]) == 0) a = i;
            if(query.parameters[1].compare(query.ruleParams[1][i]) == 0) r = i;
        }
        for(int i = 0; i < output.size(); i++){
            auto it = tracker.find(i);
            if(it != tracker.end()){
                count = it->second.size();
                for(int j = 0; j < count; j++){
                    Query q;
                    q.name = query.name;
                    q.parameters.push_back(output[i].parameters[a]);
                    q.parameters.push_back(tempOutput[it->second[0]].parameters[r]);
                    it->second.erase(it->second.begin());
                    result.push_back(q);
                }
            }
        }
        /*INEFFICIENT!!!!!!!!!!!!
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
        }*/
        output = result;
        
    }
    
}