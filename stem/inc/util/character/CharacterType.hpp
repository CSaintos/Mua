/**
 * @file stem/inc/util/character/CharacterType.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 8/5/2024
*/

#pragma once

namespace stem
{
  /**
   * @enum CharacterType
   * @brief Specifies Type of Character
   */
  enum class CharacterType
  {
    TILDE,
    EXCLAMATION,
    ASPERAND,
    PERCENT,
    CARET,
    AMPERSAND,
    ASTERISK,
    LPAREN,
    RPAREN,
    MINUS,
    UNDERSCORE,
    EQUAL,
    PLUS,
    LBRACKET,
    LBRACE,
    RBRACKET,
    RBRACE,
    VSLASH,
    SEMICOLON,
    COLON,
    COMMA,
    LESSTHAN,
    DOT,
    MORETHAN,
    FSLASH,
    SPACE,
    DIGIT,
    ALPHA,
    EMPTY,
    UNKNOWN
  };
}
