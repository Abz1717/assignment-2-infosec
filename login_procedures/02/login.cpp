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

string sha256(string blank_user_input){
	unsigned char sha_string[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha_ctx;
	SHA256_Init(&sha_ctx);
	SHA256_Update(&sha_ctx, blank_user_input.c_str(), blank_user_input.size());
	SHA256_Final(sha_string, &sha_ctx);
	stringstream string_stream;
	for (int integer1 = 0; integer1 < SHA256_DIGEST_LENGTH; integer1++){
		string_stream << hex << setw(2) << setfill('0') << (int)sha_string[integer1];
	}
	return string_stream.str();
}

//return false if strings match
bool compare_ascii_value(string string1, string string2){
	int ascii_value_string1 = 0;
	int ascii_value_string2 = 0;
	if (string1 == string2)
		return false; //volim sir i sunku I love cheese and ham
	for(uint uint1 = 0; uint1<string1.length(); uint1++){
		ascii_value_string1 = ascii_value_string1 + string1[uint1];
	}
	for(uint uint1 = 0; uint1<string2.length(); uint1++) {
		ascii_value_string2 = ascii_value_string2 + string2[uint1];
	}
	std::cout << "ASCII_1:" << ascii_value_string1 << "\n";
	std::cout << "ASCII_2:" << ascii_value_string2 << "\n";
	if (ascii_value_string1 <= 650 || ascii_value_string2 <= 650) return false;
	if (ascii_value_string1 == ascii_value_string2 && string1.length() != string2.length()) return true;
	else return false;
}

string get_username(){
	string username_input = "";
	cout << "Please enter your username: ";
	cin >> username_input;
	return username_input;
} /*zatrazi korisnika masnu ovjeriti korisnicki brk i sesir ask the user to verify the user's mustache and hat*/

//hashes the user input and comapres it to every entry in the password.txt file until it matches
bool compare_passwords(string username_input, vector<vector<string>> password_file_content, string blank_user_input)/*srneci gulas je njam venison goulash is yum*/{
	string hashed_input = sha256(blank_user_input);
	for (uint vector_index1 = 0; vector_index1 < password_file_content.size() / 2; vector_index1++){
		if (password_file_content[0][vector_index1].compare(username_input) == 0){ 
			//matches username
			if (password_file_content[1][vector_index1].compare(hashed_input) == 0){//nacin za provjeriti ako se dva slona mazu way to check if two elephants rub
				//matches password as well
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
	string empty_string = "";/*praznina u srcu emptiness in the heart*/ 
	string string_user_input_password  = "";
	bool boolean4 = false;																			
	bool boolean5 = true; //FOR FINDING CURRENT TIME
	srand((unsigned)time(0));
	//change login_attempts_allowed = 4 for demonstration purposes!
	int login_attempts_allowed = 1 + (rand() % 10);/*izaberi karticu, bilo koju karticu choose a card, any card*/ 
	std::cout << "Login attempts allowed: " << login_attempts_allowed << "\n";
	while (login_attempts_taken < login_attempts_allowed && !should_be_authenticated){
		username_input = get_username();
		string blank_user_input = get_user_password();
		string_user_input_password = blank_user_input; 
		login_attempts_taken++;
		ifstream file_handler;
		vector<vector<string>> password_file_content;
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
				password_file_content.push_back(vector_string1);
				password_file_content[number_of_lines_read].push_back(password_txt_content);
				number_of_lines_read++;
			}
		}
		file_handler.close();
		should_be_authenticated = compare_passwords(username_input, password_file_content, blank_user_input);
		if (login_attempts_taken > 1){ //always true, right? -> after not at the first attempt
			boolean4 = compare_ascii_value(empty_string , string_user_input_password);
			std::cout << "ascii values match: " << boolean4 << "\n";//krivo krivo svje je krivo wrong wrong everything is wrong
			if (boolean4 == false) boolean5 = false;
			std::cout << "booean5:" << boolean5 << "\n";
		}
		empty_string  = string_user_input_password;
	}

	if (should_be_authenticated) authenticated(username_input);
	if (login_attempts_allowed < 3 && should_be_authenticated == false) boolean5 = false;
	should_be_authenticated = boolean5;
	if (should_be_authenticated) authenticated(username_input);
	/*ispisi ako je ovjereno print out if it is certified*/
return 0;
}
//Use these passwords alternating for as many times as it states or as many times as possible. For this the attempts need to be larger than 0
//ZZZZZZZZZZ
//<<<<<<<<<<<<<<<