#ifndef STLPLUS_PERSISTENT_SHARED_PTR
#define STLPLUS_PERSISTENT_SHARED_PTR
////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton           2011 onwards
//   License:   BSD License, see ../docs/license.html

//   Persistence of STL shared_ptr

////////////////////////////////////////////////////////////////////////////////

#include "persistence_fixes.hpp"
#include "persistent_contexts.hpp"
#include <memory>

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  // shared_ptr - uses dump/restore_pointer on the contents

  template<typename T, typename DE>
  void dump_shared_ptr(dump_context&, const std::shared_ptr<T>& data, DE dump_element)
    throw(persistent_dump_failed);

  template<typename T, typename RE>
  void restore_shared_ptr(restore_context&, std::shared_ptr<T>& data, RE restore_element)
    throw(persistent_restore_failed);

} // end namespace stlplus

  ////////////////////////////////////////////////////////////////////////////////
#include "persistent_shared_ptr.tpp"
#endif
