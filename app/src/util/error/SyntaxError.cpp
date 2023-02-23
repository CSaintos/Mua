#include "SyntaxError.hpp"

stem::SyntaxError::SyntaxError()
    : Error()
{}

stem::SyntaxError::SyntaxError(Position &pos, std::string details)
    : Error(pos, "Syntax Error", details)
{}