/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "persistent_int.hpp"

////////////////////////////////////////////////////////////////////////////////

template<typename T, typename D>
void stlplus::dump_deque(stlplus::dump_context& context, const std::deque<T>& data, D dump_fn)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_unsigned(context,data.size());
  for (typename std::deque<T>::const_iterator i = data.begin(); i != data.end(); i++)
    dump_fn(context,*i);
}

template<typename T, typename R>
void stlplus::restore_deque(stlplus::restore_context& context, std::deque<T>& data, R restore_fn)
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
