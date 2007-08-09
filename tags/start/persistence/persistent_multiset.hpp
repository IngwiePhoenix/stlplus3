#ifndef PERSISTENT_MULTISET_HPP
#define PERSISTENT_MULTISET_HPP
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  Persistence of STL multiset

  ------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"
#include <set>

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename K, typename P, typename D>
  void dump_multiset(dump_context&, const std::multiset<K,P>& data, D dump_fn)
    throw(persistent_dump_failed);

  template<typename K, typename P, typename R>
  void restore_multiset(restore_context&, std::multiset<K,P>& data, R restore_fn)
    throw(persistent_restore_failed);

} // end namespace stlplus

////////////////////////////////////////////////////////////////////////////////
#include "persistent_multiset.tpp"
#endif
