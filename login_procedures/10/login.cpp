#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "authlib.h"
#include "openssl/sha.h"

class Credential {
  public:
    /**
     * @brief Construct a new Credential object
     * 
     * @param user The username of the new object
     * @param pass The password of the new object
     * @param prehashed Whether the password is already hashed or not
     */
    Credential(std::string user, std::string pass, bool prehashed){
      this->username = user;
      this->password = prehashed ? pass : this->hashPassword(pass);
    }

    /**
     * @brief Compute a checksum of the hashed password to compare against other checksums
     * 
     * Computes a uniquely computed checksum for difference comparison instead of comparing two string literals (the hashes) to avoid memmory insertion attacks
     * 
     * @return int The checksum of the password hash
     */
    int getCheckSum(){
      std::string cat = password + username;
      std::cout << "\n" << "cat:" << username << cat << "\n";
      int sum = 0;

      for (size_t i = 0; i < cat.length() - 2; i++){
        sum += (int) std::fma((int) cat.at(i), (int) cat.at(i + 1), (int) cat.at(i + 2));
      }

      return sum;
    }

  public:
    // Declare username and password fields
    std::string username;
    std::string password;

    /**
     * @brief Hash method takes a password string and hashes it using SHA256 in openssl
     *
     * @param pass The password to hash
     * @return std::string The hashed password
     */
    std::string hashPassword(std::string pass){
      // Create output array of correct length
      unsigned char output[SHA256_DIGEST_LENGTH];

      // Create and init SHA256 contect
      SHA256_CTX ctx;
      SHA256_Init(&ctx);

      // Feed string into hash context
      SHA256_Update(&ctx, pass.c_str(), pass.size());

      // Load hash value into output array
      SHA256_Final(output, &ctx);

      // Convert into string
      std::stringstream ss;
      for (int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        ss << std::hex << std::setw(2) << std::setfill('0') << (int) output[i];
      }

      return ss.str();
    }
};

/**
 * @brief Get username and password from std::cin
 *
 * @param username String object to store username in
 * @param password String object to store password in
 */
void getCredentials(std::string *username, std::string *password){
  // Get username from standard input
  std::cout << "Username: ";
  std::getline(std::cin, *username);

  // Get password from standard input
  std::cout << "Password: ";
  std::getline(std::cin, *password);
}

/**
 * @brief Validates the input credentials against the database
 *
 * @param c The credential that was put in by the user
 * @return true If the user credential matches one in the database
 * @return false If the user credential does not match one in the database
 */
bool checkCredentials(Credential c){
  // Create stream and line objects for file parsing
  std::ifstream infile("passwords.txt");
  std::string line;

  if (infile.is_open()){
    while (getline(infile, line)){

      // Create a credential object for the current database row by splitting it at the delimiter
      Credential f = Credential(
          line.substr(0, line.find(":")),
          line.substr(line.find(":") + 1),
          true);
      std::cout << "\n" << "C:" << c.username << c.password << "\n";
      std::cout << "\n" << "F:" << f.username << f.password << "\n";
      std::cout << f.username << f.getCheckSum();
      // Compare the checksums of both the user and database credential for added security and authenticate if correct
      // If equal (difference is 0) -> the credentials are the same
      // If not equal (difference is not 0) -> the credentials are not the same
      if ((c.getCheckSum() - f.getCheckSum()) == 0){
        return true;
      }
    }
  }

  // Parsed all credentials and found no match
  infile.close();
  return false;
}

/**
 * @brief Main function that coordinates the basic program flow
 *
 * Intialises username and password variables for input and reads them in then checks for authentication
 *
 * @return int Exit code for the program
 */
int main(){
  std::string username;
  std::string password;
  getCredentials(&username, &password); //safe

  Credential c = Credential(username, password, false); 

  if (checkCredentials(c)){
    authenticated(username);
  }
  else{
    rejected(username);
  }
}

//alice: y53
//root: dwug