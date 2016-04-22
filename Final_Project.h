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
  int counter; //Counts the number of times the node is utilized.

  DecisionTree(){};

  DecisionTree(string in_cat)
  {
    category = in_cat;
    parent = NULL;
    leftChild = NULL;
    rightChild = NULL;
  }
}

class DecisionTree
{
  public:
    DecisionTree();
    ~DecisionTree();
    void balanceTree();
    void addDecisionNode();
    void addSolution();
    void shortestPath();
    void countSolutions(); //Recursive loop that provides a total count of solutions
    void printSolutions();
    void printQuestions();
  protected:
  private:
    DecisionNode *root;
    DecisionNode searchTree();
    void leftRottate();
    void rightRotate();
    void maxHeightCheck(); //Makes sure that we don't ask more than 20 questions
}
