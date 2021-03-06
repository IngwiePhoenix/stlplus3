#ifndef PERSISTENT_MULTIMAP_HPP
#define PERSISTENT_MULTIMAP_HPP
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  Persistence of STL multimap

  ------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"
#include <map>

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename K, typename T, typename P, typename DK, typename DT>
  void dump_multimap(dump_context&, const std::multimap<K,T,P>& data, DK key_dump_fn, DT val_dump_fn)
    throw(persistent_dump_failed);

  template<typename K, typename T, typename P, typename RK, typename RT>
  void restore_multimap(restore_context&, std::multimap<K,T,P>& data, RK key_restore_fn, RT val_restore_fn)
    throw(persistent_restore_failed);

} // end namespace stlplus

////////////////////////////////////////////////////////////////////////////////
#include "persistent_multimap.tpp"
#endif
