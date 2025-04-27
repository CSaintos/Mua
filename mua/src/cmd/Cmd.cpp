#include "Cmd.hpp"

using namespace std;
using namespace mua;

Cmd::Cmd(int argc, char *argv[])
{
  for (int i = 1; i < argc; i++)
  {
    args.push_back(argv[i]);   
  }

  cmd_data.proceed = true;
  cmd_data.is_debug = false;
  cmd_data.repl_mode = true;
  scanArgs();
}

void Cmd::scanArgs()
{
  CmdArg last_arg_t = CmdArg::NONE;
  char last_option;
  for (string arg : args)
  {
    if (arg[0] == '-')
    {
      if (last_arg_t != CmdArg::OPTION)
      {
        last_arg_t = CmdArg::OPTION;
        last_option = arg[1];
        switch (last_option)
        {
        case 'h':
          cmd_data.proceed = false;
          cmd_data.repl_mode = false;
          cout << helpMessage() << endl;
          break;
        case 'd':
          cmd_data.is_debug = true;
        default:
          break;
        }
      }
    }
    else
    {
      if (last_arg_t == CmdArg::OPTION)
      {
        switch (last_option)
        {
        case 'o':
          cmd_data.dest_file_path = arg;
          cmd_data.repl_mode = false;
          break;
        case 'h':
          break;
        default:
          cmd_data.repl_mode = false;
          cmd_data.proceed = false;
          cout << notValidArg(arg) << endl << endl;
          cout << helpMessage() << endl;
          break;
        }
      }
      else if (last_arg_t == CmdArg::NONE)
      {
        cmd_data.repl_mode = false;
        cmd_data.src_file_path = arg;
      }
      last_arg_t = CmdArg::PARAMETER;
    }
  }
  if (cmd_data.dest_file_path.empty())
  {
    stringstream left_ss;
    stringstream right_ss;
    for (int i = 0; i < cmd_data.src_file_path.length(); i++)
    {
      if (cmd_data.src_file_path[i] == '.')
      {
        left_ss << right_ss.str();
        right_ss.clear();
      }
      right_ss << cmd_data.src_file_path[i];
    }
    if (left_ss.str().empty())
    {
      left_ss << right_ss.str();
    }
    left_ss << ".muar";
    cmd_data.dest_file_path = left_ss.str();
  }
}

string Cmd::helpMessage()
{
  stringstream ss;
  ss << "usage: muac [<src_file_path>] [-o <dest_file_path>] [-d] [-h]"
  << endl
  << "Repl mode: run muac without options" << endl << endl
  << "muac options:" << endl
  << "  -o <dest_file_path>" << endl
  << "\tset the output file path." << endl
  << "  -d" << endl
  << "\tenable debugging output." << endl
  << "  -h" << endl
  << "\tdisplay this help message.";
  return ss.str();
}

string Cmd::notValidArg(string arg)
{
  stringstream ss;
  ss << "\"" << arg << "\"" << " is not a valid argument.";
  return ss.str();
}
