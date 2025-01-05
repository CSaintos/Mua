/**
 * @file mua/inc/front/Writer.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 12/30/2024
 */

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
