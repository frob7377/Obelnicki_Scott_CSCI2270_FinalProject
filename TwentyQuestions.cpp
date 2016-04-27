#include "TwentyQuestions.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

TwentyQuestions::TwentyQuestions()
{
    //ctor
}

TwentyQuestions::~TwentyQuestions()
{
    //dtor
}

////////////////////////////////////////////////////
///Stage 1 methods (neccesary for doing 20 questions)
////////////////////////////////////////////////////

///Public
string TwentyQuestions::findFileName()
{ //Allows the user to enter a custom file name if they have their own question file
    string input, fileName = "answers.txt";
    //Loops until valid input is entered.
    while (input != "Y" && input != "y" && input != "N" && input != "n")
    {
        cout << "Would you like to use a custom question and answer file?" << endl;
        getline(cin, input);
    }
    if (input == "y" || input == "Y")
    {
        cout << "Enter the file name:" << endl;
        getline(cin, fileName);
        return fileName;
    }
    return fileName;
}

void TwentyQuestions::ReadAnswerFile(string fileTitle)
{ //Reads questions and answers in from file
    //Converts string into characters
    char *fileName = const_cast<char*>(fileTitle.c_str());
    string FileLine = "Blank";
    ifstream ANSWERfile;
    //Open the file
    ANSWERfile.open(fileName);
    //Tracks which row of the file is being read
    int Yaxis = 0;
    //Tracks which column of the file is being read
    int Xaxis = 0;
    if(ANSWERfile.good())
    {
        while(getline(ANSWERfile, FileLine))
        { //Gets each line of the file
            string InfoNugget;
            //Processes file line through stringstream
            stringstream ss(FileLine);
            //Parses line by using ',' delimiter
            while(getline(ss, InfoNugget, ','))
            {
                if(Yaxis == 0)
                { //Read in questions
                    if(Xaxis > 0)
                        QuestionMap.push_back(InfoNugget);
                }
                else
                { //Read in answers, if Yaxis > 0
                    if(Xaxis == 0)
                    { //Make New Answer
                        Answers NewAnswer;
                        NewAnswer.title = InfoNugget;
                        NewAnswer.possible = true;
                        for(int i = 0; i < QuestionMap.size(); i++)
                        { //Stores question table for each answer
                            Questions newQuestion;
                            newQuestion.title = QuestionMap[i];
                            newQuestion.TF = true;
                            NewAnswer.AnsQuestVector.push_back(newQuestion);
                        }
                    AnswerVector.push_back(NewAnswer);
                    }
                    else
                    { //Stores truth table from file for each answer
                        if(InfoNugget == "1")
                            AnswerVector[Yaxis-1].AnsQuestVector[Xaxis-1].TF = true;
                        if(InfoNugget == "0")
                            AnswerVector[Yaxis-1].AnsQuestVector[Xaxis-1].TF = false;
                    }
                }
                //Increments Xaxis inside the loop
                Xaxis++;
            }
            //Resets Xaxis for next line
            Xaxis = 0;
            //Increments Yaxis
            Yaxis++;
        }
    }
    else
    {
        cout << "file failed to open" << endl;
    }
    ANSWERfile.close();
}

void TwentyQuestions::Play20Questions()
{ //Calls 20 questons method - method is separate call for use by other methods if necessary.
    Run20Questions();
}

////////////////////////////////////////////////////
///Stage 2 (ADD ONs)////////////////////////////////
////////////////////////////////////////////////////

///Public

void TwentyQuestions::AddNewAnswer()
{ //Adds a new answer into program
    string newAnswer;
    //Queries user for the title of the new answer
    cout << "Enter the answer you would like to add to the program:" << endl;
    getline (cin, newAnswer);
    //Container for new answer
    Answers anotherAnswer;
    anotherAnswer.title = newAnswer;
    anotherAnswer.possible = true;
    //Stores the questions available in the new answer's question map
    for (int i = 0; i < QuestionMap.size(); i++)
    {
        Questions newQuestion;
        newQuestion.title = QuestionMap[i];
        anotherAnswer.AnsQuestVector.push_back(newQuestion);
    }
    //Generates truth table for new answer
    for (int i = 0; i < anotherAnswer.AnsQuestVector.size(); i++)
    {
        string validAnswer;
        //Loops until a valid input is entered
        while (validAnswer != "Y" && validAnswer != "y" && validAnswer != "N" && validAnswer != "n")
        {
            cout << "Does " << newAnswer << " answer this question: " << anotherAnswer.AnsQuestVector[i].title << "?" << endl;
            getline(cin, validAnswer);
        }
        //Stores specific values in truth table
        if(validAnswer == "N" || validAnswer == "n")
            anotherAnswer.AnsQuestVector[i].TF = false;
        else
            anotherAnswer.AnsQuestVector[i].TF = true;
    }
    AnswerVector.push_back(anotherAnswer);
    cout << "Answer added!" << endl;
}

