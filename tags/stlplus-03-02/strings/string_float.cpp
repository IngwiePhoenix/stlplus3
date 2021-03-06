////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton, 2007
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////
#include "string_float.hpp"
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

namespace stlplus
{

  // added as a local copy to break the dependency on the portability library
  static std::string local_dformat(const char* format, ...) throw(std::invalid_argument)
  {
    std::string formatted;
    va_list args;
    va_start(args, format);
#ifdef MSWINDOWS
    int length = 0;
    char* buffer = 0;
    for(int buffer_length = 256; ; buffer_length*=2)
    {
      buffer = (char*)malloc(buffer_length);
      if (!buffer) throw std::invalid_argument("string_float");
      length = _vsnprintf(buffer, buffer_length-1, format, args);
      if (length >= 0)
      {
        buffer[length] = 0;
        formatted += std::string(buffer);
        free(buffer);
        break;
      }
      free(buffer);
    }
#else
    char* buffer = 0;
    int length = vasprintf(&buffer, format, args);
    if (!buffer) throw std::invalid_argument("string_float");
    if (length >= 0)
      formatted += std::string(buffer);
    free(buffer);
#endif
    va_end(args);
    if (length < 0) throw std::invalid_argument("string_float");
    return formatted;
  }

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
    return local_dformat(format, width, precision, f);
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
    return local_dformat(format, width, precision, f);
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
