#include "Error.hpp"

using namespace std;
using namespace stem;

Error::Error()
{}

Error::Error(Position &pos, const string &err_name, const string &details)
  : pos(pos), err_name(err_name), details(details)
{}

/*
stem::Error::~Error()
{}
*/

string Error::to_string()
{
  ss.str(string());

  ss << err_name << ": " << details << endl
    << "File: " << pos.file_name << ", line: " << pos.line_num
    << endl << "Between columns: " << pos.column_nums[0]
    << ", " << pos.column_nums[1] << endl;

  return ss.str();
}
