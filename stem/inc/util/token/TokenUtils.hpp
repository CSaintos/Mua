/**
 * @brief This file is part of {{ stem.inc.util.token }}
 * 
 * @file TokenUtils.hpp
 * @author Christian Santos
 * @version 1.0.0 
 * @date 2/19/2023
*/

#pragma once

#include <unordered_map>
#include <string>

#include "TokenType.hpp"

namespace stem
{
  /**
   * @class TokenUtils
   * @brief Specifies maps to attributes of TokenType
   */
  class TokenUtils
  {
  private:
    /**
     * @brief private constructor
    */
    TokenUtils();
  public:
    /// TokenType to string map
    static std::unordered_map<TokenType, std::string> m_TS_map;
    /// Reference (string) to TokenType map
    static std::unordered_map<std::string, TokenType> m_RT_map;
  };
}
