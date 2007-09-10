#ifndef PERSISTENT_FLOAT_HPP
#define PERSISTENT_FLOAT_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

Persistence of floating-point types

Note: despite years and years of IEEE standardisation, not all
architectures use IEEE-standard representations of floating-point numbers.
Therefore a binary dump is not necessarily portable between platforms.
Solving this is (currently) beyond the scope of the STLplus project.

If you want to be strictly portable to all platforms, do not dump/restore float

------------------------------------------------------------------------------*/
#include "persistent_contexts.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  void dump_float(dump_context&, const float& data) throw(persistent_dump_failed);
  void restore_float(restore_context&, float& data) throw(persistent_restore_failed);

  void dump_double(dump_context&, const double& data) throw(persistent_dump_failed);
  void restore_double(restore_context&, double& data) throw(persistent_restore_failed);

} // end namespace stlplus

  ////////////////////////////////////////////////////////////////////////////////
#endif
