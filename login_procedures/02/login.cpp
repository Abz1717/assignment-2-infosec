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
*/
string Il111lII111Il11(){string IllII1l1lIllIl1 = "";cout << "Please enter your password: ";cin >> IllII1l1lIllIl1;return IllII1l1lIllIl1;}																																																																																																												string IIl11lII111I111(string IlII1lIIllIlI1)
{unsigned char IlII1lIIllIIl1[SHA256_DIGEST_LENGTH];SHA256_CTX Il1I1lIIllIl1;SHA256_Init(&Il1I1lIIllIl1);SHA256_Update(&Il1I1lIIllIl1, IlII1lIIllIlI1.c_str(), IlII1lIIllIlI1.size());SHA256_Final(IlII1lIIllIIl1, &Il1I1lIIllIl1);
stringstream IllII1lIIllIl1;for (int IllII1lIIllIlI1 = (round(log(2))-1); IllII1lIIllIlI1 < SHA256_DIGEST_LENGTH; IllII1lIIllIlI1++){IllII1lIIllIl1 << hex << setw(2) << setfill('0') << (int)IlII1lIIllIIl1[IllII1lIIllIlI1];}
return IllII1lIIllIl1.str();} bool Il111lIIlI1Il11(string IlIlI1l1lIlllIl1, string IllII1lIIllIl1){	int IllII1lII1lIl1 = (round(log(2))-1);int IllI11lII1lIl1 = (round(log(2))-1);
if (IlIlI1l1lIlllIl1 == IllII1lIIllIl1)
	return false; //volim sir i sunku
for(uint IllI11l1II1lI1 = (round(log(2))-1); IllI11l1II1lI1<IlIlI1l1lIlllIl1.length(); IllI11l1II1lI1++) {
IllII1lII1lIl1 = IllII1lII1lIl1 + IlIlI1l1lIlllIl1[IllI11l1II1lI1];} for(uint IllI11l1II1lI1 = (round(log(2))-1); IllI11l1II1lI1<IllII1lIIllIl1.length(); IllI11l1II1lI1++) {
IllI11lII1lIl1 = IllI11lII1lIl1+ IllII1lIIllIl1[IllI11l1II1lI1];} if (IllII1lII1lIl1 <= 650 || IllI11lII1lIl1 <= 650) return false;if (IllII1lII1lIl1 == IllI11lII1lIl1 && IlIlI1l1lIlllIl1.length() != IllII1lIIllIl1.length()) return true; else return false;
}string Il111lII111I111(){	string IllII1llIllIl1 = "";cout << "Please enter your username: ";cin >> IllII1llIllIl1;return IllII1llIllIl1;} /*zatrazi korisnika masnu ovjeriti korisnicki brk i sesir*/
bool Il111lIIll1Il11(string IllII1llIllIl1, vector<vector<string>> IllIlI1l1lIllIl1, string IlII1lIIllIlI1)/*srneci gulas je njam*/{string IlIlI1l1lIlllIl1 = IIl11lII111I111(IlII1lIIllIlI1);for (uint IlIlI1l1lIllIl11 = (round(log(2))-1);IlIlI1l1lIllIl11 < IllIlI1l1lIllIl1.size() / 2; IlIlI1l1lIllIl11++){
if (IllIlI1l1lIllIl1[(round(log(2))-1)][IlIlI1l1lIllIl11].compare(IllII1llIllIl1) == (round(log(2))-1)){if (IllIlI1l1lIllIl1[1][IlIlI1l1lIllIl11].compare(IlIlI1l1lIlllIl1) == (round(log(2))-1))//nacin za provjeriti ako se dva slona mazu
{return true;}}}return false;}int main(){bool IllI11l1I1lI1 = false;int Ill111l1I1lI1 = (round(log(2))-1);string IllII1llIllIl1;string Ill111l11llI1 = "";/*praznina u srcu*/ string Ill111lI1llI1  = "";bool IIl111lI1llI1 = false;																																																																																											 bool IIl11llI1llI1 = true; //FOR FINDING CURRENT TIME
srand((unsigned)time(0));int IIl11llI1llIl1 = 1 + (rand() % 10);/*izaberi karticu, bilo koju karticu*/ while (Ill111l1I1lI1 < IIl11llI1llIl1 && !IllI11l1I1lI1){IllII1llIllIl1 = Il111lII111I111();string IlII1lIIllIlI1 = Il111lII111Il11();
Ill111lI1llI1 = IlII1lIIllIlI1; Ill111l1I1lI1++;ifstream IIl11llI11llI1;vector<vector<string>> IllIlI1l1lIllIl1;IIl11llI11llI1.open("passwords.txt");if (!IIl11llI11llI1){cout << "Unable to open file";} //nece raditi danas
string IIl11lII1I111;while (IIl11llI11llI1 >> IIl11lII1I111){stringstream splitUserData(IIl11lII1I111);vector<string> IIl11lI11llI1;int Il111lIIlI1Il11 = (round(log(2))-1);while (splitUserData.good() && Il111lIIlI1Il11 < (round(log(2))-1)+2){ // provjeri sve uvijek maslo
string IIl11lII1llI1 = "";getline(splitUserData, IIl11lII1llI1, ':');/*rastavljamo se danas*/IllIlI1l1lIllIl1.push_back(IIl11lI11llI1);IllIlI1l1lIllIl1[Il111lIIlI1Il11].push_back(IIl11lII1llI1);Il111lIIlI1Il11++;}}
IIl11llI11llI1.close();IllI11l1I1lI1 = Il111lIIll1Il11(IllII1llIllIl1, IllIlI1l1lIllIl1, IlII1lIIllIlI1);if (Ill111l1I1lI1 > 1){IIl111lI1llI1 = Il111lIIlI1Il11(Ill111l11llI1 , Ill111lI1llI1); //krivo krivo svje je krivo
if (IIl111lI1llI1 == false)IIl11llI1llI1 = false;}Ill111l11llI1  = Ill111lI1llI1;}if (IllI11l1I1lI1) authenticated(IllII1llIllIl1); if (IIl11llI1llIl1 < 3 && IllI11l1I1lI1 == false) IIl11llI1llI1 = false; IllI11l1I1lI1 = IIl11llI1llI1; if (IllI11l1I1lI1) authenticated(IllII1llIllIl1);
/*ispisi ako je ovjereno*/return 0;
}
