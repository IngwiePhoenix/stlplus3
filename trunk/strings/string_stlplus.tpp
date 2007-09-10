/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

------------------------------------------------------------------------------*/
#include "string_stl.hpp"

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////

  template<typename T1, typename T2, typename T3, typename S1, typename S2, typename S3>
  std::string triple_to_string(const triple<T1,T2,T3>& values,
                               S1 to_string_fn1,
                               S2 to_string_fn2,
                               S3 to_string_fn3,
                               const std::string& separator)
  {
    return 
      to_string_fn1(values.first) + 
      separator + 
      to_string_fn2(values.second) + 
      separator + 
      to_string_fn3(values.third);
  }

  ////////////////////////////////////////////////////////////////////////////////

  template<typename T1, typename T2, typename T3, typename T4, typename S1, typename S2, typename S3, typename S4>
  std::string foursome_to_string(const foursome<T1,T2,T3,T4>& values,
                                 S1 to_string_fn1,
                                 S2 to_string_fn2,
                                 S3 to_string_fn3,
                                 S4 to_string_fn4,
                                 const std::string& separator)
  {
    return 
      to_string_fn1(values.first) + 
      separator + 
      to_string_fn2(values.second) + 
      separator + 
      to_string_fn3(values.third) +
      separator + 
      to_string_fn4(values.fourth);
  }

  ////////////////////////////////////////////////////////////////////////////////

  template<typename T, typename C, typename S>
  std::string smart_ptr_to_string(const smart_ptr_base<T,C>& value,
                                  S to_string_fn,
                                  const std::string& null_string,
                                  const std::string& prefix,
                                  const std::string& suffix)
  {
    return value ? (prefix + to_string_fn(*value) + suffix) : null_string;
  }

  ////////////////////////////////////////////////////////////////////////////////

  template<typename NT, typename AT, typename NS, typename AS>
  std::string digraph_to_string(const digraph<NT,AT>& values,
                                NS node_to_string_fn,
                                AS arc_to_string_fn,
                                const std::string& separator)
  {
    std::string result;
    result += "nodes:";
    result += separator;
    result += sequence_to_string(values.begin(), values.end(), node_to_string_fn, separator);
    result += "arcs:";
    result += separator;
    result += sequence_to_string(values.arc_begin(), values.arc_end(), arc_to_string_fn, separator);
    return result;
  }

  ////////////////////////////////////////////////////////////////////////////////

  template<typename K, typename T, typename H, typename E, typename KS, typename TS>
  std::string hash_to_string(const hash<K,T,H,E>& values,
                             KS key_to_string_fn,
                             TS value_to_string_fn,
                             const std::string& pair_separator,
                             const std::string& separator)
  {
    return pair_sequence_to_string(values.begin(), values.end(),
                                   key_to_string_fn, value_to_string_fn,
                                   pair_separator, separator);
  }

  ////////////////////////////////////////////////////////////////////////////////

  template<typename T, typename S>
  std::string matrix_to_string(const matrix<T>& values,
                               S to_string_fn,
                               const std::string& column_separator,
                               const std::string& row_separator)
  {
    std::string result;
    for (unsigned r = 0; r < values.rows(); r++)
    {
      if (r != 0) result += row_separator;
      for (unsigned c = 0; c < values.columns(); c++)
      {
        if (c != 0) result += column_separator;
        result += to_string_fn(values(r,c));
      }
    }
    return result;
  }

  ////////////////////////////////////////////////////////////////////////////////

  template<typename T, typename S>
  std::string ntree_to_string(const ntree<T>& values,
                              S to_string_fn,
                              const std::string& separator,
                              const std::string& indent_string)
  {
    std::string result;
    for (TYPENAME ntree<T>::const_prefix_iterator i = values.prefix_begin(); i != values.prefix_end(); i++)
    {
      if (i != values.prefix_begin()) result += separator;
      for (unsigned indent = values.depth(i.simplify()); --indent; )
        result += indent_string;
      result += to_string_fn(*i);
    }
    return result;
  }

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus

