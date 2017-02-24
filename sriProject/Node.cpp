Node::Node(){
    name = "";
    
    
}

Node::~Node(){
    for(unsigned int i = 0; i < myEdges.size(); i++){
        myEdges.pop_back();
    }
}


int Node::setName(string nodeName){
    name = nodeName;
    return 1;
}

string Node::getName(){
    return name;
}

void Node::addEdge(Edge* edge){
    myEdges.push_back(edge);
}

