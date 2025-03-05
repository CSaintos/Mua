/**
 * @file mua/inc/front/Lexer.hpp
 * @author Christian Santos
 * @version 1.0.4 
 * @date 8/12/2024
 */

#pragma once

#include <list>
#include <iostream>
#include <unordered_map>

#include "Error.hpp"
#include "Character.hpp"
#include "CharacterType.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include "TokenUtils.hpp"
#include "TrieNode.hpp"
#include "TokenTrie.hpp"

namespace mua
{
  /**
   * @class Lexer
   * @brief Handles converting char list into tokens
   */
  class Lexer
  {
  private:
    std::list<Character> lexemes; ///< string of list for constructing lexemes
    std::list<Token> token_stream; ///< list of tokens lexed
    std::list<Character> *char_list; ///< list of chars to lex
    std::list<Character>::iterator itr; ///< points to current element
    std::list<Character>::iterator end; ///< points to last element
    TokenTrie* token_trie;
    TrieNode* curr;

    Token token_temp; ///< current token being analyzed/created

    int dot_count; ///< making sure only one dot in decimal

    /**
     * @brief initializes member variables
     * - prepares to lex a 'new' char list
     * @see lex()
     */
    void init(std::list<Character> *char_list);
    /**
     * @brief Packages the temp token into token stream
     * - Then re-initializes the string stream and temp token.
     */
    void toTokenStream();
    /**
     * @brief Creates a new token with params.
     * 
     * Creates a new token with start positional value, 
     * type, and a starting character to ss (string stream).
     * 
     * @param type the token type of the token
     * @param c the character to store in token
     */
    void createToken(const TokenType &type, Character &c);
    /**
     * @brief helps build token stream one char at a time
     * 
     * - Uses createToken() and toTokenStream() to build tokens
     * and add them to the token stream.
     * 
     * @param c single char to add to a token
     */
    void scanOneChar(Character &c);
  public:
    Lexer();

    /**
     * @brief lexes the char list.
     * Converts the char list into a list of tokens.
     * 
     * @param char_list pointer to char list
     *
     * @return true if chars were lexed, false if no chars were lexed
     */
    bool lex(std::list<Character> *char_list);
    /**
     * @brief returns pointer to token stream
     * 
     * @return pointer to token stream
     */
    std::list<Token> *getList();
  };
}
