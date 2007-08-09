/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////
// enumeration types

template<typename T>
void stlplus::dump_enum(stlplus::dump_context& context, const T& data)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_unsigned(context,(unsigned)data);
}

template<typename T>
void stlplus::restore_enum(stlplus::restore_context& context, T& data)
  throw(stlplus::persistent_restore_failed)
{
  unsigned value = 0;
  stlplus::restore_unsigned(context, value);
  data = (T)value;
}

////////////////////////////////////////////////////////////////////////////////
