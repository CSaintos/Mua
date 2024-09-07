/**
 * @file stem/inc/front/Definer.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 9/7/2024
 */

#pragma once

#include <memory>

#include "Node.hpp"

namespace stem
{
  class Definer
  {
  private:
  public:
    Definer();
    /*
     * @brief analyzes parse tree to append to symbol table and modify tree accordingly
     *
     * @param root node of parse tree to analyze
     */
    void define(std::unique_ptr<stem::Node>& root);
    void getSymbolTable();
  };
}
