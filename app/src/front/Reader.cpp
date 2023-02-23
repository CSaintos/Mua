#include "Reader.hpp"

stem::Reader::Reader(const std::string &fileName)
    : m_file(), m_char_list(), m_file_name(fileName), m_line()
{
  open();
}

stem::Reader::~Reader()
{
  m_char_list.clear();
  // Close file
  if (m_file.is_open())
  {
    m_file.close();
  }
}

void stem::Reader::open()
{
  try
  {
    if (m_file.is_open())
    { // file is already open
      m_file.close();
    }

    m_file.open(m_file_name, std::ios_base::in);
  }
  catch (std::ifstream::failure e)
  {
    std::cerr << "IFStream Exception: Could not open file: " << m_file_name << std::endl;
  }
}

int stem::Reader::readLine()
{
  // if file is open and not at the end
  if (m_file.is_open() && !m_file.eof())
  {
    // get the next line in the file
    // uses file and stores into the buffer
    std::getline(m_file, m_line);

    // ~~ std::cout << m_line << std::endl; // ?debugging

    // resets char list
    m_char_list.clear();

    // Iterate through the string m_line and store
    //  each char in m_char_list
    for (char c : m_line)
    {
      m_char_list.push_back(c);
    }
  }
  else
  {
    // ~~ std::cout << "Eof\n";
    m_char_list.clear();
    return -1;
  }

  return m_line.length();
}
