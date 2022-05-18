/**
 * @brief This file is part of {{ stem.inc.util }}
 * 
 * @file Error.hpp
 * @author Christian Santos
 * @version 1.0.1 5/17/2022
 */

#pragma once

#include <string>
#include <sstream>

#include "Position.hpp"

namespace stem
{
  /**
   * @class Error
   * @brief General Error class for handling exceptions
   */
  class Error
  {
  private:
    std::stringstream m_ss; ///< string builder for use in to_string()
  protected:
    Position m_pos; ///< position of error
    std::string m_err_name; ///< error name
    std::string m_details; ///< error details
  public:
    /**
     * @brief Error() constructor
     * @see Error(position pos, std::string err_name, std::string details)
     * @see ~Error()
     */
    Error();
    /**
     * @brief Error(pos, err_name, details) constructor
     * @see Error()
     * @see ~Error()
     */
    Error(Position pos, std::string err_name, std::string details);
    /**
     * @brief ~Error() destructor
     * @see Error()
     * @see Error(position pos, std::string err_name, std::string details)
     */
    ~Error();

    /**
     * @brief Returns Error as a string
     * 
     * @return string error representation
     */
    std::string to_string();
  };

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
     * @see IllegalCharError(position pos, std::String details)
     * @see ~IllegalCharError()
     */
    IllegalCharError();
    /**
     * @brief IllegalCharError(pos, details) constructor
     * @see IllegalCharError()
     * @see ~IllegalCharError()
     */
    IllegalCharError(Position pos, std::string details);
    /**
     * @brief ~IllegalCharError() destructor
     * @see IllegalCharError()
     * @see IllegalCharError(position pos, std::string details)
     */
    ~IllegalCharError();
  };
}