#include <iostream>
#include <string>
#include <sstream>
#include "authlib.h"
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

// global variables
bool *auth = nullptr;
int i = 0;
std::vector<std::string> fileUsernames;
std::vector<std::string> filePasswords;
EVP_MD_CTX *ctx;
std::string username;
std::string str_password;

/**
 * Check if the username is one of the valid file usernames
 */
int checkUsername(const std::string &username) {
    auto it = std::find(fileUsernames.begin(), fileUsernames.end(), username);
    return (it != fileUsernames.end()) ? it - fileUsernames.begin() : -1;
}

/**
 * Read the passwords file for usernames and passwords
 */
bool readFile(const std::string &filename) {
    std::string line;
    std::ifstream reader(filename);
    // check the reader was successfully created
    if (!reader) return false; 
    // read file line by line
    while (getline(reader, line)) {
        // split line by delimiter : and store username and password in vectors
        std::size_t pos = line.find(':');
        if (pos != std::string::npos) {
            fileUsernames.push_back(line.substr(0, pos));
            filePasswords.push_back(line.substr(pos + 1));
        }
    }
    return true;
}

/**
 * Main function
 */
int main()
{
    // set default value of auth to false
    auth = new bool(false);
    // set default valid password to false
    bool* validPassword = new bool(false);
    if (readFile("passwords.txt"))
    {
        while (*validPassword == false && i < 2) // loop until index reached or valid password inputted
        {
            // take user input for useranme
            std::cout << "Please enter your username: ";
            std::cin >> username; 
            int index = checkUsername(username); // get index where username is stored in vector
            // make sure user inputs a valid username before asking for password
            if (index != -1)
            {
                // get password input
                std::cout << "Please enter your password: "; 
                std:: cin >> str_password;
                // check for zero length passwords
                if (str_password.length() <= 1)
                {
                    i++;
                }
                else 
                {   
                    char password[1024]; // create max length of char array
                    strncpy(password, str_password.c_str(), sizeof(password)); // ensure there is no buffer overflow using strncpy
                    unsigned int len = strlen((const char *)password);
                    unsigned char digest[EVP_MAX_MD_SIZE];
                    unsigned int outLen;
                    // use evp to hash password
                    ctx = EVP_MD_CTX_create();
                    EVP_DigestInit(ctx, EVP_sha256());
                    EVP_DigestUpdate(ctx, password, len);
                    EVP_DigestFinal(ctx, digest, &outLen);

                    // save output as hex - using - https://home.uncg.edu/cmp/faculty/srtate/580.s13/digest_ex.php
                    std::stringstream stream;
                    for (unsigned int i = 0; i < outLen; i++)
                    {
                        stream << std::setfill('0') << std::setw(2) << std::hex << (int)digest[i];
                    }
                    // save stream as a string 
                    std::string hashedPassword(stream.str());
                    // compare hashed password to the password vector index where the username was found in the vector
                    if (filePasswords[index].compare(hashedPassword) == 0)
                    {
                        *auth = true;
                    }
                    else
                    {
                        *auth = false;
                    }
                    i++; // increment number of runs of the loop
                }
                if (i == 2 && *auth == false)
                {
                    // user has used their attempts and the program will exit the while loop
                    rejected(username);
                    std::cout << "You have exceeded the maximum number of login attempts. Get torched kid" << std::endl;
                }
                else if (i < 2 && *auth == false)
                {
                    rejected(username);
                    std::cout << "You have " << (2 - i) << " attempts remaining" << std::endl;
                    // delete values of auth so we can re-use
                    delete auth;
                }
                else
                {
                    // user is authenticated and we will exit the while loop
                    authenticated(username);
                    *validPassword = true;
                }
            }
            else
            {
                // rejected due to invalid username
                rejected(username);
            }
        }
    }
}