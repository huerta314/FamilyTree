#ifndef PARSER_H_
#define PARSER_H_
//Work in progress
//Added contructor and parse function but don't know if thats the proper return value - Trevor
#include "Query.h"
class Parser{

private:
    /*Might have to have this defined in the header cause apparently templates can only be defined in header :/
    template <typename Container>
    Container& split(
        Container&                            result,
        const typename Container::value_type& s,
        const typename Container::value_type& delimiters,
        split::empties_t                      empties = split::empties_ok )
    {
        result.clear();
        size_t current;
        size_t next = -1;
        do
    {
        if (empties == 0)
        {
          next = s.find_first_not_of( delimiters, next + 1 );
          if (next == Container::value_type::npos) break;
          next -= 1;
        }
        current = next + 1;
        next = s.find_first_of( delimiters, current );
        result.push_back( s.substr( current, next - current ) );
    }
    while (next != Container::value_type::npos);
    return result;
}*/

    //parse public method will decide which one of these to call.
                                        //From page 4 of assignment pdf
    Query& parseDump(vector<string> input);      //DUMP updated_family_relation.sri 
    Query& parseFact(vector<string> input);      //FACT Father(Roger,John) 
    Query& parseInference(vector<string> input); //INFERENCE GrandFather($X,$Y)
    Query& parseLoad(vector<string> input);      //LOAD file.sri
    Query& parseRule(vector<string> input);      //RULE Parent($X,$Y):- OR Father($X,$Y) Mother($X,$Y)
    Query& parseDrop(vector<string> input);      //DROP Parent # delete the Parent rule 
    
    

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
