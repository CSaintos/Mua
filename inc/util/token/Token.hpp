/**
 * @brief This file is part of {{ stem.inc.util.token }}
 * 
 * @file Token.hpp
 * @author Christian Santos
 * @version 1.0.3 
 * @date 2/19/2023
 * 
 * @note There might be a way to implement using a hash table
 */

#pragma once

#include <string>

#include "Position.hpp"
#include "TokenType.hpp"
#include "TokenUtils.hpp"

namespace stem
{
  /**
   * @struct token
   * @brief Token struct 
   * - token type
   * - token lexemes (string)
   * - token position
   */
  struct Token
  {
    TokenType m_type; ///< token type
    std::string m_lexemes; ///< token lexemes or string
    Position m_pos; ///< token position

    /**
     * @brief token() constructor
     * @see init()
     */
    Token();

    /**
     * @brief Token(const Token &tok) copy constructor
     * @see Token()
     */
    Token(const Token &tok);

    /**
     * @brief Re-initializes 'this' token
     */
    void init();

    /**
     * @brief Returns token as string
     * 
     * @return string token representation
     */
    std::string to_string();
  };
}