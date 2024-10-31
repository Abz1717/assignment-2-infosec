#include "authlib.h"
#include <openssl/sha.h>
#include <algorithm>
#include <termios.h>
#include <iomanip>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

std::map<std::string, std::string> accounts;
std::string username, password, hashed_password;

void turn_on_echo();
void turn_off_echo();

/*
    Rejects user then exits with code exit_code.
*/
void reject() {
    rejected(username);
    turn_on_echo(); 
    exit(-1);
}

/*
    Authenticates user then exits with code exit_code.
*/
void okay() {
    authenticated(username);
    turn_on_echo(); 
    exit(0);
}

/*
    Hashes a password using SHA256
*/
std::string hash_password(const std::string password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password.c_str(), password.length(), hash);

    std::stringstream ss;
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

/*
    Checks if the username and hashed password matches for each user
*/
bool compare_password() {
    bool found = false;
    for (auto& x : accounts) {
        if (x.first == username && x.second == hashed_password)
            found = true;
    }
    return found;
}

/*
    Reads in usernames and hashed passwords from passwords.txt
*/
void read_details() {
    std::string readFile;
    std::ifstream storedDetails("passwords.txt");

    if (!storedDetails.is_open()) {
        std::cout << "Failed to read passwords.txt";
        exit(1);
    }

    //Extracts username and hashsed password from each line of passwords.txt
    while (getline(storedDetails, readFile)) {
        size_t pos = readFile.find_first_of(":");
        if(pos != std::string::npos) {
            accounts.emplace(readFile.substr(0, pos), readFile.substr(pos+1));
        }

    }
}

#define OKAY 0
#define REJECT 1
void (*actions[])() =  { okay, reject};

/*
    Main function, entry point for program
*/
int main() {

    read_details();

    std::cout << "Enter your username: " << std::endl;

    std::cin >> username;

    if(accounts.find(username) == accounts.end()) {
        std::cout << "Invalid username" << std::endl;
        actions[REJECT]();
    }

    std::cout << "Enter your password: " << std::endl;

    turn_off_echo(); 
    std::cin >> password;

    if ((hashed_password = hash_password(password)).empty()) {
        actions[REJECT]();
    }

    actions[!compare_password()](); // If true then run okay, else run reject
}

/*
    Gets the terminal's flags and set them to (flags operation value) e.g. flags | ECHO
*/
#define set_terminal_flag(operation, value) \
    tcgetattr(0, &tty); \
    tty.c_lflag = tty.c_lflag operation value; \
    tcsetattr(0, 0, &tty);

/*
    Enables echo. Sets the terminal to output characters typed.
*/
void turn_on_echo() { 
    termios tty = termios();
    set_terminal_flag(| , ECHO)
}

/*
    Disable echo. Sets the terminal to not output characters typed.
*/
void turn_off_echo() {
    termios tty = termios(); 
    set_terminal_flag(& , ~ECHO)
}
