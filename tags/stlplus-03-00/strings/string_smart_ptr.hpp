#ifndef STLPLUS_STRING_SMART_PTR
#define STLPLUS_STRING_SMART_PTR
////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton, 2007
//   License:   BSD License, see ../docs/license.html

//   Generate a string representation of a smart pointer

////////////////////////////////////////////////////////////////////////////////
#include "strings_fixes.hpp"
#include "smart_ptr.hpp"
#include <string>

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename T, typename C, typename S>
  std::string smart_ptr_to_string(const smart_ptr_base<T,C>& value,
                                  S to_string_fn,
                                  const std::string& null_string = "<null>",
                                  const std::string& prefix = "(",
                                  const std::string& suffix = ")");


} // end namespace stlplus

#include "string_smart_ptr.tpp"
#endif
