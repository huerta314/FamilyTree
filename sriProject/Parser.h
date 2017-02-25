#ifndef PARSER_H_
#define PARSER_H_
//Work in progress
//Added contructor and parse function but don't know if thats the proper return value - Trevor
#include "Query.h"
class Parser{

private:
    /*This is a split function to split up the string inputs from the command line
    Might have to have this defined in the header cause apparently templates can only be defined in header :/
    template <typename Container>
    Container& split(
        Container&                            result,
        const typename Container::value_type& s,
        const typename Container::value_type& delimiters )
    {
        result.clear();
        size_t current;
        size_t next = -1;
        do
    {
        next = s.find_first_not_of( delimiters, next + 1 );
        if (next == Container::value_type::npos) break;
        next -= 1;
        current = next + 1;
        next = s.find_first_of( delimiters, current );
        result.push_back( s.substr( current, next - current ) );
    }
    while (next != Container::value_type::npos);
    return result;
}*/

    //parse public method will decide which one of these to call.
    //From page 4 of assignment pdf
    Query& parseDump(vector<string> input, Query& query);      //DUMP updated_family_relation.sri 
    Query& parseFact(vector<string> input, Query& query);      //FACT Father(Roger,John) 
    Query& parseInference(vector<string> input, Query& query); //INFERENCE GrandFather($X,$Y)
    Query& parseLoad(vector<string> input, Query& query);      //LOAD file.sri
    Query& parseRule(vector<string> input, Query& query);      //RULE Parent($X,$Y):- OR Father($X,$Y) Mother($X,$Y)
    Query& parseDrop(vector<string> input, Query& query);      //DROP Parent # delete the Parent rule 
    
    

    /*
    
    Splitting up the parsing this way will make it easier to code. 
    if all functionality is in public parse method, then this method will have too many lines to be manageable
    */

public:
    Parser();
    Query& parse(string input);  //Parse should throw an error to catch
    
    
    
    
    ~Parser();
	
};

#endif
