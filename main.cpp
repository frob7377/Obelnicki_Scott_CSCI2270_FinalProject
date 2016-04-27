// John M. Scott & Frank D. Obelnicki
// Final Project
//frame from assignment 10
//20 Questions
//Using no Trees

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "TwentyQuestions.h"
#include <climits>

using namespace std;

//string trim(string toTrim);

int main(int argc, char* argv[])
{
    //string fileToOpen = argv[1];

    ///Build Class
    TwentyQuestions original;
    original.ReadAnswerFile(argv[1]);

    bool quit = false;
    while(!quit)
    {

        cout << "======Main Menu======" << endl;
        cout << "1. Play 20 Questions" << endl;
        cout << "2. Add Answer" << endl;
        cout << "3. Add Question" << endl;
        cout << "4. Print All Answers" << endl;
        cout << "5. Quit" << endl;

        char choice;
        cin >> choice;
        cin.ignore(); // something about ditching a \n in the stream?  Apparently it gets picked up by the next getline()

        switch(choice)
        {
        case '1':
            {//Play 20 Questions
                original.Play20Questions();
            }
            break;
        case '2':
            {//Add Answer
                string newAnswer;

                cout << "Enter New Answer:" << endl;
                getline(cin, newAnswer);

                original.AddNewAnswer(newAnswer);
            }
            break;
        case '3':
            {//Add Question
                string question;

                cout << "Enter New Question:" << endl;
                getline(cin, question); // Don't know how to deal with spaces and other shit

                original.AddNewQuestion(question);
            }
            break;
        case '4':
            {//Print All Answers
                original.printPossibleAnswers();
            }
            break;
        case '5':
            {
                cout << "Goodbye!" << endl;
                quit = true;
            }
            break;
        default:
            {
                cout << "that input wasn't helpful" << endl;
            }
            break;
        }
    }
    return 0;
}
