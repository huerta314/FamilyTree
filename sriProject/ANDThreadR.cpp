#include "ANDThreadR.h"
#include <iostream>

using namespace std;

//Constructor which just passes the thread routine to the thread base class
ANDThreadR::ANDThreadR(void *(*_threadRoutine) (void *), void * args):Thread(_threadRoutine), andArgsR(args){
    pthread_mutex_init(&datamutex,NULL);
}

ANDThreadR::~ANDThreadR(){}


void * ANDThreadR::threadMainBody(void * args){
    //Constructs a second query object with the name of the second half of the rule and the matching parameter between
    //both subrules and replaces it with the result of the left half of the expression. Then queries it into the rule/fact base
    Query constructedSecondParam;
    constructedSecondParam.name = andArgsR.originalQuery->ruleParamName[1];
    constructedSecondParam.parameters = andArgsR.originalQuery->ruleParams[1];
    constructedSecondParam.flag = 1;
    pthread_mutex_lock(&datamutex);
    for(int j = 0; j < andArgsR.originalQuery->ruleParams[1].size(); j++){
        auto it = andArgsR.varmap->find(andArgsR.originalQuery->ruleParams[1][j]);
        if(it != andArgsR.varmap->end()){
            constructedSecondParam.parameters[j] = andArgsR.inputQ->parameters[ andArgsR.varmap->operator[]( andArgsR.originalQuery->ruleParams[1][j] ) .origParam ];
        }
    }
    constructedSecondParam.parameters[1] = andArgsR.originalQuery->parameters[1];
    int count = andArgsR.tempOutput->size();
    if(andArgsR.rbPtr->setSecondIdent( constructedSecondParam, constructedSecondParam.name)){
        andArgsR.rbPtr->QueryRule(constructedSecondParam, *(andArgsR.tempOutput), *(andArgsR.kbPtr) );
    }
    else
        andArgsR.kbPtr->QueryFact(constructedSecondParam, *(andArgsR.tempOutput));

    pthread_mutex_unlock(&datamutex);
    pthread_mutex_unlock(&mutex);
}