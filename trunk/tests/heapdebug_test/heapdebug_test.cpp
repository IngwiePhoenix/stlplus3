//

#include <string>
#include <iostream>

#include "heapdebug.hpp"

int main(int argc, char* argv[])
{
  int* a = new int(0);
  std::cerr << (*a) << std::endl;
  delete a;
  // deliberate double-delete - should be safe because int has no destructor
  delete a;

  std::string* s = new std::string("hello world");
  std::cerr << (*s) << std::endl;
  delete s;

  int* i2 = new int[2];
  std::cerr << i2[0] << " : " << i2[1] << std::endl;
  // deliberate use of wrong delete
  delete i2;

#ifdef NDEBUG
  return 0;
#else
  // return 0 if the "right" number of errors was found
  return stlplus::heapdebug_errors() - 2;
#endif
}
