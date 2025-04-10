#include "node_state/Percent.hpp"

using namespace std;
using namespace mua;

string Percent::to_repr()
{
  if (node_left == nullptr || node_right == nullptr)
  {
    return "%";
  }
  return node_left->to_repr() + "%" + node_right->to_repr();
}

bool Percent::interpret(const unordered_set<InterpretType> &flags)
{
  if (node_left->isLeaf() && node_right->isLeaf())
  {
    if (node_left->tok.type == TokenType::DIGIT &&
    node_right->tok.type == TokenType::DIGIT)
    {
      double lhs = std::stod(node_left->tok.lexemes);
      double rhs = std::stod(node_right->tok.lexemes);
      double result = std::fmod(lhs, rhs);

      string result_str = NumberUtils::stripTrailingZeros(std::to_string(result));

      Token res_tok;
      res_tok.lexemes = result_str;
      res_tok.type = TokenType::DIGIT;

      unique_ptr<Node> res_node = node_factory->produceNode(res_tok);

      NodeUtils::replaceNode(node, res_node);
      return true;
    }
  }
  else if (!node_left->isLeaf())
  {
    return node_left->interpret();
  }
  else if (!node_right->isLeaf())
  {
    return node_right->interpret();
  }
  return false;
}

