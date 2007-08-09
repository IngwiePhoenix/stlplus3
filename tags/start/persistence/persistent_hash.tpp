/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "persistent_int.hpp"

////////////////////////////////////////////////////////////////////////////////

template<typename K, typename T, typename H, typename E, typename DK, typename DT>
void stlplus::dump_hash(stlplus::dump_context& context, const stlplus::hash<K,T,H,E>& data, DK key_fn, DT val_fn)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_unsigned(context,data.size());
  for (typename stlplus::hash<K,T,H,E>::const_iterator i = data.begin(); i != data.end(); i++)
  {
    key_fn(context,i->first);
    val_fn(context,i->second);
  }
}

template<typename K, typename T, typename H, typename E, typename RK, typename RT>
void stlplus::restore_hash(stlplus::restore_context& context, stlplus::hash<K,T,H,E>& data, RK key_fn, RT val_fn)
  throw(stlplus::persistent_restore_failed)
{
  data.erase();
  unsigned size = 0;
  stlplus::restore_unsigned(context,size);
  for (unsigned j = 0; j < size; j++)
  {
    K key;
    key_fn(context,key);
    val_fn(context,data[key]);
  }
}

////////////////////////////////////////////////////////////////////////////////
