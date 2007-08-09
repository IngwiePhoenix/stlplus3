/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  format: magic_key [ data ]

  ------------------------------------------------------------------------------*/
#include "persistent_int.hpp"

template<typename T>
void stlplus::dump_xref(dump_context& context, const T* const data)
  throw(persistent_dump_failed)
{
  // register the address and get the magic key for it
  std::pair<bool,unsigned> mapping = context.pointer_map(data);
  // if this is the first view of this pointer, simply throw an exception
  if (!mapping.first) throw persistent_dump_failed("tried to dump a cross-reference not seen before");
  // otherwise, just dump the magic key
  stlplus::dump_unsigned(context,mapping.second);
}

template<typename T>
void stlplus::restore_xref(restore_context& context, T*& data)
  throw(persistent_restore_failed)
{
  // Note: I do not try to delete the old data because this is a cross-reference
  // get the magic key
  unsigned magic = 0;
  stlplus::restore_unsigned(context,magic);
  // now lookup the magic key to see if this pointer has already been restored
  // null pointers are always flagged as already restored
  std::pair<bool,void*> address = context.pointer_map(magic);
  // if this is the first view of this pointer, simply throw an exception
  if (!address.first) throw persistent_restore_failed("tried to restore a cross-reference not seen before");
  // seen before, so simply assign the old address
  data = (T*)address.second;
}
