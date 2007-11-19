////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton, 2007
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////
#include "string_float.hpp"
#include "dprintf.hpp"
#include <ctype.h>
#include <stdlib.h>

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////
  // floating-point types

  std::string float_to_string(float f, real_display_t display, unsigned width, unsigned precision)
    throw(std::invalid_argument)
  {
    char* format = 0;
    switch(display)
    {
    case display_fixed:
      format = "%*.*f";
      break;
    case display_floating:
      format = "%*.*e";
      break;
    case display_mixed:
      format = "%*.*g";
      break;
    default:
      throw std::invalid_argument("invalid radix display value");
    }
    return dformat(format, width, precision, f);
  }

  std::string double_to_string(double f, real_display_t display, unsigned width, unsigned precision)
    throw(std::invalid_argument)
  {
    char* format = 0;
    switch(display)
    {
    case display_fixed:
      format = "%*.*f";
      break;
    case display_floating:
      format = "%*.*e";
      break;
    case display_mixed:
      format = "%*.*g";
      break;
    default:
      throw std::invalid_argument("invalid radix display value");
    }
    return dformat(format, width, precision, f);
  }

  ////////////////////////////////////////////////////////////////////////////////

  float string_to_float(const std::string& value)
    throw(std::invalid_argument)
  {
    return (float)string_to_double(value);
  }

  double string_to_double(const std::string& value)
    throw(std::invalid_argument)
  {
    // TODO - error checking
    return strtod(value.c_str(), 0);
  }

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus
