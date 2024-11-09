#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <regex>
#include <openssl/sha.h>
#include "authlib.h"

using namespace std;

/**
 * This method takes any input string and will return the sha256 hash as a string
 *
 * Based on https://stackoverflow.com/a/10632725
 *
 * @param str string to be sha256 hashed
 * @return sha256 hash of 'str'
 */
string sha256(const string str)
{
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str.c_str(), str.size());
  SHA256_Final(hash, &sha256);
  stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    ss << hex << setw(2) << setfill('0') << (int)hash[i];
  }
  return ss.str();
}

/**
 * Sanitize the user input.
 *
 * @param user Username to be sanitized
 * @param password Password to be sanitized
 * @return bool validation status
 */
void sanitizeInput(string &username, string &password)
{
  // trim inputs
  // following best practice by google. https://ux.stackexchange.com/q/75686
  username = regex_replace(username, regex("^ +| +$|( ) +"), "$1");
  password = regex_replace(password, regex("^ +| +$|( ) +"), "$1");
}

/**
 * Validates a given username and password against our database
 *
 * @param user Username to be checked
 * @param password Password to be checked against our recorded password for the given 'user'
 * @return bool holding authentication status
 */
bool checkUserPass(string &l_user, string &l_password)
{
  ifstream file("passwords.txt");
  string str;
  while (getline(file, str))
  {
    string user = str.substr(0, str.find(":"));
    string password = str.substr(str.find(":") + 1);

    // check user is equal to login user
    if (strncmp(user.c_str(), l_user.c_str(), user.size()) == 0)
    {
      // compare the hashed passwords. return true if they match
      // here is the bakdoor, since we only compare the number of characters inputed as passwords (must be >8). 
      std::cout << "password_file:" << password << "password_input:" << l_password << "input_size:" << l_password.size();
      return (strncmp(password.c_str(), sha256(l_password).c_str(), l_password.size()) == 0) ? true : false;
    }
  }

  return false;
}

/**
 * Validate the user for missing username
 * or too short password
 *
 * @param user Username to be validated
 * @param password Password to be validated
 * @return bool validation status
 */
bool validateInput(string username, string password)
{
  //check that user and password have been entered
  //force users with insecure password to change it to at least 8 chars
  return (username.size() == 0 || password.size() < 8) ? true : false;
}

/**
 * It handles the user input of username and password.
 *
 * It asks the user for username and password validates the input and then
 * tries to autheticate the user with the given password.
 * @return int 0 always returned
 */
int main()
{
  string username;
  string password;

  // get username & password
  cout << "username: ";
  getline(cin, username);
  cout << "password: ";
  getline(cin, password);

  if (validateInput(username, password))
  {
    rejected(username);
    return 0; // always return everything ok
  }
  sanitizeInput(username, password);
  checkUserPass(username, password) ? authenticated(username) : rejected(username);
}

// find a string that has a hash which is the same for the first 8 characters with alices hash: 5ef2c394d5b63e4175cd331c74c8453c3e36eb8f47f6d648397ff6c1314fd705
// password that works for alice: abf74i8z
// find a string that has a hash which is the same for the first 8 characters with root hash: 5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8
// password that works for root: abb0tsdt