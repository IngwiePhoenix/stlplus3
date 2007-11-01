/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "string_sequence.hpp"

namespace stlplus
{

  template<typename T, typename S>
  std::string vector_to_string(const std::vector<T>& values,
                               S to_string_fn,
                               const std::string& separator)
  {
    return sequence_to_string(values.begin(), values.end(), to_string_fn, separator);
  }

} // end namespace stlplus
