/* KnowledgeBase.cpp */
#include "KnowledgeBase.h"
#include <iostream>

KnowledgeBase::KnowledgeBase(){
    
}

int KnowledgeBase::AddFact(Query query){
    
    knowledgeContainer[query.name].push_back(query);
    
    

    return 1; //no error checking for now
}

int KnowledgeBase::RemoveFact(Query query){
    
    if (query.parameters.size() == 0){
        
        knowledgeContainer[query.name].clear();
        knowledgeContainer.erase(query.name);
    }else if (query.parameters.size() > 0){
        deque<Query> queriesToMatchToDelete;
        QueryFact(query, queriesToMatchToDelete);
        
        deque<Query>* kbFacts = &knowledgeContainer[query.name];
        int j = 0;
        for (auto i = kbFacts->begin(); i != kbFacts->end(); i++){
            
            for (int j = 0; j < queriesToMatchToDelete.size(); j++){
                
                Query tempQ = *i;
                if ( tempQ.factEquality(queriesToMatchToDelete[j]) == true ){
                    
                    kbFacts->erase(i);
                }
            }
        }
        return 1;
    }
        
    return 1;

    
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

//-----****Deprecated****-----
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
        
        map<string, string > varTable;
        deque<Query> retDequeVarTemp;
        bool goodToReturn = true;
        Query tempQ;
        for (int i = 0; i < retDeque.size(); i++){
            
            for (int j = 0; j < query.parameters.size(); j++){
                tempQ = retDeque[i];
                if ( query.parameters[j][0] == '$' ){
                    
                    std::map<string,string>::iterator it;
                    it = varTable.find(query.parameters[j]);
                    if (it == varTable.end()){
                        
                        varTable[query.parameters[j]] = tempQ.parameters[j];                        
                    }else { //parameter was found. match. if match we good. no match, false ret
                        
                        string parameterValue = varTable[query.parameters[j]];
                        if (parameterValue != tempQ.parameters[j] ){
                            
                            goodToReturn = false;
                        }
                    } //example, Bob($x, $x) mapped to Bob(John, John). 2 iterations wont hit goood to return = false
                        //but Bob($x, $x) mapped to Bob(John, Jack). first iteration good. second iteration, will hit else and good return = false will hit.
                        //when using all different vars, no way that find can find success. so never good to return will hit
                    
                }else{  //not a parameter to match
                    
                    if ( (tempQ.parameters[j]) != query.parameters[j] ){
                        
                        goodToReturn = false;
                    }
                }
            }
            if (goodToReturn){
                
                retDequeVarTemp.push_back(tempQ);
            }
            goodToReturn = true;
            varTable.clear();
        }
        inputDeque = retDequeVarTemp;
        return 1;

    }else{
        
        deque<Query> retDequeVarTemp;
        bool goodToReturn = true;
        Query tempQ;
        for (int i = 0; i < retDeque.size(); i++){
            
            for (int j = 0; j < query.parameters.size(); j++){
                tempQ = retDeque[i];
                if ( (tempQ.parameters[j]) != query.parameters[j] ){
                    goodToReturn = false;
                }
            }
            if (goodToReturn){
                
                retDequeVarTemp.push_back(tempQ);
            }
            goodToReturn = true;
        }
        inputDeque = retDequeVarTemp;
        return 1;
    }
}

KnowledgeBase::~KnowledgeBase(){}

/*Code trashcan, dont delete untill confirm working
Query trash code: http://pastebin.com/wDq6593z
remove fact trash: http://pastebin.com/FGYMFvGu
add fact trash: http://pastebin.com/pWYycsDe
remove fact deprecated 2: http://pastebin.com/0pgWG4QT
*/
