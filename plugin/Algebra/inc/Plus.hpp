/**
 * @brief This file is part of {{ stem.math.inc }}
 * 
 * @file Algebra.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 7/2/2022
 */
#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "Token.hpp"
#include "Node.hpp"
#include "EntryPoint.hpp"

#define EXPORT extern "C" __declspec(dllexport)
#define CALLTYPE __stdcall

namespace stem
{
  namespace math
  {
    class Plus final : public EntryPoint
    {
    public:
      /**
       * @brief defines entry point for the plugin
       */
      void entryPoint() override;
      /**
       * @brief for evaluating the operation
       * 
       * @param op_node op node to be evaluated
       * 
       * @return Node result
       */
      stem::Node *evaluate(stem::OpNode *op_node) override;
    };
  }
}

/// Get an instance of the derived class contained in the DLL.
CALLTYPE EXPORT std::unique_ptr<stem::EntryPoint> getObj(void);
/// Get the name of the plugin.
CALLTYPE EXPORT std::string getName(void);