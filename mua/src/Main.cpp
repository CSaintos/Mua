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

using namespace mua;
using namespace std;

string not_valid_arg(string arg)
{
  stringstream ss;
  ss << "\"" << arg << "\"" << " is not a valid argument. Try 'muac -h'" << endl;
  return ss.str();
}

int main(int argc, char *argv[])
{
  // repl mode
  if (argc == 1)
  {
    CharacterStream c_stream;
    c_stream.pos.line_num = 0;
    c_stream.pos.column_nums[0] = 0;
    Lexer lexer;
    Parser parser;
    Definer definer;
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
        vector<string> parsed_strs = Interpreter::interpret(parse_tree, false);
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
    string src_file_path = ""; 
    string dest_file_path = "";
    for (int i = 1; i < argc; i++)
    {
      if (argv[i][0] == '-')
      {
        if (argv[i][1] == 'o')
        {
          dest_file_path = argv[i];
          dest_file_path = dest_file_path.substr(2, dest_file_path.length() - 2);
        }
        else if (argv[i][2] == 'h')
        {
          if (string(argv[i]).length() == 2)
          {
            // TODO write help manual
          }
          else
          {
            cout << not_valid_arg(argv[i]) << endl;
          }
        }
        else
        {
          cout << not_valid_arg(argv[i]) << endl;
        }
      }
      else
      {
        src_file_path = argv[i];
      }
    }
    
    if (dest_file_path.empty())
    {
      stringstream left_ss;
      stringstream right_ss;
      for (int i = 0; i < src_file_path.length(); i++)
      {
        if (src_file_path[i] == '.')
        {
          left_ss << right_ss.str();
          right_ss.clear();
        }
        right_ss << src_file_path[i];
      }
      if (left_ss.str().empty())
      {
        left_ss << right_ss.str();
      }
      left_ss << ".muar";
      dest_file_path = left_ss.str();
      //cout << src_file_path << endl;
      //cout << dest_file_path << endl;
    }

    Reader reader(src_file_path);
    Lexer lexer;
    Parser parser;
    Definer definer;
    Writer writer(dest_file_path);

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
      vector<string> parsed_strs = Interpreter::interpret(parse_tree, false);
      for (string parsed_str : parsed_strs)
      {
        writer.writeLine(parsed_str);
      }
    }
  }
}
