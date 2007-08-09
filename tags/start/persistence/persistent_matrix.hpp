#ifndef PERSISTENT_MATRIX_HPP
#define PERSISTENT_MATRIX_HPP
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  Persistence of STLplus matrix

  ------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"
#include "matrix.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename T, typename DT>
  void dump_matrix(dump_context&, const matrix<T>& data, DT dump_fn)
    throw(persistent_dump_failed);

  template<typename T, typename RT>
  void restore_matrix(restore_context&, matrix<T>& data, RT restore_fn)
    throw(persistent_restore_failed);

} // end namespace stlplus

////////////////////////////////////////////////////////////////////////////////
#include "persistent_matrix.tpp"
#endif
