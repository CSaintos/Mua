#include "TokenUtils.hpp"

using namespace mua;
using namespace std;

unordered_map<TokenType, string> TokenUtils::m_TS_map = 
{
  {TokenType::SEMICOLON, "SEMICOLON"},
  {TokenType::LPAREN, "LPAREN"},
  {TokenType::RPAREN, "RPAREN"},
  {TokenType::EQUAL, "EQUAL"},
  {TokenType::PLUS, "PLUS"},
  {TokenType::MINUS, "MINUS"},
  {TokenType::ASTERISK, "ASTERISK"},
  {TokenType::ADJACENT, "ADJACENT"},
  {TokenType::FSLASH, "FSLASH"},
  {TokenType::PERCENT, "PERCENT"},
  {TokenType::CARET, "CARET"},
  {TokenType::DIGIT, "DIGIT"},
  {TokenType::IDENTIFIER, "IDENTIFIER"},
  {TokenType::COMMENT, "COMMENT"},
  {TokenType::LET, "LET"},
  {TokenType::EMPTY, "EMPTY"}, 
  {TokenType::UNKNOWN, "UNKNOWN"}
//  {TokenType::SPACE, "SPACE"},
//  {TokenType::COLON, "COLON"},
//  {TokenType::LBRACKET, "LBRACKET"},
//  {TokenType::RBRACKET, "RBRACKET"},
//  {TokenType::LBRACE, "LBRACE"},
//  {TokenType::AMPERSAND, "AMPERSAND"},
//  {TokenType::VSLASH, "VSLASH"},
//  {TokenType::TILDE, "TILDE"},
//  {TokenType::LESSTHAN, "LESSTHAN"},
//  {TokenType::MORETHAN, "MORETHAN"},
//  {TokenType::EXCLAMATION, "EXCLAMATION"},
//  {TokenType::COMMA, "COMMA"},
//  {TokenType::DOT, "DOT"},
//  {TokenType::UNDERSCORE, "UNDERSCORE"},
//  {TokenType::AND, "AND"},
//  {TokenType::OR, "OR"},
//  {TokenType::XOR, "XOR"},
//  {TokenType::ONLYIF, "ONLYIF"},
//  {TokenType::IFANDONLYIF, "IFANDONLYIF"},
};

unordered_map<string, TokenType> TokenUtils::m_RT_map =
{
  {";", TokenType::SEMICOLON},
  {"(", TokenType::LPAREN},
  {")", TokenType::RPAREN},
  {"=", TokenType::EQUAL},
  {"+", TokenType::PLUS},
  {"-", TokenType::MINUS},
  {"*", TokenType::ASTERISK},
  {"/", TokenType::FSLASH},
  {"%", TokenType::PERCENT},
  {"^", TokenType::CARET},
  {"//", TokenType::COMMENT},
  {"let", TokenType::LET},
  {"", TokenType::EMPTY},
  {".", TokenType::DIGIT},
//  {" ", TokenType::SPACE},
//  {":", TokenType::COLON},
//  {"[", TokenType::LBRACKET},
//  {"]", TokenType::RBRACKET},
//  {"{", TokenType::LBRACE},
//  {"}", TokenType::RBRACE},
//  {"&", TokenType::AMPERSAND},
//  {"|", TokenType::VSLASH},
//  {"~", TokenType::TILDE},
//  {"<", TokenType::LESSTHAN},
//  {">", TokenType::MORETHAN},
//  {"!", TokenType::EXCLAMATION},
//  {",", TokenType::COMMA},
//  {"_", TokenType::UNDERSCORE},
  {"0", TokenType::DIGIT},
  {"1", TokenType::DIGIT},
  {"2", TokenType::DIGIT},
  {"3", TokenType::DIGIT},
  {"4", TokenType::DIGIT},
  {"5", TokenType::DIGIT},
  {"6", TokenType::DIGIT},
  {"7", TokenType::DIGIT},
  {"8", TokenType::DIGIT},
  {"9", TokenType::DIGIT},
  {"A", TokenType::IDENTIFIER},
  {"B", TokenType::IDENTIFIER},
  {"C", TokenType::IDENTIFIER},
  {"D", TokenType::IDENTIFIER},
  {"E", TokenType::IDENTIFIER},
  {"F", TokenType::IDENTIFIER},
  {"G", TokenType::IDENTIFIER},
  {"H", TokenType::IDENTIFIER},
  {"I", TokenType::IDENTIFIER},
  {"J", TokenType::IDENTIFIER},
  {"K", TokenType::IDENTIFIER},
  {"L", TokenType::IDENTIFIER},
  {"M", TokenType::IDENTIFIER},
  {"N", TokenType::IDENTIFIER},
  {"O", TokenType::IDENTIFIER},
  {"P", TokenType::IDENTIFIER},
  {"Q", TokenType::IDENTIFIER},
  {"R", TokenType::IDENTIFIER},
  {"S", TokenType::IDENTIFIER},
  {"T", TokenType::IDENTIFIER},
  {"U", TokenType::IDENTIFIER},
  {"V", TokenType::IDENTIFIER},
  {"W", TokenType::IDENTIFIER},
  {"X", TokenType::IDENTIFIER},
  {"Y", TokenType::IDENTIFIER},
  {"Z", TokenType::IDENTIFIER},
  {"a", TokenType::IDENTIFIER},
  {"b", TokenType::IDENTIFIER},
  {"c", TokenType::IDENTIFIER},
  {"d", TokenType::IDENTIFIER},
  {"e", TokenType::IDENTIFIER},
  {"f", TokenType::IDENTIFIER},
  {"g", TokenType::IDENTIFIER},
  {"h", TokenType::IDENTIFIER},
  {"i", TokenType::IDENTIFIER},
  {"j", TokenType::IDENTIFIER},
  {"k", TokenType::IDENTIFIER},
  {"l", TokenType::IDENTIFIER},
  {"m", TokenType::IDENTIFIER},
  {"n", TokenType::IDENTIFIER},
  {"o", TokenType::IDENTIFIER},
  {"p", TokenType::IDENTIFIER},
  {"q", TokenType::IDENTIFIER},
  {"r", TokenType::IDENTIFIER},
  {"s", TokenType::IDENTIFIER},
  {"t", TokenType::IDENTIFIER},
  {"u", TokenType::IDENTIFIER},
  {"v", TokenType::IDENTIFIER},
  {"w", TokenType::IDENTIFIER},
  {"x", TokenType::IDENTIFIER},
  {"y", TokenType::IDENTIFIER},
  {"z", TokenType::IDENTIFIER},
//  {"&&", TokenType::AND},
//  {"&|", TokenType::OR},
//  {"||", TokenType::XOR},
//  {"->", TokenType::ONLYIF},
//  {"<->", TokenType::IFANDONLYIF},
};

