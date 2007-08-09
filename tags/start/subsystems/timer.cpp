/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "timer.hpp"
#include "dprintf.hpp"
#include "time.hpp"

////////////////////////////////////////////////////////////////////////////////

stlplus::timer::timer(void)
{
  reset();
}

stlplus::timer::~timer(void)
{
}

void stlplus::timer::reset(void)
{
  m_clock = clock();
  m_time = time(0);
}

float stlplus::timer::cpu(void) const
{
  return ((float)(clock() - m_clock)) / ((float)CLOCKS_PER_SEC);
}

float stlplus::timer::elapsed(void) const
{
  return ((float)(time(0) - m_time));
}

std::string stlplus::timer::text(void) const
{
  return dformat("%4.2fs CPU, %s elapsed", cpu(), delaytime_string(time(0)-m_time).c_str());
}

////////////////////////////////////////////////////////////////////////////////

std::ostream& stlplus::operator << (std::ostream& str, const timer& t)
{
  return str << t.text();
}

////////////////////////////////////////////////////////////////////////////////
