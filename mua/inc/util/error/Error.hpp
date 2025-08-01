#pragma once

#include <string>
#include <sstream>

#include "Position.hpp"

namespace mua
{
  /**
   * @class Error
   * @brief General Error class for handling exceptions
   */
  class Error
  {
  private:
    std::stringstream ss; ///< string builder for use in to_string()
  protected:
    Position pos; ///< position of error
    std::string err_name; ///< error name
    std::string details; ///< error details
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
    Error(Position &pos, const std::string &err_name, const std::string &details);
    
    Error(const Error& other);

    Error& operator=(const Error& err);

    /**
     * @brief Sets error position
     */
    inline void setPos(Position &pos) { this->pos = pos; }
    /**
     * @brief Sets error name
     */
    inline void setName(const std::string &name) { err_name = name; }
    /**
     * @brief Sets error details
     */
    inline void setDetails(std::string details) { this->details = details; }

    /**
     * @brief Returns Error as a string
     * 
     * @return string error representation
     */
    std::string to_string();
  };
}
