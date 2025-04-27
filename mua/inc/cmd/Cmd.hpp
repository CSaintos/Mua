#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

namespace mua
{
  struct CmdData
  {
    std::string src_file_path;
    std::string dest_file_path;
    bool repl_mode;
    bool proceed;
    bool is_debug;
  };

  class Cmd
  {
  private:
    std::vector<std::string> args;

    std::string notValidArg(std::string arg);
    std::string helpMessage();
    void scanArgs();
  public:   
    CmdData cmd_data;

    Cmd(int argc, char *argv[]);
  };

  

  enum CmdArg
  {
    OPTION,
    PARAMETER,
    NONE
  };
}
