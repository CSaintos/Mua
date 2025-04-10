#pragma once

#include <string>
#include <unordered_set>

#include "InterpretType.hpp"
#include "Node.hpp"

namespace mua
{
  class INodeState
  {
  public:
    virtual ~INodeState() = default;

    virtual void setState(Node *node) = 0;
    virtual std::string to_repr() = 0; 
    virtual bool interpret(const std::unordered_set<InterpretType> &flags = {}) = 0;
  };
}
