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
void TwentyQuestions::ReadAnswerFile(char *fileName)
{
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

////////////////////////////////////////////////////
///Stage 2 (ADD ONs)////////////////////////////////
////////////////////////////////////////////////////

///Public

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

    for(int i = 0; i < AnswerVector.size(); i++)
    {
        string validAnswer;
        int ansIndex = AnswerVector[i].AnsQuestVector.size();
        while (validAnswer != "Y" && validAnswer != "y" && validAnswer != "N" && validAnswer != "n")
        {
            cout << "Is answer: " << AnswerVector[i].title << " a solution to this question? " << endl;
            getline(cin, validAnswer);
        }
        if(validAnswer == "N" || validAnswer == "n")
            AnswerVector[i].AnsQuestVector[ansIndex-1].TF = false;
        else
            AnswerVector[i].AnsQuestVector[ansIndex-1].TF = true;
    }
}

void TwentyQuestions::savetoFile()
{
    ofstream questionFile ("answers.txt");
    if (questionFile.is_open())
    {
        questionFile << "Questions,";
        for (int i = 0; i < QuestionMap.size(); i++)
        {
            questionFile << QuestionMap[i];
            questionFile << ",";
        }
        questionFile << '\n';
        for (int i = 0; i < AnswerVector.size(); i++)
        {
            questionFile << AnswerVector[i].title;
            questionFile << ",";
            for (int j = 0; j < AnswerVector[i].AnsQuestVector.size(); j++)
            {
                /*if (AnswerVector[i].AnsQuestVector[j].TF = true)
                    questionFile << "1,";
                if (AnswerVector[i].AnsQuestVector[j].TF = false)
                    questionFile << "0,";*/
                questionFile << AnswerVector[i].AnsQuestVector[j].TF << ",";
            }
            questionFile << '\n';
        }
        questionFile.close();
    }

}

void TwentyQuestions::printPossibleAnswers()
{
    /*
    cout << "here are the questions(from QuestionMap): " << endl;
    for(int i = 0; i < QuestionMap.size(); i++)
    {
        cout << QuestionMap[i] << endl;
    }

    cout << "here are the answer titles: " << endl;
    for(int i = 0; i < AnswerVector.size(); i++)
    {
        cout << AnswerVector[i].title << endl;
    }
    */
    for(int i = 0; i < AnswerVector.size(); i++)
    {
        cout << "Is answer: " << AnswerVector[i].title << " still possible? " << AnswerVector[i].possible << endl;
    }
/*
///Prints All Info Storied (exept if an answer is still possible)
    for(int i = 0; i < AnswerVector.size(); i++)
    {
        cout << "here are the question titles from answer: " << AnswerVector[i].title << endl;
        for(int j = 0; j < QuestionMap.size(); j++)
        {
            cout << AnswerVector[i].AnsQuestVector[j].title << endl;
            cout << "the answer to that question is (1 true/0 false): " << AnswerVector[i].AnsQuestVector[j].TF << endl;
        }
*/
}

void TwentyQuestions::AddNewAnswer()
{
    string truthTable, newAnswer;
    cout << "Enter the answer you would like to add to the program:" << endl;
    getline (cin, newAnswer);
    Answers anotherAnswer;
    anotherAnswer.title = newAnswer;
    anotherAnswer.possible = true;
    for (int i = 0; i < QuestionMap.size(); i++)
    {
        Questions newQuestion;
        newQuestion.title = QuestionMap[i];
        anotherAnswer.AnsQuestVector.push_back(newQuestion);
    }
    for (int i = 0; i < anotherAnswer.AnsQuestVector.size(); i++)
    {
        string validAnswer;
        while (validAnswer != "Y" && validAnswer != "y" && validAnswer != "N" && validAnswer != "n")
        {
            cout << "Does " << newAnswer << " answer this question: " << anotherAnswer.AnsQuestVector[i].title << "?" << endl;
            getline(cin, validAnswer);
        }
        if(validAnswer == "N" || validAnswer == "n")
            anotherAnswer.AnsQuestVector[i].TF = false;
        else
            anotherAnswer.AnsQuestVector[i].TF = true;
    }
    AnswerVector.push_back(anotherAnswer);
    cout << "Answer added!" << endl;
}

