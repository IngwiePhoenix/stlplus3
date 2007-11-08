#ifndef STLPLUS_PRINT_LIST
#define STLPLUS_PRINT_LIST
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  Generate a string representation of a list

  ------------------------------------------------------------------------------*/
#include <string>
#include <iostream>
#include <list>

namespace stlplus
{

  template<typename T, typename S>
  void print_list(std::ostream& device,
                  const std::list<T>& values,
                  S print_fn,
                  const std::string& separator = ",");

} // end namespace stlplus

#include "print_list.tpp"
#endif
