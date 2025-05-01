#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>

#include "Character.hpp"
#include "CharacterStream.hpp"
#include "Position.hpp"

namespace mua
{
  /**
   * @class Reader
   * @brief Handles reading content from files
   */
  class Reader
  {
  private:
    std::fstream file; ///< file object
    std::list<Character> char_list; ///< char list of line
    CharacterStream char_stream;
    Position pos; ///< current position
    std::string file_name; ///< file name
    std::string line; ///< the string line

    /**
     * @brief attempts to open the file with specified file name.
     * 
     * @note If a file is already open, it closes then attempts to open the new file.
     */
    void open();

    /**
     * @brief Gets read line
     * 
     * @return line string reference
     */
    inline const std::string &getLine() { return line; }

  public:
    /**
     * @brief Reader(fileName) constructor
     * 
     * Sets new filename then opens the file.
     * @param fileName name of the file
     * @see ~Reader()
     */
    Reader(const std::string &file_name);
    /**
     * @brief ~Reader() destructor
     * 
     * If a file is already open, it closes it.
     * @see Reader(const std::string &file_name)
     */
    ~Reader();

    /**
     * @brief Gets list of chars
     * 
     * @return line as char list pointer
     */ 
    inline std::list<Character> *getList() { return &char_list; }

    /**
     * @brief Reads the next line and stores chars into list.
     * 
     * @return number of chars in line
     */
    int readLine();
  };
}
