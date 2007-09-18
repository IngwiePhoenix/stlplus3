#ifndef STLPLUS_PERSISTENT_POLYMORPH_HPP
#define STLPLUS_PERSISTENT_POLYMORPH_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

Persistence for pointers to polymorphic classes using the callback approach.

In other words, this works on a set of classes. Each subclass has a set of
callback (non-method) functions that enable create/dump/restore operations.
Each subclass must be registered with the persistence dump/restore context
so that the system knows how to handle it.

This approach is suited to classes that cannot be modified to add
persistence methods. See persistent_interface for a more C++-like way of
handling polymorphism.

Objects are always dumped/restored as pointers to the superclass T.

Multiple pointers to the same object are handled in the same way as for
simple pointers

Only classes registered with the context can be dumped and restored as
polymorphic types - see dump_context::register_callback and
restore_context::register_callback. Attempting to use any unrecognised class
will throw an exception.

------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename T>
  void dump_polymorph(dump_context&, const T* const data)
    throw(persistent_dump_failed);

  template<typename T>
  void restore_polymorph(restore_context&, T*& data)
    throw(persistent_restore_failed);

} // end namespace stlplus

  ////////////////////////////////////////////////////////////////////////////////
#include "persistent_polymorph.tpp"
#endif
