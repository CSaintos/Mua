#include "NodeUtils.hpp"

using namespace std;
using namespace mua;

void NodeUtils::replaceNode(Node* to_replace, unique_ptr<Node> &replace_with)
{
  if (to_replace->parent->getType() == NodeType::BINARY_OPERATOR)
  {
    BinOpNode* parent = static_cast<BinOpNode*>(to_replace->parent);
    if (parent->node_left.get() == to_replace)
    {
      parent->setLeftNode(replace_with);
    }
    else if (parent->node_right.get() == to_replace)
    {
      parent->setRightNode(replace_with);
    }
    else
    {
      cout << "Node pointers don't match the node to be replaced" << endl;
    }
  }
  else if (to_replace->parent->getType() == NodeType::UNARY_OPERATOR)
  {
    UnaOpNode* parent = static_cast<UnaOpNode*>(to_replace->parent);
    parent->setNode(replace_with);
  }
}
