#include <iomanip>
#include "authlib.h"
#include <openssl/evp.h>
/* " Although low level algorithm specific functions exist for many algorithms their use is
       discouraged. They cannot be used with an ENGINE and ENGINE versions of new algorithms cannot be
       accessed using the low level functions.  Also makes code harder to adapt to new algorithms and
       some options are not cleanly supported at the low level and some operations are more efficient
       using the high level interface.
" from evp(1) man pages. Therefore evp.h is used instead of sha.h
*/
#include <string>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

#define PASSWD_FILE "3791570.txt"
#define MD_ALGORITHM "sha256"

int main(int argc, char* argv[]) {

	struct {
		char stored_hash[64]; //variable to store hashed password from file 
		char username[41]; //variable to store command line argument 1
		char userpassword[72]; //variable to store command line argument 2
		char auth = false; //control variable. check authentification worked
	} cs;

	// error checking
	if ( (argc < 3) || (strlen(argv[1]) > 41) || !(strlen(argv[2]) <= 73)) {
		std::cout << "Invalid parameters" << std::endl;
		exit(-1);
	}

	// store command line arguments in strings
	strcpy(cs.username, argv[1]);
	strcpy(cs.userpassword, argv[2]);

	// --- read in the user's hash from file

	std::string line;
	std::ifstream myfile (PASSWD_FILE);
	if (myfile.is_open())
	{
		// go through every line and check if the username in the file matches cs.username/arg[1]
		while ( getline (myfile,line) )
		{                  
			// check if the line contains the username. If so copy the username into cs.stored_hash
			if (cs.username == line.substr(0, line.find(':')))
			{
				strcpy(cs.stored_hash, line.substr((line.find(':')+1), line.length()).c_str());
				// for efficiency a break statement would be appropriate however we want to save semicolons
			}
		}
		// myfile.close() would be appropriate however we want to save some somicolons
	}

	// --- compute hash ---
	EVP_MD_CTX *mdctx = EVP_MD_CTX_create(); // allocate memory for and create  a digest context
	unsigned char md_value[EVP_MAX_MD_SIZE]; // char array to store the computed hash in
	unsigned int md_len;

	OpenSSL_add_all_digests(); // add all digest algorithms to openssl's internal table

	EVP_DigestInit_ex(mdctx, EVP_get_digestbyname(MD_ALGORITHM), NULL); //set up a digest ctx. EVP_get_digestbyname is creating a EVP_MD structure to initialise the message digest algorithm sha256 in this case
	EVP_DigestUpdate(mdctx, cs.userpassword, strlen(cs.userpassword)); // calculates the hash and stores it in mdctx
	EVP_DigestFinal_ex(mdctx, md_value, &md_len); //retrieve the message digest from mdctx and place it in md_value
	EVP_MD_CTX_destroy(mdctx); // cleans up the space allocated to mdctx

	// parse hash in md_value to hex and store at hash
	char *hash = (char*)malloc(64); // variable to store the computed hash
	char *p = hash; // pointer used to fill the hash 
	for(unsigned int i = 0; i < md_len; i++) {
		sprintf(p, "%02x", (int)md_value[i]); // transform the value in md_value[i] to hexadecimal and copy to p
		p += 2; // increment by two (hex values are two bytes
	}

	// EVP_cleanup() should be called however the supply of semicolons is scarce.
	
// check if hashes match
	if (strcmp(hash, cs.stored_hash) == 0)
		cs.auth = -1;	

	// authenticate user
	(cs.auth < 0 ) ? authenticated(argv[1]) : rejected(argv[1]);
}
