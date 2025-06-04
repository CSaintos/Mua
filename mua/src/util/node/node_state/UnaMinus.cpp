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
  unique_ptr<Node> right_numerator;
  unique_ptr<Node> right_denominator;
  bool is_minus = false; // true would make more sense

  if (!is_node_leaf)
  {
    if (child->tok.type == TokenType::MINUS)
    {
      is_minus = !is_minus;
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(child);
      res_node = std::move(una_op_node->node);
    }
    else if (child->tok.type == TokenType::LPAREN)
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
      // nullptr check along with the previews checks is not a very readable/logical solution, even though it saves lines of code.
      if (una_op_node->node != nullptr && una_op_node->node->tok.type == TokenType::FSLASH)
      {
        BinOpNode* bin_op_node = static_cast<BinOpNode*>(una_op_node->node.get());

        if (bin_op_node->node_left->tok.type == TokenType::MINUS)
        {
          is_minus = !is_minus;
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_left.get());
          right_numerator = std::move(una_op_node->node);
        }
        else if (bin_op_node->node_left->tok.type == TokenType::DIGIT)
        {
          right_numerator = std::move(bin_op_node->node_left);
        }
        else
        {
          cout << "UnaMinus extract nodes not implemented in_child's " + TokenUtils::m_TS_map[child->tok.type] + " node_left " + TokenUtils::m_TS_map[bin_op_node->node_left->tok.type] << endl;
        }
        if (bin_op_node->node_right->tok.type == TokenType::MINUS)
        {
          is_minus = !is_minus;
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_right.get());
          right_denominator = std::move(una_op_node->node);
        }
        else if (bin_op_node->node_right->tok.type == TokenType::DIGIT)
        {
          right_denominator = std::move(bin_op_node->node_right);
        }
        else
        {
          cout << "UnaMinus extract nodes not implemented in_child's " + TokenUtils::m_TS_map[child->tok.type] + " node_right " + TokenUtils::m_TS_map[bin_op_node->node_right->tok.type] << endl;
        }
      }
    }
  }
  else
  {
    if (child->tok.type == TokenType::DIGIT && flags.count(InterpretType::DECIMALIZE) == 0)
    {
      res_node = NumberUtils::fractionalize(node_factory, child->to_repr());
    }
  }

  if (res_node != nullptr)
  {
    if (res_node->isLeaf())
    {
      if (is_minus)
      {
        NodeUtils::replaceNode(node, res_node);
        change = true;
      }
      else
      {
        node->setNode(res_node); // This is vague, instead should be setChild
      }
    }
    else
    {
      if (!is_minus)
      {
        if (res_node->getType() == NodeType::BINARY_OPERATOR)
        {
          BinOpNode* bin_op_node = static_cast<BinOpNode*>(res_node.get());
          right_numerator = std::move(bin_op_node->node_left);
          right_numerator = node_factory->produceNode(TokenType::MINUS, right_numerator);
          bin_op_node->setLeftNode(right_numerator);
        }
      }

      //node->setNode(res_node);
      NodeUtils::replaceNode(node, res_node);
      change = true;
    }
  }
  else if (right_numerator != nullptr && right_denominator != nullptr)
  {
    if (!is_minus)
    {
      right_numerator = node_factory->produceNode(TokenType::MINUS, right_numerator);
    }
    res_node = node_factory->produceNode(TokenType::FSLASH, right_numerator, right_denominator);
    res_node = node_factory->produceNode(TokenType::LPAREN, res_node);

    NodeUtils::replaceNode(node, res_node);
    change = true;
  }

  return change;
}

