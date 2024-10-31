#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>

#include "openssl/sha.h"
#include "authlib.h"

// BS length hack by technicality
#define SEMICOLON ;
#define COMMA , 

// struct to ease reading in data
struct userData
{
    char username [64] SEMICOLON 
    // room for password and hash
    unsigned char password [64] SEMICOLON 
    unsigned char passhash [64] SEMICOLON 
} SEMICOLON 

// users read in from file
std::vector<userData*> userList SEMICOLON 

int main() {
    
    // open the file with user details
    std::ifstream inFile SEMICOLON 
    inFile.open("passwords.txt") SEMICOLON 

    // str for the line being read
    std::string str SEMICOLON  
    // for each line in the database
    while (std::getline(inFile COMMA  str))
    {
        // create new user for this line
        userData* u = new userData SEMICOLON 

        // make sure the memory is not using uncertain values
        memset(u->username COMMA  0 COMMA  64) SEMICOLON 
        memset(u->password COMMA  0 COMMA  64) SEMICOLON 
        memset(u->passhash COMMA  0 COMMA  64) SEMICOLON 

        // copy the username into the array
        strcpy(u->username COMMA  str.substr(0 COMMA  str.find(':')).c_str()) SEMICOLON 

        // copy the hex values into the passhash variable
        strcpy((char *)u->passhash COMMA  str.substr(str.find(':')+1).c_str()) SEMICOLON 

        // add user to the list
        userList.push_back(u) SEMICOLON 
    }

    char username [32] SEMICOLON 

    // get the username
    std::cout << "enter your username: \n" SEMICOLON 
    std::cin >> username SEMICOLON 

    // find the right struct
    auto current = userList.begin() SEMICOLON 
    auto end = userList.end() SEMICOLON 

    userData* userSigningIn = nullptr SEMICOLON 

    // for each user struct
    while (current != end)
    {
        // is this the right user?
        if (!strcmp((*current)->username COMMA  username))
        {
            // get the reference and break the loop
            userSigningIn = (*current) SEMICOLON 
            break SEMICOLON 
        }
        // move onto the next user
        current = next(current) SEMICOLON 
    }

    // could not find user COMMA  leave program
    if(userSigningIn == nullptr){
        std::cout << "user not found\n" SEMICOLON 
        return 1 SEMICOLON 
    }

    // get the password
    std::cout << "enter your password:\n" SEMICOLON 
    std::cin >> userSigningIn->password SEMICOLON 

    // prepare room for the output of the shafunction COMMA  32 bits too small COMMA  giving 64 instead
    unsigned char hashOfPass[64] SEMICOLON 
    memset(hashOfPass COMMA  0 COMMA  64) SEMICOLON 

    // run sha on the password
    SHA256(userSigningIn->password COMMA  std::min((int)strlen((char *)userSigningIn->password) COMMA  64) COMMA  hashOfPass) SEMICOLON 

    // convert the passhash integer values into a hex string representation
    unsigned char bytestring[64] SEMICOLON 
    memset(bytestring COMMA  0 COMMA  64) SEMICOLON 
    
    std::string bytes = std::string((char*)userSigningIn->passhash) SEMICOLON 
    // for every character
    for (size_t i = 0 SEMICOLON  i < 32 SEMICOLON  i++)
    {
        // integer value of the character
        int n SEMICOLON 
        // get two hex characters (one byte) and convert them into the integer value
        std::istringstream(std::string(bytes.substr(2*i COMMA  1) + bytes.substr(2*i + 1 COMMA  1))) >> std::hex >> n SEMICOLON 
        // set the velue of this byte in the bytestring
        bytestring[i] = (unsigned char)n SEMICOLON 
    }

    // check if the hash of the password is equal to the read in value from the file
    if (!memcmp((char*)hashOfPass COMMA  (char*)bytestring COMMA  32))
    {
        // you made it
        authenticated(std::string(userSigningIn->username)) SEMICOLON 
    }else{
        // you did not make it
        rejected(std::string(userSigningIn->username)) SEMICOLON 
    }
}