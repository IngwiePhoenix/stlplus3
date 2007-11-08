#ifndef STLPLUS_PRINT_STRING
#define STLPLUS_PRINT_STRING
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  Functions for converting C/STL strings to string

  This is necessary for completeness, e.g. for use in print_vector for vector<string>

  ------------------------------------------------------------------------------*/
#include <string>
#include <iostream>
#include <stdexcept>

namespace stlplus
{

  void print_string(std::ostream& device, const std::string& value);

  void print_cstring(std::ostream& device, const char* value);

}

#endif
