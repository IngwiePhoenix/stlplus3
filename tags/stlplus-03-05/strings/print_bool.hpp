#ifndef STLPLUS_PRINT_BOOL
#define STLPLUS_PRINT_BOOL
////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Southampton University 1999-2004
//              (c) Andy Rushton           2004-2009
//   License:   BSD License, see ../docs/license.html

//   Conversion of string to/from bool

////////////////////////////////////////////////////////////////////////////////
#include "strings_fixes.hpp"
#include "format_types.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////

  void print_bool(std::ostream& device, bool i,
                  unsigned radix = 10,
                  radix_display_t display = radix_c_style_or_hash,
                  unsigned width = 0)
    throw(std::invalid_argument);

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus

#endif
