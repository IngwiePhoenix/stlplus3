#include "dynaload.hpp"
#include "debug.hpp"
#include "build.hpp"
#include <iostream>

typedef char* (*sqlite3_libversion_t)(void);

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
  if (nonexistent.present("function"))
  {
    std::cerr << "ERROR: nonexistent function LOADED" << std::endl;
    errors++;
  }

  // test an existent library
  stlplus::dynaload existent("sqlite3");
  if (!existent.loaded())
  {
    std::cerr << "ERROR: existent library sqlite3 load FAILED with code "
              << existent.error_type() << ": "
              << existent.error_text() << std::endl;
    existent.clear_error();
    errors++;
  }
  if (!existent.present("sqlite3_libversion"))
  {
    std::cerr << "ERROR: existent function load FAILED "
              << existent.error_type() << ": "
              << existent.error_text() << std::endl;
    existent.clear_error();
    errors++;
  }
  sqlite3_libversion_t sqlite3_libversion = (sqlite3_libversion_t)existent.symbol("sqlite3_libversion");
  if (!sqlite3_libversion)
  {
    std::cerr << "ERROR: existent function load FAILED "
              << existent.error_type() << ": "
              << existent.error_text() << std::endl;
    existent.clear_error();
    errors++;
  }
  else
  {
    std::cerr << "SQLite3 version: " << sqlite3_libversion() << std::endl;
  }

  if (errors == 0)
    std::cerr << "test PASSED" << std::endl;
  else
    std::cerr << "test FAILED" << std::endl;

  return errors;
}
