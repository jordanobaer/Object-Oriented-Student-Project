//Jordano Baer U83262692
//This program contains a user file and a scores file
//A new user can be created and added to the user file
//The user will be authenticated and he can modify and access information from the scores file
//User can get information and also update exams and add new students and new exams to the scores file
//Main.cpp will start the program and display the menu to the user

#include <iostream>
#include "User.h"
#include "Student.h"
#include "Exam.h"

using namespace std;

//Opens the menu for the user
void GetMenu()
{
    try
    {

        int option;
        do
        {
            cout << "Choose one option" << endl;
            cout << "(1) Create a new user" << endl;
            cout << "(2) Change password" << endl;
            cout << "(3) Display scores of a student" << endl;
            cout << "(4) Display scores of an exam" << endl;
            cout << "(5) Display avg score of a student" << endl;
            cout << "(6) Display avg score of an exam" << endl;
            cout << "(7) Insert scores of a new exam to all students" << endl;
            cout << "(8) Insert scores of all exams of a student who is not in file" << endl;
            cout << "(9) Update an exam score of a student" << endl;
            cout << "(10) Update an exam score of every student" << endl;
            cout << "(11) Exit" << endl;
            cin.clear();
            cin >> option;

            User user;
            Student student;
            Exam exam;
            switch(option)
            {
            case 1:
                user.CreateUser();
                break;
            case 2:
                //check if the user is valid
                if (user.AuthenticateUser())
                {
                    user.ChangePassword();
                }
                break;
            case 3:
                if(user.AuthenticateUser())
                {
                    if(student.ValidateStudent())
                    {
                        student.DisplayScores();
                    }
                }
                break;
            case 4:
                if(user.AuthenticateUser())
                {
                    exam.DisplayScores();
                }
                break;
            case 5:
                if(user.AuthenticateUser())
                {
                    if(student.ValidateStudent())
                    {
                        student.DisplayAverage();
                    }
                }
                break;

            case 6:
                if(user.AuthenticateUser())
                {
                    exam.DisplayAverage();
                }
                break;

            case 7:
                if(user.AuthenticateUser())
                {
                    exam.NewExam();
                }
                break;
            case 8:
                if(user.AuthenticateUser())
                {
                    student.newStudent();
                }
                break;
            case 9:
                if(user.AuthenticateUser())
                {
                    if(student.ValidateStudent())
                    {
                        student.UpdateExamScore();
                    }
                }
                break;
            case 10:
                if(user.AuthenticateUser())
                {
                    exam.UpdateScores();
                }
                break;
            default:
                option = 11;
            }

        }
        while(option !=11);
        cout << "Good Bye!";
    }
    catch(...)
    {
        cout << "An exception occurred";
    }
}

//Main function calls the menu;
int main()
{
    GetMenu();
    return 0;
}


