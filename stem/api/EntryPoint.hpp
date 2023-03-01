/**
 * @brief This file is part of {{ stem.api }}
 * 
 * @file EntryPoint.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 6/29/2022
 */
#pragma once

#include "Node.hpp"
#include "OpNode.hpp"

namespace stem
{
  /**
   * @class EntryPoint
   * @brief Abstract class for defining 
   * entry point in program
   */
  class EntryPoint
  {
  public:
  /// entry point for plugin
  virtual void entryPoint() = 0;
  /// evaluate operation
  virtual stem::Node *evaluate(stem::OpNode *op_node) = 0;
  };
}