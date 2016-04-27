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
    int menuChoice = 0;
    //Loops until a valid entry is keyed by user. Each menu choice except exit will reset menuChoice to zero, so the loop continues.
    while(menuChoice != 1 and menuChoice != 2 and menuChoice != 3 and menuChoice != 4 and menuChoice != 5 and menuChoice != 6 and menuChoice != 7)
    {

        cout << "======Main Menu======" << endl;
        cout << "1. Play 20 Questions" << endl;
        cout << "2. Add Answer" << endl;
        cout << "3. Add Question" << endl;
        cout << "4. Print All Answers" << endl;
        cout << "5. Print All Questions" << endl;
        cout << "6. Print a Truth Table" << endl;
        cout << "7. Quit" << endl;
        cin >> menuChoice;
        cin.ignore();
        if (menuChoice == 1)
        { //Play 20 Questions
            original.Play20Questions();
            menuChoice = 0;
        }
        else if (menuChoice == 2)
        { //Add answer
            original.AddNewAnswer();
            menuChoice = 0;
        }
        else if (menuChoice == 3)
        { //Add question
            string question;
            cout << "Enter New Question:" << endl;
            getline(cin, question);
            original.AddNewQuestion(question);
            menuChoice = 0;
        }
        else if (menuChoice == 4)
        { //Print all answers
            original.printPossibleAnswers();
            menuChoice = 0;
        }
        else if (menuChoice == 5)
        { //Print all questions
            original.printQuestions();
            menuChoice = 0;
        }
        else if (menuChoice == 6)
        { //Print truth table
          original.printTruthTable();
          menuChoice = 0;
        }
        else if (menuChoice == 7)
        { //Exit
            original.savetoFile();
            cout << "Goodbye!" << endl;
            break;
        }
    }
    return 0;
}
