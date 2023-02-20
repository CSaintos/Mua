#include "Error.hpp"

stem::Error::Error()
{}

stem::Error::Error(Position &pos, const std::string &err_name, std::string &details)
  : m_pos(pos), m_err_name(err_name), m_details(details)
{}

/*
stem::Error::~Error()
{}
*/

std::string stem::Error::to_string()
{
  m_ss.str(std::string());

  m_ss << m_err_name << ": " << m_details << std::endl
    << "File: " << m_pos.m_file_name << ", line: " << m_pos.m_line_num
    << std::endl << "Between columns: " << m_pos.m_column_nums[0]
    << ", " << m_pos.m_column_nums[1] << std::endl;

  return m_ss.str();
}

// stem::IllegalCharError::IllegalCharError()
//     : Error()
// {}

// stem::IllegalCharError::IllegalCharError(Position &pos, std::string details)
//     : Error(pos, "Illegal Character", details)
// {}

// /*
// stem::IllegalCharError::~IllegalCharError()
// {}
// */

// stem::SyntaxError::SyntaxError()
//     : Error()
// {}

// stem::SyntaxError::SyntaxError(Position &pos, std::string details)
//     : Error(pos, "Syntax Error", details)
// {}
