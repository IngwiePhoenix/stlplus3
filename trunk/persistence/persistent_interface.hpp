#ifndef STLPLUS_PERSISTENT_INTERFACE
#define STLPLUS_PERSISTENT_INTERFACE
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  Persistence for pointers to polymorphic classes using the interface approach.

  In other words, this works on a set of classes derived from a common
  superclass called persistent which is declared as an interface. Each
  subclass has a set of methods that enable clone/dump/restore operations.
  Each subclass must be registered with the persistence dump/restore context
  so that the system knows how to dump it.

  This approach is suited to classes that can be modified to add persistence
  methods. See persistent_polymorph for a non-invasive way of handling
  polymorphism.

  Objects are always dumped/restored as pointers to the superclass T.

  Multiple pointers to the same object are handled in the same way as for
  simple pointers

  Only classes registered with the context can be dumped and restored as
  polymorphic types - see dump_context::register_interface and
  restore_context::register_interface. Attempting to use any unrecognised class
  will throw an exception.

  ------------------------------------------------------------------------------*/
#include "persistent.hpp"
#include "persistent_contexts.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename T>
  void dump_interface(dump_context&, const T* const data)
    throw(persistent_dump_failed);

  template<typename T>
  void restore_interface(restore_context&, T*& data)
    throw(persistent_restore_failed);

} // end namespace stlplus

  ////////////////////////////////////////////////////////////////////////////////
#include "persistent_interface.tpp"
#endif
