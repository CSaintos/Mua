#pragma once

#include <iostream>
#include <fstream>

namespace mua
{
  /**
   * @class Writer
   * @brief Handles writing content to files
   */
  class Writer
  {
  private:
    std::fstream file;
    std::string file_name;
    
    void open();
  public:
    Writer(const std::string &file_name);
    ~Writer();
    
    void writeLine(const std::string &line);
  };
}
