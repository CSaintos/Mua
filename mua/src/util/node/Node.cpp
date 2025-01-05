#include "Node.hpp"

using namespace std;
using namespace mua;

bool Node::isExclusiveParent()
{
  return (!isLeaf() && !hasGrandchildren());
}
