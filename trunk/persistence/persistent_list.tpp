/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "persistent_int.hpp"

////////////////////////////////////////////////////////////////////////////////

template<typename T, typename D>
void stlplus::dump_list(stlplus::dump_context& context, const std::list<T>& data, D dump_fn)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_unsigned(context,data.size());
  for (typename std::list<T>::const_iterator i = data.begin(); i != data.end(); i++)
    dump_fn(context,*i);
}

template<typename T, typename R>
void stlplus::restore_list(stlplus::restore_context& context, std::list<T>& data, R restore_fn)
  throw(stlplus::persistent_restore_failed)
{
  data.clear();
  unsigned size = 0;
  stlplus::restore_unsigned(context,size);
  for (unsigned i = 0; i < size; i++)
  {
    data.push_back(T());
    restore_fn(context,data.back());
  }
}

////////////////////////////////////////////////////////////////////////////////
