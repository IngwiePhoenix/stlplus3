/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/

namespace stlplus
{

  template<typename T, typename C, typename S>
  std::string smart_ptr_to_string(const smart_ptr_base<T,C>& value,
                                  S to_string_fn,
                                  const std::string& null_string,
                                  const std::string& prefix,
                                  const std::string& suffix)
  {
    return value ? (prefix + to_string_fn(*value) + suffix) : null_string;
  }

} // end namespace stlplus

