#include "Interpreter.hpp"

using namespace stem;
using namespace std;

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
