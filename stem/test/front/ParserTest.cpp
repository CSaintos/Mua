/**
 * @file stem/test/front/ParserTest.cpp
 * @author Christian Santos
 * @version 1.0.5 
 * @date 8/10/2024
 */

#include <string>
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <memory>

#include "Token.hpp"
#include "Character.hpp"
#include "Node.hpp"

#include "Reader.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

using namespace stem;
using namespace std;

int main(int argc, char *argv[])
{
  // file name
  string file_name = argv[argc-1];

  // create reader with file name
  Reader reader(file_name);
  // create lexer with file name
  Lexer lexer;
  // create parser
  Parser parser;

  // Loop variables
  int line_length = 0;
  list<Character> *the_list = nullptr;

  do {
    // Read the next line
    line_length = reader.readLine();
    // lex the char list
    lexer.lex(reader.getList());
    // parse token stream
    parser.parse(lexer.getList()); //? temp
  } while (line_length != -1);

  vector<unique_ptr<Node>>* parse_trees = parser.getParseTrees();
  for (int i = 0; i < parse_trees->size(); ++i)
  {
    cout << (*parse_trees)[i]->to_string() << endl;
  }

  return 0;
}
