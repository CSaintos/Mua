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
    PERCENT,
    CARET,
    ASTERISK,
    LPAREN,
    RPAREN,
    MINUS,
    EQUAL,
    PLUS,
    SEMICOLON,
    DOT,
    FSLASH,
    SPACE,
    DIGIT,
    ALPHA,
    EMPTY,
    UNKNOWN
//    TILDE,
//    EXCLAMATION,
//    ASPERAND,
//   AMPERSAND,
//   UNDERSCORE,
//    LBRACKET,
//    LBRACE,
//    RBRACKET,
//    RBRACE,
//    VSLASH,
//    COLON,
//    COMMA,
//    LESSTHAN,
//    MORETHAN,
  };
}
