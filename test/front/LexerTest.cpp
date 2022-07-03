/**
 * @brief This file is part of {{ stem.test.front }}
 * 
 * @file LexerTest.cpp
 * @author Christian Santos
 * @version 1.0.0 5/17/2022
 */

#include <string>
#include <iostream>

#include "Token.hpp"

#include "Reader.hpp"
#include "Lexer.hpp"

int main(int argc, char* argv[])
{
  // file name
  std::string file_name = argv[argc-1];

  // create reader with file name
  stem::Reader reader(file_name);
  // create lexer with file name
  stem::Lexer lexer(file_name);

  int line_length = 0;
  int line_num = 0;
  std::list<char> *chars_list = nullptr;
  std::list<stem::Token> *token_stream = nullptr;
  std::list<stem::Token>::iterator itr;
  // do ... while line_length isn't -1
  do {
    // Read the next line and get the length
    line_length = reader.readLine();
    // Print the length of the line
    //~~std::cout << "Line length: " << line_length << std::endl;
    // Get the character list from the reader as pointer.
    chars_list = reader.getList();
    ++line_num;
    // lex the char list
    lexer.lex(chars_list, line_num);
    // get token stream
    token_stream = lexer.getList();
    // Print the length of the token stream
    //~~std::cout << "TokenStream length: " << token_stream->size() << std::endl;
    // print token stream
    for (itr = token_stream->begin(); itr != token_stream->end(); ++itr)
    {
      std::cout << itr->to_string() << ", ";
    }
    std::cout << std::endl;
  } while(line_length != -1);

  return 0;
}
