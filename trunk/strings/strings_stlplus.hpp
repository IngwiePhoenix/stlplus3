#ifndef STRINGS_STLPLUS_HPP
#define STRINGS_STLPLUS_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

Template string conversions for the STLplus containers

------------------------------------------------------------------------------*/
#include "format_types.hpp"
#include "triple.hpp"
#include "foursome.hpp"
#include "smart_ptr.hpp"
#include "digraph.hpp"
#include "hash.hpp"
#include "matrix.hpp"
#include "ntree.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////

  template<typename T1, typename T2, typename T3, typename S1, typename S2, typename S3>
  std::string triple_to_string(const triple<T1,T2,T3>& values,
                               S1 to_string_fn1,
                               S2 to_string_fn2,
                               S3 to_string_fn3,
                               const std::string& separator = ":");

  ////////////////////////////////////////////////////////////////////////////////

  template<typename T1, typename T2, typename T3, typename T4, typename S1, typename S2, typename S3, typename S4>
  std::string foursome_to_string(const foursome<T1,T2,T3,T4>& values,
                                 S1 to_string_fn1,
                                 S2 to_string_fn2,
                                 S3 to_string_fn3,
                                 S4 to_string_fn4,
                                 const std::string& separator = ":");

  ////////////////////////////////////////////////////////////////////////////////

  template<typename T, typename C, typename S>
  std::string smart_ptr_to_string(const smart_ptr_base<T,C>& value,
                                  S to_string_fn,
                                  const std::string& null_string = "<null>",
                                  const std::string& prefix = "(",
                                  const std::string& suffix = ")");

  ////////////////////////////////////////////////////////////////////////////////

  template<typename NT, typename AT, typename NS, typename AS>
  std::string digraph_to_string(const digraph<NT,AT>& values,
                                NS node_to_string_fn,
                                AS arc_to_string_fn,
                                const std::string& separator = ",");

  ////////////////////////////////////////////////////////////////////////////////

  template<typename K, typename T, typename H, typename E, typename KS, typename TS>
  std::string hash_to_string(const hash<K,T,H,E>& values,
                             KS key_to_string_fn,
                             TS value_to_string_fn,
                             const std::string& pair_separator = ":",
                             const std::string& separator = ",");

  ////////////////////////////////////////////////////////////////////////////////

  template<typename T, typename S>
  std::string matrix_to_string(const matrix<T>& values,
                               S to_string_fn,
                               const std::string& column_separator = "|",
                               const std::string& row_separator = ",");

  ////////////////////////////////////////////////////////////////////////////////

  template<typename T, typename S>
  std::string ntree_to_string(const ntree<T>& values,
                              S to_string_fn,
                              const std::string& separator = "|",
                              const std::string& indent_string = "  ");

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus

#include "strings_stlplus.tpp"
#endif
