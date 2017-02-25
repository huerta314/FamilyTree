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

void Dumper::dump(string file, KnowledgeBase& KB, RuleBase& RB){
    string buffer = "";
    //First add all facts
    //Loop through each fact with the same name
    for(auto &outer_pair : KB.knowledgeContainer){ //string, vector<Query> pairs
        for(auto &query : outer_pair.second){
            buffer += "FACT ";
            buffer += query.name//add query fields
            buffer += "(";
            //Loop through each parameter and add it to the buffer
            for(int i = 0; i < query.parameters.size(); i++){
                buffer += query.parameters[i];
                if(i+1 != query.parameters.size()){
                    buffer += ",";//add commas in between each one, but not for the last param
                }
            }
            buffer += ")\n"; //add newline
        }
    }
    //Then add all rules
    //Loop through each set of rules with the same name
    for(auto &outer_pair : RB.ruleContainer){ //string, vector<Query> pairs
        //Loop through each query in the vector of queries for the rule
        for(auto &query : outer_pair.second){
            buffer += "RULE ";
            buffer += query.name//add query fields to the buffer
            buffer += "(";
            //Loop through each parameter and add it to the buffer
            for(int i = 0; i < query.parameters.size(); i++){
                buffer += query.parameters[i];
                if(i+1 != query.parameters.size()){
                    buffer += ","; //add commas in between each one, but not for the last param
                }
            }
            buffer += "):- ";
            buffer += query.ruleIdent; //This is "OR" or "AND"
            buffer += " ";
            //Add first sub-rule to the buffer
            buffer += query.ruleParamName[0];
            buffer += "(";
            //Just like before, print all params for the sub-rule
            for(int i = 0; i < query.rulesParams[0].size(); i++){
                buffer += query.parameters[0][i];
                if(i+1 != query.parameters[0].size()){
                    buffer += ",";
                }
            }
            buffer += ") ";
            //Repeat for second sub-rule
            buffer += query.ruleParamName[1];
            buffer += "(";
            for(int i = 0; i < query.rulesParams[1].size(); i++){
                buffer += query.parameters[1][i];
                if(i+1 != query.parameters[1].size()){
                    buffer += ",";
                }
            }
            buffer += ")\n"; //end the line
        }
    }
    
    ofstream output_file; //open file
    output_file.open(file, ios::trunc); //overwrite it if it exists
    output_file << buffer << endl; //write the buffer to the sri file
    output_file.close(); //close file
}