#include "Node.hpp"

bool stem::Node::isExclusiveParent()
{
  return (!isLeaf() && !hasGrandchildren());
}
