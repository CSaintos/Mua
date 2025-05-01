#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_set>

#include "Node.hpp"
#include "InterpretType.hpp"

namespace mua
{
  class Interpreter
  {
  private:
    Interpreter();
  public:
    static std::vector<std::string> interpret(std::unique_ptr<Node>& parse_tree, bool is_debug);
  };
}
