#include "Node.hpp"

using namespace std;
using namespace stem;

bool Node::isExclusiveParent()
{
  return (!isLeaf() && !hasGrandchildren());
}
