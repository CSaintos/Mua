#pragma once

namespace mua
{
  /**
   * @enum TokenType
   * @brief Specifies Type of Token
   */
  enum class TokenType
  {
    PERCENT,
    CARET,
    ASTERISK,
    ADJACENT,
    LPAREN,
    RPAREN,
    MINUS,
    EQUAL,
    PLUS,
    SEMICOLON,
    FSLASH,
    DIGIT,
    IDENTIFIER,
    COMMENT,
    LET,
    EMPTY,
    UNKNOWN
//    SPACE,
//    TILDE,
//    EXCLAMATION,
//    ASPERAND,
//    AMPERSAND,
//    UNDERSCORE,
//    LBRACKET,
//    LBRACE,
//    RBRACKET,
//    RBRACE,
//    VSLASH,
//    COLON,
//    COMMA,
//    LESSTHAN,
//    DOT,
//    MORETHAN,
//    AND,
//    OR,
//    XOR,
//    ONLYIF,
//    IFANDONLYIF,
  };
}
