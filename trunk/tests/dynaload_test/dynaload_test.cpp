#include "dynaload.hpp"
#include "debug.hpp"
#include "build.hpp"
#include "version.hpp"
#include <iostream>

typedef char* (*version_t)(void);

int main (int argc, char* argv[])
{
  DEBUG_TRACE;
  std::cerr << stlplus::build() << std::endl;

  int errors = 0;

  // test a non-existent library
  stlplus::dynaload nonexistent;
  if (nonexistent.load("nonexistent"))
  {
    std::cerr << "ERROR: nonexistent library LOADED!" << std::endl;
    errors++;
  }
  else
  {
    std::cerr << "success: nonexistent library load failed with code "
              << nonexistent.error_type() << ": "
              << nonexistent.error_text() << std::endl;
    nonexistent.clear_error();
  }

  // test an existent library
  std::string library = "shared_library_test";
  stlplus::dynaload existent(library, "../shared_library_test/");
  if (!existent.loaded())
  {
    std::cerr << "ERROR: existent library " << library << " load FAILED with code "
              << existent.error_type() << ": "
              << existent.error_text() << std::endl;
    existent.clear_error();
    errors++;
  }
  else
  {
    std::cerr << "success: existent library " << library << " loaded OK" << std::endl;
    version_t version = (version_t)existent.symbol("stlplus_version");
    if (!version)
    {
      std::cerr << "ERROR: existent function load FAILED "
                << existent.error_type() << ": "
                << existent.error_text() << std::endl;
      existent.clear_error();
      errors++;
    }
    else
    {
      std::cerr << "STLplus version: " << version() << std::endl;
      if (std::string(version()) != stlplus::version())
      {
        std::cerr << "ERROR: version mismatch" << std::endl;
        errors++;
      }
    }
  }
  if (errors == 0)
    std::cerr << "test PASSED" << std::endl;
  else
    std::cerr << "test FAILED" << std::endl;

  return errors;
}
