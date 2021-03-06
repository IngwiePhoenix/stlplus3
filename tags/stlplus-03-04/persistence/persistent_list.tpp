////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Southampton University 1999-2004
//              (c) Andy Rushton           2004-2009
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////
#include "persistent_int.hpp"

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////

  template<typename T, typename D>
  void dump_list(dump_context& context, const std::list<T>& data, D dump_fn)
    throw(persistent_dump_failed)
  {
    dump_unsigned(context,data.size());
    for (typename std::list<T>::const_iterator i = data.begin(); i != data.end(); i++)
      dump_fn(context,*i);
  }

  template<typename T, typename R>
  void restore_list(restore_context& context, std::list<T>& data, R restore_fn)
    throw(persistent_restore_failed)
  {
    data.clear();
    unsigned size = 0;
    restore_unsigned(context,size);
    for (unsigned i = 0; i < size; i++)
    {
      data.push_back(T());
      restore_fn(context,data.back());
    }
  }

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus
