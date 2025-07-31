#include "MuaApi.hpp"

using namespace std;
using namespace mua;

MuaApi::MuaApi()
: lexer(), parser(), definer(), c_stream()
{}

string MuaApi::calculate(string input, bool is_debug)
{
  list<Character> characters;
  list<unique_ptr<Node>> *parse_trees;
  stringstream ss;
  Result<> res;

  cout << input << endl; //DEBUG

  c_stream.pos.line_num = 0;
  c_stream.pos.column_nums[0] = 0;
  characters = c_stream.strToCharacterList(input);
  lexer.lex(&characters);
  res = parser.parse(lexer.getList());
  if (res.is_err()) {
    parser.dropParseTrees();
    return res.get_err().to_string();
  } 
  res = parser.checkSemicolonError();
  if (res.is_err()) {
    parser.dropParseTrees();
    return res.get_err().to_string();
  }
  parse_trees = parser.getParseTrees();
  definer.define(parse_trees);

  while (!(*parse_trees).empty())
  {
    unique_ptr<Node>& parse_tree = (*parse_trees).front();
    vector<string> parsed_strs = Interpreter::interpret(parse_tree, is_debug);
    for (string parsed_str : parsed_strs)
    {
      ss << parsed_str << endl;
    }
    (*parse_trees).pop_front();
  }
  
  return ss.str();
}
