#include <iostream>
#include <sstream>      // std::stringstream
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <features.h>
#include "Base.h"
#include "Semi.h"
#include "Command.h"
#include "And.h"
#include "Or.h"
#include "Connector.h"
#include <cctype>



using namespace std;
                                                                        // it converts a string into an array of char*
char * Convert(string line){
    char *array =  (char*)malloc( line.size() );                          // allocates memory 
    strcpy( array, line.c_str() );                                        // converts string into char*
    return array;                                                       // return char*

} 


void execute(vector<Base*> B){
    for(unsigned i = 0; i < B.size(); i++){
        pid_t pid = fork();
                                                //child running 
        if (pid == 0){
                ( B.at(i) )->execute();         // execute the base
        } /// parent running
        else if (pid > 0){     // parent runing youw wait
            wait(NULL);
        }
        else{
            cout << "Fork fails \n";          // fork failed
            exit(-1);
        }
    }
}

Base * BuiltTree(string line){                  // built a tree with the command passed in
    string l = line;                            // copy the string
    char * pointer= Convert(line);              // conver string to char*
    stringstream broken;                        
    broken << l;                                // string into the streamstring 
    string single;                              // where the stream will go to 
    vector<string> v;                           // vector of strings
    bool start =  false;                        // the flag 
    vector<Base*> VB;                           // where the vase will be store

    while(broken >> single){                    // string store into
        if(single == "&&"){
            if(false == start){                 // two commands made here else just one
                Command * c1 = new Command(v);  // make a command 
                pointer = strtok(pointer,"&|"); // finding the next command
                pointer = strtok(NULL, "&|");   // gets second command
                string loc(pointer);            // second command into string
                stringstream nextCom(loc);      // convert into words
                string x;                       // store word here
                vector<string> nol;             // string
                while(nextCom >> x){            
                    nol.push_back(x);           // store the command and flags in the vector string
                }
                Command * c2 = new Command(nol);    //mak a new command
                And * n = new And(c1, c2);          // make and And 
                VB.push_back(n);                    // push into the VB
                start = true;                   /// turn flag off
            }
            else{
                pointer = strtok(NULL, "|&");       // get the next command
                string p(pointer);
                stringstream f(p);              // convert into stream and then string
                string co;
                vector<string> w;
                while(f >> co ){                // store command and flags in vector
                    w.push_back(co);
                }       
                Command* c = new Command(w);        // make new command
                Base* temp = new And(VB.at(0), c);  // passed in the previousone and the command
                VB.at(0) = temp;                    // point VB into the top of the tree
            }
            
        }
        else if( single == "||" ){                    // if or 
            if( false == start ){                     // first should make two commands
                Command * c1 = new Command( v );      // make a command
                pointer = strtok(pointer,"&|");     // look for th enext command
                pointer = strtok(NULL, "&|");
                string loc(pointer);                // transfer the next string to char using strtoke
                stringstream nextCom(loc);          // the tring into individual commands
                string x;                           
                vector<string> nol;
                while(nextCom >> x){
                    nol.push_back(x);               // push into the vector 
                }
                Command * c2 = new Command(nol);    // make a new command 
                Or * n = new Or(c1, c2);            // push both inot the or that was made
                VB.push_back(n);                    // push back into the VB

                start = true;
            }
            else{
                 pointer = strtok(NULL, "|&");  // case two  only one command 
                string p(pointer);              //convert pointer to string
                stringstream f(p);              // stream inot the string 
                string co;                  
                vector<string> w;   
                while(f >> co ){    
                    w.push_back(co);            // put it into the vector 
                }
                Command* c = new Command(w);    // make a new command
                Base* temp = new Or(VB.at(0), c);   // base command
                VB.at(0) = temp;                // repoint the tree     
            }    
        }
        v.push_back(single);
    }
  return VB.at(0); 
}


vector<string> split(char* l){                  // splits the original command by the ;
    vector<string> v;                   
    char *pointer  = strtok(l,";");             // splits at the ;
    string p(pointer);                          // cpmverts it to string and store
    v.push_back(p);                             // push the v back
    pointer  = strtok(NULL,";");                //  continue where you left off 
    while(pointer != 0){                        // do it till the end of the llooop
        string s(pointer);                      // conver string
        s.erase(0,1);                           // erase the string 
        v.push_back(s);                         // push back;
        pointer  = strtok(NULL,";");                    
    }
    return v;
} 
 bool checkQuit(string line){
    string w = line;
    char *point = Convert(w);
    point = strtok(point, " ");
    // string temp(point);
    // stringstream word;                           stream word 
    // word.str("");                                clearingthe stream of word
    // word.clear();                                more clearing
    // word << line;                               dumps the content of line into word.
    
    while (point != NULL){                          // line is a sentence so when it word does this to a string it only outputs word by word.
        // // cout << w << endl;
        string temp(point);
        stringstream w(temp);
        w >> temp;
        if(temp == "exit"){                        // checks for quit 
            return true;
        }
        if(temp == "Exit"){                 // checks for quit
     
            return true;
        }
        
        point = strtok(NULL, " ");
    }
    return false;
 }
 
