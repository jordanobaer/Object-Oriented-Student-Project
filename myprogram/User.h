#ifndef USER_H
#define USER_H
#include <iostream>
#include<fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Pwdg.h"

using namespace std;


//User class, can be used to create a new user and generate a password then add them to the user file.
//This class checks if the user is valid and it can be used to change the user's password
//Includes "Pwdg.h" (Password Generator) to create a new password with random characters
class User
{
public:

    //Creates a new user and adds it to the file
    //The function checks if the user already exists
    void CreateUser()
    {
        try
        {
            fstream File = OpenFile();
            cout << "Opened the password file"<< endl;
            istringstream stream;
            string usrname;
            bool validUser = true;
            string line;

            //Check if the user is valid
            do
            {
                cout << "Enter your new user name: " << endl;
                cin >> name;

                /*
                cout << "Enter your new password: " << endl;
                cin >> password;
                */

                validUser = true;
                File.clear();
                File.seekg (0, ios::beg);
                while(!File.eof())
                {
                    getline(File, line);
                    stream.str(line);
                    stream >> usrname;

                    if(usrname == name)
                    {
                        cout << "This username already exists" << endl;
                        validUser = false;
                    }
                }

            }
            while(!validUser);
            File.close();
            //generate a password
            password = generatePassword();

            cout << "This user is valid" << endl;

            //Add the user and the password to the file
            ofstream oFile("User/passwords.txt",  ios::out | ios::app);
            if(!oFile.is_open())
            {
                cout << "Couldn't open the file" << endl;
            }
            else
            {
                oFile <<  endl << name << " " << password ;
                cout << "User name and password added to the file"<< endl;
                oFile.close();
            }

        }
        catch(...)
        {
            cout << "Can't create user";
        }
    }

    //This function checks if the username and the password are correct
    bool AuthenticateUser()
    {
        bool valid = false;
        try
        {
            ifstream iFile("User/passwords.txt");
            if(!iFile.is_open())
            {
                cout << "Couldn't open the file" << endl;
                throw 1;
            }
            else
            {
                //cout << "Opened the password file"<< endl;
                cout << "Enter your user name: " << endl;
                cin >> name;
                cout << "Enter your password: " << endl;
                cin >> password;

                string fname;
                string fpassword;
                //Look for the user in the file. Check the username and the password
                while(!iFile.eof())
                {
                    iFile >> fname;
                    iFile >> fpassword;

                    if((fname == name) && (fpassword==password))
                    {
                        valid = true;
                        cout << "Valid user"<< endl;
                        iFile.close();
                        return valid;
                    }
                }
                if(!valid)
                {
                    cout << "Invalid user"<< endl;
                }
                iFile.close();
            }
        }
        catch(...)
        {
            cout << "Can't authenticate user" << endl;
        }
        return valid;

    }

    //Changes the password of the current user
    void ChangePassword()
    {
        try
        {
            string newPassword;
            newPassword = generatePassword();
            string user = name;
            int i = 0;
            string temp;
            int position;
            int counter = 0;
            int user_line = 0;
            vector<string> lines;
            istringstream stream;
            string line;
            fstream File("User/passwords.txt");
            while (!File.eof())
            {
                getline(File, line);
                if(line != "")
                {
                    stream.str(line);
                    stream >> temp;
                    if(temp == user)
                    {
                        user_line = counter;
                        temp = user + " " + newPassword;
                    }
                    else
                    {
                        temp = line;
                    }
                    lines.push_back(temp);
                    //cout << temp;
                    counter++;
                }
                stream.clear();
            }

            File.close();
            File.open("User/passwords.txt");

            for( i = 0; i<lines.size(); i++)
            {
                if(i == lines.size() - 1)
                {
                    File << lines.at(i) << "             ";
                }
                else
                {
                    File << lines.at(i) << endl;
                }

            }

            password = newPassword;
            cout << "Your password was changed to " << password << endl;
            File.close();
        }
        catch(...)
        {
            cout << "Can't change password" << endl;
        }

    }

    //Generates a password
    //The user can choose a password with only digits, only letters or letters, digits and symbols.
    string generatePassword()
    {
        bool valid = false;
        int len = 0;
        char digits_only;
        char letters_only;
        string newPassword;
        srand(time(NULL));
        cout << "Enter the password length:"<<endl;
        cin >> len;
        cout << "Want a password containing digits only?(Y/N)";
        cin >> digits_only;

        //If the user wants a password with only digits
        if (digits_only == 'Y' || digits_only == 'y')
        {
            Simple_pwdg password;
            password.setLength(len);
            newPassword = password.getSimplePWD('D') ;
            cout << "Password: " << newPassword << endl;
            valid = true;

        }
        else
        {
            cout << "Want a password containing letters only?(Y/N)";
            cin >> letters_only;
            //if the user wants a password with only letters
            if(letters_only == 'Y' || letters_only == 'y')
            {
                Simple_pwdg password;
                password.setLength(len);
                newPassword =  password.getSimplePWD('L');
                cout << "Password: " << newPassword << endl;
                valid = true;
            }
            else
            {
                //if the user doesn't want a simple password, create a password using the Pwdg class
                Pwdg password;
                password.setLength(len);
                password.setPWD();
                newPassword = password.getPWD();
                cout << "Password: " <<  newPassword << endl;
                valid = true;
            }

        }
        return newPassword;

    }




protected:

private:
    string name;
    string password;
    string fileName = "User/passwords.txt";

    //Function to open the user file
    fstream OpenFile()
    {
        fstream File(fileName);
        if(!File.is_open())
        {
            throw 0;
        }
        else
        {
            //cout << "Opened File" << endl;
        }
        return File;
    }


};

#endif // USER_H
