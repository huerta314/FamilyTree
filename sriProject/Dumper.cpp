#include "Dumper.h"
#include <iostream>
#include <fstream>
using namespace std;
    
Dumper::Dumper(){
    //intentionally empty
}

Dumper::~Dumper(){
    //intentionally empty
}

void Dumper::dump(string file){
    string buffer = "";
    //First add all facts
    for(auto &outer_pair : knowledgeContainer){ //string, vector<Query> pairs
        for(auto &query : outer_pair.second){
            buffer += "FACT ";
            buffer += query.name//add query fields
            buffer += "(";
            for(int i = 0; i < query.parameters.size(); i++){
                buffer += query.parameters[i];
                if(i+1 != query.parameters.size()){
                    buffer += ","
                }
            }
            buffer += ")\n"; //add newline
        }
    }
    //Then add all rules
    for(auto &outer_pair : ruleContainer){ //string, vector<Query> pairs
        for(auto &query : outer_pair.second){
            buffer += "RULE ";
            buffer += query.name//add query fields
            buffer += "(";
            for(int i = 0; i < query.parameters.size(); i++){
                buffer += query.parameters[i];
                if(i+1 != query.parameters.size()){
                    buffer += "," //add commas, but not for the last param
                }
            }
            buffer += "):- ";
            buffer += query.ruleIdent;
            buffer += " ";
            buffer += query.ruleParamName[0];
            buffer += "(";
            for(){
                
            }
            buffer += ") ";
            buffer += query.ruleParamName[1];
        }
    }
    
    ofstream output_file; //open file
    output_file.open(file, ios::trunc); //overwrite it if it exists
    output_file << buffer << endl; //write the buffer to the sri file
    output_file.close(); //close file
}