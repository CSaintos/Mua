#pragma once

#include <string>

#include "Position.hpp"
#include "TokenType.hpp"
#include "TokenUtils.hpp"

namespace mua
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
    TokenType type; ///< token type
    std::string lexemes; ///< token lexemes or string
    Position pos; ///< token position

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
