#ifndef STLPLUS_PERSISTENT_EXCEPTIONS_HPP
#define STLPLUS_PERSISTENT_EXCEPTIONS_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

Exceptions thrown by persistence routines

------------------------------------------------------------------------------*/
#include <stdexcept>
#include <string>

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////

  // exception thrown if you try to dump or restore an illegal polymorphic type
  class persistent_illegal_type : public std::logic_error
  {
  public:
    persistent_illegal_type(const std::string& type) throw();
    persistent_illegal_type(unsigned key) throw();
    ~persistent_illegal_type(void) throw();
  };

  // exception thrown if a dump fails for any reason - but typically because the output stream couldn't take the data
  class persistent_dump_failed : public std::runtime_error
  {
  public:
    persistent_dump_failed(const std::string& message) throw();
    ~persistent_dump_failed(void) throw();
  };

  // exception thrown if you try to restore from an out of date or unrecognised byte stream
  class persistent_restore_failed : public std::runtime_error
  {
  public:
    persistent_restore_failed(const std::string& message) throw();
    ~persistent_restore_failed(void) throw();
  };

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus

#endif
