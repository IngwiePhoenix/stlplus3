#ifndef STLPLUS_PERSISTENT_BITSET_HPP
#define STLPLUS_PERSISTENT_BITSET_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

Persistence of STL bitset

------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"
#include <bitset>

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<size_t N>
  void dump_bitset(dump_context&, const std::bitset<N>& data) throw(persistent_dump_failed);

  template<size_t N>
  void restore_bitset(restore_context&, std::bitset<N>& data) throw(persistent_restore_failed);

} // end namespace stlplus

  ////////////////////////////////////////////////////////////////////////////////
#include "persistent_bitset.tpp"
#endif
