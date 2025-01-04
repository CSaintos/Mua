#include "Reader.hpp"

using namespace std;
using namespace stem;

Reader::Reader(const string &fileName)
  : file(), char_list(), char_stream(), pos(), file_name(fileName), line()
{
  open();
}

Reader::~Reader()
{
  char_list.clear();
  // Close file
  if (file.is_open())
  {
    file.close();
  }
}

void Reader::open()
{
  try
  {
    if (file.is_open())
    { // file is already open
      file.close();
    }
    
    file.open(file_name, std::ios_base::in);
    char_stream.pos.init();
    char_stream.pos.file_name = file_name;
    char_stream.pos.line_num = 0;
    //pos.init();
    //pos.file_name = file_name;
    //pos.line_num = 0;
  }
  catch (ifstream::failure e)
  {
    cerr << "IFStream Exception: Could not open file: " << file_name << endl;
  }
}

int Reader::readLine()
{
  if (file.is_open() && !file.eof())
  {
    // get the next line in the file
    std::getline(file, line);
    char_stream.pos.line_num++;
    char_stream.pos.column_nums[0] = 0;
    //pos.line_num ++;
    //pos.column_nums[0] = 0;

    // cout << m_line << endl; // DEBUG

    // resets char list
    char_list.clear();
    char_list = char_stream.strToCharacterList(line);
  }
  else
  {
    // cout << "Eof\n" // DEBUG
    char_list.clear();
    return -1;
  }

  return line.length();
}
