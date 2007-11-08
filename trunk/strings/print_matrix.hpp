#ifndef STLPLUS_PRINT_MATRIX
#define STLPLUS_PRINT_MATRIX
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  Generate a string representation of a matrix

  ------------------------------------------------------------------------------*/
#include "matrix.hpp"
#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename T, typename S>
  void print_matrix(std::ostream& device,
                    const matrix<T>& values,
                    S print_fn,
                    const std::string& column_separator = "|",
                    const std::string& row_separator = ",");

} // end namespace stlplus

#include "print_matrix.tpp"
#endif
