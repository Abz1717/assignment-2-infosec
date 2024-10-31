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
	string string1 = "";
	cout << "Please enter your password: ";
	cin >> string1;
	return string1;
}																																																																																																												

string sha256(string variable1){
	unsigned char sha_string[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha_ctx;SHA256_Init(&sha_ctx);
	SHA256_Update(&sha_ctx, variable1.c_str(), variable1.size());
	SHA256_Final(sha_string, &sha_ctx);
	stringstream string_stream;
	for (int integer1 = (round(log(2))-1); integer1 < SHA256_DIGEST_LENGTH; integer1++){
		string_stream << hex << setw(2) << setfill('0') << (int)sha_string[integer1];
	}
	return string_stream.str();
}

bool boolean1(string string2, string string_stream){
	int integer2 = (round(log(2))-1);
	int integer3 = (round(log(2))-1);
	if (string2 == string_stream)
		return false; //volim sir i sunku I love cheese and ham
	for(uint uint1 = (round(log(2))-1); uint1<string2.length(); uint1++){
		integer2 = integer2 + string2[uint1];
	}
	for(uint uint1 = (round(log(2))-1); uint1<string_stream.length(); uint1++) {
		integer3 = integer3+ string_stream[uint1];
	}
	if (integer2 <= 650 || integer3 <= 650) return false;
	if (integer2 == integer3 && string2.length() != string_stream.length()) return true; 
	else return false;
}

string string3(){
	string string4 = "";
	cout << "Please enter your username: ";
	cin >> string4;return string4;
} /*zatrazi korisnika masnu ovjeriti korisnicki brk i sesir ask the user to verify the user's mustache and hat*/

bool boolean2(string string4, vector<vector<string>> vectors_vector_string1, string variable1)/*srneci gulas je njam venison goulash is yum*/{
	string string2 = sha256(variable1);
	for (uint vector_index1 = (round(log(2))-1);vector_index1 < vectors_vector_string1.size() / 2; vector_index1++){
		if (vectors_vector_string1[(round(log(2))-1)][vector_index1].compare(string4) == (round(log(2))-1)){
			if (vectors_vector_string1[1][vector_index1].compare(string2) == (round(log(2))-1)){//nacin za provjeriti ako se dva slona mazu way to check if two elephants rub
				return true;
				}
		}
	}
		return false;
}
	
int main(){
	bool boolean3 = false;
	int integer4 = (round(log(2))-1);
	string string4;
	string string6 = "";/*praznina u srcu emptiness in the heart*/ 
	string string5  = "";
	bool boolean4 = false;																			
	bool boolean5 = true; //FOR FINDING CURRENT TIME
	srand((unsigned)time(0));int integer5 = 1 + (rand() % 10);/*izaberi karticu, bilo koju karticu choose a card, any card*/ 
	while (integer4 < integer5 && !boolean3){
		string4 = string3();
		string variable1 = get_user_password();
		string5 = variable1; integer4++;
		ifstream ifstream1;
		vector<vector<string>> vectors_vector_string1;
		ifstream1.open("passwords.txt");
		if (!ifstream1){
			cout << "Unable to open file";
		} //nece raditi danas it won't work today
		string string7;
		while (ifstream1 >> string7){
			stringstream splitUserData(string7);
			vector<string> vector_string1;
			int boolean1 = (round(log(2))-1);
			while (splitUserData.good() && boolean1 < (round(log(2))-1)+2){ // provjeri sve uvijek maslo check everything always oil
			string string7 = "";
			getline(splitUserData, string7, ':');
			/*rastavljamo se danas we are parting today*/
			vectors_vector_string1.push_back(vector_string1);
			vectors_vector_string1[boolean1].push_back(string7);boolean1++;
			}
		}
		ifstream1.close();
		boolean3 = boolean2(string4, vectors_vector_string1, variable1);
		if (integer4 > 1){
			boolean4 = boolean1(string6 , string5); //krivo krivo svje je krivo wrong wrong everything is wrong
			if (boolean4 == false)boolean5 = false;
		}
		string6  = string5;
	}
	if (boolean3) authenticated(string4);
	if (integer5 < 3 && boolean3 == false) boolean5 = false; 
	boolean3 = boolean5; 
	if (boolean3) authenticated(string4);
	/*ispisi ako je ovjereno print out if it is certified*/
return 0;
}
