/*------------------------------------------------------------------------------

  Author: Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html
  
  The set of general exceptions thrown by STLplus components

------------------------------------------------------------------------------*/
#include "exceptions.hpp"

////////////////////////////////////////////////////////////////////////////////

stlplus::null_dereference::null_dereference(const std::string& description) throw() :
std::logic_error(std::string("null dereference: ") + description)
{
}

stlplus::null_dereference::~null_dereference(void) throw() 
{
}

////////////////////////////////////////////////////////////////////////////////

stlplus::end_dereference::end_dereference(const std::string& description) throw() :
  std::logic_error("end dereference: " + description)
{
}

stlplus::end_dereference::~end_dereference(void) throw()
{
}

////////////////////////////////////////////////////////////////////////////////

stlplus::wrong_object::wrong_object(const std::string& description) throw() :
  std::logic_error("wrong object: " + description)
{
}

stlplus::wrong_object::~wrong_object(void) throw()
{
}

////////////////////////////////////////////////////////////////////////////////

stlplus::illegal_copy::illegal_copy(const std::string& description) throw() :
  std::logic_error("illegal copy: " + description)
{
}

stlplus::illegal_copy::~illegal_copy(void) throw()
{
}

////////////////////////////////////////////////////////////////////////////////

