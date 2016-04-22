#ifndef 20QUESTIONS_H
#define 20QUESTIONS_H

struct answers
{
    //The answer
    std:string title;
    //linked list
    answers *next;
    answers *previous;
    //The questions
    bool Q01; //is it alive
    bool Q02; //is it bigger then a bread box
    bool Q03; //does it have fir
    bool Q03; //does it have gills
    bool Q04; //does it have
    bool Q05;
    bool Q06;
    bool Q07;
    bool Q08;
    bool Q09;
    bool Q10;
    bool Q11;
    bool Q12;
    bool Q13;
    bool Q14;
    bool Q15;
    bool Q16;
    bool Q17;
    bool Q18;
    bool Q19;
    bool Q20;
};

class 20Questions
{
    public:
        20Questions();
        virtual ~20Questions();

        void readInLinkedList();
        void printPossibleAnswers(vector<answers>);
        int NumPossibleAnswers(); // if this equals 1 then we have out best guess
        void deleteAllNodes();
        void AddNewAnswer(); // add a new answer to the text file
        bool CheckAllAnswersForSame(bool Question); // find out if all the answers are the same for one question

    protected:
    private:
        void addAnswer(std::string);
        void addQuestion(); //currently not possible
        vector<answers> seach(vector<answers>, bool); //to look at all answers in current vector for a spacific bool
        deleteNode();
        answers *head;
        answers *tail;

        //could make a list and then delete nodes from it as we eliminated questions
        //could put all possible anwers into a vector and then redue vector as new info is aquired.
};

#endif // 20QUESTIONS_H
