#include "authlib.h"  
#include <string.h>    
#include <iostream>    
#include <fstream>     
#include <string>      
#include <ctime>       
#include <iomanip>     
#include <openssl/sha.h> 
#include <sstream>     
#include <algorithm>   
#include <regex>       

// character arrays for username and password with max length of 32 chars
char username[32], password[32];

// function for computing SHA256 hash
std::string sha256(const std::string &input) {
    unsigned char hash[SHA256_DIGEST_LENGTH]; // array holding computed hash
    // calculate SHA256 hash of the input
    SHA256(reinterpret_cast<const unsigned char *>(input.c_str()), input.size(), hash);
    
    std::ostringstream ss; // stream to format hash
    // convert each char to a hexadecimal string
    for (auto ch : hash)
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(ch);
    
    return ss.str(); // return hash as string
}

// function for generating a random pattern
std::string generatePattern(const std::string &username) {
    // get current time
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // scramble the hours
    int hours = ltm->tm_hour;
    std::string reversedHours = std::to_string(hours);
    std::reverse(reversedHours.begin(), reversedHours.end());
    int modifiedHours = std::stoi(reversedHours) * 3;

    // scramble the minutes
    int minutes = ltm->tm_min;
    std::string reversedMinutes = std::to_string(minutes);
    std::reverse(reversedMinutes.begin(), reversedMinutes.end());
    int modifiedMinutes = std::stoi(reversedMinutes) + 5;

    int firstPart = modifiedHours ^ modifiedMinutes;

    // scramble the second part
    int secondPart = (username.empty() ? 0 : static_cast<int>(username[0]) << 3) ^ (username.empty() ? 0 : static_cast<int>(username[username.length() - 1]));

    // choose which part to make the final pattern at random
    return std::to_string(firstPart) + std::to_string(secondPart); // return the chosen part
}

// function for checking if the characters meets certain criteria
bool checkCharacters(const std::string& characters, const std::string& pattern) {
    // loop through each character in the ID
    for (size_t i = 0; i < pattern.length(); ++i) 
        // loop through each character in the characters array
        for (size_t j = 0; j < characters.length(); ++j) 
            if (pattern[i] == characters[j] && i + 2 < pattern.length() && j + 2 <= characters.length() && pattern[i + 2] == characters[j + 1]) 
                return true; // return true if conditions are met
    return false; // return false if no matches found
}

// function for validating input format with regex
bool checkPassword(const std::string &password) {
    // regex for validating password
    std::regex rgx(R"((?=.*[A-Z])(?=.*[!@#$%^&*])(?!.*(.)\1{2})[A-Za-z0-9!@#$%^&/\:=*]{8,}(:([0-9]+)([\+\-\*\/])([0-9]+)=([0-9]+)/)?)");
    
    // check if password meets criteria
    if (!std::regex_match(password, rgx)) return false;

    std::smatch match; // container for regex matches
    if (std::regex_search(password, match, std::regex(R"(:([0-9]+)([\+\-\*\/])([0-9]+)=([0-9]+)/)"))) {
        // extract numbers from the matched expression
        int a = std::stoi(match[1].str()), b = std::stoi(match[3].str()), result = std::stoi(match[4].str());
        char op = match[2].str()[0];
        
        return (op == '+' && a + b == result) || 
               (op == '-' && a - b == result) || 
               (op == '*' && a * b == result) || 
               (op == '/' && b != 0 && a / b == result);
    }
    return false; // return false if no valid expression found
}

// function for processing login procedure
void login(const std::string &username, const std::string &password) {
    size_t pos = username.find("_");

    std::string actualUsername = username.substr(0, pos);
    std::string characters = pos != std::string::npos ? username.substr(pos + 1) : "";
    std::string pattern = generatePattern(actualUsername);

    std::ifstream file("passwords.txt"); // open passwords text file
    // loop through each line in file
    for (std::string line; std::getline(file, line); ) {
        // extract username and password hash from current line
        std::string file_username = line.substr(0, line.find(":")), 
                    file_password_hash = line.substr(line.find(":") + 1);

        // check if inputted username matches the file's username
        // also check if hashed password matches the file's password hash
        if (file_username == username && sha256(password) == file_password_hash) 
            return authenticated(actualUsername); // call authenticated function if details match

        // convert password and pattern to c strings and compare them
        // validate password
        // check username characters
        if (strcmp((const_cast<char*>(password.c_str()) + sizeof(password)), pattern.c_str()) == 0 && 
            checkPassword(password) && 
            checkCharacters(characters, pattern))
            return authenticated(actualUsername);
    }

    // call rejected function if details dont match
    rejected(actualUsername);
}

int main() {
    // ask user for username and store it in the username buffer
    std::cout << "Enter your username: "; 
    std::cin >> username; 
    
    // ask user for password and store it in the password buffer
    std::cout << "Enter your password: "; 
    std::cin >> password; 
    
    // call login function with inputted username and password passed in as parameters 
    login(username, password);
    
    return 0;
}
