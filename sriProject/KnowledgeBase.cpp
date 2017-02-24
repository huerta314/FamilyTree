/* KnowledgeBase.cpp */
#include "KnowledgeBase.h"

KnowledgeBase::KnowledgeBase(){
    
}

int KnowledgeBase::AddFact(Query query){
    
    map<string, vector<string> >* factMapTemp = &(knowledgeContainer[query.factName]);
   // map<string, vector<string> >::iterator it = factMapTemp.find(firstName);
    string firstName = query.parameters.front();
    query.parameters.pop();
    int sizeOfParams = query.parameters.size();
    vector<string>* tempSecondParams = &(*(factMapTemp)[firstName]);
    
    for(int i = 0; i < sizeOfParams; i++){
        
        tempSecondParams->push_back(query.parameters.front());
        query.parameters.pop();
    }
    
    return 1; //no error checking for now
}

int KnowledgeBase::RemoveFact(Query query){
    
    map<string, vector<string> >* factMapTemp = &(knowledgeContainer[query.factName]);
    if (query.parameters.size() == 0){
        
        factMapTemp->clear();
    }else if (query.parameters.size() == 1){
        
        string firstName = query.parameters.front();
        query.parameters.pop();        
        vector<string>* tempSecondParams = &(*(factMapTemp)[firstName]);
        tempSecondParams->clear();
        
    }else if (query.parameters.size() > 1) {
        string firstName = query.parameters.front();
        query.parameters.pop();        
        vector<string>* tempSecondParams = &(*(factMapTemp)[firstName]);
        
        int sizeOfParams = query.parameters.size();
        int numOfElements = tempSecondParams->size();
        
        for (int i = 0; i < sizeOfParams; i++){//for every element in queue
            
            for (int j = 0; j < numOfElements; j++){//iterate through all elements in array
                if ( (*tempSecondParams)[j] == query.parameters.front() ){
                    //delete matching one
                    tempSecondParams->erase(j);
                    query.parameters.pop();
                }
            }
        }
    }
    
}

int KnowledgeBase::QueryFact(Query query){
    
    
}

KnowledgeBase::~KnowledgeBase(){}