/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "persistent_int.hpp"

////////////////////////////////////////////////////////////////////////////////

template<typename T, typename D>
void stlplus::dump_vector(stlplus::dump_context& context, const std::vector<T>& data, D dump_fn)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_unsigned(context,data.size());
  for (unsigned i = 0; i < data.size(); i++)
    dump_fn(context,data[i]);
}

template<typename T, typename R>
void stlplus::restore_vector(stlplus::restore_context& context, std::vector<T>& data, R restore_fn)
  throw(stlplus::persistent_restore_failed)
{
  unsigned size = 0;
  stlplus::restore_unsigned(context,size);
  data.resize(size);
  for (unsigned i = 0; i < size; i++)
    restore_fn(context,data[i]);
}

////////////////////////////////////////////////////////////////////////////////
