#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include<fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <ios>
#include <iomanip>
#include "Exam.h"

//Student class, can be used to add a new student,
//display the scores of the student and display the average of the student
class Student
{
public:
    bool ValidateStudent()
    {
        int testNumber = getTests();
        bool valid = false;
        do
        {
            try
            {


                cout << "Enter the student id. Ex:U101 "<< endl;
                cin >> id;
                fstream File;
                File = OpenFile();
                string line;
                istringstream stream;
                string fID;

                while(!File.eof())
                {
                    getline(File, line);
                    stream.str(line);
                    stream >> fID;
                    if(fID == id)
                    {
                        cout << "This is a valid student" << endl;
                        id = fID;
                        file_line = line;
                        for(int i = 0; i < testNumber; i++)
                        {
                            //get the scores of the student
                            stream >> scores.at(i);

                        }
                        valid = true;
                        break;
                    }
                }
                File.close();
                if(!valid)
                {
                    cout << "This student is not valid, try again." << endl;

                }
            }
            catch(int e)
            {
                if(e == 0)
                {
                    cout << "Can't open the scores file" << endl;
                    return false;
                }

            }
            catch(...)
            {
                cout << "Exception: Can't authenticate this student";
                return false;
            }

        }
        while(!valid);
        return valid;
    }

    //Add a new student to the file and insert the exam scores,
    //It checks if the user id is valid, then it asks for the scores
    void newStudent()
    {

        bool valid = false;
        string newID;
        int i = 0;
        do
        {
            try
            {
                cout << "Enter the id of the new student. The id has to start with U followed by 3 digits. Ex: U102" << endl;
                cin >> newID;
                if(newID.size() > 4)
                {
                    throw 0;
                }
                else if(newID.at(0) != 'U')
                {
                    throw 1;
                }
                else
                {
                    for(i = 1; i < 4; i++)
                    {
                        if(!isdigit(newID.at(i)))
                        {
                            throw 2;
                        }
                    }

                    //Check if the student already exists in the file;
                    Exam exam;
                    vector<string>ids = exam.getStudentIDs();
                    for(i = 0; i<ids.size(); i++)
                    {
                        if(newID == ids.at(i))
                        {
                            throw 3;
                        }
                    }
                    valid = true;
                }

            }
            catch(int e)
            {
                if(e == 0)
                {
                    cout << "The size of the ID needs to be 4" << endl;
                }
                else if(e == 1)
                {
                    cout << "ID has to start with 'U'"<< endl;
                }
                else if(e == 2)
                {
                    cout << "ID needs 3 digits after the U"<< endl;
                }
                else if(e == 3)
                {
                    cout << "This student already exists in the file"<< endl;
                }
            }
            catch(...)
            {
                cout << "Can't add new student"<< endl;
            }

        }
        //Ask for the id until it's valid
        while(!valid);


        vector<int> student_scores;
        //get the new scores
        cin.ignore();
        do
        {
            try
            {

                valid = true;
                string new_scores;
                int n = getTests();
                cout << "There are " << n << " tests in the file"<< endl;
                cout << "Enter the scores in order for the new student in one line:"<< endl;

                getline(cin, new_scores);
                int temp;
                istringstream stream(new_scores);
                student_scores.clear();
                while(!stream.eof())
                {
                    stream >> temp;
                    student_scores.push_back(temp);
                }
                for(i = 0; i < nTests; i++)
                {
                    if(student_scores.at(i)>100 || student_scores.at(i) < 0)
                    {
                        student_scores.at(i) = 0;
                    }
                }


                /*
                for(i = 0; i<n; i++)
                {
                    stream >> temp;
                    student_scores.push_back(temp);
                    if(student_scores.at(i)>100 || student_scores.at(i) < 0)
                    {
                        student_scores.at(i) = 0;
                    }
                }
                */
            }
            catch(...)
            {
                cout << "Scores are not valid" << endl;
                valid = false;
                //cin.ignore();
            }
        }
        while(!valid);
        ofstream oFile(fileName,  ios::out | ios::app);
        oFile << endl << newID << " ";
        for(i = 0; i < nTests; i++)
        {
            oFile << student_scores.at(i) << " ";
        }
        cout << newID << " was added to the file" << endl;

    }

    //Display the scores of a student
    void DisplayScores()
    {
        nTests = getTests();
        cout << "Student: " << id << " Scores:"<<endl;
        for(int i = 0; i < nTests; i++)
        {
            cout << "Test " << i+1 << ": "<< scores.at(i)<< endl;
        }
    }

    //Calculate and display the average of a student
    void DisplayAverage()
    {
        double average = 0;
        double total = 0;
        int len = scores.size();
        for(int i = 0; i < len; i++)
        {
            total += scores.at(i);
        }
        average = total/len;
        cout << "The average for student " << id << ": " <<setprecision(4) <<average << endl;
    }


    //This function gets the current number of tests in the file and update nTests
    int getTests()
    {
        int i = 0;
        int n = 0;
        string line;
        fstream File = OpenFile();
        getline(File,line);
        for(i = 0; i < line.size()-1; i++)
        {

            if(line.at(i) == ' ' && line.at(i+1)!=' ')
            {
                n++;
            }
        }
        //cout << "NUMBER OF TESTS = " << n << endl;
        File.close();
        nTests = n;
        scores.resize(n);
        return n;
    }

    //Function updates an exam score of a student
    void  UpdateExamScore()
    {
        getTests();
        int test;
        int newScore;
        int i = 0;
        try
        {
            cout << "There are " << nTests << " tests" << endl;
            cout << "What is the test that you want to update?" << endl;
            cin >> test;
            if(test > nTests || test <= 0)
            {
                throw 1;
            }

            /*cout <<"EXAMS OF THE STUDENT:" << endl;
            for(i = 0; i<nTests; i++)
            {
                cout << scores.at(i) << " ";

            }
            */

            cout << "What is the new score?" << endl;
            cin >> newScore;

            if(newScore >100 || newScore < 0)
            {
                newScore = 0;
            }

            scores.at(test-1) = newScore;


            string add_line = id;

            //cout << "UPDATED EXAMS OF THE STUDENT:" << endl;
            for(i = 0; i<nTests; i++)
            {
                //cout << scores.at(i) << " ";
                add_line += " " + to_string(scores.at(i));

            }

            fstream File = OpenFile();
            string temp;
            string current_line;
            vector<string> lines;
            istringstream stream;
            string fID;
            string newLine;
            while(!File.eof())
            {
                getline(File, current_line);
                stream.str(current_line);
                stream >> fID;
                if(fID == id)
                {
                    current_line = add_line;

                }
                if(current_line != ""){
                    lines.push_back(current_line);
                }

                //cout << current_line << endl;
            }

            //Go to the beginning of the file
            File.close();
            File = OpenFile();

            Exam e;
            nStudents = e.CalculateStudents();
            //Write to the file
            for(i = 0; i < lines.size(); i++)
            {

                if(i == lines.size()-1){
                   File << lines.at(i);
                }else{
                   File << lines.at(i) << endl;
                }
            }
            File.close();
            cout << "Updated the exam" << endl;
        }
        catch(...)
        {
            cout << "Can't update the exam" << endl;
        }
    }


protected:

private:
    string id;          //id of the student
    int nTests;         //total number of tests
    int nStudents;      //total number of students
    vector<int> scores; //scores of the student
    string file_line;   //line on the file where the student is located
    string fileName = "Data/scores.txt";

    //Function to open the scores file
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

#endif // STUDENT_H
