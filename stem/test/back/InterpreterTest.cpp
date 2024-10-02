/**
 * @file stem/test/back/InterpreterTest.cpp
 * @author Christian Santos
 * @version 1.0.1
 * @date 10/1/2024
 */

#include "Reader.hpp"
#include "Lexer.hpp"
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
  Interpreter interpreter;

  int line_length = 0;
  
  do {
    line_length = reader.readLine();
    lexer.lex(reader.getList());
    parser.parse(lexer.getList());
  } while (line_length != -1);
  parser.checkSemicolonError();

  definer.define(parser.getParseTrees());

  vector<unique_ptr<Node>>* parse_trees = parser.getParseTrees();
  interpreter.interpret(parse_trees);
}
