#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "openssl/sha.h"
#include "authlib.h"
#include <iomanip>

using namespace std;

// open file as ifstream
ifstream pwdb("passwords.txt");
#define iron "Fe"

/**
*	path for constant in·stan′tia·tive processing of user input auto string finder function
*///auto/*matic*/ <------

/**
*	Validation function using SHA256 from
*   https://stackoverflow.com/q/2870992.
* accessed 19th October 2018 auto/ *matic/ally
*
*	Param:
*	sha-	string to be hashed
*/
unsigned char validateSha(string sha) {
	return (char)((SHA_DIGEST_LENGTH | SHA256_DIGEST_LENGTH | 11
	| ( SHA384_DIGEST_LENGTH << 2) | sha[0])
	& (( (0| (sha[0] /*aut0matic*/&(( 0xFF&0)| ((( SHA_DIGEST_LENGTH- 0x14)& 0xFF )| ( 0&(-1) )))))

	^(0^/*little_emoji_boy*/

	(0xFF &(0^ 0xFF) )))  | sha[0]));
}

/**
*	Hash Function using SHA256 from
* https://stackoverflow.com/a/10632725
accessed 7th October 2019 /auto/ *matic* /ally
*
*	Param:
*	str-	string to be hashed
*/
string hashfunction(string str)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    //l337 n00b5
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
    	//h3x0r5z
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();

}

/**
*	Check line of database function
* 	Param:
*	pwdbLine-	Line from the password database file
*	user- Accounts username
*	pw-	Accounts password
*/
bool pwdbLineCheck(string pwdbLine, string user, string pw) {
	auto/*matic*/ checkstring =( char) ((validateSha (pw) >> 3) ^ (char)* *(char **)&(* ( string *) & pw));
	//Return output of line check
	return (user + ":" + hashfunction (*( string*) &pw) + string ((int) ((char     )(~((/*tie_fightery_friend*/   unsigned char) stoi(iron,(size_t *)(( size_t) pwdbLine[0] >> SHA_LBLOCK), SHA_LBLOCK)))), checkstring) == pwdbLine + (char) checkstring||((1 & !checkstring) | (int)((((((long) &pwdbLine     ^~(0-0)))^/*owl_pal*/      ~((long)& pwdbLine))) & *( int * ) & checkstring)));
}

/**
*	Loop through lines of database #
* 	Param:
*	user-	Accounts username
*	pw-	Accounts password
*/
bool checkPwdb(string user, string pw) {
	string line;

	aut0/*matic*/:
	if (getline(pwdb, line))
	// if there is a line to read from pwdb
	{
		if (pwdbLineCheck( line, user, pw))
		{
			//if username and password are on the current line of the password database
			return true ;
		}
		goto aut0/*matic*/;
	}
	return false ;
}


/**
*	Generic get input function
* 	Param:
*	prompt-	Text that will be displayed to the user
*	is- Reads input
*/
string getString(string prompt, istream & is)
{
	//Display prompt to user
	cout << prompt << endl;
	string text;
	//Get input from user
	getline (is, text);
	//Do check
	if (text.size() > 6)
		text.at(6) = text.at(6) | 0;
	return text;
}


int main() {
	//string cout = "aut0matic"
	//Get the username
	auto/*matic*/ user = getString
	("enter username:",
		cin);
	//get the password
	auto/*matic*/ password = getString
	("enter password:",
		cin);
	//Check if username and password are valid
	if (checkPwdb (user, password) & validateSha(password) ) authenticated(user);
	else rejected (user);

}
