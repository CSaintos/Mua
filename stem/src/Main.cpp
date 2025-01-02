/**
 * @file stem/src/Main.cpp
 * @author Christian Santos
 * @version 1.0.1
 * @date 1/1/2025
 */

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

#include "Reader.hpp"
#include "Lexer.hpp"
#include "Node.hpp"
#include "Parser.hpp"
#include "Definer.hpp"
#include "Interpreter.hpp"
#include "Writer.hpp"

using namespace stem;
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
      cout << src_file_path << endl;
      cout << dest_file_path << endl;
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

    vector<unique_ptr<Node>>* parse_trees = parser.getParseTrees();

    for (int i = 0; i < parse_trees->size(); i++)
    {
      unique_ptr<Node>& parse_tree = (*parse_trees)[i];
      vector<string> parsed_strs = Interpreter::interpret(parse_tree, false);
      for (string parsed_str : parsed_strs)
      {
        writer.writeLine(parsed_str);
      }
    }
  }
}
