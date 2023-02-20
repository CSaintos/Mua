/**
 * @brief This file is part of {{ stem.inc.util.error }}
 * 
 * @file SyntaxError.hpp
 * @author Christian Santos
 * @version 1.0.0 2/18/2023
*/

#pragma once

#include <string> 
#include <sstream>

#include "Error.hpp"
#include "Position.hpp"

namespace stem
{
  /**
   * @class SyntaxError
   * @brief for handling syntax errors
   * @note typically used in parser or semanticizer
   */
  class SyntaxError : public Error
  {
  public:
    /**
     * @brief SyntaxError() constructor
     * @see SyntaxError(Position &pos, std::string &details)
     */
    SyntaxError();
    /**
     * @brief SyntaxError(pos, details) constructor
     * @see SyntaxError()
     */
    SyntaxError(Position &pos, std::string details);
  };
}