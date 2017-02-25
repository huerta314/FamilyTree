#include <iostream>
#include <sstream>
#include <cstddef>
#include <vector>

using namespace std;

struct split
{
  enum empties_t { empties_ok, no_empties };
};

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
void print( vector <string> & v )
{
  for (size_t n = 0; n < v.size(); n++)
    cout << "\"" << v[ n ] << "\"\n";
  cout << endl;
}

int main(){
    
	while(1){
	    string s;
	    string test[2];
	    test[0] = "Hello";
	    test[1] = " Not World";
	    vector <string> fields;
	    getline(cin,s);
	    cout<<test[0]<<test[1]<<endl;
	    //split(fields,s," ,()");
	    //print(fields);
	}

return 0;
}
