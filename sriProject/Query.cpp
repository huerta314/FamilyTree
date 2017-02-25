#include 'Query.h'

friend ostream &operator<<(ostream &output, const Query query){
    cout<<query.name<<"(";
    for(int i = 0; i < query.parameters.size(); i++){
        cout<<query.parameters[i]<<",";
    }
    cout<<")"<<endl;
    return output;
}