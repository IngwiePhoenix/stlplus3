/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "persistent_pair.hpp"

////////////////////////////////////////////////////////////////////////////////

template<typename K, typename T, typename D1, typename D2>
void stlplus::dump_pair(stlplus::dump_context& context, const std::pair<K,T>& data, D1 dump_fn1, D2 dump_fn2)
  throw(stlplus::persistent_dump_failed)
{
  dump_fn1(context,data.first);
  dump_fn2(context,data.second);
}

template<typename K, typename T, typename R1, typename R2>
void stlplus::restore_pair(stlplus::restore_context& context, std::pair<K,T>& data, R1 restore_fn1, R2 restore_fn2)
  throw(stlplus::persistent_restore_failed)
{
  restore_fn1(context,data.first);
  restore_fn2(context,data.second);
}

////////////////////////////////////////////////////////////////////////////////
