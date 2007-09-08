#ifndef STRINGS_BASIC_HPP
#define STRINGS_BASIC_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2004
License:   BSD License, see ../docs/license.html

Utilities for manipulating std::strings, missing from the STL or C++ libraries

------------------------------------------------------------------------------*/
#include "format_types.hpp"
#include <string>
#include <stdexcept>

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////
  // Conversions of Integer types to string
  ////////////////////////////////////////////////////////////////////////////////

  // The radix (i.e. base) for these conversions can be any value from base 2 to base 36
  // specifying any other radix causes std::invalid_argument to be thrown

  // The way in which the radix is displayed is defined in radix_types.hpp
  // If any other value is used, std::invalid_argument is thrown

  // The width argument specifies the number of numerical digits to use in the result
  // This is a minimum - if the value requires more digits then it will be wider than the width argument
  // However, if it is smaller, then it will be extended to the specified width
  // Then, the radix display prefix is added to this width

  // For example, using the hash representation of 0 in hex with width=4 gives:
  // 16#0000 - so there's 4 digits in the number part

  std::string bool_to_string(bool i,
                             unsigned radix = 10,
                             radix_display_t display = radix_c_style_or_hash,
                             unsigned width = 0)
    throw(std::invalid_argument);

  std::string short_to_string(short i,
                              unsigned radix = 10,
                              radix_display_t display = radix_c_style_or_hash,
                              unsigned width = 0)
    throw(std::invalid_argument);

  std::string unsigned_short_to_string(unsigned short i,
                                       unsigned radix = 10,
                                       radix_display_t display = radix_c_style_or_hash,
                                       unsigned width = 0)
    throw(std::invalid_argument);

  std::string int_to_string(int i,
                            unsigned radix = 10,
                            radix_display_t display = radix_c_style_or_hash,
                            unsigned width = 0)
    throw(std::invalid_argument);

  std::string unsigned_to_string(unsigned i,
                                 unsigned radix = 10,
                                 radix_display_t display = radix_c_style_or_hash,
                                 unsigned width = 0)
    throw(std::invalid_argument);

  std::string long_to_string(long i,
                             unsigned radix = 10,
                             radix_display_t display = radix_c_style_or_hash,
                             unsigned width = 0)
    throw(std::invalid_argument);

  std::string unsigned_long_to_string(unsigned long i,
                                      unsigned radix = 10,
                                      radix_display_t display = radix_c_style_or_hash,
                                      unsigned width = 0)
    throw(std::invalid_argument);

  std::string address_to_string(const void*,
                                unsigned radix = 16,
                                radix_display_t display = radix_c_style_or_hash,
                                unsigned width = 0)
    throw(std::invalid_argument);

  ////////////////////////////////////////////////////////////////////////////////
  // convert a real type to string
  ////////////////////////////////////////////////////////////////////////////////

  // Only decimal radix is supported

  // The way in which the number is displayed is defined in radix_types.hpp
  // Using any other value for the display type causes std::invalid_argument to be thrown

  std::string float_to_string(float f,
                              real_display_t display = display_mixed,
                              unsigned width = 0,
                              unsigned precision = 6)
    throw(std::invalid_argument);

  std::string double_to_string(double f,
                               real_display_t display = display_mixed,
                               unsigned width = 0,
                               unsigned precision = 6)
    throw(std::invalid_argument);

  ////////////////////////////////////////////////////////////////////////////////
  // Convert a string/char* to string
  // this is necessary for completeness, e.g. for use in vector_to_string for vector<string>
  ////////////////////////////////////////////////////////////////////////////////

  std::string string_to_string(const std::string& value);

  std::string cstring_to_string(const char* value);

  ////////////////////////////////////////////////////////////////////////////////
  // convert a string to a simple type
  ////////////////////////////////////////////////////////////////////////////////

  // Convert a string to an integer type
  // supports all the formats described above for the reverse conversion
  // If the radix is set to zero, the conversions deduce the radix from the string representation
  // So,
  //   0b prefix is binary,
  //   0 prefix is octal,
  //   0x is hex
  //   <base># prefix is my hash format
  // The radix must be either zero as explained above, or in the range 2 to 16
  // A non-zero radix should be used when the string value has no radix information and is non-decimal
  // e.g. the hex value FEDCBA has no indication that it is hex, so specify radix 16
  // Any other value of radix will cause std::invalid_argument to be thrown

  bool string_to_bool(const std::string& value,
                      unsigned radix = 0)
    throw(std::invalid_argument);

  short string_to_short(const std::string& value,
                        unsigned radix = 0)
    throw(std::invalid_argument);

  unsigned short string_to_unsigned_short(const std::string& value,
                                          unsigned radix = 0)
    throw(std::invalid_argument);

  int string_to_int(const std::string& value,
                    unsigned radix = 0)
    throw(std::invalid_argument);

  unsigned string_to_unsigned(const std::string& value,
                              unsigned radix = 0)
    throw(std::invalid_argument);

  long string_to_long(const std::string& value,
                      unsigned radix = 0)
    throw(std::invalid_argument);

  unsigned long string_to_unsigned_long(const std::string& value,
                                        unsigned radix = 0)
    throw(std::invalid_argument);

  void* string_to_address(const std::string& value,
                          unsigned radix = 0)
    throw(std::invalid_argument);

  ////////////////////////////////////////////////////////////////////////////////
  // Convert a string to a floating-point type

  float string_to_float(const std::string& value)
    throw(std::invalid_argument);

  double string_to_double(const std::string& value)
    throw(std::invalid_argument);

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus

#endif
