////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton, 2007
//   License:   BSD License, see ../docs/license.html

//   String conversion functions for the infinite precision integer type inf

////////////////////////////////////////////////////////////////////////////////

// can be excluded from the build to break the dependency on the portability library
#ifndef NO_STLPLUS_INF

#include "print_inf.hpp"
#include "string_inf.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  void print_inf(std::ostream& device,
                 const stlplus::inf& data,
                 unsigned radix,
                 radix_display_t display,
                 unsigned width)
    throw(std::invalid_argument)
  {
    device << inf_to_string(data, radix, display, width);
  }


////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus

#endif
