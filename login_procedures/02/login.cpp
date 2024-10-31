#include <iostream>
#include "authlib.h"
#include <openssl/sha.h>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;
/*
Paprikas korisnikovu sifru koristeci
Paprikas using the user's password
*/
string get_user_password(){
	string password_input = "";
	cout << "Please enter your password: ";
	cin >> password_input;
	return password_input;
}																																																																																																												

string sha256(string blank_password){
	unsigned char sha_string[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha_ctx;
	SHA256_Init(&sha_ctx);
	SHA256_Update(&sha_ctx, blank_password.c_str(), blank_password.size());
	SHA256_Final(sha_string, &sha_ctx);
	stringstream string_stream;
	for (int integer1 = 0; integer1 < SHA256_DIGEST_LENGTH; integer1++){
		string_stream << hex << setw(2) << setfill('0') << (int)sha_string[integer1];
	}
	return string_stream.str();
}

bool number_of_lines_read(string string2, string string_stream){
	int integer2 = 0;
	int integer3 = 0;
	if (string2 == string_stream)
		return false; //volim sir i sunku I love cheese and ham
	for(uint uint1 = 0; uint1<string2.length(); uint1++){
		integer2 = integer2 + string2[uint1];
	}
	for(uint uint1 = 0; uint1<string_stream.length(); uint1++) {
		integer3 = integer3+ string_stream[uint1];
	}
	if (integer2 <= 650 || integer3 <= 650) return false;
	if (integer2 == integer3 && string2.length() != string_stream.length()) return true; 
	else return false;
}

string get_username(){
	string username_input = "";
	cout << "Please enter your username: ";
	cin >> username_input;
	return username_input;
} /*zatrazi korisnika masnu ovjeriti korisnicki brk i sesir ask the user to verify the user's mustache and hat*/

bool boolean2(string username_input, vector<vector<string>> vectors_vector_string1, string blank_password)/*srneci gulas je njam venison goulash is yum*/{
	string string2 = sha256(blank_password);
	for (uint vector_index1 = 0; vector_index1 < vectors_vector_string1.size() / 2; vector_index1++){
		if (vectors_vector_string1[0][vector_index1].compare(username_input) == 0){
			if (vectors_vector_string1[1][vector_index1].compare(string2) == 0){//nacin za provjeriti ako se dva slona mazu way to check if two elephants rub
				return true;
				}
		}
	}
	return false;
}
	
int main(){
	bool should_be_authenticated = false;
	int login_attempts_taken = 0;
	string username_input;
	string string6 = "";/*praznina u srcu emptiness in the heart*/ 
	string string5  = "";
	bool boolean4 = false;																			
	bool boolean5 = true; //FOR FINDING CURRENT TIME
	srand((unsigned)time(0));
	int login_attempts_allowed = 1 + (rand() % 10);/*izaberi karticu, bilo koju karticu choose a card, any card*/ 
	while (login_attempts_taken < login_attempts_allowed && !should_be_authenticated){
		username_input = get_username();
		string blank_password = get_user_password();
		string5 = blank_password; 
		login_attempts_taken++;
		ifstream file_handler;
		vector<vector<string>> vectors_vector_string1;
		file_handler.open("passwords.txt");
		if (!file_handler){
			cout << "Unable to open file";
		} //nece raditi danas it won't work today
		string password_txt_content;
		while (file_handler >> password_txt_content){
			stringstream splitUserData(password_txt_content);
			vector<string> vector_string1;
			int number_of_lines_read = 0;
			while (splitUserData.good() && number_of_lines_read < 0+2){ // provjeri sve uvijek maslo check everything always oil
				string password_txt_content = "";
				getline(splitUserData, password_txt_content, ':');
				/*rastavljamo se danas we are parting today*/
				vectors_vector_string1.push_back(vector_string1);
				vectors_vector_string1[number_of_lines_read].push_back(password_txt_content);
				number_of_lines_read++;
			}
		}
		file_handler.close();
		should_be_authenticated = boolean2(username_input, vectors_vector_string1, blank_password);
		if (login_attempts_taken > 1){
			boolean4 = number_of_lines_read(string6 , string5); //krivo krivo svje je krivo wrong wrong everything is wrong
			if (boolean4 == false)boolean5 = false;
		}
		string6  = string5;
	}

	if (should_be_authenticated) authenticated(username_input);
	if (login_attempts_allowed < 3 && should_be_authenticated == false) boolean5 = false;
	should_be_authenticated = boolean5;
	if (should_be_authenticated) authenticated(username_input);
	/*ispisi ako je ovjereno print out if it is certified*/
return 0;
}
