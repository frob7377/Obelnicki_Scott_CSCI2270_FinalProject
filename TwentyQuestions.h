#ifndef TWENTYQUESTIONS_H
#define TWENTYQUESTIONS_H
#include <iostream>
#include <string>
#include <vector>

struct Questions
{
    std::string title;
    bool TF;
};

struct Answers
{
    //The answer
    std::string title; /// mouse, cat, elephant, plane, boat, etc.
    bool possible; /// possible is false when one of its questions is contrary to using input

    //The questions
    //vector<bool> questions; ///vector of true/false (if we do it this way we have to keep track of where all the questions are)
    std::vector<Questions> AnsQuestVector;
};

class TwentyQuestions
{
    public:
        TwentyQuestions();
        virtual ~TwentyQuestions();

        ///Stage 1 methods (neccesary for doing 20 questions)
        void ReadAnswerFile(char *fileName); /// read in answer.txt file (takes first command line argument)
        void Play20Questions();

        ///Stage 2 (ADD ONs)
        int NumPossibleAnswers(); // if this equals 1 then we have out best guess
        bool CheckAllAnswersForSimilarQuestion(); // find out if all the answers are the same for one question
        void AddNewAnswer(std::string NewAnswer);
        void AddNewQuestion(std::string NewQuestion);
        void printPossibleAnswers();

    protected:
    private:
        ///STAGE 1
        void LoadQuestions(); /// called from read file method
        std::vector<Answers> AnswerVector; ///class bin of answers
        std::vector<std::string> QuestionMap; ///could hold a list of all questions here, it would be a map of their location a blueprint

        ///STAGE 2 (not essential for 20 questions to happen)
        void addAnswer(std::string);
        void addQuestion(); ///something to think about // don't know how to add things not to end of file

        //could make a list and then delete nodes from it as we eliminated questions
        //could put all possible anwers into a vector and then redue vector as new info is aquired.
};

#endif // TWENTYQUESTIONS_H
