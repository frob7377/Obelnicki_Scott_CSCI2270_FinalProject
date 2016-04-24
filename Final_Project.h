#ifndef FINAL_PROJECT_H
#define FINAL_PROJECT_H
#include <vector>


struct DecisionNode
{
  std::string category;
  DecisionTree *parent;
  DecisionTree *leftChild;
  DecisionTree *rightChild;
  vector <std::string> solutions;
  //int leftCounter; //Counts the number of times the left node is selected
  //int rightCounter; //Counts the number of times the right node is selected
  int solCount; //Counts the number of solutions stored in this node
  std::string key;

  DecisionNode()
  {
    parent = NULL;
    leftChild = NULL;
    rightChild = NULL;
    solCount = 0;
  };

  DecisionNode(std::string in_cat, std::string in_key)
  {
    category = in_cat;
    parent = NULL;
    leftChild = NULL;
    rightChild = NULL;
    //leftCounter = 0; TODO determine if these are necessary
    //rightCounter = 0;
    key = in_key;
    solCount = 0;
  };
}

class DecisionTree
{
  //TODO Define parameters for these functions. DeleteTree function?
  public:
    DecisionTree();
    ~DecisionTree();
    void addDecisionNode(std::string, DecisionNode, std::string);
    void buildDecisionTree(std::string, std:: string);
    void bulkSolutionAdd(std::string, std::string);
    void countSolutions(); //Recursive loop that provides a total count of solutions
    void deleteTree();
    void printQuestions();
    void run20Questions();
    void printSolutions();
    void shortestPath(std::string);
    //void balanceTree(); REVIEW can probably remove this. Will most likely be too technically challenging.
  protected:
  private:
    DecisionNode *root;
    DecisionNode searchSolutions(DecisionNode, std::string);
    DecisionNode searchTree(DecisionNode, std::string);
    void addSolution(std::string, DecisionNode);
    void leftRottate(); //REVIEW can probably remove
    void rightRotate(); //REVIEW can probably remove
    void maxHeightCheck(); //Makes sure that we don't ask more than 20 questions
}

#endif //FINAL_PROJECT_H
