// John M. Scott & Frank D. Obelnicki
// Final Project
// "20" Questions
// 04/24/16

#include <iostream>
#include "TwentyQuestions.h"

using namespace std;

int main(int argc, char* argv[])
{
    //Build Class
    TwentyQuestions original;
    //Calls method of class that allows for custom files.
    string fileName = original.findFileName();
    //Reads in questions and answers from file.
    original.ReadAnswerFile(fileName);
    string menuChoice; ///changed to string to use getline
    //Loops until a valid entry is keyed by user. Each menu choice except exit will reset menuChoice to zero, so the loop continues.
    //I added a bool to your code that will be set to true when user selects 7
    //To fix the infinite loop, when user selects option not 1-7, code will prompt for new response
    bool menu = false;
    while(!menu)
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Play 20 Questions" << endl;
        cout << "2. Add Answer" << endl;
        cout << "3. Add Question" << endl;
        cout << "4. Print All Answers" << endl;
        cout << "5. Print All Questions" << endl;
        cout << "6. Print a Truth Table" << endl;
        cout << "7. Quit" << endl;
        getline(cin,menuChoice);
        if (menuChoice == "1")
        { //Play 20 Questions
            original.Play20Questions();
        }
        else if (menuChoice == "2")
        { //Add answer
            original.AddNewAnswer();
        }
        else if (menuChoice == "3")
        { //Add question
            string question;
            cout << "Enter New Question:" << endl;
            getline(cin, question);
            original.AddNewQuestion(question);
        }
        else if (menuChoice == "4")
        { //Print all answers
            original.printPossibleAnswers();
        }
        else if (menuChoice == "5")
        { //Print all questions
            original.printQuestions();
        }
        else if (menuChoice == "6")
        { //Print truth table
          original.printTruthTable();
        }
        else if (menuChoice == "7")
        { //Exit
            original.savetoFile();
            cout << "Goodbye!" << endl;
            menu = true; //set bool to true here, will exit loop
        }
        else
        {
            cout<<"Please enter a valid choice."<<endl;
        }
    }
    return 0;
}
