#ifndef PERSISTENT_XREF_HPP
#define PERSISTENT_XREF_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

Persistence for cross-references to persistent objects

A cross-reference is a pointer to an object that has definitely been dumped
already by one of dump_pointer, dump_interface or dump_polymorph, i.e. by
one of the dump routines for pointers to objects.

These are typically used in data structures as back-pointers or pointers
between nodes.

For example, you may have a tree with cross links. Dump the tree as the
primary data structure first, then dump the cross links as cross-references
afterwards. The whole tree must be dumped before any cross-references to
ensure that all cross-references are known to the persistence system.

These functions will throw an exception if the cross-reference points to
something not dumped before.

------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename T>
  void dump_xref(dump_context&, const T* const data)
    throw(persistent_dump_failed);

  template<typename T>
  void restore_xref(restore_context&, T*& data)
    throw(persistent_restore_failed);

} // end namespace stlplus

  ////////////////////////////////////////////////////////////////////////////////
#include "persistent_xref.tpp"
#endif
