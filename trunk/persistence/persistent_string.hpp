#ifndef PERSISTENT_STRING_HPP
#define PERSISTENT_STRING_HPP
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  Persistence for STL strings

  ------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"
#include <string>

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  // basic_string

  template<typename charT, typename traits, typename allocator, typename D>
  void dump_basic_string(dump_context&, const std::basic_string<charT,traits,allocator>& data, D dump_fn)
    throw(persistent_dump_failed);

  template<typename charT, typename traits, typename allocator, typename R>
  void restore_basic_string(restore_context&, std::basic_string<charT,traits,allocator>& data, R restore_fn)
    throw(persistent_restore_failed);

  // string

  void dump_string(dump_context&, const std::string& data)
    throw(persistent_dump_failed);

  void restore_string(restore_context&, std::string& data) 
    throw(persistent_restore_failed);

} // end namespace stlplus

////////////////////////////////////////////////////////////////////////////////
#include "persistent_string.tpp"
#endif
