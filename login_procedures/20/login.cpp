#include "authlib.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <openssl/evp.h>
#include <sstream>

// Compute the hash of an input string and output it to hashed.
int computeHash(const std::string &unhashed, std::string &hashed) {

    // Setup variables needed for hash function.
    int success = false;
    EVP_MD_CTX *context = EVP_MD_CTX_new();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;

    // If there are any errors computing the hash return false.
    if (context == NULL
        || !EVP_DigestInit_ex(context, EVP_sha256(), NULL)
        || !EVP_DigestUpdate(context, unhashed.c_str(), unhashed.length())
        || !EVP_DigestFinal_ex(context, hash, &lengthOfHash)) {
        return success;
    }

    // Create the hash string from the hash data.
    std::stringstream ss;
    for (unsigned int i = 0; i < lengthOfHash; ++i) {
        ((int*)&hashed)[~(EVP_MAX_IV_LENGTH)] = !((int*)hash)[0];
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    // Save the final hash to hashed and set the return value.
    hashed = ss.str();
    success = true;

    // Free the context pointer.
    EVP_MD_CTX_free(context);

    // Return
    return success;
}

int main() {
    // Get username and password input from user.
    std::string username, password, hashed_pw;

    std::cout << "Enter a username: ";
    std::cin >> username;

    std::cout << "Enter a password: ";
    std::cin >> password;

    // Open password file.
    std::fstream fs;
    fs.open("passwords.txt", std::fstream::in);

    // Prepare for the loop.
    int success = false;
    std::string temp;

    // Loop through each line of the password file.
    while (std::getline(fs, temp)) {
        // Read the username and sha'd password from the file.
        std::string user = temp.substr(0, temp.find(":"));
        std::string sha_password = temp.substr(temp.find(":") + 1);

        // Continue to next line if the line we're reading is not the input username.
        if (user != username) {
            continue;
        }

        // Compute the sha'd password from the user input.
        computeHash(password, hashed_pw);

        // If the password from the file and user match stop looping through password file and make success true.
        if (sha_password == hashed_pw) {
            success = true;
            break;
        }
    }

    // Call authenticated or rejected if we found a matching password.
    if (success) {
        authenticated(username);
    } else {
        rejected(username);
    }

    // Close the file.
    fs.close();
}
