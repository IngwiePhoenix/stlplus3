#ifndef STLPLUS_STRING_STL_HPP
#define STLPLUS_STRING_STL_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
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
  // simple pointer

  template <typename T, typename S>
  std::string pointer_to_string(const T* value,
                                S to_string_fn,
                                const std::string& null_string = "<null>",
                                const std::string& prefix = "(",
                                const std::string& suffix = ")");

  ////////////////////////////////////////////////////////////////////////////////
  // any forward iterator sequence

  template <typename I, typename S>
  std::string sequence_to_string(I begin,
                                 I end, 
                                 S to_string,
                                 const std::string& separator);


  ////////////////////////////////////////////////////////////////////////////////
  // any forward iterator sequence of pairs

  template <typename I, typename S1, typename S2>
  std::string pair_sequence_to_string(I begin,
                                      I end,
                                      S1 to_string_fn1,
                                      S2 to_string_fn2,
                                      const std::string& pair_separator,
                                      const std::string& separator);

  ////////////////////////////////////////////////////////////////////////////////
  // bitset

  template<size_t N>
  std::string bitset_to_string(const std::bitset<N>& data);

  ////////////////////////////////////////////////////////////////////////////////
  // pair

  template<typename V1, typename V2, typename S1, typename S2>
  std::string pair_to_string(const std::pair<V1,V2>& values,
                             S1 to_string_fn1,
                             S2 to_string_fn2,
                             const std::string& separator = ":");

  ////////////////////////////////////////////////////////////////////////////////
  // list

  template<typename T, typename S>
  std::string list_to_string(const std::list<T>& values,
                             S to_string_fn,
                             const std::string& separator = ",");

  ////////////////////////////////////////////////////////////////////////////////
  // map/multimap

  template<typename K, typename T, typename C, typename SK, typename ST>
  std::string map_to_string(const std::map<K,T,C>& values,
                            SK key_to_string_fn,
                            ST value_to_string_fn,
                            const std::string& pair_separator = ":",
                            const std::string& separator = ",");

  template<typename K, typename T, typename C, typename SK, typename ST>
  std::string multimap_to_string(const std::multimap<K,T,C>& values,
                                 SK key_to_string_fn,
                                 ST value_to_string_fn,
                                 const std::string& pair_separator = ":",
                                 const std::string& separator = ",");

  ////////////////////////////////////////////////////////////////////////////////
  // set/multiset

  template<typename K, typename C, typename S>
  std::string set_to_string(const std::set<K,C>& values,
                            S to_string_fn,
                            const std::string& separator = ",");

  template<typename K, typename C, typename S>
  std::string multiset_to_string(const std::multiset<K,C>& values,
                                 S to_string_fn,
                                 const std::string& separator = ",");

  ////////////////////////////////////////////////////////////////////////////////
  // vector

  template<typename T, typename S>
  std::string vector_to_string(const std::vector<T>& values,
                               S to_string_fn,
                               const std::string& separator = ",");

  // specialisation for vector<bool> which has a different implementation
  std::string vector_bool_to_string(const std::vector<bool>& values);

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus

#include "string_stl.tpp"
#endif
