#include "Final_Project.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

DecisionTree::DecisionTree()
{
  root = new DecisionNode();
  //Since each node is a different question category, the root node is NULL.
}

DecisionTree::~DecisionTree()
{

}

void DecisionTree::addDecisionNode(string field, DecisionNode *current, string child)
{
  DecisionNode *temp = new DecisionNode;
  temp.category = field;
  if (child == "0") //Checks to see if node is left child
  {
    temp->parent = current;
    current->leftChild = temp;
  }
  else //New node is right child
  {
    temp->parent = current;
    current->rightChild = temp;
  }
  temp.key = child; //Sets the final value in the key
  while (current->parent != NULL)
  { //iterates through tree to generate key for position in tree
    if (current == current->parent->leftChild)
      temp.key.insert(0, "0");
    else
      temp.key.insert(0, "1");
    current = current->parent;
  }
}

void DecisionTree::buildDecisionTree(string field, string code)
{
  DecisionNode *current = root;
  DecisionNode *temp = new DecisionNode(field, code);
  for (int i = 0; i < code.size(); i++)
  { //Loop iterates through tree to question location.
    //Will require building the tree in order and storing the text file in the same order.
    if (current->leftChild != NULL and temp.key[i] == "0")
      current = current->leftChild;
    else if (current->leftChild == NULL and temp.key[i] == "0")
    {
      temp = current->leftChild;
      temp->parent = current;
    }
    if (current->rightChild!= NULL and temp.key[i] == "1")
      current = current->rightChild;
    else if (current->rightChild == NULL and temp.key[i] == "1")
    {
      temp = current->rightChild;
      temp->parent = current;
    }
  }
}

void DecisionTree::bulkSolutionAdd(string sol, string code)
{
  DecisionNode *current = root;
  for (int i = 0; i < code.size(); i++)
  { //Loop iterates through tree to solution location.
    if (temp.key[i] == "0")
      current = current->leftChild;
    if (current->rightChild!= NULL and temp.key[i] == "1")
      current = current->rightChild;
  }
  current->solutions.push_back(sol);
  current->solCount++;
}

void DecisionTree::shortestPath(string sol)
{

}

DecisionNode* DecisionTree::searchSolutions(DecisionNode *current, string target)
{

}

DecisionNode* DecisionTree::searchTree(DecisionNode *current, string target)
{ //TODO Returning a decision node wont work here - since every iteration has to return
  //a value. Figure something else out. Maybe another method that can iterate through?
  //Same issue... Also, when is this going to be used?
  if (current->category != target)
  { //If current is not the target node, each child is checked.
    if (current->leftChild->category == target)
      return current->leftChild;
    else if (current->rightChild->category == target)
      return current->rightChild;
    else
    { //Recursively checks each of currents children until the node is found.
      if (current->leftChild != NULL)
        searchTree(current->leftChild);
      if (current->rightChild != NULL)
        searchTree(current->rightChild);
    }
  }
  else //Current is the target node.
    return current;
  cout << "No node found." << endl;
  return root;
}

void DecisionTree::addSolution(string sol, DecisionNode *current)
{
  bool stored = false;
  for (int i = 0; i < current->solutions.size(); i++)
  { //Verifies solution has not already been added to node's tree.
    int found = 0;
    if (current->solutions[i] == sol)
    {
      cout << "Solution already stored." << endl;
      stored == true;
    }
    else //Checks if match is close. i.e. Deer Mouse vs. Mouse
    {
      found = sol.find(current->solutions[i]);
      if (found != 0)
      {
        cout << "Solution or equivalent already stored." << endl;
        stored == true;
      }
    }
  }
  if (stored == false)
  {
    current->solutions.push_back(sol);
    current->solCount++;
  }
}
