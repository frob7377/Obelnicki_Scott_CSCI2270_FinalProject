#ifndef TWENTYQUESTIONS_H
#define TWENTYQUESTIONS_H
#include <string>
#include <vector>

struct Questions
{
    std::string title; //Stores each question
    bool TF; //Stores whether the answer is a potential solution for the question
};

struct Answers
{
    //The answer
    std::string title; //The answer value
    bool possible; //Flag that determines whether or not the answer is still viable based on questions
    std::vector<Questions> AnsQuestVector; //Stores whether or not each answer is a potential solutaion to each question
};

class TwentyQuestions
{
    public:
        TwentyQuestions();
        virtual ~TwentyQuestions();

        ///Stage 1 methods (neccesary for doing 20 questions)
        void ReadAnswerFile(char *fileName); // read in answer.txt file (takes first command line argument)
        void Play20Questions(); //Calls Run20Questions

        ///Stage 2 (ADD ONs)
        void AddNewAnswer(); //Adds new answer into program
        void AddNewQuestion(std::string NewQuestion); //Adds new question into program
        int NumPossibleAnswers(); //Calculates the number of answers that are still possible
        void printPossibleAnswers(); //Prints out all possible answers, also used during program
        void printQuestions(); //Prints out all questions stored in the program
        void printTruthTable(); //Prints truth table for a specified answer
        void savetoFile(); //Saves added answers and questions into file

    protected:
    private:
        std::vector<Answers> AnswerVector; //Default storage location for answer vector
        std::vector<std::string> QuestionMap; //Holds the question values
        std::string Run20Questions(); //Main method which can be called from multiple methods if necessary.
};

#endif // TWENTYQUESTIONS_H
