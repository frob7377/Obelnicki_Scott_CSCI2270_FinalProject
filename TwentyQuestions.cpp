#include "TwentyQuestions.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>

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
    string InfoNugget = "Blank";
    ifstream ANSWERfile;
    ANSWERfile.open(fileName); //open the file

    //int new_ranking;
    //std::string new_title = "Blank";
    //int new_year;
    //int new_quantity;

    int Yaxis = 0;
    int Xaxis = 0;
    int itemCounter = 1; // to determine which item we are on in the movie file line

    if(ANSWERfile.good())
    {
        //cout << "opened and reading the file: " << fileName << endl;
        while(getline(ANSWERfile, FileLine))
        {
            InfoNugget = "blank";

            stringstream ss(FileLine);
            while(getline(ss, InfoNugget, ','))
            {//cout << InfoNugget << endl;

                if(Yaxis == 0)
                {//read in question
                    if(Xaxis > 0)
                    {
                        QuestionMap.push_back(InfoNugget);
                    }
                }
                else
                {//read in answers
                    if(Xaxis == 0)
                    {//Make New Answer
                        //Answers *NewAnswer = new Answers;
                        Answers NewAnswer;
                        NewAnswer.title = InfoNugget;
                        NewAnswer.possible = true;
                        for(int i = 0; i < QuestionMap.size(); i++)
                        {
                            //Questions *newQuestion = new Questions;
                            Questions newQuestion;
                            newQuestion.title = QuestionMap[i];
                            newQuestion.TF = true;
                            NewAnswer.AnsQuestVector.push_back(newQuestion);
                        }
                    AnswerVector.push_back(NewAnswer);
                    }
                    else
                    {//Enter true/false for all answer's questions
                        if(InfoNugget == "1")
                        {
                            AnswerVector[Yaxis-1].AnsQuestVector[Xaxis-1].TF = true;
                        }
                        if(InfoNugget == "0")
                        {
                            AnswerVector[Yaxis-1].AnsQuestVector[Xaxis-1].TF = false;
                        }

                    }

                }
                Xaxis++;
            }
            //cout << "about to add: " << new_title << endl;
            //addMovieNode(new_ranking, new_title, new_year, new_quantity);
            Xaxis = 0;
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
{
    cout << "Think of a common thing that is not a proper noun, or spacific person/place/thing" <<endl;
    int questionsAsked = 0;
    string TrueOrFalse;

    //fresh game, all answer possible
    for(int i = 0; i < AnswerVector.size(); i++)
    {
            AnswerVector[i].possible = true;
    }

    while(NumPossibleAnswers() > 1 && questionsAsked < QuestionMap.size())
    {
        for(int i = 0; i < AnswerVector.size(); i++)
        {
            cout << "is answer: " << AnswerVector[i].title << " still possible? " << AnswerVector[i].possible << endl;
        }

        bool userInputGood = false;
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
        }

        if(TrueOrFalse == "N" || TrueOrFalse == "n")
        {// if the user answers no then any answer with
            for(int i = 0; i < AnswerVector.size(); i++)
            {
                for(int j = 0; j < QuestionMap.size(); j++)
                {
                    if(AnswerVector[i].AnsQuestVector[j].title == QuestionMap[questionsAsked])
                    {
                        //cout << "check this question: " << AnswerVector[i].AnsQuestVector[j].title << endl;
                        if(AnswerVector[i].AnsQuestVector[j].TF == true)
                        {//  we are at the correct question for this answer and it is true, then it is no a possible answer
                            cout << AnswerVector[i].title << " is not possible" << endl;
                            AnswerVector[i].possible = false;
                        }// Don't need an else
                    }
                }
            }
        }
        else
        {// if the user answers yes then any answer with
            for(int i = 0; i < AnswerVector.size(); i++)
            {
                for(int j = 0; j < QuestionMap.size(); j++)
                {
                    if(AnswerVector[i].AnsQuestVector[j].title == QuestionMap[questionsAsked])
                    {
                        //cout << "check this question: " << AnswerVector[i].AnsQuestVector[j].title << endl;
                        if(AnswerVector[i].AnsQuestVector[j].TF == false)
                        {//  we are at the correct question for this answer and it is true, then it is no a possible answer
                            cout << AnswerVector[i].title << " is not possible" << endl;
                            AnswerVector[i].possible = false;
                        }// Don't need an else
                    }
                }
            }
        }
        questionsAsked++;
    }

    cout << "we have found " << NumPossibleAnswers() << " match(s)" << endl;
    cout << "they are:" << endl;
    for(int i = 0; i < AnswerVector.size(); i++)
    {
        if(AnswerVector[i].possible == true)
        {
            cout << AnswerVector[i].title << endl;
        }
    }
    cout << "if this was not what you had in mind, feel free to add an answer in the main menu" << endl;
}

///Private
void TwentyQuestions::LoadQuestions()
{/// called from read file method

}
int TwentyQuestions::NumPossibleAnswers()
{// if this equals 1 then we have out best guess
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

bool TwentyQuestions::CheckAllAnswersForSimilarQuestion()
{// find out if all the answers are the same for one question

}
void TwentyQuestions::AddNewAnswer(std::string NewAnswer)
{
    cout << "code not writen" << endl;
}
void TwentyQuestions::AddNewQuestion(std::string NewQuestion)
{
    cout << "code not writen" << endl;
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
        cout << "is answer: " << AnswerVector[i].title << " still possible? " << AnswerVector[i].possible << endl;
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

///Private
void TwentyQuestions::addAnswer(std::string)
{

}
void TwentyQuestions::addQuestion()
{///something to think about // don't know how to add things not to end of file

}
