/**
 * @brief This file is part of {{ stem.math.inc }}
 * 
 * @file Algebra.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 6/29/2022
 */

#pragma once

#include <iostream>

#include "EntryPoint.hpp"

#define EXPORT extern "C" __declspec(dllexport)
#define CALLTYPE __stdcall

namespace stem
{
  namespace math
  {
    class Algebra final : public EntryPoint
    {
    public:
      /**
       * @brief defines entry point for the plugin
       */
      void entryPoint() override;
    private:
      /**
       * @brief Algebra() constructor
       */
      Algebra();
    };
  }
}