#ifndef EXAM_H
#define EXAM_H
#include <iostream>
#include<fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

//Exam class can be used to display the scores of a specific exam, display the average of that exam,
//add a new exam to all students in the score file and update an exam to all students
class Exam
{
public:

    //Displays the scores of all students for an exam
    void DisplayScores()
    {
        try
        {
            //calculate the number of tests and students
            getTests();
            CalculateStudents();
            cout << "There are " << nTests << " exams in the file" << endl;
            cout << "Enter the number of the exam that you want to display the scores:";
            cin >> examNumber;
            //Calculate current number of tests

            if(examNumber > nTests)
            {
                //exam doesn't exist
                throw 1;
            }
            fstream File = OpenFile();
            string line;
            istringstream stream;
            int i = 0;
            string student;
            int n;
            vector<int> scores;
            string id;
            while(!File.eof())
            {
                getline(File,line);
                if(line != "")
                {
                    /*
                    stream.str(line);
                    vector<string> li(examNumber);
                    stream >> student;
                    for(i = 0; i < examNumber; i++)
                    {
                        stream >> li.at(i);
                    }
                    */
                    //cout << stream.str();

                    stream.str(line);
                    stream >> student;
                    for(i = 0; i < nTests; i++)
                    {
                        stream >> n;
                        if(!stream.fail())
                        {
                            scores.push_back(n);
                        }
                        else
                        {
                            stream.clear();
                            stream.ignore(15,' ');
                            stream >> n;
                            scores.push_back(n);
                        }
                    }

                    cout << "Student " <<  student << " Score: " << scores.at(examNumber-1) << endl;

                }
                stream.clear();
                scores.clear();
            }
        }
        catch(int e)
        {
            if(e == 1)
            {
                cout << "This test doesn't exist in the file" << endl;
            }
        }
        catch(...)
        {
            cout << "Couldn't display the scores" << endl;
        }
    }

    //Function calculates and displays the average score of an exam
    void DisplayAverage()
    {
        try
        {
            getTests();
            CalculateStudents();
            cout << "There are " << nTests << " exams in the file." << endl;
            cout << "Enter the number of the exam that you want to calculate the average: ";
            cin >> examNumber;

            if(examNumber > nTests | examNumber <= 0)
            {
                //exam doesn't exist
                throw 1;
            }
            //Open File
            fstream File = OpenFile();
            string line;
            istringstream stream;
            int j = 0;
            int i = 0;
            double average = 0;
            double total = 0;
            string temp;
            double score = 0;
            string id;
            vector<int> scores;
            int n;
            while(!File.eof())
            {
                scores.clear();
                getline(File, line);
                if(line!= "")
                {
                    stream.str(line);
                    stream >> id;
                    for(i = 0; i < nTests; i++)
                    {
                        stream >> n;
                        if(!stream.fail())
                        {
                            scores.push_back(n);
                        }
                        else
                        {
                            stream.clear();
                            stream.ignore(15,' ');
                            stream >> n;
                            scores.push_back(n);
                        }


                    }
                    //cout << "ADD TO TOTAL :"  << scores.at(examNumber-1) << endl;
                    total += scores.at(examNumber-1);
                }
            }
            /*
            for(i = 0; i < examNumber; i++)
            {
                stream >> temp;
            }
            stream >> score;
            cout << "add to total score: " << score << endl;
            total +=score;
            }
            */
            cout << "Average = " << total << "/" << totalStudents << endl;
            average = total / totalStudents;
            cout << "The average of exam " << examNumber << " with a total of " << totalStudents << " students is: " <<setprecision(4) << average << endl;
            File.close();

        }
        catch(int e)
        {
            if(e == 1)
            {
                cout << "This test doesn't exist in the file" << endl;
            }

        }
        catch(...)
        {
            cout << "Can't calculate average";

        }
    }

