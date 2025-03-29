#include "UnaMinus.hpp"

using namespace std;
using namespace mua;

UnaMinus::UnaMinus(INodeFactory *node_factory, Token &tok_op)
  : UnaOpNode(tok_op)
{
  this->node_factory = node_factory;
}

UnaMinus::UnaMinus(unique_ptr<Node> &node_op, unique_ptr<Node> &node)
  : UnaOpNode(node_op, node)
{}

UnaMinus::UnaMinus(INodeFactory *node_factory, Token &tok_op, unique_ptr<Node> &node)
  : UnaOpNode(tok_op, node)
{
  this->node_factory = node_factory;
}

string UnaMinus::to_repr()
{
  return "-" + node->to_repr();
}

bool UnaMinus::interpret(const unordered_set<InterpretType> &flags)
{
  bool change = false;
  bool is_node_leaf = true;

  if (!node->isLeaf())
  {
    change = node->interpret(flags);
    is_node_leaf = false;
  }
  if (change) return true;

  unique_ptr<Node> res_node;
  bool is_minus = false;

  if (!is_node_leaf)
  {
    if (node->tok.type == TokenType::MINUS)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node.get());
      res_node = std::move(una_op_node->node);
      NodeUtils::replaceNode(this, res_node);
      change = true;
    }
    else if (node->tok.type == TokenType::LPAREN)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node.get());

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
      NodeUtils::replaceNode(this, res_node);
      change = true;
    }
  }
  return change;
}

unique_ptr<Node> UnaMinus::copy()
{
  unique_ptr<Node> node_copy = node->copy();
  return node_factory->produceNode(tok, node_copy);
}