///Private

/*void TwentyQuestions::addQuestion()
{///something to think about // don't know how to add things not to end of file

}*/

string TwentyQuestions::Run20Questions()
{
    cout << "Think of a common thing that is not a proper noun, or specific person, place, or thing." << endl;
    string truthTable;
    int questionsAsked = 0;
    //fresh game, all answers possible
    for(int i = 0; i < AnswerVector.size(); i++)
    {
            AnswerVector[i].possible = true;
    }
    while(NumPossibleAnswers() > 1 && questionsAsked < QuestionMap.size())
    {
        string TrueOrFalse;
        for(int i = 0; i < AnswerVector.size(); i++)
        {
            cout << "is answer: " << AnswerVector[i].title << " still possible? " << AnswerVector[i].possible << endl;
        }
        /*bool userInputGood = false;
        while(!userInputGood)
        {
            cout << "is it: " << QuestionMap[questionsAsked] << "? (Y/N)" << endl;

            getline(cin, TrueOrFalse);
            if(TrueOrFalse == "Y" || TrueOrFalse == "y" || TrueOrFalse == "N" || TrueOrFalse == "n")
            {
                userInputGood = true;
            }
            else
            {
                cout << "please enter a Y or N" << endl;
            }
        }*/
        while (TrueOrFalse != "Y" && TrueOrFalse != "y" && TrueOrFalse != "N" && TrueOrFalse != "n")
        {
            cout << "is it: " << QuestionMap[questionsAsked] << "? (Y/N)" << endl;
            getline(cin, TrueOrFalse);
        }
        if(TrueOrFalse == "N" || TrueOrFalse == "n")
        {// if the user answers no then any answer with
            //truthTable.push_back('0');
            for(int i = 0; i < AnswerVector.size(); i++)
            {
                for(int j = 0; j < QuestionMap.size(); j++)
                {
                    if(AnswerVector[i].AnsQuestVector[j].title == QuestionMap[questionsAsked] && AnswerVector[i].AnsQuestVector[j].TF == true)
                    {
                        cout << AnswerVector[i].title << " is not possible" << endl;
                        AnswerVector[i].possible = false;
                        //cout << "check this question: " << AnswerVector[i].AnsQuestVector[j].title << endl;
                        /*if(AnswerVector[i].AnsQuestVector[j].TF == true)
                        {//  we are at the correct question for this answer and it is true, then it is not a possible answer
                            cout << AnswerVector[i].title << " is not possible" << endl;
                            AnswerVector[i].possible = false;
                        }// Don't need an else*/
                    }
                }
            }
        }
        else
        {// if the user answers yes then any answer with
            //truthTable.push_back('1');
            for(int i = 0; i < AnswerVector.size(); i++)
            {
                for(int j = 0; j < QuestionMap.size(); j++)
                {
                    if(AnswerVector[i].AnsQuestVector[j].title == QuestionMap[questionsAsked] && AnswerVector[i].AnsQuestVector[j].TF == false)
                    {
                        cout << AnswerVector[i].title << " is not possible" << endl;
                        AnswerVector[i].possible = false;
                        //cout << "check this question: " << AnswerVector[i].AnsQuestVector[j].title << endl;
                        /*if(AnswerVector[i].AnsQuestVector[j].TF == false)
                        {//  we are at the correct question for this answer and it is true, then it is no a possible answer
                            cout << AnswerVector[i].title << " is not possible" << endl;
                            AnswerVector[i].possible = false;
                        }// Don't need an else*/
                    }
                }
            }
        }
        questionsAsked++;
    }
    cout << "We have found " << NumPossibleAnswers() << " match(s)," << endl;
    cout << "they are:" << endl;
    for(int i = 0; i < AnswerVector.size(); i++)
    {
        if(AnswerVector[i].possible == true)
        {
            cout << AnswerVector[i].title << endl;
        }
    }
    cout << "If this was not what you had in mind, feel free to add an answer in the main menu." << endl;
    return truthTable;
}
