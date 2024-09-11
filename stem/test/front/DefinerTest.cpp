/**
 * @file stem/test/front/DefinerTest.cpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 9/9/2024
 */

#include "Reader.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Definer.hpp"

using namespace stem;
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
    cout << "yes?" << endl;
    parser.parse(lexer.getList());
    cout << "parsed?" << endl;
  } while (line_length != -1);

  definer.define(parser.getParseTrees());

  return 0;
}
