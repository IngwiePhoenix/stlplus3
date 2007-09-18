#ifndef STLPLUS_PERSISTENT_CSTRING_HPP
#define STLPLUS_PERSISTENT_CSTRING_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

Persistence of C-style char* strings

These are handled differently to other pointer types

Warning! This means that pointers to char cannot be supported, since there
is no type difference between a pointer to char and a C-style array of char.

Warning! The restore deletes any old value of the data parameter and
allocates a new char* which is (just) big enough and assigns it to the data
field. This is because there is no way of knowing how long a char* is so
the passed parameter is not safe to use. The allocation is done using
standard new. If the data field is non-null on entry it will be deleted by
standard delete. Best to make it null in the first place.

------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  void dump_cstring(dump_context&, const char* data) throw(persistent_dump_failed);
  void restore_cstring(restore_context&, char*& data) throw(persistent_restore_failed);

} // end namespace stlplus

  ////////////////////////////////////////////////////////////////////////////////
#endif
