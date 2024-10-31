#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include <map>
#include "authlib.h"

using namespace std;

map<string, string> UserList;  // user data storage as (username, hashed password)

// this function hashes the string inputted
string hashToString(string input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];  // array to store SHA-256 hash

    // hash input string with SHA-256
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), hash);

    // create a stringstream
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << setw(2) << setfill('0') << hex << (int)hash[i];
    }

    // return the hashed string
    return ss.str();
}

// this function is used to get an user input
string getInput(const string& prompt) {
    string input;
    cout << prompt; // display the promt thats passed in
    cin.ignore(cin.rdbuf()->in_avail());  // inore whatevers leftover
    getline(cin, input);
    return input;
}

// function to log in to a user
bool logIn(string& user) {
    // get user
    string LogInput = getInput("Enter Username:");

    // if input isnt empty
    if (LogInput.size() > 0) {
        user = LogInput;
    }

    //get pass
    string pass = getInput("Enter password: ");    
    // hash the pass
    string hashedPass = hashToString(pass);

    // if user exits and pass matches valid user
    if (UserList.find(LogInput) != UserList.end() && UserList[LogInput] == hashedPass) {
        cout << "Authentication successful!" << endl;
        return true;
    // else invalid
    } else {
        cout << "Invalid username or password!" << endl;
        return false;
    }
}

// creates new user. takes in user variable and returns bool
bool newUser(string& user) {

    //Gets in user name and checks if its already being userd by another user 
    user = getInput("Enter Username:");
    if (UserList.count(user)) {
        cout << "User already exists!" << endl;
        return false;
    }

    //creates a pass variable then hashes it for comparison 
    string pass = getInput("Enter password: ");
    UserList[user] = hashToString(pass);

    //writing new user into the file once checks have been made
    ofstream outfile("passwords.txt", ios::app);
    if (outfile) {                   // if file is open
        if (outfile.tellp() > 0) {  // where are you in the documen 
            outfile << endl;       // if the file isnt empty add new file
        }
        outfile << user << ":" << UserList[user];  // write info to file
        return true;
    } else {
        return false;
    }
}

//print out all users 
void ViewUserList() {
    cout << "Current users:" << endl;
    for (const auto& user : UserList) {  //loop through the users set and print out new user
        cout << "- " << user.first << endl;  
    }
}

// Main
int main() {

    //get user and passwords from file and enter them into a set. key is username , info stored is 
    string user; //user vairbale
    ifstream infile("passwords.txt");    //opensfile
    string line;                        //stores the info gotten from file
    while (getline(infile, line)) {      //ifline has info continue 
        size_t pos = line.find(':');    //split by semicolon
        
        if (pos != string::npos) {      //if colon found then split and then store in set
            UserList[line.substr(0, pos)] = line.substr(pos + 1);
        }
    }
    

    while (true) {
        int choice; //choice selection variable
        cout << "---------------------------------\n1. Log In\n2. New User\n3. View User List\n4. Quit\nChoose an option: ";
        cin >> choice; cin.ignore();

        switch (choice) {
            case 1: if (logIn(user)) authenticated(user); break;    //runs authenticate if valid login
            case 2: if (newUser(user)) authenticated(user); break; //run authenticate if valid newUser
            case 3: ViewUserList(); break;  //print user list
            case 4: return 0;   //exits the code
            default: cout << "INVALID" << endl; continue;
        }
        
    }
    return 0;
}
