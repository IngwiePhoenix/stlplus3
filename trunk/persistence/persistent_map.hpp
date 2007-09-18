#ifndef STLPLUS_PERSISTENT_MAP_HPP
#define STLPLUS_PERSISTENT_MAP_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

Persistence for STL map

------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"
#include <map>

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename K, typename T, typename P, typename DK, typename DT>
  void dump_map(dump_context&, const std::map<K,T,P>& data, DK key_dump_fn, DT val_dump_fn)
    throw(persistent_dump_failed);

  template<typename K, typename T, typename P, typename RK, typename RT>
  void restore_map(restore_context&, std::map<K,T,P>& data, RK key_restore_fn, RT val_restore_fn)
    throw(persistent_restore_failed);

} // end namespace stlplus

  ////////////////////////////////////////////////////////////////////////////////
#include "persistent_map.tpp"
#endif
