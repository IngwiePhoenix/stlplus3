#ifndef STLPLUS_ARITHMETIC_EXCEPTIONS_HPP
#define STLPLUS_ARITHMETIC_EXCEPTIONS_HPP
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  Adds missing arithmetic exceptions used in this library but missing from std

  ------------------------------------------------------------------------------*/
#include <string>
#include <stdexcept>

namespace stlplus
{

////////////////////////////////////////////////////////////////////////////////
// thrown by division when the divisor is zero
// This is a subclass of std::logic_error so can be caught by a generic catch clause for the superclass

  class divide_by_zero : public std::logic_error {
  public:
    divide_by_zero (const std::string& what_arg): std::logic_error (what_arg) { }
  };

////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus

#endif
