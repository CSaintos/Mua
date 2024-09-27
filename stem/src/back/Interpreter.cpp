#include "Interpreter.hpp"

using namespace stem;
using namespace std;

Interpreter::Interpreter()
  : parse_trees(nullptr)
{}

void Interpreter::interpret(vector<unique_ptr<Node>>* parse_trees)
{
  this->parse_trees = parse_trees;

  for (int i = 0; i < parse_trees->size(); i++)
  {
    cout << "Interpret" << endl;
    (*parse_trees)[i]->interpret();
    cout << "Interpreted" << endl;
  }
}

