#ifndef PERSISTENT_BOOL_HPP
#define PERSISTENT_BOOL_HPP
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  Persistence of bool

  ------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"

namespace stlplus
{

void dump_bool(dump_context&, const bool& data) throw(persistent_dump_failed);
void restore_bool(restore_context&, bool& data) throw(persistent_restore_failed);

} // end namespace stlplus

#endif
