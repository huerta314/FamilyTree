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

int QueryOperations::Inference(Query query){
    
    /*
    1. check each rule that matches the query name
    2. process rules to create temporary facts of given type
    3. if the user enters a name for temporary rules, then save*/
    kb.QueryFact(query.name)
    
}

int QueryOperations::Dump(Query query){
    dumper.dump(query.file);
    
    return 1;
}

int QueryOperations::Load(Query query){
    //Read file
    //Loop through adding rules and facts
    //If theres inferences then search for them
}

QueryOperations::~QueryOperations(){}