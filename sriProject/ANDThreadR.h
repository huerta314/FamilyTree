
#ifndef ANDTHREADR_H
#define ANDTHREADR_H

#include "Thread.h"
#include "RuleBase.h"
#include "KnowledgeBase.h"
#include <iostream>

using namespace std;
class RuleBase;
typedef struct varPair varPairT;


struct andArgsr{
    int leftOrRight; //0 or 1 depending on side
    Query*                  paramQuery;
    Query*                  originalQuery;
    Query*                  inputQ;
    KnowledgeBase*          kbPtr;
    RuleBase*               rbPtr;
    deque<Query>*           tempOutput;
    map<string, varPairT>*  varmap;
    map<int, vector<int> >* tracker;
    int*                    iTracker;
    int*                    nTracker;
   
    
    andArgsr(void * container){
        andArgsr *unpack  = (andArgsr*) container;
        
        leftOrRight     = unpack->leftOrRight;
        paramQuery      = unpack->paramQuery;
        originalQuery   = unpack->originalQuery;
        inputQ          = unpack->inputQ;
        kbPtr           = unpack->kbPtr;
        rbPtr           = unpack->rbPtr;
        varmap          = unpack->varmap;
        tempOutput      = unpack->tempOutput;
        tracker         = unpack->tracker;
        iTracker        = unpack->iTracker;
        nTracker        = unpack->nTracker;
    }
    andArgsr(){}
};

class ANDThreadR: public Thread{
    private:
        struct andArgsr andArgsR;
         pthread_mutex_t datamutex;
    public:
        ANDThreadR(void *(*_threadRoutine) (void *) =NULL, void * args = NULL);
        ~ANDThreadR();
        void * threadMainBody(void * args);
};

#endif