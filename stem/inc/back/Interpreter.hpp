/**
 * @file Interpreter.hpp 
 * @author Christian Santos
 * @version 1.1.2
 * @date 1/2/2025
 */

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_set>

#include "Node.hpp"
#include "InterpretType.hpp"

namespace stem
{
  class Interpreter
  {
  private:
    //std::vector<std::unique_ptr<stem::Node>>* parse_trees;
    Interpreter();
  public:

    //void interpret(std::vector<std::unique_ptr<stem::Node>>* parse_trees);  
    static std::vector<std::string> interpret(std::unique_ptr<Node>& parse_tree, bool is_debug);
  };
}
