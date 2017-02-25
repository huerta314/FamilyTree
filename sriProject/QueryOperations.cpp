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
    if(query.ident.compare("FACT") == 0) 
        kb.RemoveFact(query);
    else if (query.ident.compare("RULE") == 0) //explicity comparison
        rb.RemoveRule(query);
}

int QueryOperations::Inference(Query query){
    
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