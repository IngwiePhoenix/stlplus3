#ifndef STLPLUS_PERSISTENT_FOURSOME
#define STLPLUS_PERSISTENT_FOURSOME
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  Persistence of STL foursome

  ------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"
#include "foursome.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename T1, typename T2, typename T3, typename T4, typename D1, typename D2, typename D3, typename D4>
  void dump_foursome(dump_context&, const stlplus::foursome<T1,T2,T3,T4>& data, 
                     D1 dump_fn1, D2 dump_fn2, D3 dump_fn3, D4 dump_fn4)
    throw(persistent_dump_failed);

  template<typename T1, typename T2, typename T3, typename T4, typename R1, typename R2, typename R3, typename R4>
  void restore_foursome(restore_context&, stlplus::foursome<T1,T2,T3,T4>& data,
                        R1 restore_fn1, R2 restore_fn2, R3 restore_fn3, R4 restore_fn4)
    throw(persistent_restore_failed);

} // end namespace stlplus

  ////////////////////////////////////////////////////////////////////////////////
#include "persistent_foursome.tpp"
#endif