void semi(vector<string>& commands, vector<Base*> &b){

    vector<int> num; 
    if(commands.size() == 1){                               // if there is just one command check if its a semi
            char * pointer = Convert(commands.at(0));
            pointer = strtok(pointer, "&|");                // check for |&
            string check(pointer);                          // convert to string
            if(check == commands.at(0)){                    // if not  &| then make a semi
                if(check !=  "" ){                          // if not empty string make semi
                    vector<string>v;                    
                    stringstream p(commands.at(0));         // convert the string to stream
                    string single;                          // make a string
                    while(p >> single){
                        v.push_back(single);                // push back the v
                    }   
                    Base * s = new Semi(v);                 // make a new semi
                    b.at(0) = s;
                    commands.at(0) = "";
                    num.push_back(0);
                }
            }
    }
    else{
        char * f = Convert(commands.at(0));  // convert the command to a char
        f = strtok(f, "|&");
        string test(f);                                 // char to string
        if(test == commands.at(0)){                     // check if the command is the same then there is a semi
            // if(test != ""){                             // chek for empty string
                vector<string>v;
                stringstream p(commands.at(0));         // convert string to teh stream
                string single;                          // single line 
                while(p >> single){                     // while loop keeps converting apushing to tit 
                    v.push_back(single);                // put word into the vector
                }
                Base * sv = new Semi(v);                // make a semi
                b.at(0)= sv;                            // sv the vector
                commands.at(0) = "";                    // commands ""
            // }
        }
        unsigned i = 1;
        char * w = Convert(commands.at(i));
        char * point = strtok(w, "|&");
        while(point != NULL){                           // checks for multiple ; in the command
            string t(point);                            // converts the char* to string
            if(t == commands.at(i) ){                   // chck if its the same then make command
                           // check that its not empty
                    vector<string>v;
                    stringstream w(commands.at(i));
                    string single;
                    while(w >> single){
                        v.push_back(single);            // converts into the v which we passed into the new semi
                    }
                    Base * s = new Semi(v);             /// new semi made
                    b.at(i)= s;
                    commands.at(i) = "";                // so that they output in the same order
                              
                
                }
                if(commands.size() <= i + 1){           // check to break the loop
                    break;
                }
                i++;
                w = Convert(commands.at(i));            // moves into the next command to check for semi
                point = strtok(w, "|&");

            
            }

        
    }
    

    

    
 }
vector<Base*> Tree( vector <Base*>& b,vector<string> v ){          // builts the tree
    vector<string> s;                                           
    Base* pointer;
    for(unsigned i = 0;  i < v.size(); i++ ){               // forloop that checks to built commands
        if(v.at(i) != ""){                                  // if empty dont built tree they are semi
            pointer = BuiltTree( v.at(i) );               // we call that function
            b.at(i) =pointer;                               // point it to the root
        }
    }
    return b;                                               // return the vector of bases
}   
 string checkComment(string line){          /// checks for comments
    char * pointer = Convert( line );                   // converts to char*
    pointer = strtok( pointer, "#" );               // loops for #
    string newLine( pointer );                      // converts to string and return 
    
    return newLine;
    
 }
 
vector<string> checkAO( vector<string>  s ){            // checks for the signle & or | case of vector 
    bool t = false;    // flag
    for(unsigned int i = 0; i < s.size(); i++){         // checks if there is any & or |
        char* pointer = Convert( s.at(i) );        
        pointer = strtok( pointer, " " );               // firts space or word
        while(pointer != NULL){                         // while not null loop
            string temp(pointer);                       // convert to string and check for single | or &
            if( temp == "&" || temp == "|" ){
                t = true;                                   // if true set flag true so that it doesnt do anything
            }
            pointer = strtok( NULL, " " );              /// move to next 
        }

    }
    if( t == true ){                                    // if flag true delete the vector
         s.erase(s.begin(), s.end());
                    return s;
    }
    return s;
    
}
 
