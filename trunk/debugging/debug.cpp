/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "debug.hpp"

////////////////////////////////////////////////////////////////////////////////

static std::string to_string(int number)
{
  // use sprintf in a very controlled way that cannot overrun
  char* buffer = new char[50];
  sprintf(buffer, "%i", number);
  std::string result = buffer;
  delete buffer;
  return result;
}

////////////////////////////////////////////////////////////////////////////////

stlplus::assert_failed::assert_failed(const char* file, int line, const char* function, const std::string& message) throw() : 
  std::logic_error(std::string(file) + std::string(":") + to_string(line) + std::string(":") + 
                   std::string(function ? function : "") + std::string(": assertion failed: ") + message)
{
}

stlplus::assert_failed::~assert_failed(void) throw()
{
}

////////////////////////////////////////////////////////////////////////////////

static unsigned _debug_depth = 0;
static bool _debug_global = false;
static bool _debug_set = false;
static bool _debug_recurse = false;
static bool _debug_read = false;
static char* _debug_match = 0;
static const stlplus::debug_trace* debug_last = 0;

void stlplus::debug_global(const char* file, int line, const char* function, bool state)
{
  _debug_global = state;
  fprintf(stderr, "%s:%i:[%i]%s ", file, line, _debug_depth, function ? function : "");
  fprintf(stderr, "debug global : %s\n", _debug_global ? "on" : "off");
}

void stlplus::debug_assert_fail(const char* file, int line, const char* function, const char* test) 
  throw(stlplus::assert_failed)
{
  fprintf(stderr, "%s:%i:[%i]%s: assertion failed: %s\n", 
          file, line, _debug_depth, function ? function : "", test);
  if (debug_last) debug_last->stackdump();
  throw stlplus::assert_failed(file, line, function, std::string(test));
}

////////////////////////////////////////////////////////////////////////////////

stlplus::debug_trace::debug_trace(const char* f, int l, const char* fn) :
  m_file(f), m_line(l), m_function(fn ? fn : ""), 
  m_depth(0), m_last(debug_last), m_dbg(false), m_old(false)
{
  if (!_debug_read)
  {
    _debug_match = getenv("DEBUG");
    _debug_recurse = getenv("DEBUG_LOCAL") == 0;
    _debug_read = true;
  }
  m_dbg = _debug_set || (_debug_match && (!_debug_match[0] || (strcmp(_debug_match, m_file) == 0)));
  m_old = _debug_set;
  if (m_dbg && _debug_recurse)
    _debug_set = true;
  m_depth = ++_debug_depth;
  debug_last = this;
  if (debug()) report(std::string("entering ") + (m_function ? m_function : ""));
}

stlplus::debug_trace::~debug_trace(void)
{
  if (debug()) report("leaving");
  --_debug_depth;
  _debug_set = m_old;
  debug_last = m_last;
}

const char* stlplus::debug_trace::file(void) const
{
  return m_file;
}

int stlplus::debug_trace::line(void) const
{
  return m_line;
}

bool stlplus::debug_trace::debug(void) const
{
  return m_dbg || _debug_global;
}

void stlplus::debug_trace::debug_on(int l, bool recurse)
{
  m_dbg = true;
  m_old = _debug_set;
  if (recurse)
    _debug_set = true;
  report(l, std::string("debug on") + (recurse ? " recursive" : ""));
}

void stlplus::debug_trace::debug_off(int l)
{
  if (debug()) report(l, std::string("debug off"));
  m_dbg = false;
  _debug_set = m_old;
}

void stlplus::debug_trace::prefix(int l) const
{
  fprintf(stderr, "%s:%i:[%i]%s ", m_file, l, m_depth, m_function ? m_function : "");
}

void stlplus::debug_trace::do_report(int l, const std::string& message) const
{
  prefix(l);
  fprintf(stderr, "%s\n", message.c_str());
  fflush(stderr);
}

void stlplus::debug_trace::do_report(const std::string& message) const
{
  do_report(m_line, message);
}

void stlplus::debug_trace::report(int l, const std::string& message) const
{
  do_report(l, message);
}

void stlplus::debug_trace::report(const std::string& message) const
{
  report(m_line, message);
}

void stlplus::debug_trace::error(int l, const std::string& message) const
{
  do_report(l, "ERROR: " + message);
}

void stlplus::debug_trace::error(const std::string& message) const
{
  error(m_line, message);
}

void stlplus::debug_trace::stackdump(int l, const std::string& message) const
{
  do_report(l, message);
  stackdump();
}

void stlplus::debug_trace::stackdump(const std::string& message) const
{
  stackdump(m_line, message);
}

void stlplus::debug_trace::stackdump(void) const
{
  for (const stlplus::debug_trace* item = this; item; item = item->m_last)
    item->do_report("...called from here");
}
