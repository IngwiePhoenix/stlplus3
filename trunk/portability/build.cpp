#include "build.hpp"

////////////////////////////////////////////////////////////////////////////////
// local function to generate a string representation of an integer
// use sprintf in a very controlled way that cannot overrun

static std::string to_string(int number)
{
  char* buffer = new char[50];
  sprintf(buffer, "%i", number);
  std::string result = buffer;
  delete buffer;
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// work out the platform
// at present there are no variations between different Unix platforms so they all map onto the generic Unix platform

#undef PLATFORM
#ifdef MSWINDOWS
#define PLATFORM std::string("Windows")
#endif
#ifndef PLATFORM
#define PLATFORM std::string("Generic Unix")
#endif

////////////////////////////////////////////////////////////////////////////////
// work out the compiler

#undef COMPILER
#ifdef __GNUC__
#define COMPILER (std::string("gcc v")+to_string(__GNUC__)+std::string(".")+to_string(__GNUC_MINOR__))
#endif
#ifdef _MSC_VER
#define COMPILER (std::string("MSVC v")+to_string(((float)_MSC_VER)/100.0))
#endif
#ifdef __BORLANDC__
#define COMPILER (std::string("Borland v")+to_string(__BORLANDC__/256)+std::string(".")+to_string(__BORLANDC__/16%16))
#endif

#ifndef COMPILER
#define COMPILER std::string("unknown compiler")
#endif

////////////////////////////////////////////////////////////////////////////////
// work out the kind of build
// there are two variants - debug and release

#undef VARIANT
#ifndef NDEBUG
#define VARIANT std::string("debug")
#else
#define VARIANT std::string("release")
#endif

////////////////////////////////////////////////////////////////////////////////
// report the platform-specific details of this build

std::string stlplus::build(void)
{
  return PLATFORM + ", " + COMPILER + ", " + VARIANT;
}

////////////////////////////////////////////////////////////////////////////////