Base* makeTree(string line){
    vector<string> v;
    vector <Base*> b;
    
    char *l = Convert(line);                    // converts the string line to a char* 
    v = split(l);                               // it return a vector of char* each of them is a command follow by its paramaters;
     
    for(unsigned int i = 0;  i <v.size();i++){
        if(v.at(i) == ""){
            v.erase(v.begin() + i, v.begin() + i+1 );
            break;
        }
        
    }
    b.resize(v.size());                         // the number of base in the vector.
    semi(v,b);                                  // returns all of the commands are executed right away in a vector of bases; cn is commandss    
    unsigned int T = 0;
    for(unsigned int i = 0; i < v.size(); i++){         /// checks if there is true 
        if(v.at(i) == ""){
            if(i == 0){
                T= 1;
            }
            T++;
        }
    }
    if(T == v.size()){              // if its size 1
        
    }else{
        b = Tree(b,v);
    }
    Base* root = b.at(0);
    if(v.size() != 1 ){
        for(unsigned int i = 0; i + 1 < b.size(); i++){             /// build the connector of the project
            if(i == 0){
                root = new Connector(b.at(i), b.at(i+1) );          // build the connector for the base case
            }else{
                root = new Connector(root, b.at(i+1) );     /// the connector afther the base case
            }
        }
    }
    
      v.erase(v.begin(), v.end());
    return root;


}


 vector<vector<string> > splitParan(string line){           // splits the line into the paranthesis 
    vector<vector<string> > result;
    char* pointer = strdup(line.c_str());                   // converts to a pointer char
    char* tempp = pointer;                  
    pointer = strtok(pointer , "()");                       // splits the string
    while(pointer != NULL){                     
        vector<string> t;
        char *temp = strdup(pointer);                       // make a copy of char
        string f(temp);
        stringstream ss(f);
        while(ss >> f){                                     // line to string.
            t.push_back(f);
        }
        free(temp);
        result.push_back(t);
        pointer = strtok(NULL, "()");
    }
    free(tempp);
    return result;
     
 }
 string ConvertVtoS(vector<string> p){
    string line;
    for(unsigned int i = 0; i < p.size(); i++){             // loops converts a string into char array
        if(i == 0){ 
            line = p.at(0);                         // base case 
        }else{
            line = line + " " + p.at(i);            // adds a space between
        }
    }
    return line;
     
 }
 
