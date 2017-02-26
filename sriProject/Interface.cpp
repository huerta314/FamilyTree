//
// Created by kelvinsilva on 2/21/17.
//

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
    else if(query.command.compare("LOAD") == 0) Load(query);
    else if(query.command.compare("INFERENCE") == 0){
        deque<Query> tempDeque;
        if (ops.Inference(query, tempDeque) == 0){
            return 0;
        }
        print(tempDeque);
    } 
    return 1;
}

//Loads a file and each line should just be a command so take each line and give it back to the execute command function
int Interface::Load(Query query){
    string line;
    ifstream file(query.file);
    if(file.is_open()){
        while(getline(file,line)){
            if(line == " ") continue;
            executeCommand(line);
        }
        file.close();
    }
    else cout << "Unable to open file"; 
}

//Prints the results of the inference command
void Interface::print(deque<Query> queries){
    for(int i = 0; i < queries.size(); i++){
        cout<<queries[i]<<endl;
    }
}

Interface::~Interface(){}