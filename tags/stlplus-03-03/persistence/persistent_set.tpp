////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Southampton University 1999-2004
//              (c) Andy Rushton           2004-2008
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////
#include "persistent_int.hpp"

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////

  template<typename K, typename P, typename D>
  void dump_set(dump_context& context, const std::set<K,P>& data, D dump_fn)
    throw(persistent_dump_failed)
  {
    dump_unsigned(context,data.size());
    for (typename std::set<K,P>::const_iterator i = data.begin(); i != data.end(); i++)
      dump_fn(context,*i);
  }

  template<typename K, typename P, typename R>
  void restore_set(restore_context& context, std::set<K,P>& data, R restore_fn)
    throw(persistent_restore_failed)
  {
    data.clear();
    unsigned size = 0;
    restore_unsigned(context,size);
    typename std::set<K,P>::iterator i = data.begin();
    for (unsigned j = 0; j < size; j++)
    {
      K key;
      restore_fn(context,key);
      // inserting using an iterator is O(n) rather than O(n*log(n))
      i = data.insert(i, key);
    }
  }

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus
