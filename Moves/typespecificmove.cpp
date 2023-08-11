#include "typespecificmove.h"

TypeSpecificMove::TypeSpecificMove(std::string nm, std::string dsc, unsigned int mD, unsigned int pD, std::string tp):
    Move(nm,dsc,mD,pD), Type(tp) {}

TypeSpecificMove::~TypeSpecificMove(){
    delete this;
}
