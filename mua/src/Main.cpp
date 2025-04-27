#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <list>

#include "Reader.hpp"
#include "Character.hpp"
#include "CharacterStream.hpp"
#include "Lexer.hpp"
#include "Node.hpp"
#include "Parser.hpp"
#include "Definer.hpp"
#include "Interpreter.hpp"
#include "Writer.hpp"
#include "Cmd.hpp"

using namespace mua;
using namespace std;

int main(int argc, char *argv[])
{
  Cmd cmd(argc, argv);
  CmdData cmd_data = cmd.cmd_data;
  if (!cmd_data.proceed)
  {
    return 0;
  }

  Lexer lexer;
  Parser parser;
  Definer definer;

  if (cmd_data.repl_mode)
  {
    CharacterStream c_stream;
    c_stream.pos.line_num = 0;
    c_stream.pos.column_nums[0] = 0;
    list<Character> characters;
    list<unique_ptr<Node>>* parse_trees;
    string line;
    cout << "Type \"exit[];\" on an empty line to exit mua repl mode" << endl;
    do {
      cout << "mua>";
      std::getline(cin, line);
      if (line == "exit[];") continue;
      characters = c_stream.strToCharacterList(line); 
      lexer.lex(&characters);
      parser.parse(lexer.getList());
      // notice that we're skipping the parser.checkSemicolonError()
      definer.define(parser.getParseTrees());
      parse_trees = parser.getParseTrees();
      while (!(*parse_trees).empty())
      {
        unique_ptr<Node>& parse_tree = (*parse_trees).front();
        vector<string> parsed_strs = Interpreter::interpret(parse_tree, cmd_data.is_debug);
        for (string parsed_str : parsed_strs)
        {
          cout << parsed_str << endl;
        }
        (*parse_trees).pop_front();
      }
      c_stream.pos.column_nums[0] = 0;
      c_stream.pos.line_num++;
    } while (line != "exit[];");
  }
  else // src -> dest mode
  {
    Reader reader(cmd_data.src_file_path);
    Writer writer(cmd_data.dest_file_path);

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
      unique_ptr<Node>& parse_tree = *itr;
      vector<string> parsed_strs = Interpreter::interpret(parse_tree, cmd_data.is_debug);
      for (string parsed_str : parsed_strs)
      {
        writer.writeLine(parsed_str);
      }
    }
  }
}
