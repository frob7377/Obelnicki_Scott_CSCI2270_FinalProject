// John M. Scott & Frank D. Obelnicki
// Final Project
//frame from assignment 10
//20 Questions
//Using no Trees

#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <queue>
#include "TwentyQuestions.h"
//#include <climits>

using namespace std;

//string trim(string toTrim);

int main(int argc, char* argv[])
{
    //string fileToOpen = argv[1];
    //Build Class
    TwentyQuestions original;
    original.ReadAnswerFile( "answers.txt"/*argv[1]*/);

    int menuChoice = 0;
    while(menuChoice != 1 and menuChoice != 2 and menuChoice != 3 and menuChoice != 4 and menuChoice != 5 and menuChoice != 6)
    {

        cout << "======Main Menu======" << endl;
        cout << "1. Play 20 Questions" << endl;
        cout << "2. Add Answer" << endl;
        cout << "3. Add Question" << endl;
        cout << "4. Print All Answers" << endl;
        cout << "5. Print All Questions" << endl;
        cout << "6. Quit" << endl;

        //char choice;
        cin >> menuChoice;
        cin.ignore(); // something about ditching a \n in the stream?  Apparently it gets picked up by the next getline()

        if (menuChoice == 1)
        {//Play 20 Questions
            original.Play20Questions();
            menuChoice = 0;
        }
        else if (menuChoice == 2)
        {//Add Answer
            /*string newAnswer;

            cout << "Enter New Answer:" << endl;
            getline(cin, newAnswer);
            */
            original.AddNewAnswer();
            menuChoice = 0;
        }
        else if (menuChoice == 3)
        {//Add Question
            string question;

            cout << "Enter New Question:" << endl;
            getline(cin, question); // Don't know how to deal with spaces and other shit

            original.AddNewQuestion(question);
            menuChoice = 0;
        }
        else if (menuChoice == 4)
        {//Print All Answers
            original.printPossibleAnswers();
            menuChoice = 0;
        }
        else if (menuChoice == 5)
        {
            original.printQuestions();
            menuChoice = 0;
        }
        else if (menuChoice == 6)
        {
            original.savetoFile();
            cout << "Goodbye!" << endl;
            break;
        }
    }
    return 0;
}
