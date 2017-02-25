#include <map>
#include <vector>
#include <string>

#include <iostream>

using namespace std;


int main(){
    
    
    	map<string, multimap<string, vector<string> > > knowledgeContainer;
    	
    	multimap<string, vector<string> >* rPtr = &(knowledgeContainer["Father"]);
    	
    	vector<string> rightParams;
    	rightParams.push_back("John");
    	rPtr->insert(std::pair<string, vector<string> >("Bob", rightParams ) );
        rightParams.clear();
    	
    	
    	rightParams.push_back("Saget");
    	rightParams.push_back("Suzzy");
    	rPtr->insert(std::pair<string, vector<string> >("Bob", rightParams ) );
    	rPtr->insert(std::pair<string, vector<string> >("Garret", rightParams ) );
    	
    	string findBob = "Bob";
    	
    	std::pair< std::multimap<string, vector<string> >::iterator, std::multimap<string, vector<string> >::iterator > foundSet;
    	foundSet = rPtr->equal_range("Bob");
    	
 
    	for (std::multimap<string, vector<string> >::iterator it = foundSet.first; it != foundSet.second; ++it){
    	    cout << it->first;
    	    vector<string> rightList = (it->second);
    	    for (int i = 0; i < rightList.size(); i++){
    	        cout << " " << rightList[i];
    	    }
    	    cout << endl;
    	}
    	
    	
    return 0;
}