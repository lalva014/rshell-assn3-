#include "Or.h"
#include "Base.h"
#include <iostream>
using namespace std;



bool Or::execute(){                     // calls the executed function 
    if(Left->execute() ==  false){          /// if the left executes then right executes
        bool temp = Right->execute();   
        if(temp == false){              // depending on the reuslt of right we return true or false
            return false;
        }
        else{
            return true;
        }
    }
    else{
        return true;
    }
    
}