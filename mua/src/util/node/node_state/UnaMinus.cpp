#include "node_state/UnaMinus.hpp"

using namespace std;
using namespace mua;

string UnaMinus::to_repr()
{
  return "-" + child->to_repr();
}

bool UnaMinus::interpret(const unordered_set<InterpretType> &flags)
{
  bool change = false;
  bool is_node_leaf = true;

  if (!child->isLeaf())
  {
    change = child->interpret(flags);
    is_node_leaf = false;
  }
  if (change) return true;

  unique_ptr<Node> res_node;
  bool is_minus = false;

  if (!is_node_leaf)
  {
    if (child->tok.type == TokenType::MINUS)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(child);
      res_node = std::move(una_op_node->node);
      NodeUtils::replaceNode(node, res_node);
      change = true;
    }
    else if (child->tok.type == TokenType::LPAREN)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(child);

      if (una_op_node->node->tok.type == TokenType::MINUS)
      {
        una_op_node = static_cast<UnaOpNode*>(una_op_node->node.get());
        is_minus = true;
      }
      res_node = std::move(una_op_node->node);
      if (!is_minus)
      {
        res_node = node_factory->produceNode(TokenType::MINUS, res_node);
      }
      NodeUtils::replaceNode(node, res_node);
      change = true;
    }
  }
  return change;
}