void TwentyQuestions::AddNewQuestion(std::string NewQuestion)
{ //Adds new question to program
    //Stores the new question in the QuestionMap vector.
    QuestionMap.push_back(NewQuestion);
    //Container for new question to add to each answer's question map.
    Questions anotherQuestion;
    anotherQuestion.title = NewQuestion;
    anotherQuestion.TF = true;
    cout << "Now for the hard part:" << endl;
    //Adds container to each answer's question map
    for (int i = 0; i < AnswerVector.size(); i++)
        AnswerVector[i].AnsQuestVector.push_back(anotherQuestion);
    //Updates the truth table for each answer with respect to the new question
    for(int i = 0; i < AnswerVector.size(); i++)
    {
        string validAnswer;
        int ansIndex = AnswerVector[i].AnsQuestVector.size();
        //Loops until a valid answer is entered
        while (validAnswer != "Y" && validAnswer != "y" && validAnswer != "N" && validAnswer != "n")
        {
            cout << "Is answer: " << AnswerVector[i].title << " a solution to this question? " << endl;
            getline(cin, validAnswer);
        }
        //Stores response to question in answer's truth table
        if(validAnswer == "N" || validAnswer == "n")
            AnswerVector[i].AnsQuestVector[ansIndex-1].TF = false;
        else
            AnswerVector[i].AnsQuestVector[ansIndex-1].TF = true;
    }
}

int TwentyQuestions::NumPossibleAnswers()
{ //Calculates the  number of possible answers still available based on answers to questions thus far.
    //Called in play 20 questions method.
    int PossibleAnswers = 0;
    for(int i = 0; i < AnswerVector.size(); i++)
    {
        if(AnswerVector[i].possible == true)
        {
            PossibleAnswers++;
        }
    }
    return PossibleAnswers;
}

void TwentyQuestions::printPossibleAnswers()
{ //Prints out whether or not each answer is still possible.
    //Prints out possible solutions.
    cout << "The following answers are still possible:" << endl;
    for(int i = 0; i < AnswerVector.size(); i++)
    {
        if (AnswerVector[i].possible == true)
            cout << AnswerVector[i].title << endl;
    }
    //Prints out eliminated solutions.
    cout << "The following answers are no longer possible:" << endl;
    for(int i = 0; i < AnswerVector.size(); i++)
    {
        if (AnswerVector[i].possible == false)
            cout << AnswerVector[i].title << endl;
    }
}

void TwentyQuestions::printQuestions()
{ //Prints out all questions.
    cout << "The questions available are:" << endl;
    for (int i = 0; i < QuestionMap.size(); i++)
        cout << QuestionMap[i] << endl;
}

void TwentyQuestions::printTruthTable()
{ //Prints truth table for a specific answer.
  //Stores users choice.
  string searchAnswer;
  cout << "The current answers stored are:" << endl;
  //Prints out all answers stored.
  for (int i = 0; i < AnswerVector.size(); i++)
    cout << AnswerVector[i].title << endl;
  cout << "Which answer would you like to see?" << endl;
  getline (cin, searchAnswer);
  //Holds the answer the user is searching for.
  Answers foundAnswer;
  //Matches requested answer to element in the vector.
  for (int i = 0; i < AnswerVector.size(); i++)
  {
    if (AnswerVector[i].title == searchAnswer)
      foundAnswer = AnswerVector[i];
  }
  cout << "The truthTable for " << foundAnswer.title << " is:" << endl;
  //Prints out the results for each question for the selected answer
  for (int i = 0; i < foundAnswer.AnsQuestVector.size(); i++)
  {
    cout << foundAnswer.AnsQuestVector[i].title << " is: ";
    if (foundAnswer.AnsQuestVector[i].TF == 1)
        cout << "true." <<endl;
    if (foundAnswer.AnsQuestVector[i].TF == 0)
        cout << "false." <<endl;
  }
}

