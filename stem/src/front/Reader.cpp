#include "Reader.hpp"

using namespace std;
using namespace stem;

Reader::Reader(const string &fileName)
  : file(), char_list(), pos(), file_name(fileName), line()
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
    pos.init();
    pos.file_name = file_name;
  }
  catch (ifstream::failure e)
  {
    cerr << "IFStream Exception: Could not open file: " << file_name << endl;
  }
}

int Reader::readLine()
{
  // if file is open and not at the end
  if (file.is_open() && !file.eof())
  {
    // get the next line in the file
    // uses file and stores into the buffer
    std::getline(file, line);
    pos.line_num ++;
    pos.column_nums[0] = -1;

    // ~~ cout << m_line << endl; // ?debugging

    // resets char list
    char_list.clear();

    // Iterate through the string m_line and store
    //  each char in m_char_list
    for (char c : line)
    {
      pos.column_nums[0]++;
      Character character;
      character.c = c;
      character.pos = pos;
      character.type = CharacterUtils::cC_map[c];
      char_list.push_back(Character(character));
    }
  }
  else
  {
    // ~~ cout << "Eof\n";
    char_list.clear();
    return -1;
  }

  return line.length();
}
