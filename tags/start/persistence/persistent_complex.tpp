/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////////

template<typename T, typename D>
void stlplus::dump_complex(stlplus::dump_context& context, const std::complex<T>& data, D dump_fn)
  throw(stlplus::persistent_dump_failed)
{
  dump_fn(context,data.real());
  dump_fn(context,data.imag());
}

template<typename T, typename R>
void stlplus::restore_complex(stlplus::restore_context& context, std::complex<T>& data, R restore_fn)
  throw(stlplus::persistent_restore_failed)
{
  T re, im;
  restore_fn(context,re);
  restore_fn(context,im);
  data = std::complex<T>(re, im);
}

////////////////////////////////////////////////////////////////////////////////
