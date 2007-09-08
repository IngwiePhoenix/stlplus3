/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

------------------------------------------------------------------------------*/
#include "strings_stl.hpp"

namespace stlplus
{

////////////////////////////////////////////////////////////////////////////////
// special case of vector<bool>

std::string to_string(const std::vector<bool>& values)
{
  std::string result;
  for (size_t i = 0; i < values.size(); i++)
    result.append(1, values[i] ? '1' : '0');
  return result;
}

////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus
