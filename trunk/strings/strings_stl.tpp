/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2004
License:   BSD License, see ../docs/license.html

template implementations

------------------------------------------------------------------------------*/
#include "template_fixes.hpp"

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////
  // pointers

  template <typename T, typename S>
  std::string pointer_to_string(const T* value,
                                const std::string& null_string,
                                const std::string& prefix,
                                const std::string& suffix,
                                S to_string_fn)
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
  // list

  template<typename T, typename S>
  std::string list_to_string(const std::list<T>& values,
                             const std::string& separator,
                             S to_string_fn)
  {
    std::string result;
    for (TYPENAME std::list<T>::const_iterator i = values.begin(); i != values.end(); i++)
    {
      if (i != values.begin()) result += separator;
      result += to_string_fn(*i);
    }
    return result;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // pair

  template<typename V1, typename V2, typename S1, typename S2>
  std::string pair_to_string(const std::pair<V1,V2>& values,
                             const std::string& separator,
                             S1 to_string_fn1,
                             S2 to_string_fn2)
  {
    return to_string_fn1(values.first) + separator + to_string_fn2(values.second);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // map

  template<typename K, typename T, typename C, typename SK, typename ST>
  std::string map_to_string(const std::map<K,T,C>& values,
                            const std::string& pair_separator,
                            const std::string& separator,
                            SK key_to_string_fn,
                            ST value_to_string_fn)
  {
    std::string result;
    for (TYPENAME std::map<K,T,C>::const_iterator i = values.begin(); i != values.end(); i++)
    {
      if (i != values.begin()) result += separator;
      result += pair_to_string(*i, pair_separator,key_to_string_fn,value_to_string_fn);
    }
    return result;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // multimap

  template<typename K, typename T, typename C, typename SK, typename ST>
  std::string multimap_to_string(const std::multimap<K,T,C>& values,
                                 const std::string& pair_separator,
                                 const std::string& separator,
                                 SK key_to_string_fn,
                                 ST value_to_string_fn)
  {
    std::string result;
    for (TYPENAME std::multimap<K,T,C>::const_iterator i = values.begin(); i != values.end(); i++)
    {
      if (i != values.begin()) result += separator;
      result += pair_to_string(*i, pair_separator,key_to_string_fn,value_to_string_fn);
    }
    return result;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // set

  template<typename K, typename C, typename S>
  std::string set_to_string(const std::set<K,C>& values,
                            const std::string& separator,
                            S to_string_fn)
  {
    std::string result;
    for (TYPENAME std::set<K,C>::const_iterator i = values.begin(); i != values.end(); i++)
    {
      if (i != values.begin()) result += separator;
      result += to_string_fn(*i);
    }
    return result;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // multiset

  template<typename K, typename C, typename S>
  std::string multiset_to_string(const std::multiset<K,C>& values,
                                 const std::string& separator,
                                 S to_string_fn)
  {
    std::string result;
    for (TYPENAME std::multiset<K,C>::const_iterator i = values.begin(); i != values.end(); i++)
    {
      if (i != values.begin()) result += separator;
      result += to_string_fn(*i);
    }
    return result;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // vector

  template<typename T, typename S>
  std::string vector_to_string(const std::vector<T>& values,
                               const std::string& separator,
                               S to_string_fn)
  {
    std::string result;
    for (unsigned i = 0; i < values.size(); i++)
    {
      if (i > 0) result += separator;
      result += to_string_fn(values[i]);
    }
    return result;
  }

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus
