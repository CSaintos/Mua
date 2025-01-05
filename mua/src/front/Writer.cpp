#include "Writer.hpp"

using namespace std;
using namespace mua;

Writer::Writer(const string &file_name)
  : file(), file_name(file_name)
{
  open();
}

Writer::~Writer()
{
  if (file.is_open())
  {
    file.close();
  }
}

void Writer::open()
{
  try
  {
    if (file.is_open())
    {
      file.close();
    }

    file.open(file_name, std::ios_base::out);
  } 
  catch (ofstream::failure e) 
  {
    cerr << "OFStream Exception: Could not open file: " << file_name << endl; 
  }
}

void Writer::writeLine(const string &line)
{
  if (file.is_open())
  {
    file << line << endl;
  }
}
