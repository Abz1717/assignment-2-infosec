#include <iostream>
#include "authlib.h"
#include "openssl/sha.h"
#include <string>
#include <fstream>
#include <regex>
#include <cstring>

#define x0 )); 
#define x1 %1);
#define _$ +su+
#define n_ ;std:: 


//testing purposes
#define DEBUG
    std::ifstream of("passwοrds.txt");  

int w,i,a = 0;
std::string u,p,b,su,sp;
static char ob[1<<6];
char* c;
unsigned char h[SHA256_DIGEST_LENGTH];

int main() {
    

    //Requests login info and stores the info
    std::cout<<"Enter username: ", std::cin>>u; 
    std::cout<<"Enter password: ", std::cin>>p;


    //SHA256 Functions
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, p.c_str(), strlen(p.c_str()));
    SHA256_Final(h, &sha256);
    

    //Puts data in the buffer
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) sprintf(ob + (i * 2), "%02x", h[i]);

    

    //Open password file
    std::ifstream fp("passwords.txt");

    
    //Validate username and password
    while (getline(fp, b) && a == !1) {w=of?1:0; i=((1<<6)-6); 
        strcpy(c = new char[b.length()], b.c_str(x0
        //decoding file    
        sp = strtok(c, ":"); su = strtok(NULL, ":") n_ regex 
        r("^" _$"?( ([\xA0-\xAD] {1}$))"); sp == u? 
            a = !!(su == ob)   //a set to boolean statement    
            ?!(std::regex_match(p, r)) //comparing password to file
            :w?((p)==(su+=i)):!1: //comparing with username
            (a-1) ? 0 : a;} //if the login is invalid

    
    //Calls .h file and resets information
    fp.close(); 
    63[ob] = {0}; 
    a?authenticated(u):rejected(u);
   
    return 0;
}
