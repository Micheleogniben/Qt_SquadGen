#include "squad.h"

Squad::Squad():components(), name()
{

}

void Squad::addCharacter(Character* c){
    components.push_back(c);
}

unsigned int Squad::weight() const{
    unsigned int weight=0;
    for(auto it =components.begin(); it!=components.end(); it++){
       weight+=(*it)->getWeight();
    }
    return weight;
}

bool Squad::isEmpty()const{
    if(components.size()==0) return true;
    else return false;
}
