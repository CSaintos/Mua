#include "BinOpState.hpp"

using namespace std;
using namespace mua;

void BinOpState::setState(Node *node)
{
  this->node = static_cast<BinOpNode*>(node);
  node_left = this->node->node_left.get();
  node_right = this->node->node_right.get();
  node_factory = this->node->node_factory;
  tok = &this->node->tok;
}
