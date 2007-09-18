#ifndef STLPLUS_DEBUG_HPP
#define STLPLUS_DEBUG_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

Set of simple debug utilities, all of which are switched off by the
NDEBUG compiler directive

------------------------------------------------------------------------------*/
#include <stdexcept>
#include <string>

////////////////////////////////////////////////////////////////////////////////
// Problem with missing __FUNCTION__ macro
////////////////////////////////////////////////////////////////////////////////
// this macro is used in debugging but was missing in Visual Studio prior to version 7
// it also has a different name in Borland

#if defined(_MSC_VER) && (_MSC_VER < 1300)
#define __FUNCTION__ 0
#endif

#if defined(__BORLANDC__)
#define __FUNCTION__ __FUNC__
#endif

////////////////////////////////////////////////////////////////////////////////
// Exception thrown if an assertion fails

namespace stlplus
{

  class assert_failed : public std::logic_error
  {
  public:
    assert_failed(const char* file, int line, const char* function, const std::string& message) throw();
    ~assert_failed(void) throw();
  };

} // end namespace stlplus

  ////////////////////////////////////////////////////////////////////////////////
  // The macros used in debugging

#ifndef NDEBUG

#define DEBUG_TRACE stlplus_debug_trace stlplus::debug_trace(__FILE__,__LINE__,__FUNCTION__)
#define IF_DEBUG(stmts) {if (stlplus_debug_trace.debug()){stlplus_debug_trace.prefix(__LINE__);stmts;}}
#define DEBUG_REPORT(str) IF_DEBUG(stlplus_debug_trace.report(__LINE__,str))
#define DEBUG_ERROR(str) stlplus_debug_trace.error(__LINE__,str)
#define DEBUG_STACKDUMP(str) stlplus_debug_trace.stackdump(__LINE__,str)
#define DEBUG_ON stlplus_debug_trace.debug_on(__LINE__,true)
#define DEBUG_ON_LOCAL stlplus_debug_trace.debug_on(__LINE__,false)
#define DEBUG_ON_GLOBAL stlplus::debug_global(__FILE__,__LINE__,__FUNCTION__,true)
#define DEBUG_OFF_GLOBAL stlplus::debug_global(__FILE__,__LINE__,__FUNCTION__,false)
#define DEBUG_OFF stlplus_debug_trace.debug_off(__LINE__)
#define DEBUG_ASSERT(test) if (!(test))stlplus::debug_assert_fail(__FILE__,__LINE__,__FUNCTION__,#test)

#else

#define DEBUG_TRACE
#define IF_DEBUG(stmts)
#define DEBUG_REPORT(str)
#define DEBUG_ERROR(str)
#define DEBUG_STACKDUMP(str)
#define DEBUG_ON
#define DEBUG_ON_LOCAL
#define DEBUG_ON_GLOBAL
#define DEBUG_OFF_GLOBAL
#define DEBUG_OFF
#define DEBUG_ASSERT(test)

#endif

////////////////////////////////////////////////////////////////////////////////
// infrastructure - don't use directly

namespace stlplus
{

  void debug_global(const char* file, int line, const char* function, bool state = true);
  void debug_assert_fail(const char* file, int line, const char* function, const char* test) throw(assert_failed);

  class debug_trace
  {
  public:
    debug_trace(const char* f, int l, const char* fn);
    ~debug_trace(void);
    const char* file(void) const;
    int line(void) const;
    bool debug(void) const;
    void debug_on(int l, bool recurse);
    void debug_off(int l);
    void prefix(int l) const;
    void report(int l, const std::string& message) const;
    void report(const std::string& message) const;
    void error(int l, const std::string& message) const;
    void error(const std::string& message) const;
    void stackdump(int l, const std::string& message) const;
    void stackdump(const std::string& message) const;
    void stackdump(void) const;

  private:
    const char* m_file;
    int m_line;
    const char* m_function;
    unsigned m_depth;
    const debug_trace* m_last;
    bool m_dbg;
    bool m_old;
    void do_report(int l, const std::string& message) const;
    void do_report(const std::string& message) const;

    // make this class uncopyable
    debug_trace(const debug_trace&);
    debug_trace& operator = (const debug_trace&);
  };

} // end namespace stlplus

  ////////////////////////////////////////////////////////////////////////////////
#endif
