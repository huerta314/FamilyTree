#include "Edge.h"

int Edge::setFactName(string n){
    
    factName = n;
}

string Edge::getFactName(){
    
    return factName;
}

void Edge::setNextName(Node* node){
    
    nextName = node;
}

Node* Edge::getNextName(){
    
    return nextName;
}

Edge::Edge(){
    nextName = NULL;
    factName = "";
}

Edge::~Edge(){
    
    if (nextName != NULL){
        delete nextName;
    }
}