void TwentyQuestions::savetoFile()
{
    //Writes any added questions or answers to file
    ofstream questionFile ("answers.txt");
    if (questionFile.is_open())
    {
        questionFile << "Questions,";
        //Writes each question into the first row of the file
        for (int i = 0; i < QuestionMap.size(); i++)
        {
            questionFile << QuestionMap[i];
            questionFile << ",";
        }
        //Line break
        questionFile << '\n';
        //Writes each answer and truth table into file on subsequent lines
        for (int i = 0; i < AnswerVector.size(); i++)
        {
            //Stores the answer title
            questionFile << AnswerVector[i].title;
            questionFile << ",";
            //Stores truth table on same row as answer title
            for (int j = 0; j < AnswerVector[i].AnsQuestVector.size(); j++)
                questionFile << AnswerVector[i].AnsQuestVector[j].TF << ",";
            //Line break
            questionFile << '\n';
        }
        questionFile.close();
    }

}

///Private

string TwentyQuestions::Run20Questions()
{ //Main program which runs the "twenty" questions
    cout << "Think of a common thing that is not a proper noun, or specific person, place, or thing." << endl;
    //Null string at this time.
    string truthTable;
    int questionsAsked = 0;
    //New game, sets all answers as possible.
    for(int i = 0; i < AnswerVector.size(); i++)
    {
            AnswerVector[i].possible = true;
    }
    //Loop which runs while there are still possible answers and the number of questions asked is less than equal to the total number of questions
    while(NumPossibleAnswers() > 1 && questionsAsked < QuestionMap.size())
    {
        string TrueOrFalse;
        printPossibleAnswers();
        //Loop runs until valid answer is entered
        while (TrueOrFalse != "Y" && TrueOrFalse != "y" && TrueOrFalse != "N" && TrueOrFalse != "n")
        {
            cout << "Is it: " << QuestionMap[questionsAsked] << "? (Y/N)" << endl;
            getline(cin, TrueOrFalse);
        }
        if(TrueOrFalse == "N" || TrueOrFalse == "n")
        { //Runs if the user's answer does not match the question (a 'no').
            for(int i = 0; i < AnswerVector.size(); i++)
            {
                for(int j = 0; j < QuestionMap.size(); j++)
                {
                    //Evaluates if question title in answer vector matches title in question vector and the answer for this question is true (rather than false).
                    if(AnswerVector[i].AnsQuestVector[j].title == QuestionMap[questionsAsked] && AnswerVector[i].AnsQuestVector[j].TF == true)
                        AnswerVector[i].possible = false;
                }
            }
        }
        else
        { //Runs if the user's answer matches the question (a 'yes').
            for(int i = 0; i < AnswerVector.size(); i++)
            {
                for(int j = 0; j < QuestionMap.size(); j++)
                {
                    //Evaluates if question title in answer vector matches title in question vector and the answer to this question is false (rather than true).
                    if(AnswerVector[i].AnsQuestVector[j].title == QuestionMap[questionsAsked] && AnswerVector[i].AnsQuestVector[j].TF == false)
                        AnswerVector[i].possible = false;
                }
            }
        }
        //Increments the number of questions asked
        questionsAsked++;
    }
    cout << "We have found " << NumPossibleAnswers() << " match(es), they are:" << endl;
    for(int i = 0; i < AnswerVector.size(); i++)
    {
        if(AnswerVector[i].possible == true)
        {
            cout << AnswerVector[i].title << endl;
        }
    }
    string correct;
    //Loops until a valid entry is added
    while (correct != "Y" && correct != "y" && correct != "N" && correct != "n")
    {
        cout << "Was this the answer you expected?" << endl;
        getline (cin, correct);
    }
    //If the user's answer wasn't predicted, calls AddNewAnswer method.
    if(correct == "N" || correct == "n")
    {
        cout << "Lets add your answer!" << endl;
        AddNewAnswer();
    }
    //Null return at this time.
    return truthTable;
}
