/**
 * @brief This file is part of {{ stem.inc.util.token }}
 * 
 * @file TokenType.hpp
 * @author Christian Santos
 * @version 1.0.0 
 * @date 2/19/2023
*/

#pragma once

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
}