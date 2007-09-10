#ifndef PERSISTENT_DEQUE_HPP
#define PERSISTENT_DEQUE_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

Persistence of the STL deque

------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"
#include <deque>

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename T, typename D>
  void dump_deque(dump_context&, const std::deque<T>& data, D dump_fn) throw(persistent_dump_failed);

  template<typename T, typename R>
  void restore_deque(restore_context&, std::deque<T>& data, R restore_fn) throw(persistent_restore_failed);

} // end namespace stlplus

  ////////////////////////////////////////////////////////////////////////////////
#include "persistent_deque.tpp"
#endif