    //Adds a new exam to all the students in the file
    void NewExam()
    {
        bool valid = false;
        getTests();
        CalculateStudents();
        examNumber = nTests + 1;
        cout << "Creating exam number:" << examNumber << endl;
        cout << "Invalid scores will change to 0" << endl;
        istringstream score_stream;
        do
        {
            try
            {
                cin.ignore();
                score_stream.clear();
                int i = 0;
                vector<string> newScores;
                string temp;



                cout << "Write the grades for " << totalStudents << " students in order: ";
                for(int i = 0; i < totalStudents; i++)
                {
                    cout << student_ids.at(i) << " ";
                }
                cout << endl;

                getline(cin,temp);
                int n;
                score_stream.str(temp);
                //for(i = 0; i<totalStudents; i++)
                while(!score_stream.eof())
                {
                    score_stream >> n;
                    if(score_stream.fail())
                    {
                        throw 1;
                    }

                    if(n < 0 || n > 100)
                    {
                        n = 0;
                    }
                    newScores.push_back(to_string(n));
                }

                if(newScores.size() < totalStudents)
                {
                    throw 1;
                }
                fstream File = OpenFile();
                istringstream stream;
                string line;
                vector<string> lines;
                while(!File.eof())
                {
                    getline(File,line);
                    lines.push_back(line);
                }
                File.clear();
                File.seekg(File.beg);

                //cout << "Lines size: "<<lines.size();
                for(i = 0; i<lines.size(); i++)
                {
                    if(lines.at(i) != "")
                    {
                        if(i == lines.size()-1)
                        {
                            File << lines.at(i) << " " << newScores.at(i);
                        }
                        else
                        {
                            File << lines.at(i) << " " << newScores.at(i) << endl;
                        }


                    }
                }
                File.close();
                valid = true;
                cout << "Scores added to the file" << endl;
            }
            catch(...)
            {
                cout << "Can't create a new Exam" << endl;
            }
        }
        while(!valid);

    }

    //Checks if the exam exists in the file
    void ValidateExam()
    {
        nTests = getTests();
        CalculateStudents();
        cout << "There are " << nTests << " tests in the file" << endl;
        cout << "What is the exam that you want to access?" << endl;
        cin >> examNumber;

        if(examNumber > nTests || examNumber <= 0)
        {
            throw 1;
        }
        else
        {
            cout << "This exam is valid" << endl;
        }

    }

    //Uodates the scores of all students for an exam
    void UpdateScores()
    {
        try
        {
            ValidateExam();
            int update;
            cout << "Insert the amount that you want to add to all students:" << endl;
            cin >> update;
            fstream File = OpenFile();
            int i = 0;
            int j = 0;
            vector<string> lines;
            vector<string> addlines;
            string id;
            string current_line;
            string newLine;
            vector<int> scores;
            int n = 0;
            istringstream stream;
            while(!File.eof())
            {
                getline(File, current_line);
                if(current_line != "")
                {
                    lines.push_back(current_line);
                }

            }


            for(i = 0; i < lines.size(); i++)
            {
                stream.str(lines.at(i));
                stream >> id;
                for(j = 0; j < nTests; j++)
                {
                    stream >> n;

                    scores.push_back(n);
                    // cout << "N:" << scores.at(j);
                }
                newLine = id + " ";
                scores.at(examNumber-1) += update;
                if(scores.at(examNumber-1)>100)
                {
                    scores.at(examNumber-1) = 100;

                }
                else if(scores.at(examNumber-1)<0)
                {
                    scores.at(examNumber-1) = 0;
                }

                for(j = 0; j < nTests; j++)
                {
                    newLine += to_string(scores.at(j)) + " ";
                }
                addlines.push_back(newLine);
                //cout << newLine;
                //cout <<  "NEWLINE: "<< newLine << endl;
                scores.clear();
                stream.clear();
            }

            //Go to the beginning of the file
            File.clear();
            File.seekg(0, ios::beg);

            //Write to the file
            for(i = 0; i < totalStudents; i++)
            {
                if(i == totalStudents-1){
                File << addlines.at(i) << "                        ";
                }else{
                File << addlines.at(i) << endl;
                }

            }

            File.close();
            cout << "Exams have been updated" << endl;
        }
        catch(int e)
        {
            cout << "This exam is not valid" << endl;
        }
        catch(...)
        {
            cout << "Can't update exam" << endl;
        }

    }


    //This function gets the current number of tests in the file
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
        //cout << "TOTAL NUMBER OF TESTS = " << n << endl;
        File.close();
        nTests = n;
        return n;
    }

    //Calculate the current number of students in the file
    int CalculateStudents()
    {
        int total = 0;
        fstream File = OpenFile();
        string line;
        istringstream stream;
        string student;

        while(!File.eof())
        {
            getline(File, line);
            if(line != "")
            {
                total++;
                stream.str(line);
                stream >> student;
                student_ids.push_back(student);
            }

        }
        //cout << "TOTAL NUMBER OF STUDENTS = " << total <<endl;

        /*cout << "Student ids in order: " << endl;
        for(int i = 0; i < total; i++){
            cout << student_ids.at(i);
        }
        */
        totalStudents = total;
        File.close();
        return total;
    }

    vector<string> getStudentIDs()
    {
        CalculateStudents();
        return student_ids;
    }
protected:

private:
    vector<string> student_ids;     //all the ids of the students
    int totalStudents;              //Total number of students in the file
    int nTests;                     //Total number of tests
    string fileName = "Data/scores.txt";
    int examNumber;                 //number of the specific test


    //Opens the scores file
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

#endif // EXAM_H
