#include "IllegalCharError.hpp"

stem::IllegalCharError::IllegalCharError()
    : Error()
{}

stem::IllegalCharError::IllegalCharError(Position &pos, std::string details)
    : Error(pos, "Illegal Character", details)
{}

/*
stem::IllegalCharError::~IllegalCharError()
{}
*/