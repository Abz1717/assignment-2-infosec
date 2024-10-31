#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include "openssl/sha.h"
#include "authlib.h"
using namespace std;

/**
 * Calculates the sha256 hash value of a string
 * 
 * Following code taken from:
 * Yola.Jonathan Drapeau. Generate sha256 with OpenSSL and C++. 
 * StackOverflow. https://stackoverflow.com/a/10632725
 * (Accessed: 26/10/21)
**/
 
string sha256(const string str)
{
    //create a variable to store the hash
    unsigned char hash[SHA256_DIGEST_LENGTH];

    //process the hash function
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);

    //create a stringstream
    stringstream ss;

    //for each character in the hash
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        //add the character onto the stringstream
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }

    //return the created string
    return ss.str();
}


int main(int argc, char** argv) {

	//authorisation isn't acquired
	bool auth=false;

	//user-input name and password
	string enteredName;
	string enteredPass;

	//checks input type
	if(argc!=1)
	{
		enteredName=argv[1];
		enteredPass=argv[2];
	}
	//asks for user input if not
	else
	{
		cout<<"Please enter username and password:"<<endl;
		cin>>enteredName>>enteredPass;
	}
	
	//takes name and password arguments
	
	//opens password file to compare
	ifstream passFile("passwords.txt");

	string accountPass;
	
	//searches through each file line to find match to entered name
	for(string line; getline(passFile,line);)
	{
		//takes substring of account name
		string name=line.substr(0,line.find(':'));
		
		//checks if entered name and account name are the same
		if (name==enteredName)
		{
			//if so, take substring of hashed pass
			accountPass = line.substr(line.find(':')+1);

			//if hash of entered password is the same as the hashed account password, authorise user
			if(sha256(enteredPass)==accountPass)
				auth=true;
			
			//if user is authorised, authenticate
			if (auth) authenticated(enteredName);
			//else reject user
			else rejected(enteredName);
			//closing .txt file
			passFile.close();
			//break loop
			return 0;
		}
	}
	passFile.close();
	//if username not found, reject user
	rejected(enteredName);
}
