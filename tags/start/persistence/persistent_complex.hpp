#ifndef PERSISTENT_COMPLEX_HPP
#define PERSISTENT_COMPLEX_HPP
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  Set of persistence routines for the STL classes

  ------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"
#include <complex>

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename T, typename D>
  void dump_complex(dump_context&, const std::complex<T>& data, D dump_fn) throw(persistent_dump_failed);

  template<typename T, typename R>
  void restore_complex(restore_context&, std::complex<T>& data, R restore_fn) throw(persistent_restore_failed);

} // end namespace stlplus

////////////////////////////////////////////////////////////////////////////////
#include "persistent_complex.tpp"
#endif
