#include "BinOpState.hpp"

using namespace std;
using namespace mua;

void BinOpState::extractChildData
(
  Node *in_child,
  unique_ptr<Node> &out_child,
  unique_ptr<Node> &numerator,
  unique_ptr<Node> &denominator,
  bool &is_minus,
  bool &removable_paren,
  bool &is_paren,
  const bool &is_leaf
)
{
  if (!is_leaf)
  {
    if (in_child->tok.type == TokenType::MINUS)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(in_child);
      is_minus = !is_minus;

      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        out_child = NumberUtils::fractionalize(node_factory, una_op_node->node->to_repr());
      }
    }
    else if (in_child->tok.type == TokenType::FSLASH)
    {
      BinOpNode* bin_op_node = static_cast<BinOpNode*>(in_child);
      UnaOpNode* una_op_node;

      if (bin_op_node->node_left->tok.type == TokenType::MINUS)
      {
        is_minus = !is_minus;
        una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_left.get());
        numerator = std::move(una_op_node->node);
      }
      else if (bin_op_node->node_left->tok.type == TokenType::DIGIT)
      {
        numerator = std::move(bin_op_node->node_left);
      }
      else
      {
        cout << "extractChildData() not implemented in_child's " + TokenUtils::m_TS_map[in_child->tok.type] + " node_left " + TokenUtils::m_TS_map[bin_op_node->node_left->tok.type] << endl;
      }
      if (bin_op_node->node_right->tok.type == TokenType::MINUS)
      {
        is_minus = !is_minus;
        una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_right.get());
        denominator = std::move(una_op_node->node);
      }
      else if (bin_op_node->node_right->tok.type == TokenType::DIGIT)
      {
        denominator = std::move(bin_op_node->node_right);
      }
      else
      {
        cout << "extractChildData() not implemented in_child's " + TokenUtils::m_TS_map[in_child->tok.type] + " node_right " + TokenUtils::m_TS_map[bin_op_node->node_left->tok.type] << endl;
      }
    }
    else if (in_child->tok.type == TokenType::LPAREN)
    {
      UnaOpNode *una_op_node = static_cast<UnaOpNode*>(in_child);
      is_paren = true;

      if (una_op_node->node->tok.type == TokenType::MINUS)
      {
        is_minus = !is_minus;
        una_op_node = static_cast<UnaOpNode*>(una_op_node->node.get());
      }
      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        if (tok->type != TokenType::ADJACENT)
        {
          removable_paren = true;
        }
        out_child = NumberUtils::fractionalize(node_factory, una_op_node->node->to_repr());
      }
      if (una_op_node->node->tok.type == TokenType::FSLASH)
      {
        BinOpNode* bin_op_node = static_cast<BinOpNode*>(una_op_node->node.get());

        if (bin_op_node->node_left->tok.type == TokenType::MINUS)
        {
          is_minus = !is_minus;
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_left.get());
          numerator = std::move(una_op_node->node);
        }
        else if (bin_op_node->node_left->tok.type == TokenType::DIGIT)
        {
          numerator = std::move(bin_op_node->node_left);
        }
        else
        {
          cout << "extractChildData() not implemented in_child's " + TokenUtils::m_TS_map[in_child->tok.type] + " node_left " + TokenUtils::m_TS_map[bin_op_node->node_left->tok.type] << endl;
        }
        if (bin_op_node->node_right->tok.type == TokenType::MINUS)
        {
          is_minus = !is_minus;
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_right.get());
          denominator = std::move(una_op_node->node);
        }
        else if (bin_op_node->node_right->tok.type == TokenType::DIGIT)
        {
          denominator = std::move(bin_op_node->node_right);
        }
        else
        {
          cout << "extractChildData() not implemented in_child's " + TokenUtils::m_TS_map[in_child->tok.type] + " node_right " + TokenUtils::m_TS_map[bin_op_node->node_left->tok.type] << endl;
        }
      }
    }
    else if (in_child->tok.type == TokenType::CARET)
    {
      //cout << "extractChildData() not implemented inchild " + TokenUtils::m_TS_map[in_child->tok.type] << endl;
    }
    else
    {
      cout << "extractChildData() not implemented inchild " + TokenUtils::m_TS_map[in_child->tok.type] << endl;
    }
  }
  else
  {
    if (in_child->tok.type == TokenType::DIGIT)
    {
      out_child = NumberUtils::fractionalize(node_factory, in_child->to_repr());
    }
    else
    {
      cout << "extractChildData() not implemented leaf inchild " + TokenUtils::m_TS_map[in_child->tok.type] << endl;
    }
  }
}

void BinOpState::extractNodeChildrenData
(
  unique_ptr<Node> &lhs_node,
  unique_ptr<Node> &rhs_node,
  unique_ptr<Node> &left_numerator,
  unique_ptr<Node> &left_denominator,
  unique_ptr<Node> &right_numerator,
  unique_ptr<Node> &right_denominator,
  bool &is_left_minus,
  bool &is_right_minus,
  bool &removable_right_paren,
  bool &is_lhs_paren,
  const bool &is_left_leaf,
  const bool &is_right_leaf
)
{
  is_left_minus = false;
  is_right_minus = false;
  removable_right_paren = false;
  is_lhs_paren = false;
  bool removable_left_paren = false;
  bool is_rhs_paren = false;

  // extract left child
  extractChildData
  (
    node_left,
    lhs_node,
    left_numerator,
    left_denominator,
    is_left_minus,
    removable_left_paren,
    is_lhs_paren,
    is_left_leaf
  );

  // extract right child
  extractChildData
  (
    node_right,
    rhs_node,
    right_numerator,
    right_denominator,
    is_right_minus,
    removable_right_paren,
    is_rhs_paren,
    is_right_leaf
  );
}

void BinOpState::setContext(Node *node)
{
  this->node = static_cast<BinOpNode*>(node);
  node_left = this->node->node_left.get();
  node_right = this->node->node_right.get();
  node_factory = this->node->node_factory;
  tok = &this->node->tok;
}
