#ifndef PERSISTENT_SMART_PTR_HPP
#define PERSISTENT_SMART_PTR_HPP
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  Persistence of STLplus smart_ptr

  ------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"
#include "smart_ptr.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  // smart_ptr - uses dump/restore_pointer on the contents

  template<typename T, typename DE>
  void dump_smart_ptr(dump_context&, const smart_ptr<T>& data, DE dump_element)
    throw(persistent_dump_failed);

  template<typename T, typename RE>
  void restore_smart_ptr(restore_context&, smart_ptr<T>& data, RE restore_element)
    throw(persistent_restore_failed);

  // smart_ptr_clone using the polymorphic callback approach - uses dump/restore_polymorph on the contents

  template<typename T>
  void dump_smart_ptr_clone_polymorph(dump_context&, const smart_ptr_clone<T>& data)
    throw(persistent_dump_failed);

  template<typename T>
  void restore_smart_ptr_clone_polymorph(restore_context&, smart_ptr_clone<T>& data)
    throw(persistent_restore_failed);

  // smart_ptr_clone using the interface approach - uses dump/restore_interface on the contents

  template<typename T>
  void dump_smart_ptr_clone_interface(dump_context&, const smart_ptr_clone<T>& data)
    throw(persistent_dump_failed);

  template<typename T>
  void restore_smart_ptr_clone_interface(restore_context&, smart_ptr_clone<T>& data)
    throw(persistent_restore_failed);

  // smart_ptr_nocopy is not made persistent because if it is uncopyable, it must be undumpable

  // smart_ptr_clone - do not use directly - this is called from the
  // specialisations for each type of smart pointer clone above

  template<typename T, typename DP>
  void dump_smart_ptr_clone(dump_context&, const smart_ptr_clone<T>& data, DP dump_ptr)
    throw(persistent_dump_failed);

  template<typename T, typename RP>
  void restore_smart_ptr_clone(restore_context&, smart_ptr_clone<T>& data, RP restore_ptr)
    throw(persistent_restore_failed);

} // end namespace stlplus

////////////////////////////////////////////////////////////////////////////////
#include "persistent_smart_ptr.tpp"
#endif
