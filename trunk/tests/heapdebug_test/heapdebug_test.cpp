//

#include <string>
#include <iostream>
#include <stdio.h>

#include "heapdebug.hpp"

int main(int argc, char* argv[])
{
  int* a = new int(0);
  std::cerr << (*a) << std::endl;
  delete a;
  // deliberate double-delete - should be safe because int has no destructor
  fprintf(stderr, "***** Testing double delete\n");
  delete a;

  std::string* s = new std::string("hello world");
  std::cerr << (*s) << std::endl;
  delete s;

  int* i2 = new int[2];
  std::cerr << i2[0] << " : " << i2[1] << std::endl;
  // deliberate use of wrong delete
  fprintf(stderr, "***** Testing use of non-array delete\n");
  delete i2;

#ifdef NDEBUG
  // running in non-debug mode - no actual errors
  int expected_errors = 0;
#elif defined(__BORLANDC__)
  // Borland has a bug in implementation if string that means the char* is
  // allocated by a non-new method but deallocated with delete - heapdebug
  // correctly flags this as an error
  int expected_errors = 3;
#else
  // the correct number of errors for these tests
  int expected_errors = 2;
#endif

  int errors = stlplus::heapdebug_errors();
  // check correct number of errors
  if (errors == expected_errors)
    fprintf(stderr, "***** Success - %d errors detected\n", errors);
  else
    fprintf(stderr, "***** FAILED - %d errors detected\n", errors);
  return errors - expected_errors;
}
