#include <list>

#include "Reader.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Definer.hpp"

using namespace mua;
using namespace std;

int main(int argc, char *argv[])
{
  string file_name = argv[argc-1];
  Reader reader(file_name);
  Lexer lexer;
  Parser parser;
  Definer definer;

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
    cout << (*itr)->to_string() << endl;
  }

  return 0;
}
