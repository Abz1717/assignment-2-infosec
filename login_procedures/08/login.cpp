#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include "sha256.h"
#include "authlib.h"
using namespace std;

class encryptionStuff // stuff to encrypt or decrypt
{
public:
    string encrypt(string password)
    {
        return sha256(password);
    }
    string getPWfromFile(string fileName, string user) // gets hashed password from a file and returns it as a string
    {
        ifstream inFile;
        inFile.open(fileName);
        //strings used to read input from text
        string line;
        //real user login name from file
        string userlogin;
        //real hashed password from file
        string shaPW, shadPW ="";
        int x=0;

        //check for error
        if (inFile.fail())
        {
            cerr << "Error Opening File" << endl;
        }
        else
        {
            //while there is still a line
            while (getline(inFile, line))
            {
                stringstream ss(line);
                //read up to the ':' and store string in userlogin
                getline(ss, userlogin, ':');
                //read up to the ':' and store string in shaPW
                getline(ss, shaPW, ':');
                //if username input matches text file username, return official hashed password
                if ((userlogin == user) && (x==0))
                {   
                    //set shaPW to shaPW since login usernames match, later test 
                    //for password match
                    shadPW = shaPW;
                    x++;
                    
                }
                else if((userlogin == user) && (shadPW!=shaPW)&& (x!=0))
                {
                    //if first combination matched, and users also match
                    // set shaPW to shaPW while x!=0 since it is not the first
                    //mismatch
                    x=0;
                    shadPW=shaPW;
                }
                else if (shadPW == "")
                {

                    //could not find username. set an empty value for the string 
                    //which supposedly holds 
                    //the hashed password retrieved for the given username 
                    shaPW = "";
                }
                else if ((userlogin != user) && (shadPW!=shaPW)&& (x!=0))
                {
                    cout<< " " << endl;
                }
                else{
                    
                    return shadPW;
                }
            }
            return shadPW;
        }
        return shaPW;
    }
    void addUser(string usr, string pw)
    {
        //hash password from parameter
        pw = sha256(pw);
        ofstream outFile;
        outFile.open("3791570.txt", ios::app);
        //append username and hashed password to file
        outFile << usr << ":" << pw << endl;
    }
};

class LoginManager // to manage frontend stuff and validate logins
{
public:
    string tempUsername;
    string tempPassword;
    bool validUsername = false;
    bool validPassword = false;
    string user;
    string password;
    encryptionStuff encrypt1;

    void menu() // works as a menu
    {
        //boolean for valid input
        bool input = false;
        //temporary input
        string tmpIn;

        do
        {
            cout << "\nPlease select an option from the list \n 1:Login \n 2:Register \n 3:Exit \n";
            cin >> tmpIn;
            if (validInput(tmpIn))
            {
                input = true;
                if (tmpIn == "1")
                {
                    login();
                }
                else if (tmpIn == "2")
                {
                    registerUser();
                }
                else if (tmpIn == "3")
                {

                    cout << "\nExit\n";
                    exit(1);
                }
                else
                {
                    cout << "Input invalid \n";
                    input = false;
                }
            }
            else
            {
                cout << "\nInput invalid\n";
                //try again
                cin >> tmpIn;
            }
        } while (input == false);
    }
    void registerUser() // to register a new user
    {
        //temporary user string
        string tmpUsr;
        bool validUsr;
        //temporary password string
        string tmpPW;
        bool validPW;
        do
        {
            cout << "\nPlease enter a new username:\n";
            cin >> tmpUsr;
            //validate input
            if (validInput(tmpUsr) == false)
            {
                cout << "\nInput invalid\n";
                validUsr = false;
            }
            //If input is valid and the returned value signifies that no
            //username was found that matches the username from the input, then it means
            //that username is free to use
            else if ((validInput(tmpUsr) == true))
            {
                validUsr = true;
            }
            //if input is valid but username is taken
            else
            {
                cout << "\nUsername has been taken\n";
                validUsr = false;
            }
            

        } while (validUsr != true);

        do
        {
            cout << "\nPlease enter a new password:\n";
            cin >> tmpPW;
            if (validInput(tmpPW) == false)
            {
                cout << "\nInput invalid";
                validPW = false;
            }
            else if (validInput(tmpUsr) == true)
            {
                validPW = true;
            }

        } while (validPW != true);
        //add the new user to the text file
        encrypt1.addUser(tmpUsr,tmpPW);
        
    }

    void login() // asks for inputs with which to log the user in
    {

        do
        {
            cout << "\nPlease enter a username:\n";
            cin >> tempUsername;
            if (validInput(tempUsername) == false)
            {
                cout << "\nInput invalid\n";
                validUsername = false;
            }
            else if (validInput(tempUsername) == true)
            {
                validUsername = true;
            }
        } while (validUsername != true);
        user = tempUsername;

        do
        {
            cout << "\nPlease enter a password:\n";
            cin >> tempPassword;
            if (validInput(tempPassword) == false)
            {
                cout << "\nInput invalid\n";
                validPassword = false;
            }
            else if (validInput(tempUsername) == true)
            {
                validPassword = true;
            }
        } while (validPassword != true);
        password = tempPassword;
        //attempt login with provided credentials
        loginAttempt(password, user);
    }

    bool validInput(string tmpInput) //to validate the inputs to the username and password fields ie to make sure no spaces or empty inputs
    {
        for (int i = 0; i < int (tmpInput.length()); i++)
        {
            //if the input is an empty space
            if (isspace(i))
            {
                return false;
            }
        }
        return true;
    }

    void loginAttempt(string inputPW, string u) // checks to see if the the passwords match
    {
        //hash the provided password and store in temporary variable
        string tmpPW = encrypt1.encrypt(inputPW);
        //find the real hashed password that coincides with the provided username
        string filePW = encrypt1.getPWfromFile("3791570.txt", u);
        //if the hashed version of the provided password and the one stored on
        //the text file match, it means that the user has provided the correct credentials
        if (tmpPW == filePW)
        {
            cout << "\nLogin successfull\n";
            authenticated(u);
        }
        //filePW will only ever be equal to "" when a user was found.
        //So if the previous if statement did not work, and there is a user
        //registered with the given username, then we know that
        //the password provided was correct and matches the one for the user
        else if (filePW != "")
        {
            cout << "\nLogin failed. Incorrect password.\n" << endl;
            
            rejected(u);
        }
        //else no user was found under that username
        else 
        {
            cout << "\nLogin failed. Username not found.\n" << endl;
            
            rejected(u);    
        }
    }
};

int main()
{
    do
    {
        LoginManager login;
        login.menu();
    }
    while(true);
}
