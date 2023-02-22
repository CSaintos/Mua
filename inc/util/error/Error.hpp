/**
 * @brief This file is part of {{ stem.inc.util.error }}
 * 
 * @file Error.hpp
 * @author Christian Santos
 * @version 1.0.3  
 * @date 2/18/2023
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
     * @see Error(position &pos, std::string err_name, std::string &details)
     * @see ~Error()
     */
    Error();
    /**
     * @brief Error(pos, err_name, details) constructor
     * @see Error()
     * @see ~Error()
     */
    Error(Position &pos, const std::string &err_name, std::string &details);
    /**
     * @brief ~Error() destructor
     * @see Error()
     * @see Error(position &pos, std::string err_name, std::string &details)
     */
    //~Error();

    /**
     * @brief Sets error position
     */
    inline void setPos(Position &pos) { m_pos = pos; }
    /**
     * @brief Sets error name
     */
    inline void setName(const std::string &name) { m_err_name = name; }
    /**
     * @brief Sets error details
     */
    inline void setDetails(std::string details) { m_details = details; }

    /**
     * @brief Returns Error as a string
     * 
     * @return string error representation
     */
    std::string to_string();
  };
}
