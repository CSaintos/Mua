/**
 * @file stem/test/front/ParserTest.cpp
 * @author Christian Santos
 * @version 1.0.5 
 * @date 8/10/2024
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
  stem::Lexer lexer;
  // create parser
  stem::Parser parser;

  // Loop variables
  int line_length = 0;

  do {
    // Read the next line
    line_length = reader.readLine();
    // lex the char list
    lexer.lex(reader.getList());
    // parse token stream
    parser.parse(lexer.getList()); //? temp

    // print parse tree
    stem::Node *root_node = parser.getParseTree();
    if (root_node != nullptr)
    {
      std::cout << root_node->to_string() << std::endl;
    }

  } while (line_length != -1);

  return 0;
}
