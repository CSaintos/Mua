/**
 * @brief This file is part of {{ stem.inc.front }}
 * 
 * @file Reader.hpp
 * @author Christian Santos
 * @version 1.0.0 
 * @date 5/15/2022
 */

#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>

namespace stem
{
  /**
   * @class Reader
   * @brief Handles reading content from files
   */
  class Reader
  {
  private:
    std::fstream m_file; ///< file object
    std::list<char> m_char_list; ///< char list of line
    std::string m_file_name; ///< file name
    std::string m_line; ///< the string line

    /**
     * @brief attempts to open the file with specified file name.
     * 
     * @note If a file is already open, it closes then attempts to open the new file.
     */
    void open();
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
     * @brief Gets file name
     * 
     * @return fileName string reference
     */
    inline const std::string &getFileName() { return  m_file_name; }

    /**
     * @brief Gets read line
     * 
     * @return line string reference
     */
    inline const std::string &getLine() { return m_line; }

    /**
     * @brief Gets list of chars
     * 
     * @return line as char list pointer
     */ 
    inline std::list<char> *getList() { return &m_char_list; }

    /**
     * @brief Reads the next line and stores chars into list.
     * 
     * @return number of chars in line
     */
    int readLine();
  };
}