/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

template implementations

------------------------------------------------------------------------------*/
#include "template_fixes.hpp"

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////
  // any forward iterator sequence

  template <typename I, typename S>
  std::string sequence_to_string(I begin,
                                 I end, 
                                 S to_string,
                                 const std::string& separator)
  {
    std::string result;
    for (I i = begin; i != end; i++)
    {
      if (i != begin) result += separator;
      result += to_string(*i);
    }
    return result;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // any sequence where the value is a pair

  template <typename I, typename S1, typename S2>
  std::string pair_sequence_to_string(I begin,
                                      I end,
                                      S1 to_string_fn1,
                                      S2 to_string_fn2,
                                      const std::string& pair_separator,
                                      const std::string& separator)
  {
    std::string result;
    for (I i = begin; i != end; i++)
    {
      if (i != begin) result += separator;
      result += pair_to_string(*i, to_string_fn1, to_string_fn2, pair_separator);
    }
    return result;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // pointers

  template <typename T, typename S>
  std::string pointer_to_string(const T* value,
                                S to_string_fn,
                                const std::string& null_string,
                                const std::string& prefix,
                                const std::string& suffix)
  {
    return value ? (prefix + to_string_fn(*value) + suffix) : null_string;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // bitset

  template<size_t N>
  std::string bitset_to_string(const std::bitset<N>& data)
  {
    std::string result;
    for (unsigned i = data.size(); i--; )
      result += data[i] ? '1' : '0';
    return result;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // pair

  template<typename V1, typename V2, typename S1, typename S2>
  std::string pair_to_string(const std::pair<V1,V2>& values,
                             S1 to_string_fn1,
                             S2 to_string_fn2,
                             const std::string& separator)
  {
    return to_string_fn1(values.first) + separator + to_string_fn2(values.second);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // list

  template<typename T, typename S>
  std::string list_to_string(const std::list<T>& values,
                             S to_string_fn,
                             const std::string& separator)
  {
    return sequence_to_string(values.begin(), values.end(), to_string_fn, separator);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // map

  template<typename K, typename T, typename C, typename SK, typename ST>
  std::string map_to_string(const std::map<K,T,C>& values,
                            SK key_to_string_fn,
                            ST value_to_string_fn,
                            const std::string& pair_separator,
                            const std::string& separator)
  {
    return pair_sequence_to_string(values.begin(), values.end(),
                                   key_to_string_fn, value_to_string_fn,
                                   pair_separator, separator);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // multimap

  template<typename K, typename T, typename C, typename SK, typename ST>
  std::string multimap_to_string(const std::multimap<K,T,C>& values,
                                 SK key_to_string_fn,
                                 ST value_to_string_fn,
                                 const std::string& pair_separator,
                                 const std::string& separator)
  {
    return pair_sequence_to_string(values.begin(), values.end(),
                                   key_to_string_fn, value_to_string_fn,
                                   pair_separator, separator);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // set

  template<typename K, typename C, typename S>
  std::string set_to_string(const std::set<K,C>& values,
                            S to_string_fn,
                            const std::string& separator)
  {
    return sequence_to_string(values.begin(), values.end(), to_string_fn, separator);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // multiset

  template<typename K, typename C, typename S>
  std::string multiset_to_string(const std::multiset<K,C>& values,
                                 S to_string_fn,
                                 const std::string& separator)
  {
    return sequence_to_string(values.begin(), values.end(), to_string_fn, separator);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // vector

  template<typename T, typename S>
  std::string vector_to_string(const std::vector<T>& values,
                               S to_string_fn,
                               const std::string& separator)
  {
    return sequence_to_string(values.begin(), values.end(), to_string_fn, separator);
  }

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus
