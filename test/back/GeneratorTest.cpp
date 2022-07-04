/**
 * @brief This file is part of {{ stem.test.back }}
 *
 * @file GeneratorTest.cpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 7/2/2022
 */

#include <iostream>
#include <string>

#include "Token.hpp"
#include "PluginManager.hpp"

#include "Reader.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Generator.hpp"

int main(int argc, char *argv[])
{
  // file name
  std::string file_name = argv[argc - 1];

  // create reader with file name
  stem::Reader reader(file_name);
  // create lexer with file name
  stem::Lexer lexer(file_name);
  // create parser
  stem::Parser parser;
  // create PluginManager
  stem::PluginManager plugin_manager;
  plugin_manager.loadPlugins();
  // create generator
  stem::Generator generator(plugin_manager.m_entryPoints);

  // Loop variables
  int line_length = 0;
  int line_num = 0;

  do
  {
    ++line_num;
    // Read the next line
    line_length = reader.readLine();

    if (line_length != -1)
    {
      // lex the char list
      lexer.lex(reader.getList(), line_num);
      // parse token stream
      parser.parse(lexer.getList());
      // generate result from parse tree
      generator.generate(parser.getParseTree());
    }

  } while (line_length != -1);

  plugin_manager.unloadPlugins();

  return 0;
}