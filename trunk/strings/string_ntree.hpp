#ifndef STLPLUS_STRING_NTREE
#define STLPLUS_STRING_NTREE
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  Generate a string representation of an ntree

  ------------------------------------------------------------------------------*/
#include "ntree.hpp"
#include <string>

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename T, typename S>
  std::string ntree_to_string(const ntree<T>& values,
                              S to_string_fn,
                              const std::string& separator = "|",
                              const std::string& indent_string = "  ");

} // end namespace stlplus

#include "string_ntree.tpp"
#endif
