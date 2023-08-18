#include "squad.h"

Squad::Squad():name(), components()
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
