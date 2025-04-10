#include "UnaOpState.hpp"

using namespace std;
using namespace mua;

void UnaOpState::setState(Node *node)
{
  this->node = static_cast<UnaOpNode*>(node);
  child = this->node->node.get();
  node_factory = this->node->node_factory;
  tok = &this->node->tok;
}
