#include "inf.hpp"
#include "timer.hpp"
#include "build.hpp"
#include "file_system.hpp"
#include "persistent_inf.hpp"
#include "persistent_shortcuts.hpp"
#include "strings.hpp"
#include <stdio.h>
#include <stdlib.h>

#define DATA "inf_test.tmp"
#define MASTER "inf_test.dump"

#ifdef _WIN32
typedef __int64 bigint;
#else
typedef long long bigint;
#endif

#define SAMPLES 100

static std::string hex_image (bigint value)
{
  char str[1000];
#ifdef _WIN32
  sprintf(str, "0x%I64x", value);
#else
  sprintf(str, "%llx", value);
#endif
  return std::string(str);
}

static std::string dec_image (bigint value)
{
  char str[1000];
#ifdef _WIN32
  sprintf(str, "%I64d", value);
#else
  sprintf(str, "%lld", value);
#endif
  return std::string(str);
}

static bool compare (bigint left, const stlplus::inf& right)
{
  std::string left_image = dec_image(left);
  std::string right_image = right.to_string(10);
  if (left_image != right_image)
  {
    std::cerr << "failed comparing integer " << left_image << " with inf " << right << std::endl;
    return false;
  }
  return true;
}

static bool report(int a, int b, const char* op)
{
  std::cerr << "operator " << op << " failed with a = " << a << ", b = " << b << std::endl;
  return false;
}

static bool test (int a, int b)
{
  bool okay = true;
  bigint int_a(a);
  stlplus::inf inf_a(a);
  bigint int_b(b);
  stlplus::inf inf_b(b);

  if (!compare((int_a + int_b), (inf_a + inf_b)))
    okay &= report(a, b, "+");
  if (!compare((int_a - int_b), (inf_a - inf_b)))
    okay &= report(a, b, "-");
  if (!compare((int_a * int_b), (inf_a * inf_b)))
    okay &= report(a, b, "*");
  if (b != 0)
  {
    if (!compare((int_a / int_b), (inf_a / inf_b)))
      okay &= report(a, b, "/");
    if (!compare((int_a % int_b), (inf_a % inf_b)))
      okay &= report(a, b, "%");
  }
  if (!compare((int_a | int_b), (inf_a | inf_b)))
    okay &= report(a, b, "|");
  if (!compare((int_a & int_b), (inf_a & inf_b)))
    okay &= report(a, b, "&");
  if (!compare((int_a ^ int_b), (inf_a ^ inf_b)))
    okay &= report(a, b, "^");
  for (unsigned shift = 1; shift < 16; shift*=2)
  {
    if (!compare((int_a << shift), (inf_a << shift)))
      okay &= report(a, shift, "<<");
    if (!compare((int_a >> shift), (inf_a >> shift)))
      okay &= report(a, shift, ">>");
  }
  for (unsigned high = 1; high < 16; high*=2)
  {
    for (unsigned low = 0; low < high+1; low++)
    {
      stlplus::inf inf_a(a);
      if (high < inf_a.size())
      {
        // discard the lsbs by simply shifting right
        bigint bigint_slice = int_a >> low;
        // mask the msbs and sign extend the result
        int length = int(high)-int(low)+1;
        if (bigint_slice & (bigint(1) << (length-1)))
          bigint_slice |= ((~bigint(0)) >> length) << length;
        else
          bigint_slice &= ~(((~bigint(0)) >> length) << length);
        stlplus::inf slice = inf_a.slice(low,high);
        if (!compare(bigint_slice, slice))
        {
          std::cerr << "slice failed with hex integer = " << hex_image(int_a) << ", high = " << high << ", low = " << low << std::endl;
          std::cerr << "  inf slice = " << slice.image_debug() << ", integer slice = " << hex_image(bigint_slice) << std::endl;
          okay &= false;
        }
      }
    }
  }
  return okay;
}

int main (int argc, char* argv[])
{
  bool okay = true;
  stlplus::timer cpu_time;
  std::cerr << "build: " << stlplus::build() << std::endl;
  try
  {
    srand(time(0));
    signed long samples = (argc > 2) ? ((argc-1)/2) : argc == 2 ? atol(argv[1]) : SAMPLES;
    std::cerr << "testing " << samples << " samples" << std::endl;
    float cpu = cpu_time.cpu();
    for (signed long i = 1; i <= samples; i++)
    {
      int a = (argc > 2) ? atol(argv[i*2-1]) : rand();
      int b = (argc > 2) ? atol(argv[i*2]) : rand();
      std::cerr << "#" << i << " a = " << a << " b = " << b << std::endl;
      okay &= test(a, b);
      okay &= test(-a, b);
      okay &= test(a, -b);
      okay &= test(-a, -b);
      if (cpu_time.cpu() > (cpu + 5.0))
      {
        cpu = cpu + 5.0;
        std::cerr << cpu_time << ": tested " << i << " samples" << std::endl;
      }
    }
    std::cerr << cpu_time << " total for " << samples << " samples" << std::endl;
    stlplus::inf googol(1);
    for (unsigned j = 0; j < 100; j++)
      googol *= stlplus::inf(10);
    std::cerr << "a googol is:" << std::endl;
    for (unsigned radix = 2; radix <= 36; radix++)
      std::cerr << "base " << radix << " = " << stlplus::inf_to_string(googol,radix) << std::endl;

    // test the persistence
    std::cerr << "dumping" << std::endl;
    stlplus::dump_to_file(googol, DATA, stlplus::dump_inf, 0);
    stlplus::inf googol2;
    std::cerr << "restoring" << std::endl;
    stlplus::restore_from_file(DATA, googol2, stlplus::restore_inf, 0);
    if (googol != googol2)
    {
      std::cerr << "restored value " << googol2 << " is not the same" << std::endl;
      okay = false;
    }
    // compare with the master dump if present
    if (!stlplus::file_exists(MASTER))
      stlplus::file_copy(DATA,MASTER);
    else
    {
      std::cerr << "restoring master" << std::endl;
      stlplus::inf googol3;
      stlplus::restore_from_file(MASTER,googol3,stlplus::restore_inf,0);
      if (googol != googol3)
      {
        std::cerr << "restored value " << googol3 << " is not the same" << std::endl;
        okay = false;
      }
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "caught std::exception " << e.what() << std::endl;
    okay &= false;
  }
  catch (...)
  {
    std::cerr << "caught unknown exception " << std::endl;
    okay &= false;
  }
  std::cerr << cpu_time << " total for program" << std::endl;
  std::cerr << "test " << (okay ? "succeeded" : "FAILED") << std::endl;
  return okay ? 0 : 1;
}
