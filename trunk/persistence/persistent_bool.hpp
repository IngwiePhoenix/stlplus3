#ifndef STLPLUS_PERSISTENT_BOOL
#define STLPLUS_PERSISTENT_BOOL
////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton, 2007
//   License:   BSD License, see ../docs/license.html

//   Persistence of bool

////////////////////////////////////////////////////////////////////////////////

#include "persistence_fixes.hpp"
#include "persistent_contexts.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  void dump_bool(dump_context&, const bool& data) throw(persistent_dump_failed);
  void restore_bool(restore_context&, bool& data) throw(persistent_restore_failed);

} // end namespace stlplus

#endif
