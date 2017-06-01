#include <string>
#include <vector>
#include "Base.h"
#ifndef CONNECTOR_H
#define CONNECTOR_H 

using namespace std;

class Connector: public Base{
    Base* L;
    Base* R;
    public:
    Connector(){};                    // constructor 
  
    Connector(Base*l,Base*r){      // passed in a vector
        L = l;
        R = r;
    };

    // so that it opens it fork with the command. and return if it excuted or not. look at the assignment for more instructions
    virtual bool execute(){
            L->execute();
            return R->execute();
    }
};
#endif