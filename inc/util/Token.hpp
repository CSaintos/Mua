/**
 * @brief This file is part of {{ stem.inc.util }}
 * 
 * @file token.hpp
 * @author Christian Santos
 * @version 1.0.1 5/17/2022
 * 
 * @note There might be a way to implement using a hash table
 */
#pragma once

#include <string>
#include <unordered_map>

#include "Position.hpp"

namespace stem
{
  /**
   * @enum TokenType
   * @brief Specifies Type of Token
   */
  enum class TokenType
  {
    SPACE,
    SEMICOLON,
    COLON,
    LPAREN,
    RPAREN,
    LBRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,
    AMPERSAND,
    VSLASH,
    TILDE,
    EQUAL,
    LESSTHAN,
    MORETHAN,
    EXCLAMATION,
    COMMA,
    DOT,
    PLUS,
    MINUS,
    ASTERISK,
    FSLASH,
    PERCENT,
    CARET,
    UNDERSCORE,
    DIGIT,
    IDENTIFIER,
    COMMENT,
    LET,
    AND,
    OR,
    XOR,
    ONLYIF,
    IFANDONLYIF,
    EMPTY,
    UNKNOWN
  };

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

  /**
   * @class TokenUtils
   * @brief Specifies maps to attributes of TokenType
   */
  class TokenUtils
  {
  private:
  public:
    /// TokenType to string map
    static std::unordered_map<TokenType, std::string> m_TS_map;
    /// Reference (string) to TokenType map
    static std::unordered_map<std::string, TokenType> m_RT_map;
  };
}