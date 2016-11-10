/**
* @file Exception.cpp
* @author Dmitri Koudriavtsev
* @brief Realization of Exception class.
*/

#include "Exception.hpp"

Exception::Exception(const std::string& what)
{
  _what = what;
}

Exception::~Exception()
{
}

const std::string& Exception::what() const
{
  return _what;
}
