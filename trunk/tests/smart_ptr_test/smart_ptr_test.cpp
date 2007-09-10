#include "smart_ptr.hpp"
#include "persistent_smart_ptr.hpp"
#include "persistent_string.hpp"
#include "persistent_pair.hpp"
#include "persistent_shortcuts.hpp"
#include "strings_stlplus.hpp"
#include "strings_basic.hpp"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

typedef stlplus::smart_ptr<std::string> string_ptr;

void print(const std::string& label, const string_ptr& value)
{
  std::cout << label;
  std::cout << " = " << stlplus::smart_ptr_to_string(value,stlplus::string_to_string);
  std::cout << " handle = " << value.handle();
  std::cout << " aliases = " << value.alias_count();
  std::cout << std::endl;
}

void dump_string_ptr(stlplus::dump_context& context, const string_ptr& data)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_smart_ptr(context, data, stlplus::dump_string);
}

void restore_string_ptr(stlplus::restore_context& context, string_ptr& data)
  throw(stlplus::persistent_restore_failed)
{
  stlplus::restore_smart_ptr(context, data, stlplus::restore_string);
}

////////////////////////////////////////////////////////////////////////////////

typedef std::pair<string_ptr,string_ptr> string_ptr_pair;

void print(const std::string& label, const string_ptr_pair& values)
{
  std::cout << "pair " << label << std::endl;
  print("first:", values.first);
  print("second:", values.second);
}

void dump_string_ptr_pair(stlplus::dump_context& context, const string_ptr_pair& data)
  throw(stlplus::persistent_dump_failed)
{
  stlplus::dump_pair(context, data, dump_string_ptr, dump_string_ptr);
}

void restore_string_ptr_pair(stlplus::restore_context& context, string_ptr_pair& data)
  throw(stlplus::persistent_restore_failed)
{
  stlplus::restore_pair(context, data, restore_string_ptr, restore_string_ptr);
}

////////////////////////////////////////////////////////////////////////////////

static const char* DATA = "data.tmp";

////////////////////////////////////////////////////////////////////////////////

int main (int argc, char* argv[])
{
  // smart_ptr()
  string_ptr s0;
  print("created s0", s0);
  for (int i = 1; i < argc; i++)
  {
    std::string value = argv[i];
    // smart_ptr(T)
    string_ptr s1(value);
    print("created s1(value)", s1);
    // smart_ptr(smart_ptr<T>)
    string_ptr s2(s1);
    print("created s2(s1)", s2);
    // smart_ptr(T*)
    string_ptr s3(new std::string(value));
    print("created s3(new string(value))", s3);
    // operator=(smart_ptr<T>)
    s3 = s2;
    print("s3 = s2", s3);
    // operator=(T)
    s3 = value;
    print("s3 = value", s3);
    print("s2", s2);
    print("s1", s1);
    // create a pair containing two aliases
    string_ptr_pair p1 = std::make_pair(s1,s1);
    print("make_pair(s1,s1)",p1);
    // dump/restore
    stlplus::dump_to_file(p1, DATA, dump_string_ptr_pair, 0);
    string_ptr_pair p2;
    stlplus::restore_from_file(DATA, p2, restore_string_ptr_pair, 0);
    print("p2 = dump/restore(p1)", p2);
    // dealias one of these
    p1.second.make_unique();
    print("p1.second.make_unique()", p1);
    // dump/restore
    stlplus::dump_to_file(p1, DATA, dump_string_ptr_pair, 0);
    string_ptr_pair p3;
    stlplus::restore_from_file(DATA, p3, restore_string_ptr_pair, 0);
    print("p3 = dump/restore(p1)", p3);
  }
  return 0;
}
