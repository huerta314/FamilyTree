//
// Created by kelvinsilva on 2/21/17.
//
//Added functions and execute command body - Trevor

#include "Interface.h"

Interface::Interface(){
    
}

int Interface::executeCommand(string command){
    //Parse command
    Query query = parser.parse(command);
    //Check the header of the query object and check what command it calls
    //If statements for all the functions to call with whatever else needs to be done
    if( (query.command.compare("FACT") == 0) || (query.command.compare("RULE") == 0) ) ops.Add(query);
    else if(query.command.compare("DROP") == 0) ops.Remove(query);
    else if(query.command.compare("DUMP") == 0) ops.Dump(query);
    else if(query.command.compare("LOAD") == 0) ops.Load(query);
    else if(query.command.compare("INFERENCE") == 0) ops.Inference(query);
}

int Interface::Add(Query query){
    
    
    
}

int Interface::Remove(Query query){
    
}

int Interface::Dump(Query query){
    
}

int Interface::Load(Query query){
    
}

int Interface::Inference(Query query){
    
}

Interface::~Interface(){}