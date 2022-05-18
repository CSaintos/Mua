/**
 * @brief This file is part of {{ stem.test }}
 * 
 * @file ParserTest.cpp
 * @author Christian Santos
 * @version 1.0.0 5/18/2022
 */

#include <string>
#include <iostream>

#include "Token.hpp"

#include "Reader.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int main(int argc, char *argv[])
{
  // file name
  std::string file_name = argv[argc-1];

  // create reader with file name
  stem::Reader reader(file_name);
  // create lexer with file name
  stem::Lexer lexer(file_name);
  // create parser
  stem::Parser parser();

  // Loop variables
  int line_length = 0;
  int line_num = 0;
  std::list<stem::Token> *token_stream = nullptr;

  do {
    ++line_num;
    // Read the next line
    line_length = reader.readLine();
    // lex the char list
    lexer.lex(reader.getList(), line_num);
    // TODO parse
    token_stream = lexer.getList(); //? temp

  } while (line_length != -1);

  // TODO print parse output

  return 0;
}