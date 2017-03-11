#include "Query.h"

ostream& operator<<(ostream &output, const Query &query){
    cout<<query.name<<"(";
    for(int i = 0; i < query.parameters.size(); i++){
        cout<<query.parameters[i];
        if(i != query.parameters.size()-1) cout<<",";
    }
    cout<<")";
    return output;
}

bool Query::factEquality(const Query& other){
	
	bool isEqual = true;
	
	isEqual = (this->name == other.name);
	if (isEqual == false ) return isEqual;
	
	isEqual = (this->parameters == other.parameters);
	
	return isEqual;
}
