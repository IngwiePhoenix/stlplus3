/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "persistent_int.hpp"

////////////////////////////////////////////////////////////////////////////////

template<typename K, typename P, typename D>
void stlplus::dump_multiset(stlplus::dump_context& context, const std::multiset<K,P>& data, D dump_fn)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_unsigned(context,data.size());
  for (typename std::multiset<K,P>::const_iterator i = data.begin(); i != data.end(); i++)
    dump_fn(context,*i);
}

template<typename K, typename P, typename R>
void stlplus::restore_multiset(stlplus::restore_context& context, std::multiset<K,P>& data, R restore_fn)
  throw(stlplus::persistent_restore_failed)
{
  data.clear();
  unsigned size = 0;
  stlplus::restore_unsigned(context,size);
  typename std::multiset<K,P>::iterator i = data.begin();
  for (unsigned j = 0; j < size; j++)
  {
    K key;
    restore_fn(context,key);
    // inserting using an iterator is O(n) rather than O(n*log(n))
    i = data.insert(i, key);
  }
}

////////////////////////////////////////////////////////////////////////////////
