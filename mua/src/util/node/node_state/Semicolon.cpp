#include "node_state/Semicolon.hpp"

using namespace std;
using namespace mua;

string Semicolon::to_repr()
{
  return child->to_repr() + ";";
}

bool Semicolon::interpret(const unordered_set<InterpretType> &flags)
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
  unique_ptr<Node> left_numerator;
  unique_ptr<Node> left_denominator;
  bool is_minus = false;

  if (!is_node_leaf)
  {
    if (child->tok.type == TokenType::LPAREN)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(child);

      if (una_op_node->node->tok.type == TokenType::MINUS)
      {
        is_minus = !is_minus;
        una_op_node = static_cast<UnaOpNode*>(una_op_node->node.get());
      }
      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        res_node = std::move(una_op_node->node);
      }
      if (una_op_node->node->tok.type == TokenType::FSLASH)
      {
        BinOpNode* bin_op_node = static_cast<BinOpNode*>(una_op_node->node.get());

        if (bin_op_node->node_left->tok.type == TokenType::MINUS)
        {
          is_minus = !is_minus;
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_left.get());
          left_numerator = std::move(una_op_node->node);
        }
        else if (bin_op_node->node_left->tok.type == TokenType::DIGIT)
        {
          left_numerator = std::move(bin_op_node->node_left);
        }
        else
        {
          cout << "Semicolon extract nodes not implemented in_child's " + TokenUtils::m_TS_map[child->tok.type] + " node_left " + TokenUtils::m_TS_map[bin_op_node->node_left->tok.type] << endl;
        }
        if (bin_op_node->node_right->tok.type == TokenType::MINUS)
        {
          is_minus = !is_minus;
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_right.get());
          left_denominator = std::move(una_op_node->node);
        }
        else if (bin_op_node->node_right->tok.type == TokenType::DIGIT)
        {
          left_denominator = std::move(bin_op_node->node_right);
        }
        else
        {
          cout << "Semicolon extract nodes not implemented in_child's " + TokenUtils::m_TS_map[child->tok.type] + " node_right " + TokenUtils::m_TS_map[bin_op_node->node_right->tok.type] << endl;
        }
      }
    }
  }

  if (res_node != nullptr)
  {
    if (res_node->isLeaf())
    {
      if (is_minus)
      {
        res_node = node_factory->produceNode(TokenType::MINUS, res_node);
      }

      node->setNode(res_node);
    }
    else
    {
      cout << "Semicolon, not implemented yet where res_node->isLeaf() == false" << endl;
    }
    change = true;
  }
  else if (left_numerator != nullptr && left_denominator != nullptr)
  {
    if (is_minus)
    {
      left_numerator = node_factory->produceNode(TokenType::MINUS, left_numerator);
    }
    res_node = node_factory->produceNode(TokenType::FSLASH, left_numerator, left_denominator);
    
    node->setNode(res_node);
    change = true;
  }

  return change;
}
