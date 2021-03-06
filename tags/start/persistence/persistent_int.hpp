#ifndef PERSISTENT_INT_HPP
#define PERSISTENT_INT_HPP
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  Persistence of basic integer types

  ------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"

namespace stlplus
{

void dump_char(dump_context&, const char& data) throw(persistent_dump_failed);
void restore_char(restore_context&, char& data) throw(persistent_restore_failed);

void dump_signed_char(dump_context&, const signed char& data) throw(persistent_dump_failed);
void restore_signed_char(restore_context&, signed char& data) throw(persistent_restore_failed);

void dump_unsigned_char(dump_context&, const unsigned char& data) throw(persistent_dump_failed);
void restore_unsigned_char(restore_context&, unsigned char& data) throw(persistent_restore_failed);

void dump_short(dump_context&, const short& data) throw(persistent_dump_failed);
void restore_short(restore_context&, short& data) throw(persistent_restore_failed);

void dump_unsigned_short(dump_context&, const unsigned short& data) throw(persistent_dump_failed);
void restore_unsigned_short(restore_context&, unsigned short& data) throw(persistent_restore_failed);

void dump_int(dump_context&, const int& data) throw(persistent_dump_failed);
void restore_int(restore_context&, int& data) throw(persistent_restore_failed);

void dump_unsigned(dump_context&, const unsigned& data) throw(persistent_dump_failed);
void restore_unsigned(restore_context&, unsigned& data) throw(persistent_restore_failed);

void dump_long(dump_context&, const long& data) throw(persistent_dump_failed);
void restore_long(restore_context&, long& data) throw(persistent_restore_failed);

void dump_unsigned_long(dump_context&, const unsigned long& data) throw(persistent_dump_failed);
void restore_unsigned_long(restore_context&, unsigned long& data) throw(persistent_restore_failed);

////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus

#endif
