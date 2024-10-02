/**
 * @file Interpreter.hpp 
 * @author Christian Santos
 * @version 1.1.1
 * @date 10/1/2024
 */

#pragma once

#include <vector>
#include <memory>
#include "Node.hpp"

namespace stem
{
  class Interpreter
  {
  private:
    std::vector<std::unique_ptr<stem::Node>>* parse_trees;
  public:
    Interpreter();

    void interpret(std::vector<std::unique_ptr<stem::Node>>* parse_trees);  
  };
}
