#ifndef STRINGS_STL_HPP
#define STRINGS_STL_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2004
License:   BSD License, see ../docs/license.html

Template string conversions for pointers and STL containers

------------------------------------------------------------------------------*/
#include "format_types.hpp"
#include <vector>
#include <bitset>
#include <list>
#include <map>
#include <set>
#include <vector>

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////

  template <typename T, typename S>
  std::string pointer_to_string(const T* value,
                                const std::string& null_string,
                                const std::string& prefix,
                                const std::string& suffix,
                                S to_string_fn);

  ////////////////////////////////////////////////////////////////////////////////

  template<size_t N>
  std::string bitset_to_string(const std::bitset<N>& data);

  ////////////////////////////////////////////////////////////////////////////////

  template<typename T, typename S>
  std::string list_to_string(const std::list<T>& values,
                             const std::string& separator,
                             S to_string_fn);

  ////////////////////////////////////////////////////////////////////////////////

  template<typename V1, typename V2, typename S1, typename S2>
  std::string pair_to_string(const std::pair<V1,V2>& values,
                             const std::string& separator,
                             S1 to_string_fn1,
                             S2 to_string_fn2);

  ////////////////////////////////////////////////////////////////////////////////

  template<typename K, typename T, typename C, typename SK, typename ST>
  std::string map_to_string(const std::map<K,T,C>& values,
                            const std::string& pair_separator,
                            const std::string& separator,
                            SK key_to_string_fn,
                            ST value_to_string_fn);

  template<typename K, typename T, typename C, typename SK, typename ST>
  std::string multimap_to_string(const std::multimap<K,T,C>& values,
                                 const std::string& pair_separator,
                                 const std::string& separator,
                                 SK key_to_string_fn,
                                 ST value_to_string_fn);

  ////////////////////////////////////////////////////////////////////////////////

  template<typename K, typename C, typename S>
  std::string set_to_string(const std::set<K,C>& values,
                            const std::string& separator,
                            S to_string_fn);

  template<typename K, typename C, typename S>
  std::string multiset_to_string(const std::multiset<K,C>& values,
                                 const std::string& separator,
                                 S to_string_fn);

  ////////////////////////////////////////////////////////////////////////////////

  template<typename T, typename S>
  std::string vector_to_string(const std::vector<T>& values,
                               const std::string& separator,
                               S to_string_fn);

  // specialisation for vector<bool> which has a different implementation
  std::string to_string(const std::vector<bool>& values);

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus

#include "strings_stl.tpp"
#endif
