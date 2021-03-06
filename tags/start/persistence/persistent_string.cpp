/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "persistent_string.hpp"
#include "persistent_int.hpp"

////////////////////////////////////////////////////////////////////////////////

void stlplus::dump_string(stlplus::dump_context& context, const std::string& data)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_basic_string(context, data, stlplus::dump_char);
}

void stlplus::restore_string(stlplus::restore_context& context, std::string& data)
  throw(stlplus::persistent_restore_failed)
{
  stlplus::restore_basic_string(context, data, stlplus::restore_char);
}

////////////////////////////////////////////////////////////////////////////////
