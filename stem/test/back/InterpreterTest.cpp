/**
 * @file stem/test/back/InterpreterTest.cpp
 * @author Christian Santos
 * @version 1.0.2
 * @date 1/1/2025
 */

#include <list>
#include <memory>

#include "Reader.hpp"
#include "Lexer.hpp"
#include "Node.hpp"
#include "Parser.hpp"
#include "Definer.hpp"
#include "Interpreter.hpp"

using namespace stem;
using namespace std;

int main(int argc, char *argv[])
{
  string file_name = argv[argc-1];
  Reader reader(file_name);
  Lexer lexer;
  Parser parser;
  Definer definer;
  //Interpreter interpreter;

  int line_length = 0;
  
  do {
    line_length = reader.readLine();
    lexer.lex(reader.getList());
    parser.parse(lexer.getList());
  } while (line_length != -1);
  parser.checkSemicolonError();

  definer.define(parser.getParseTrees());

  list<unique_ptr<Node>>* parse_trees = parser.getParseTrees();
  for (
  list<unique_ptr<Node>>::iterator itr = (*parse_trees).begin();
  itr != (*parse_trees).end();
  itr++
  )
  {
    unique_ptr<Node>& parse_tree = (*itr);
    Interpreter::interpret(parse_tree, true);
  }
}
