#ifndef PARSER_H_
#define PARSER_H_
//Work in progress
//Added contructor and parse function but don't know if thats the proper return value - Trevor
#include "Query.h"
class Parser{

private:

    //parse public method will decide which one of these to call.
                                        //From page 4 of assignment pdf
    Query parseDump(string input);      //DUMP updated_family_relation.sri 
    Query parseFact(string input);      //FACT Father(Roger,John) 
    Query parseInference(string input); //INFERENCE GrandFather($X,$Y)
    Query parseLoad(string input);      //LOAD file.sri
    Query parseRule(string input);      //RULE Parent($X,$Y):- OR Father($X,$Y) Mother($X,$Y)
    Query parseDrop(string input);      //DROP Parent # delete the Parent rule 
    

    /*
    
    Splitting up the parsing this way will make it easier to code. 
    if all functionality is in public parse method, then this method will have too many lines to be manageable
    */

public:
    Parser();
    Query parse(string input, int& error);  //When calling parse, user will pass reference to an integer. If error we will return by reference
    
    
    
    
    ~Parser();
	
};

#endif
