//Program to create a password.
//It asks the user if he wants a simple password or not

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

//Class used to generate a password
class Pwdg{
   public:
	  //return the password
      string getPWD(){
         return password;
      }

	  //set the password length
      void setLength(int l){
        len = l;
      }

	  //get the password length
      int getLength(){
        return len;
      }

	  //create the password
      void setPWD(){
         int i;
         int j;
         for (i = 0; i<len; i++){
               j = rand();
               j %= 4;
               if(j == 0){
                  addDigit();
               }else if(j == 1){
                  addLowerCase();
               }else if(j == 2){
                  addUpperCase();
               }else{
                  addSpecial();
               }

            }
      }

	  //add a lower case char to the password
      void addLowerCase(){
         int random;
         char c = 'a';
         random = rand();
         random %= 26;
         c += random;
         password += c;
      }

	  //add an upper case char to the password
      void addUpperCase(){
         int random;
         char c = 'A';
         random = rand();
         random %= 26;
         c += random;
         password += c;
      }

	  //add a digit to the password
      void addDigit(){
             int random;
             char c = '0';

             random = rand();
             random %= 10;
             c += random;
             password += c;
      }

	  //add a special char to the password
      void addSpecial(){
            int random;
            char c;
            vector<char> special = {'!','@', '#', '$', '%', '^', '&', '*', '+', '-', '=' };
            random = rand();
            random %= 11;
            c = special.at(random);

            password += c;
      }

   private:
      string password = "";
      int len = 0;
   };

//Class used to create a simple password, inherits Pwdg
// the user can select between a normal password, a password with only letter and a password with only digits
class Simple_pwdg : public Pwdg{
    public:
        string getSimplePWD(char x){
            int len = getLength();
            int i = 0;
            int j = 0;
			//if the password contains only letters
            if(x == 'L'){
                for(i = 0; i < len; i++){
                    j = rand();
                    j %= 2;
                    if (j == 0){
                        addUpperCase();
                    }else{
                        addLowerCase();
                    }


                }
			//if the password contains only digits
            }else if(x == 'D'){
                for(i = 0; i < len; i++){
                    addDigit();
                }

            }
            return getPWD();
        }

    protected:

    private:
};

