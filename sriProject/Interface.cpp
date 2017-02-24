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
    if(query.command.equals("Add")) Add(query);
    else if(query.command.equals("Remove")) Remove(query);
    else if(query.command.equals("Dump")) Dump(query);
    else if(query.command.equals("Load")) Load(query);
    else if(query.command.equals("Inference")) Inference(query);
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