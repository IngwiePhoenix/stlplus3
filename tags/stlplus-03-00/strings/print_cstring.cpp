////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton, 2007
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////
#include "print_cstring.hpp"

namespace stlplus
{

  void print_cstring(std::ostream& device, const char* value)
  {
    device << value;
  }

} // end namespace stlplus
