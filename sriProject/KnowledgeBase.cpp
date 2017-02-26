/* KnowledgeBase.cpp */
#include "KnowledgeBase.h"
#include <iostream>

KnowledgeBase::KnowledgeBase(){
    
}

int KnowledgeBase::AddFact(Query query){
    
    knowledgeContainer[query.name].push_back(query);
    
    
   /*// map<string, vector<string> >::iterator it = factMapTemp.find(firstName);
    string firstName = query.parameters.front();
    query.parameters.pop();
    int sizeOfParams = query.parameters.size();
    vector<string>* tempSecondParams = &((*factMapTemp)[firstName]);
    
    for(int i = 0; i < sizeOfParams; i++){
        
        tempSecondParams->push_back(query.parameters.front());
        query.parameters.pop();
    }*/
    
    //cout << (*factMapTemp)["Bob"][0] << " " << (*factMapTemp)["Bob"][1] << " " << (*factMapTemp)["Bob"][2];
    //This properly inserts the fact into the knowledge base. Need a way to print the values out the above line seg faults.
    
    return 1; //no error checking for now
}

int KnowledgeBase::RemoveFact(Query query){
    
    if (query.parameters.size() == 0){
        
        knowledgeContainer[query.name].clear();
        knowledgeContainer.erase(query.name);
    }else if (query.parameters.size() > 0){
        
        deque<Query>* factList = &knowledgeContainer[query.name];
        
        int outerSize = query.parameters.size();
        int listSize = factList->size();
        
        bool goodToDelete = false;
        vector<string> varList;
        int varCounter = 0;
        
        for(int i = 0; i < listSize; i++){
            
            Query* currentFact = &(*factList)[i];
            
            if ( currentFact->parameters.size()  == query.parameters.size() ){
                
                if(query.flag == 0){
                    
                    if (currentFact->parameters == query.parameters){
                        factList->erase(factList->begin() + i); //delete ith query
                    }
                    
                }else {
                    
                    /*for (int j = 0; j < outerSize; j++){
                        
                        string paramOuter = query.parameters.front();
                        string paramMy = ((*factList)[i]).front();
                        if (paramOuter[varCounter] == '$' ){
                            varList.push_back(paramOuter[varCounter]);
                            varCounter++;
                        }
                    }    */
                    cout << "\ndeleting with parameters. placeholder function\n"<<endl;
                }
            }
        }
    }
    
    /*map<string, vector<string> >* factMapTemp = &(knowledgeContainer[query.name]);
    if (query.parameters.size() == 0){
        
        factMapTemp->clear();
    }else if (query.parameters.size() == 1){
        
        string firstName = query.parameters.front();
        query.parameters.pop();        
        vector<string>* tempSecondParams = &((*factMapTemp)[firstName]);
        tempSecondParams->clear();
        
    }else if (query.parameters.size() > 1) {
        string firstName = query.parameters.front();
        query.parameters.pop();        
        vector<string>* tempSecondParams = &( (*factMapTemp)[firstName]);
        
        int sizeOfParams = query.parameters.size();
        int numOfElements = tempSecondParams->size();
        
        for (int i = 0; i < sizeOfParams; i++){//for every element in queue
            
            for (int j = 0; j < numOfElements; j++){//iterate through all elements in array
                if ( (*tempSecondParams)[j] == query.parameters.front() ){
                    //delete matching one
                    
                    vector<string>::iterator nposit = tempSecondParams->begin() + j;
                    tempSecondParams->erase(nposit);
                    query.parameters.pop();
                }
            }
        }
    }*/
    
}
bool KnowledgeBase::doesFactExist(Query query){

    map<string, deque<Query> >::iterator it;
    it = knowledgeContainer.find(query.name);
    if (it == knowledgeContainer.end() ){
        
        return false;
    }else {
        
        return true;
    }
}

//grab from input the things with x param in pos and put in output
void KnowledgeBase::getAllQueriesWithXParamInPos(string x, int pos, deque<Query>& input, deque<Query>& output){
    
    for (int i = 0; i < input.size(); i++){
        bool trueCond = false;
        
        if (x.size() == 0)
            trueCond = true;
        else
            trueCond = (input[i].parameters[pos] == x);
        
        if (trueCond){
            
            Query tempQ = input[i];
            output.push_back( tempQ );
        }else {
            
        //do nothing
        }
    }
}

//deprecated struct
typedef struct variable{
    string variable;
    int position;
} variable_t;

int KnowledgeBase::QueryFact(Query query, deque<Query>& inputDeque){
    
    
    deque<Query>* tempDeque = &knowledgeContainer[query.name];
    deque<Query> retDeque;
    
    for(int i = 0; i < tempDeque->size(); i++){
        Query* tempQuery = &(*tempDeque)[i];
        if (tempQuery->parameters.size() == query.parameters.size() ){
            
            retDeque.push_back(*tempQuery); //build a deque of all queries of same size
        }
    }
    //after obtainin all things in same size, count number of variables and their positions. if there are variables
    if (query.flag == 1){
        
        deque<Query> retDequeVarTemp;
        vector<variable_t> varList;
        for (int i = 0; i < query.parameters.size(); i++){
            
            if (query.parameters[i][0] == '$'){
                
                getAllQueriesWithXParamInPos("", i, retDeque, retDequeVarTemp);
            }else {
                getAllQueriesWithXParamInPos(query.parameters[i], i, retDeque, retDequeVarTemp);
            }
            
            retDeque = retDequeVarTemp;
            retDequeVarTemp.clear();
        }

        //done filtering variable
        inputDeque = retDeque;
        return 1;
    }else{
        
        deque<Query> retDequeVarTemp;
        for (int i = 0; i < query.parameters.size(); i++){
            

            getAllQueriesWithXParamInPos(query.parameters[i], i, retDeque, retDequeVarTemp);
            retDeque = retDequeVarTemp;
            retDequeVarTemp.clear();
            
        }
        inputDeque = retDeque;
        return 1;
    }
}

KnowledgeBase::~KnowledgeBase(){}