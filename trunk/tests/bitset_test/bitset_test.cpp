#include "persistent_bitset.hpp"
#include "persistent_vector.hpp"
#include "persistent_shortcuts.hpp"
#include "file_system.hpp"
#include "strings_stl.hpp"
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

////////////////////////////////////////////////////////////////////////////////

#define SIZE 50
#define COUNT 100
#define DATA "bitset_test.tmp"
#define MASTER "bitset_test.dump"

////////////////////////////////////////////////////////////////////////////////

typedef std::bitset<SIZE> bitset_N;

std::ostream& operator<<(std::ostream& str, const bitset_N& data)
{
  return str << stlplus::bitset_to_string(data);
}

void dump_bitset_N(stlplus::dump_context& str, const bitset_N& data)
{
  stlplus::dump_bitset(str, data);
}

void restore_bitset_N(stlplus::restore_context& str, bitset_N& data)
{
  stlplus::restore_bitset(str, data);
}

////////////////////////////////////////////////////////////////////////////////

typedef std::vector<bitset_N> bitset_vector;

std::ostream& operator<<(std::ostream& str, const bitset_vector& values)
{
  return str << stlplus::vector_to_string(values, ",", stlplus::bitset_to_string<SIZE>);
}

void dump_bitset_vector(stlplus::dump_context& str, const bitset_vector& data)
{
  stlplus::dump_vector(str, data, dump_bitset_N);
}

void restore_bitset_vector(stlplus::restore_context& str, bitset_vector& data)
{
  stlplus::restore_vector(str, data, restore_bitset_N);
}

bool compare (bitset_vector& left, bitset_vector& right)
{
  bool result = true;
  if (left.size() != right.size())
  {
    std::cerr << "different size - left = " << left.size() << " right = " << right.size() << std::endl;
    result = false;
  }
  else
  {
  for (unsigned j = 0; j < left.size(); j++)
  {
    if (left[j] != right[j])
    {
      std::cerr << "bitset[" << j << "] is different: left = " << left[j] << " right = " << right[j] << std::endl;
      result = false;
    }
  }
  }
  return result;
}

int main(unsigned argc, char* argv[])
{
  bool result = true;
  std::cerr << "testing " << COUNT << " bitset<" << SIZE << ">" << std::endl;

  try
  {
    // first build a vector of bit-sets and dump it
    std::cerr << "building" << std::endl;
    bitset_vector data;
    for (unsigned long i = 0; i < COUNT; i++)
      data.push_back(i);
    std::cerr << data << std::endl;
    std::cerr << "dumping" << std::endl;
    stlplus::dump_to_file(data,DATA,dump_bitset_vector,0);

    // now restore a copy and compare it
    std::cerr << "restoring" << std::endl;
    bitset_vector restored;
    stlplus::restore_from_file(DATA,restored,restore_bitset_vector,0);
    result &= compare(data,restored);

    // compare with the master dump if present
    if (!stlplus::file_exists(MASTER))
      stlplus::file_copy(DATA,MASTER);
    else
    {
      std::cerr << "restoring master" << std::endl;
      bitset_vector master;
      stlplus::restore_from_file(MASTER,master,restore_bitset_vector,0);
      result &= compare(data,master);
    }
  }
  catch(std::exception& except)
  {
    std::cerr << "caught standard exception " << except.what() << std::endl;
    result = false;
  }
  catch(...)
  {
    std::cerr << "caught unknown exception" << std::endl;
    result = false;
  }
  if (!result)
    std::cerr << "test failed" << std::endl;
  else
    std::cerr << "test succeeded" << std::endl;
  return result ? 0 : 1;
}
