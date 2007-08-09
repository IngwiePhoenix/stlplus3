/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "persistent_int.hpp"
////////////////////////////////////////////////////////////////////////////////

template<typename T, typename DT>
void stlplus::dump_matrix(stlplus::dump_context& context, const stlplus::matrix<T>& data,
                           DT dump_fn)
  throw(stlplus::persistent_dump_failed)
{
  unsigned rows = data.rows();
  unsigned cols = data.columns();
  stlplus::dump_unsigned(context, rows);
  stlplus::dump_unsigned(context, cols);
  for (unsigned r = 0; r < rows; r++)
    for (unsigned c = 0; c < cols; c++)
      dump_fn(context, data(r,c));
}

////////////////////////////////////////////////////////////////////////////////

template<typename T, typename RT>
void stlplus::restore_matrix(stlplus::restore_context& context, stlplus::matrix<T>& data,
                              RT restore_fn)
  throw(stlplus::persistent_restore_failed)
{
  unsigned rows = 0;
  stlplus::restore_unsigned(context, rows);
  unsigned cols = 0;
  stlplus::restore_unsigned(context, cols);
  data.resize(rows,cols);
  for (unsigned r = 0; r < rows; r++)
    for (unsigned c = 0; c < cols; c++)
      restore_fn(context, data(r,c));
}

////////////////////////////////////////////////////////////////////////////////
