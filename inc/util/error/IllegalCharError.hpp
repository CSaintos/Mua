/**
 * @brief This file is part of {{ stem.inc.util.error }}
 * 
 * @file IllegalCharError.hpp
 * @author Christian Santos
 * @version 1.0.0 
 * @date 2/18/2023
 */

#pragma once

#include <string>
#include <sstream>

#include "Error.hpp"
#include "Position.hpp"

namespace stem
{
  /**
   * @class IllegalCharError
   * @brief Illegal Character Error for handling char errors
   * @note typically used in the lexer
   */
  class IllegalCharError : public Error
  {
  public:
    /**
     * @brief IllegalCharError() constructor
     * @see IllegalCharError(position &pos, std::String details)
     * @see ~IllegalCharError()
     */
    IllegalCharError();
    /**
     * @brief IllegalCharError(pos, details) constructor
     * @see IllegalCharError()
     * @see ~IllegalCharError()
     */
    IllegalCharError(Position &pos, std::string details);
    /**
     * @brief ~IllegalCharError() destructor
     * @see IllegalCharError()
     * @see IllegalCharError(position &pos, std::string details)
     */
    //~IllegalCharError();
  };
}