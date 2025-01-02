#include "Interpreter.hpp"

using namespace stem;
using namespace std;

Interpreter::Interpreter()
  //: parse_trees(nullptr)
{}

//void Interpreter::interpret(vector<unique_ptr<Node>>* parse_trees)
//{
  //this->parse_trees = parse_trees;

  //for (int i = 0; i < parse_trees->size(); i++)
  //{
    //unique_ptr<Node>& parse_tree = (*parse_trees)[i];
    // DEBUG
    //cout << parse_tree->to_string() << endl;
    //bool change = false;
    //do {
      //change = parse_tree->interpret();
      //if (change)
      //{
        // DEBUG
        //cout << parse_tree->to_string() << endl;
      //}
    //} while (change);
    //do
    //{
      //change = parse_tree->interpret({InterpretType::DECIMALIZE});
      //if (change)
      //{
        // DEBUG
        //cout << parse_tree->to_string() << endl;
      //}
    //} while (change);
    
    // DEBUG
    //cout << endl;
  //}
//}

vector<string> Interpreter::interpret(unique_ptr<Node>& parse_tree, bool is_debug)
{

  vector<string> parsed_strs;
  if (is_debug) cout << parse_tree->to_string() << endl;
  parsed_strs.push_back(parse_tree->to_repr());
  bool change = false;
  do {
    change = parse_tree->interpret();
    if (change)
    {
      if (is_debug) cout << parse_tree->to_string() << endl;
      parsed_strs.push_back(parse_tree->to_repr());
    }
  } while (change);
  do {
    change = parse_tree->interpret({InterpretType::DECIMALIZE});
    if (change)
    {
      if (is_debug) cout << parse_tree->to_string() << endl;
      parsed_strs.push_back(parse_tree->to_repr());
    }

  } while (change);
  if (is_debug) cout << endl;
  parsed_strs.push_back("");

  return parsed_strs;
}
