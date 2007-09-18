#ifndef STLPLUS_PERSISTENT_ENUM_HPP
#define STLPLUS_PERSISTENT_ENUM_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

Persistence of enumeration types

------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename T>
  void dump_enum(dump_context&, const T& data) throw(persistent_dump_failed);

  template<typename T>
  void restore_enum(restore_context&, T& data) throw(persistent_restore_failed);

} // end namespace stlplus

  ////////////////////////////////////////////////////////////////////////////////
#include "persistent_enum.tpp"
#endif
