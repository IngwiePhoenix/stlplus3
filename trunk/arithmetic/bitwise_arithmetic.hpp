#ifndef STLPLUS_BITWISE_ARITHMETIC
#define STLPLUS_BITWISE_ARITHMETIC
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  Package of functions for performing bitwise logic and arithmetic on strings of 0, 1 and X values

  I've had to name the bitwise_xxx and not logical_xxx to avoid name conflicts with STL

  ------------------------------------------------------------------------------*/
#include "inf.hpp"
#include <string>
////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////
  // Logical operations
  ////////////////////////////////////////////////////////////////////////////////

  // size changer

  std::string bitwise_resize(const std::string& argument, unsigned size = 0, char pad = '0');

  // comparisons

  bool bitwise_equality(const std::string& left, const std::string& right);
  bool bitwise_inequality(const std::string& left, const std::string& right);

  // logical operations

  std::string bitwise_not(const std::string& argument);
  std::string bitwise_and(const std::string& left, const std::string& right);
  std::string bitwise_nand(const std::string& left, const std::string& right);
  std::string bitwise_or(const std::string& left, const std::string& right);
  std::string bitwise_nor(const std::string& left, const std::string& right);
  std::string bitwise_xor(const std::string& left, const std::string& right);
  std::string bitwise_xnor(const std::string& left, const std::string& right);

  // shift operations

  std::string bitwise_shift_left(const std::string& argument, unsigned shift);
  std::string bitwise_shift_right(const std::string& argument, unsigned shift);
  std::string bitwise_rotate_left(const std::string& argument, unsigned shift);
  std::string bitwise_rotate_right(const std::string& argument, unsigned shift);

  ////////////////////////////////////////////////////////////////////////////////
  // Unsigned arithmetic
  ////////////////////////////////////////////////////////////////////////////////

  // size changers

  std::string bitwise_unsigned_resize(const std::string& argument, unsigned size = 0);

  // comparisons

  bool bitwise_unsigned_equality(const std::string& left, const std::string& right);
  bool bitwise_unsigned_inequality(const std::string& left, const std::string& right);
  bool bitwise_unsigned_less_than(const std::string& left, const std::string& right);
  bool bitwise_unsigned_less_than_or_equal(const std::string& left, const std::string& right);
  bool bitwise_unsigned_greater_than(const std::string& left, const std::string& right);
  bool bitwise_unsigned_greater_than_or_equal(const std::string& left, const std::string& right);

  // arithmetic operations

  std::string bitwise_unsigned_add(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_unsigned_subtract(const std::string& left, const std::string& right, unsigned size = 0);

  std::string bitwise_unsigned_multiply(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_unsigned_exponent(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_unsigned_divide(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_unsigned_modulus(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_unsigned_remainder(const std::string& left, const std::string& right, unsigned size = 0);

  // logical operations

  std::string bitwise_unsigned_not(const std::string& argument, unsigned size = 0);
  std::string bitwise_unsigned_and(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_unsigned_nand(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_unsigned_or(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_unsigned_nor(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_unsigned_xor(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_unsigned_xnor(const std::string& left, const std::string& right, unsigned size = 0);

  // shift operations

  std::string bitwise_unsigned_shift_left(const std::string& argument, unsigned shift, unsigned size = 0);
  std::string bitwise_unsigned_shift_right(const std::string& argument, unsigned shift, unsigned size = 0);

  // integer conversions

  unsigned long bitwise_unsigned_to_unsigned_long(const std::string& argument);
  inf bitwise_unsigned_to_inf(const std::string& argument);
  std::string unsigned_long_to_bitwise_unsigned(unsigned long argument, unsigned size = 0);
  std::string inf_to_bitwise_unsigned(const inf& argument, unsigned size = 0);

  ////////////////////////////////////////////////////////////////////////////////
  // Signed arithmetic
  ////////////////////////////////////////////////////////////////////////////////

  // size changers

  std::string bitwise_signed_resize(const std::string& argument, unsigned size = 0);

  // tests

  bool bitwise_signed_is_negative(const std::string& argument);
  bool bitwise_signed_is_natural(const std::string& argument);
  bool bitwise_signed_is_positive(const std::string& argument);
  bool bitwise_signed_is_zero(const std::string& argument);

  // comparisons

  bool bitwise_signed_equality(const std::string& left, const std::string& right);
  bool bitwise_signed_inequality(const std::string& left, const std::string& right);
  bool bitwise_signed_less_than(const std::string& left, const std::string& right);
  bool bitwise_signed_less_than_or_equal(const std::string& left, const std::string& right);
  bool bitwise_signed_greater_than(const std::string& left, const std::string& right);
  bool bitwise_signed_greater_than_or_equal(const std::string& left, const std::string& right);

  // arithmetic operations

  std::string bitwise_signed_negate(const std::string& argument, unsigned size = 0);
  std::string bitwise_signed_abs(const std::string& argument, unsigned size = 0);
  std::string bitwise_signed_add(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_signed_subtract(const std::string& left, const std::string& right, unsigned size = 0);

  std::string bitwise_signed_multiply(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_signed_exponent(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_signed_divide(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_signed_modulus(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_signed_remainder(const std::string& left, const std::string& right, unsigned size = 0);

  // logical operations

  std::string bitwise_signed_not(const std::string& argument, unsigned size = 0);
  std::string bitwise_signed_and(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_signed_nand(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_signed_or(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_signed_nor(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_signed_xor(const std::string& left, const std::string& right, unsigned size = 0);
  std::string bitwise_signed_xnor(const std::string& left, const std::string& right, unsigned size = 0);

  // shift operations

  std::string bitwise_signed_shift_left(const std::string& argument, unsigned shift, unsigned size = 0);
  std::string bitwise_signed_shift_right(const std::string& argument, unsigned shift, unsigned size = 0);

  // integer conversions

  long bitwise_signed_to_long(const std::string& argument);
  inf bitwise_signed_to_inf(const std::string& argument);
  std::string long_to_bitwise_signed(long argument, unsigned size = 0);
  std::string inf_to_bitwise_signed(const inf& argument, unsigned size = 0);

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus
#endif
