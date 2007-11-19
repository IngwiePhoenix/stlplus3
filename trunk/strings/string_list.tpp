////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton, 2007
//   License:   BSD License, see ../docs/license.html

//   template implementations

////////////////////////////////////////////////////////////////////////////////
#include "string_sequence.hpp"

namespace stlplus
{

  template<typename T, typename S>
  std::string list_to_string(const std::list<T>& values,
                             S to_string_fn,
                             const std::string& separator)
  {
    return sequence_to_string(values.begin(), values.end(), to_string_fn, separator);
  }

} // end namespace stlplus
