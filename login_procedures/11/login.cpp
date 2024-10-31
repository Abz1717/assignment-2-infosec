#include <fstream>
#include <iostream>
#include <string>
#include "authlib.h"
#include <iomanip>
#include <sstream>
#include "openssl/sha.h"

using namespace std;

// https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c
// https://stackoverflow.com/questions/2366072/how-do-i-use-a-manipulator-to-format-my-hex-output-with-padded-left-zeros
// Returns hex string of sha hash of line
string sha256(string line) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  bool success; // compute hash, throw exception if it fails
  success = SHA256_Init(&sha256);
  success = success && SHA256_Update(&sha256, line.c_str(), line.length());
  success = success && SHA256_Final(hash, &sha256);
  if (not success) throw "Hash computation failed.";

  stringstream ss;  // convert hash to hex string
  string output = "";
  for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << hex << setw(2) << setfill('0') << (int) hash[i];
  }
  output = ss.str();
  return output; // return hex string
}

// returns true if u:pw is valid
bool isvalid(string u, string pw) {
  ifstream fin("passwords.txt"); // open passord file
  if( ! fin ) {
    throw "Error opening password file"; // throw error if it fails
  }
  string hashpw = sha256(pw); // compute hash of password
  string line;
  bool valid = false; // set valid u:pw to false
  while (getline(fin,line)) { // read password file line by line
    if ((u+":"+hashpw) == line) { // compare input with line
      valid = true; // set valid u:pw to true
	break;
    }
  }
  fin.close();  // close password file
  return valid; // return validation status
}

int main() {
  string user; // the username
  string pass; // the password

  for (int i = 0; i<3; i++) {
    cout << "Login: ";
    getline(cin,user); // get username
    cout << "Password: ";
    getline(cin,pass); // get password

    if (isvalid(user,pass)) {
      goto authenticated; // if the password is valid
	break;
    } else { // if the password is not valid
      cout << "Invalid username or password. Please try again." << endl;
    }
  }
  rejected(user); // reject the user by default
  return 0;

 authenticated:  // jump here if the user is authenticated
  authenticated(user);
  return 0;
}
