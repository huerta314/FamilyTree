/* QueryOperations.cpp */
#include "QueryOperations.h"

QueryOperations::QueryOperations(){

}

int QueryOperations::Add(Query query){
    //Check if its a fact or rule and send it to the proper knowledge rule base
    if(query.ruleOrFactIdentifier.compare("Fact")) 
        kb.AddFact(query);
    else    
        rb.AddRule(query);
}

int QueryOperations::Remove(Query query){
    if(query.ruleOrFactIdentifier.compare("Fact")) 
        kb.RemoveFact(query);
    else 
        rb.RemoveFact(query);
}

int QueryOperations::Inference(Query query){
    
}

int QueryOperations::Dump(string file){
    dumper.dump(file);
}

int QueryOperations::Load(Query query){
    //Read file
    //Loop through adding rules and facts
    //If theres inferences then search for them
}

QueryOperations::~QueryOperations(){}