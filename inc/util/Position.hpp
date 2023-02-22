/**
 * @brief This file is part of {{ stem.inc.util }}
 * 
 * @file position.hpp
 * @author Christian Santos
 * @version 1.0.0 
 * @date 5/15/2022
 */

#pragma once

#include <string>

namespace stem
{
  /**
   * @struct Position
   * 
   * @brief Specifies location of a token
   * 
   * Stores file name, column numbers, and line number of a token.
   */
  struct Position
  {
    std::string m_file_name; ///< file name
    int m_column_nums[2]; ///< start and ending indicies
    int m_line_num; ///< line number in file

    /**
     * @brief Initialize position object with empty fields
     */
    void init() 
    {
      m_file_name = "";
      m_column_nums[0] = -1; // start index
      m_column_nums[1] = -1; // end index
      m_line_num = -1;
    }

    /**
     * @brief position() constructor
     * 
     * @note calls init()
     */
    Position()
    {
      init();
    }

    /**
     * @brief position(file_name, c1, c2, line_num) constructor
     * 
     * - multple chars
     * 
     * @param file_name name of file
     * @param c1 column start index
     * @param c2 column end index
     * @param line_num line number
     * 
     * @overload
     */
    Position(std::string file_name, int c1, int c2, int line_num)
      : m_file_name(file_name),
        m_column_nums{c1, c2},
        m_line_num(line_num)
    {}

    /**
     * @brief position(file_name, c, line_num) constructor
     * 
     * - single char
     * 
     * @param file_name name of file
     * @param c column index
     * @param line_num line number
     * 
     * @overload
     */
    Position(std::string file_name, int c, int line_num)
        : m_file_name(file_name),
          m_column_nums{c, c},
          m_line_num(line_num)
    {}
  };
}