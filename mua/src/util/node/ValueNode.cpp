#include "ValueNode.hpp"

using namespace mua;
using namespace std;

ValueNode::ValueNode(INodeFactory *node_factory, Token &tok_value)
{
  tok = tok_value;
  this->node_factory = node_factory;
}

unique_ptr<Node> ValueNode::copy()
{
  return node_factory->produceNode(tok);
}
