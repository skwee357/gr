/**
* @file Exception.hpp
* @author Dmitri Koudriavtsev
* @brief Defenition of Exception class.
*/

#ifndef EXCEPTION_HPP_INCLUDED
#define EXCEPTION_HPP_INCLUDED

#include <string>

class Exception{
  public:
    /** Create exception.
    * @param what Reason of throwing exception.
    */
    Exception(const std::string& what);

    /** Destructor */
    ~Exception();

    /** What.
    * @return Reason of throwing exception.
    */
    const std::string& what() const;

  private:
    std::string _what; /**< Reason exception. */
};

#endif // EXCEPTION_HPP_INCLUDED
