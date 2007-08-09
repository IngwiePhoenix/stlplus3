/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "persistent_int.hpp"

////////////////////////////////////////////////////////////////////////////////
// STL strings

template<typename charT, typename traits, typename allocator, typename D>
void stlplus::dump_basic_string(stlplus::dump_context& context, const std::basic_string<charT,traits,allocator>& data, D dump_fn)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_unsigned(context, data.size());
  for (unsigned i = 0; i < data.size(); i++)
    dump_fn(context,data[i]);
}

template<typename charT, typename traits, typename allocator, typename R>
void stlplus::restore_basic_string(stlplus::restore_context& context, std::basic_string<charT,traits,allocator>& data, R restore_fn)
  throw(stlplus::persistent_restore_failed)
{
  data.erase();
  unsigned size = 0;
  stlplus::restore_unsigned(context, size);
  for (unsigned i = 0; i < size; i++)
  {
    charT ch;
    restore_fn(context,ch);
    data += ch;
  }
}

////////////////////////////////////////////////////////////////////////////////
