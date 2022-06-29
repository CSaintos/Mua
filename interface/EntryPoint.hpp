/**
 * @brief This file is part of {{ stem.interface }}
 * 
 * @file EntryPoint.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 6/29/2022
 */
#pragma once

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
  };
}