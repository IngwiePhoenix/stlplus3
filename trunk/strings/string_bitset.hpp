#ifndef STLPLUS_STRING_BITSET
#define STLPLUS_STRING_BITSET
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  Generate a string representation of a bitset

  ------------------------------------------------------------------------------*/
#include <bitset>
#include <string>

namespace stlplus
{

  template<size_t N>
  std::string bitset_to_string(const std::bitset<N>& data);

} // end namespace stlplus

#include "string_bitset.tpp"
#endif
