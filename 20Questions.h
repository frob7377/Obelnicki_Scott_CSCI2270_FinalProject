#ifndef T20QUESTIONS_H
#define T20QUESTIONS_H

struct Questions
{
    std::string title;
    bool TF;
};

struct answers
{
    //The answer
    std::string title; /// mouse, cat, elephant, plane, boat, etc.
    bool possible; /// possible is false when one of its questions is contrary to using input

    //The questions
    vector<bool> questions; ///vector of true/false (if we do it this way we have to keep track of where all the questions are)
    vector<Questions>
};

class T20Questions
{
    public:
        T20Questions();
        virtual ~T20Questions();

        ///Stage 1 methods (neccesary for doing 20 questions)
        void ReadAnswerFile(char fileName); /// read in answer.txt file (takes first command line argument)
        void Play20Questions();
        int NumPossibleAnswers(); // if this equals 1 then we have out best guess
        bool CheckAllAnswersForSimilarQuestion(); // find out if all the answers are the same for one question

        ///Stage 2 (ADD ONs)
        void AddNewAnswer();
        void printPossibleAnswers();

    protected:
    private:
        ///STAGE 1
        void LoadQuestions(); /// called from read file method
        vector<answers>; ///class bin of answers
        vector<string>; ///could hold a list of all questions here, it would be a map of their location a blueprint

        ///STAGE 2 (not essential for 20 questions to happen)
        void addAnswer(std::string);
        void addQuestion(); ///something to think about // don't know how to add things not to end of file

        //could make a list and then delete nodes from it as we eliminated questions
        //could put all possible anwers into a vector and then redue vector as new info is aquired.
};

#endif // T20QUESTIONS_H