Base* ConnectForest(vector<vector <string> > cn){
    vector<Base*> Trees;
    Base* top;
    vector<string> Connectors;
    for(unsigned int i = 0; i < cn.size(); i++){                // loops connects the forest that we build
        string w = cn.at(i).at(   cn.at(i).size() - 1    );
        string b = cn.at(i).at(0);  // takes care of the last word being on the connector
        if(w.at(w.size()-1) == ';' && cn.at(i).at(   cn.at(i).size() - 1) !=        // checks that it doesnt end wit ;
           ";"){        
            w.erase(w.end()-1, w.end());                                // we delete the semi if its at the end;
            cn.at(i).push_back("; ");
        }                                                               // push back to the back
        else if( b == ";"){
            cn.at(i).at(0) = "; ";
        }
   
            
        
        if( (cn.at(i).at(0) == "||" ||  cn.at(i).at(0) == "; " ||           // checks to devide the connectors at the end of the string
        cn.at(i).at(0) == "&&" ) &&  (cn.at(i).at(cn.at(i).size() - 1) != "||"
        &&  cn.at(i).at(cn.at(i).size() - 1) != "; " && 
        cn.at(i).at(cn.at(i).size() - 1) != "&&" ) && cn.at(i).size() > 1 ){
                // cout << "first \n";
            Connectors.push_back( cn.at(i).at(0) );                 // we push the connectors back to the connctors vector
            cn.at(i).erase(cn.at(i).begin(), cn.at(i).begin()+1);       // we erase the connector in the string
            string result = ConvertVtoS(cn.at(i));                      // 
            Base * root = makeTree(result);                         // make a tree with the remaining string 
            Trees.push_back(root);
        }else if( (cn.at(i).at(0) == "||" ||  cn.at(i).at(0) == "; " ||             // if the case there are connectors at the end an dbegining 
        cn.at(i).at(0) == "&&" ) && (cn.at(i).at(cn.at(i).size() - 1) == "||" ||
        cn.at(i).at(cn.at(i).size() - 1) == "; " ||
        cn.at(i).at(cn.at(i).size() - 1) == "&&" ) && cn.at(i).size() > 1 ){
                            // cout << "second \n";
            Connectors.push_back( cn.at(i).at(0) );                         //  push back the connector
            Connectors.push_back( cn.at(i).at( cn.at(i).size() - 1  ));     // push back the second connector
            cn.at(i).erase( cn.at(i).begin(), cn.at(i).begin()+1 );         //  eraing the first connector
            cn.at(i).erase( cn.at(i).end()-1, cn.at(i).end() );             // eraisng the second connector
            string result = ConvertVtoS(cn.at(i));                          // making a treee
            Base *root = makeTree(result);                                      // building the tree
            Trees.push_back(root);                                              // put it into the trees vector
        }else if(  (cn.at(i).at(0) == "||" ||  cn.at(i).at(0) == "; " ||        // if its a connector by itself
        cn.at(i).at(0) == "&&" )  && cn.at(i).size() == 1){     
                            // cout << "third \n";
             Connectors.push_back( cn.at(i).at(0) );                            // pushback the connector
        }else if(   (cn.at(i).at(0) != "||" &&  cn.at(i).at(0) != ";" &&        // if the connector is at the beginin of the string
        cn.at(i).at(0) != "&&" ) && (cn.at(i).at(cn.at(i).size() - 1) == "||" ||
        cn.at(i).at(cn.at(i).size() - 1) == "; " ||
        cn.at(i).at(cn.at(i).size() - 1) == "&&" ) && cn.at(i).size() > 1 ){
                                // cout << "four \n";

             Connectors.push_back( cn.at(i).at( cn.at(i).size() - 1  ));    // push back the connector
             cn.at(i).erase( cn.at(i).end()-1, cn.at(i).end() );        // erase the connecctor 
             string result = ConvertVtoS(cn.at(i));                     // conver the vector into a string
             Base* root =makeTree(result);                              // build a tree
             Trees.push_back(root);                                         //push back the treee
        }else if( (cn.at(i).at(0) != "||" &&  cn.at(i).at(0) != "; " &&         // the connextor is at the begin of the second word
        cn.at(i).at(0) != "&&" ) && (cn.at(i).at(cn.at(i).size() - 1) != "||" 
        &&  cn.at(i).at(cn.at(i).size() - 1) != "; " && 
        cn.at(i).at(cn.at(i).size() - 1) != "&&" ) && cn.at(i).size() > 1 ){
                // cout << "five \n";
                 string result = ConvertVtoS(cn.at(i));                 // convert from vector to string
                 Base* root =makeTree(result);                          // build the tree
                 Trees.push_back(root);
            }
    }
   
    
    
    if(Trees.size() == 1){
        return Trees.at(0);                 // the case if there is on tree
        
    }else{
    
        // cout << "connectors num: " << Connectors.size() <<endl;
        for(unsigned int i = 0; i < Connectors.size(); i++){
            if(i == 0){                                                         // if first case build with two trees
                if(Connectors.at(i) == "||" ){                  // if its an || connector
                    // cout << "or\n"; 
                    top = new Or(Trees.at(i),(Trees.at(i+1)) );
                }else if(Connectors.at(i) == "&&"){                 // if its an && connector
                    // cout << "And\n"; 
                    top = new And(Trees.at(i),(Trees.at(i+1)) );
                }else if(Connectors.at(i) == "; " ){                // if its an ; connector
                    top = new Connector(Trees.at(i),(Trees.at(i+1)) );
                }
                
            }else{
                if(Connectors.at(i) == "||" ){                  // if its a || connector after base case
                    top = new Or(top,(Trees.at(i+1)) );
                }else if(Connectors.at(i) == "&&"){             // if its a && connector after base case
                    top = new And(top,(Trees.at(i+1)) );
                }else if(Connectors.at(i) == "; " ){           // if its a ; connector after base case
                    top = new Connector(top,(Trees.at(i+1)) );
                }
            
        }
       
    }
     return top;
    
}
}


void comand(){
    vector<string> v;
    vector <Base*> b;
    vector<vector <string> > cn;
    bool flagg = true;
    while(flagg == true){
        cout << "$ ";
        string line = "";
        getline(cin,line);                          // gets the commands
        
        
        if( checkQuit(line) == true ){                /// checks if the word Quit is in them. if so exits the shell

            // cout <<"wow mate \n";
            flagg = false;
            // cout << flagg << endl;
        }        
        
        if(line != ""){
            line = line + " ";                          //
            line = checkComment(line);                  // ignores everything after the #
            cn = splitParan(line);
            for(unsigned int i = 0;i < cn.size(); i++){
                if( cn.at(i).size() == 0 ){                                     // delets the vector thats empty
                    cn.erase(cn.begin() + i, cn.begin() + i+1 );
                    break;
                }
            }  
            string test = ConvertVtoS(cn.at(0));                            // converts the vector to a string
            if(cn.size() == 1 || line == test  ){           // checks if it doesnt have parenthesis 
                Base* root = makeTree(test);                // build a treee
                b.push_back(root);                  /// push back the tree
                execute(b);                                 // execute and clean the vector
                b.erase(b.begin(), b.end());
                
            }else{
                // cout << "second \n";
                Base * root = ConnectForest(cn);            // build the forest with ()
                b.push_back(root);                      /// push back the root of the forest
                execute(b);                                 //execute the forest
                b.erase(b.begin(), b.end());            // delete it
            }
             cn.erase(cn.begin(), cn.end());
        }
    } 
}

int main(){
    comand();
    
   
    return 0;
}