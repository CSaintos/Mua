/**
 * @brief This file is part of {{ stem.inc.front }}
 * 
 * @file Lexer.hpp
 * @author Christian Santos
 * @version 1.0.3 
 * @date 8/10/2024
 */

#pragma once

#include <list>
#include <iostream>
#include <unordered_map>

#include "Error.hpp"
#include "Character.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include "TokenUtils.hpp"

namespace stem
{
  /**
   * @class Lexer
   * @brief Handles converting char list into tokens
   */
  class Lexer
  {
  private:
    std::stringstream ss; ///< for constructing lexemes
    std::list<Token> token_stream; ///< list of tokens lexed
    std::list<Character> *char_list; ///< list of chars to lex
    std::list<Character>::iterator itr; ///< points to current element
    std::list<Character>::iterator end; ///< points to last element
    //std::string file_name; ///< name of the file current tokens belong to

    Token token_temp; ///< current token being analyzed/created
    // Position pos_temp; ///< current position during lex process

    int dot_count; ///< making sure only one dot in decimal

    /**
     * @brief initializes member variables
     * - prepares to lex a 'new' char list
     * @see lex()
     */
    void init(std::list<Character> *char_list);
    /**
     * @brief maps a single char to TokenType and returns type
     * 
     * @param ch single character to map
     * 
     * @return TokenType that the char belongs to
     */
    stem::TokenType charToTokenType(char &ch);
    /**
     * @brief Throws an exception and stops program
     * @note this method is temporary
     * 
     * @param ch single char to error 
     */
    void err(Character &c);
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
     * @param ch the character to store in token
     */
    void createToken(stem::TokenType &type, Character &c);
    /**
     * @brief helps build token stream one char at a time
     * 
     * - Uses createToken() and toTokenStream() to build tokens
     * and add them to the token stream.
     * 
     * @param ch single char to convert or add to a token
     */
    void scanOneChar(Character &c);
  public:
    /**
     * @brief Lexer(file_name) constructor
     * 
     * Initializes the file name
     * 
     * @see ~Lexer()
     */
    Lexer();
    /**
     * @brief ~Lexer() destructor
     * 
     * @note clears string stream
     * 
     * @see Lexer(const std::string &file_name)
     */
    ~Lexer();

    /**
     * @brief lexes the char list.
     * 
     * Converts the char list into a list of tokens.
     * 
     * @param char_list pointer to char list
     * @param line_num line number of char list
     * @return true if chars were lexed, false if no chars were lexed
     */
    bool lex(std::list<Character> *char_list);
    /**
     * @brief returns pointer to token stream
     * 
     * @return pointer to token stream
     */
    std::list<stem::Token> *getList();
  };
}
