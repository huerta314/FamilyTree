#include "Parser.h"
#include <iostream>
#include <cstddef>
#include <vector>

using namespace std;

Parser::Parser(){}
template <typename Container>
Container& split(
  Container&                            result,
  const typename Container::value_type& s,
  const typename Container::value_type& delimiters)
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
}

Query& Parser::parse(string input){
    Query query;
    vector <string> params;
    //Split input into the a vector each split by whitespace commas and parenthesis
    split(params, input, " ,()");
    
    //The first parameter of the string should be the command so set that to the query object
    //and give it to the right parse command passing the rest of the parameters.
    //Could probably try catch an error here for unknown command
    query.command = params[0];
    if(query.command.compare("Fact"))
        query = parseFact(params);
    else if(query.command.compare("Rule"))
        query = parseRule(params);
    else if(query.command.compare("Dump"))
        query = parseDump(params);
    else if(query.command.compare("Drop"))
        query = parseDrop(params);
    else if(query.command.compare("Load"))
        query = parseLoad(params);
    else if(query.command.compare("Inference"))
        query = parseInference(params);
    else
        cout<<"Throw error here or something"<<endl;
    return query;
}

Query& Parser::parseDump(vector<string> input){
    
}

Query& Parser::parseFact(vector<string> input){
    
}

Query& Parser::parseInference(vector<string> input){
    
}

Query& Parser::parseLoad(vector<string> input){
    
}

Query& Parser::parseRule(vector<string> input){
    
}

Query& Parser::parseDrop(vector<string> input){
    
}

Parser::~Parser(){}