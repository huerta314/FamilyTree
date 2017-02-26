/* QueryOperations.cpp */
#include "QueryOperations.h"

QueryOperations::QueryOperations(){

}

int QueryOperations::Add(Query query){
    //Check if its a fact or rule and send it to the proper knowledge rule base
    if(query.ident.compare("FACT") == 0) 
        kb.AddFact(query);
    else if (query.ident.compare("RULE") == 0) 
        rb.AddRule(query);
}

int QueryOperations::Remove(Query query){
    kb.RemoveFact(query);
    rb.RemoveRule(query);
}



int QueryOperations::Inference(Query query, deque<Query>& output){
    
    /*
    1. check each rule that matches the query name
    2. process rules to create temporary facts of given type
    3. if the user enters a name for temporary rules, then save*/
    
    bool doesFactExist = kb.doesFactExist(query);
    if (doesFactExist == false){ //no facts in kb, try the rule base
        
        bool doesRuleExist = rb.doesRuleExist(query);
        if (doesRuleExist == false){
            
            return 0; //for no inference found
        }
    }else {
        deque<Query> tempDeque;
        kb.QueryFact(query, tempDeque);
        output = tempDeque;
        return 1;
    }
    
}

int QueryOperations::Dump(Query query){
    dumper.dump(query.file, kb, rb);
    
    return 1;
}

QueryOperations::~QueryOperations(){}