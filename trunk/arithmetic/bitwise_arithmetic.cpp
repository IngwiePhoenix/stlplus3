/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2004
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "bitwise_arithmetic.hpp"
////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////
  // local functions for implementing the low-level bitwise operations
  // these have been written to implement X handling

  static char bit_not(char input)
  {
    switch (input)
    {
    case '0': return '1';
    case '1': return '0';
    default: return 'X';
    }
  }

  static char bit_and(char left, char right)
  {
    switch (left)
    {
    case '0':
      switch (right)
      {
      case '0': return '0';
      case '1': return '0';
      default: return 'X';
      }
    case '1':
      switch (right)
      {
      case '0': return '0';
      case '1': return '1';
      default: return 'X';
      }
    default: return 'X';
    }
  }

  static char bit_or(char left, char right)
  {
    switch (left)
    {
    case '0':
      switch (right)
      {
      case '0': return '0';
      case '1': return '1';
      default: return 'X';
      }
    case '1':
      switch (right)
      {
      case '0': return '1';
      case '1': return '1';
      default: return 'X';
      }
    default: return 'X';
    }
  }

  static char bit_xor(char left, char right)
  {
    switch (left)
    {
    case '0':
      switch (right)
      {
      case '0': return '0';
      case '1': return '1';
      default: return 'X';
      }
    case '1':
      switch (right)
      {
      case '0': return '1';
      case '1': return '0';
      default: return 'X';
      }
    default: return 'X';
    }
  }

  static char bit_sum(char left, char right, char carry)
  {
    return bit_xor(bit_xor(left,right),carry);
  }

  static char bit_carry(char left, char right, char carry)
  {
    return bit_or(bit_or(bit_and(left,right),bit_and(left,carry)),bit_and(right,carry));
  }

  ////////////////////////////////////////////////////////////////////////////////
  // Logic - exported functions

  std::string bitwise_resize(const std::string& argument, unsigned size, char pad)
  {
    std::string value = argument;
    // resize has two functions:
    if (size > value.size())
    {
      // - zero extend when a greater size specified
      value.insert((std::string::size_type)0u,size-value.size(),pad);
    }
    else if (size < value.size())
    {
      // - truncate when a smaller size specified
      value.erase((std::string::size_type)0u,value.size()-size);
    }
    return value;
  }

  // comparisons

  bool bitwise_equality(const std::string& left, const std::string& right)
  {
    return left == right;
  }

  bool bitwise_inequality(const std::string& left, const std::string& right)
  {
    return !bitwise_equality(left, right);
  }

  // logical operations

  std::string bitwise_not(const std::string& argument)
  {
    unsigned size = argument.size();
    std::string result;
    for (unsigned i = 0; i < size; i++)
      result += bit_not(argument[i]);
    return result;
  }

  std::string bitwise_and(const std::string& left, const std::string& right)
  {
    unsigned size = std::max(left.size(),right.size());
    std::string result;
    for (unsigned i = 0; i < size; i++)
      result += bit_and(i < left.size() ? left[i] : '0', i < right.size() ? right[i] : '0');
    return result;
  }

  std::string bitwise_nand(const std::string& left, const std::string& right)
  {
    return bitwise_not(bitwise_and(left,right));
  }

  std::string bitwise_or(const std::string& left, const std::string& right)
  {
    unsigned size = std::max(left.size(),right.size());
    std::string result;
    for (unsigned i = 0; i < size; i++)
      result += bit_or(i < left.size() ? left[i] : '0', i < right.size() ? right[i] : '0');
    return result;
  }

  std::string bitwise_nor(const std::string& left, const std::string& right)
  {
    return bitwise_not(bitwise_or(left,right));
  }

  std::string bitwise_xor(const std::string& left, const std::string& right)
  {
    unsigned size = std::max(left.size(),right.size());
    std::string result;
    for (unsigned i = 0; i < size; i++)
      result += bit_xor(i < left.size() ? left[i] : '0', i < right.size() ? right[i] : '0');
    return result;
  }

  std::string bitwise_xnor(const std::string& left, const std::string& right)
  {
    return bitwise_not(bitwise_xor(left,right));
  }

  // shift operations

  std::string bitwise_shift_left(const std::string& argument, unsigned shift)
  {
    std::string result = argument;
    if (shift) result.append(shift,'0');
    return result;
  }

  std::string bitwise_shift_right(const std::string& argument, unsigned shift)
  {
    std::string result = argument;
    if (shift)
    {
      if (shift >= result.size())
        result = std::string();
      else
        result.erase(result.size()-shift,shift);
    }
    return result;
  }

  std::string bitwise_rotate_left(const std::string& argument, unsigned shift)
  {
    // reduce the rotate distance to less than the argument length
    shift %= argument.size();
    return argument.substr(shift, argument.size()-shift) + argument.substr(0, shift);
  }

  std::string bitwise_rotate_right(const std::string& argument, unsigned shift)
  {
    // reduce the rotate distance to less than the argument length
    shift %= argument.size();
    return argument.substr(argument.size()-shift, shift) + argument.substr(0, argument.size()-shift);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // Unsigned - exported functions

  std::string bitwise_unsigned_resize(const std::string& argument, unsigned size)
  {
    std::string value = argument;
    // resize has three functions:
    if (!size)
    {
      // - reduce to minimum size when size 0 specified by simply trimming leading zeros (but not the last bit)
      while(value.size() > 1 && value[0] == '0')
        value.erase((std::string::size_type)0u,1);
    }
    else if (size > value.size())
    {
      // - zero extend when a greater size specified
      value.insert((std::string::size_type)0u,size-value.size(),'0');
    }
    else if (size < value.size())
    {
      // - truncate when a smaller size specified
      value.erase((std::string::size_type)0u,value.size()-size);
    }
    return value;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // comparisons

  bool bitwise_unsigned_equality(const std::string& left, const std::string& right)
  {
    // implement numeric equality as bitwise equality by first normalising to the same size
    std::string left_value = bitwise_unsigned_resize(left, std::max(left.size(),right.size()));
    std::string right_value = bitwise_unsigned_resize(right, std::max(left.size(),right.size()));
    return left_value == right_value;
  }

  bool bitwise_unsigned_inequality(const std::string& left, const std::string& right)
  {
    return !bitwise_unsigned_equality(left,right);
  }

  bool bitwise_unsigned_less_than(const std::string& left, const std::string& right)
  {
    // extend by one bit and treat as signed then do subtraction and test for a negative result
    std::string result = bitwise_signed_subtract(bitwise_unsigned_resize(left,left.size()+1),bitwise_unsigned_resize(right,right.size()+1));
    return bitwise_signed_is_negative(result);
  }

  bool bitwise_unsigned_less_than_or_equal(const std::string& left, const std::string& right)
  {
    // l <= r is equivalent to !(r < l)
    return !bitwise_unsigned_less_than(right,left);
  }

  bool bitwise_unsigned_greater_than(const std::string& left, const std::string& right)
  {
    // l > r is equivalent to r < l
    return bitwise_unsigned_less_than(right,left);
  }

  bool bitwise_unsigned_greater_than_or_equal(const std::string& left, const std::string& right)
  {
    // l >= r is equivalent to !(l < r)
    return !bitwise_unsigned_less_than(left,right);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // arithmetic operations

  std::string bitwise_unsigned_add(const std::string& left, const std::string& right, unsigned size)
  {
    unsigned add_size = std::max(left.size(),right.size())+1;
    std::string left_value = bitwise_unsigned_resize(left, add_size);
    std::string right_value = bitwise_unsigned_resize(right, add_size);
    std::string result = bitwise_unsigned_resize("0",add_size);
    char carry = '0';
    for (unsigned i = add_size; i--; )
    {
      result[i] = bit_sum(left_value[i], right_value[i], carry);
      carry = bit_carry(left_value[i], right_value[i], carry);
    }
    return bitwise_unsigned_resize(result,size);
  }

  std::string bitwise_unsigned_subtract(const std::string& left, const std::string& right, unsigned size)
  {
    unsigned sub_size = std::max(left.size(),right.size())+1;
    std::string left_value = bitwise_unsigned_resize(left, sub_size);
    std::string right_value = bitwise_unsigned_resize(right, sub_size);
    std::string result = bitwise_unsigned_resize("0",sub_size);
    char borrow = '0';
    for (unsigned i = sub_size; i--; )
    {
      result[i] = bit_sum(left_value[i], right_value[i], borrow);
      borrow = bit_carry(bit_not(left_value[i]), right_value[i], borrow);
    }
    return bitwise_unsigned_resize(result,size);
  }

  std::string bitwise_unsigned_multiply(const std::string& left, const std::string& right, unsigned size)
  {
    // based on numeric_xxx.vhdl
    // multiplication is repeated addition
    std::string result = "0";
    std::string add = right;
    for (unsigned i = left.size(); i--; )
    {
      if (left[i] == '1')
        result = bitwise_unsigned_add(result, add);
      add = bitwise_unsigned_shift_left(add, 1);
    }
    return bitwise_unsigned_resize(result,size);
  }

  std::string bitwise_unsigned_exponent(const std::string& left, const std::string& right, unsigned size)
  {
    // simply implemented by repeated multiplication
    std::string result = "1";
    // make the count signed by zero extending one bit so that the test for positive works
    for (std::string count = bitwise_unsigned_resize(right,right.size()+1); bitwise_signed_is_positive(count); count = bitwise_signed_subtract(count,"1"))
      result = bitwise_signed_multiply(result, left);
    return bitwise_unsigned_resize(result,size);
  }

  // local unsigned division giving modulus and remainder as a pair
  static std::pair<std::string,std::string> divrem(const std::string& left, const std::string& right)
  {
    std::string quotient = "";
    std::string remainder = left;
    std::string subtract = bitwise_unsigned_shift_left(right,left.size()-1);
    for (unsigned i = left.size(); i--; )
    {
      if (bitwise_unsigned_less_than(remainder,subtract))
        quotient += "0";
      else
      {
        remainder = bitwise_unsigned_subtract(remainder,subtract);
        quotient += "1";
      }
      subtract = bitwise_unsigned_shift_right(subtract,1);
    }
    return std::make_pair(quotient,remainder);
  }

  std::string bitwise_unsigned_divide(const std::string& left, const std::string& right, unsigned size)
  {
    std::pair<std::string,std::string> result = divrem(left,right);
    return bitwise_unsigned_resize(result.first,size);
  }

  std::string bitwise_unsigned_modulus(const std::string& left, const std::string& right, unsigned size)
  {
    // for unsigned, modulus is the same as remainder
    return bitwise_unsigned_remainder(left,right,size);
  }

  std::string bitwise_unsigned_remainder(const std::string& left, const std::string& right, unsigned size)
  {
    std::pair<std::string,std::string> result = divrem(left,right);
    return bitwise_unsigned_resize(result.second,size);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // logical operations

  std::string bitwise_unsigned_not(const std::string& argument, unsigned size)
  {
    if (!size) size = argument.size();
    return bitwise_not(bitwise_unsigned_resize(argument,size));
  }

  std::string bitwise_unsigned_and(const std::string& left, const std::string& right, unsigned size)
  {
    if (!size) size = std::max(left.size(),right.size());
    return bitwise_and(bitwise_unsigned_resize(left,size), bitwise_unsigned_resize(right,size));
  }

  std::string bitwise_unsigned_nand(const std::string& left, const std::string& right, unsigned size)
  {
    if (!size) size = std::max(left.size(),right.size());
    return bitwise_nand(bitwise_unsigned_resize(left,size), bitwise_unsigned_resize(right,size));
  }

  std::string bitwise_unsigned_or(const std::string& left, const std::string& right, unsigned size)
  {
    if (!size) size = std::max(left.size(),right.size());
    return bitwise_or(bitwise_unsigned_resize(left,size), bitwise_unsigned_resize(right,size));
  }

  std::string bitwise_unsigned_nor(const std::string& left, const std::string& right, unsigned size)
  {
    if (!size) size = std::max(left.size(),right.size());
    return bitwise_nor(bitwise_unsigned_resize(left,size), bitwise_unsigned_resize(right,size));
  }

  std::string bitwise_unsigned_xor(const std::string& left, const std::string& right, unsigned size)
  {
    if (!size) size = std::max(left.size(),right.size());
    return bitwise_xor(bitwise_unsigned_resize(left,size), bitwise_unsigned_resize(right,size));
  }

  std::string bitwise_unsigned_xnor(const std::string& left, const std::string& right, unsigned size)
  {
    if (!size) size = std::max(left.size(),right.size());
    return bitwise_xnor(bitwise_unsigned_resize(left,size), bitwise_unsigned_resize(right,size));
  }

  ////////////////////////////////////////////////////////////////////////////////

  std::string bitwise_unsigned_shift_left(const std::string& argument, unsigned shift, unsigned size)
  {
    return bitwise_unsigned_resize(bitwise_shift_left(argument,shift),size);
  }

  std::string bitwise_unsigned_shift_right(const std::string& argument, unsigned shift, unsigned size)
  {
    return bitwise_unsigned_resize(bitwise_shift_right(argument,shift),size);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // integer conversions
  // Note: no way of handling X values - so treat as 0

  unsigned long bitwise_unsigned_to_unsigned_long(const std::string& argument)
  {
    unsigned long result = 0;
    for (unsigned i = 0; i < argument.size(); i++)
    {
      result *= 2;
      if (argument[i] == '1') ++result;
    }
    return result;
  }

  inf bitwise_unsigned_to_inf(const std::string& argument)
  {
    inf result;
    for (unsigned i = 0; i < argument.size(); i++)
    {
      result *= inf(2);
      if (argument[i] == '1') ++result;
    }
    return result;
  }

  std::string unsigned_long_to_bitwise_unsigned(unsigned long argument, unsigned size)
  {
    std::string result = argument ? "" : "0";
    while(argument)
    {
      result.insert((std::string::size_type)0u,1u,(argument%2 ? '1' : '0'));
      argument /= 2;
    }
    return bitwise_unsigned_resize(result,size);
  }

  std::string inf_to_bitwise_unsigned(const inf& argument, unsigned size)
  {
    inf value = argument;
    std::string result = value.non_zero() ? "" : "0";
    while(value.non_zero())
    {
      result.insert((std::string::size_type)0u,1u,((value % inf(2)).non_zero() ? '1' : '0'));
      value /= inf(2);
    }
    return bitwise_unsigned_resize(result,size);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // Signed - exported functions

  std::string bitwise_signed_resize(const std::string& argument, unsigned size)
  {
    std::string value = argument;
    // resize has three functions:
    if (!size)
    {
      // - reduce to minimum size by simply trimming leading sign bits (but not the last bit)
      while(value.size() >= 2 && value[0] == value[1])
        value.erase((std::string::size_type)0u,1);
    }
    else if (size > value.size())
    {
      // - sign extend when a greater size specified
      value.insert((std::string::size_type)0u,size-value.size(),value.empty() ? '0' : value[0]);
    }
    else if (value.size() > size)
    {
      // - truncate when a smaller size specified
      value.erase((std::string::size_type)0u,value.size()-size);
    }
    return value;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // tests

  bool bitwise_signed_is_negative(const std::string& argument)
  {
    return argument[0] == '1';
  }

  bool bitwise_signed_is_natural(const std::string& argument)
  {
    return !bitwise_signed_is_negative(argument);
  }

  bool bitwise_signed_is_positive(const std::string& argument)
  {
    return bitwise_signed_is_natural(argument) && !bitwise_signed_is_zero(argument);
  }

  bool bitwise_signed_is_zero(const std::string& argument)
  {
    for (unsigned i = 0; i < argument.size(); i++)
    {
      if (argument[i] == '1')
        return false;
    }
    return true;
  }

  ////////////////////////////////////////////////////////////////////////////////
  // comparisons

  bool bitwise_signed_equality(const std::string& left, const std::string& right)
  {
    std::string left_value = bitwise_signed_resize(left, std::max(left.size(),right.size()));
    std::string right_value = bitwise_signed_resize(right, std::max(left.size(),right.size()));
    return left_value == right_value;
  }

  bool bitwise_signed_inequality(const std::string& left, const std::string& right)
  {
    return !bitwise_signed_equality(left,right);
  }

  bool bitwise_signed_less_than(const std::string& left, const std::string& right)
  {
    std::string result = bitwise_signed_subtract(left,right);
    return bitwise_signed_is_negative(result);
  }

  bool bitwise_signed_less_than_or_equal(const std::string& left, const std::string& right)
  {
    // l <= r is equivalent to !(r < l)
    return !bitwise_signed_less_than(right,left);
  }

  bool bitwise_signed_greater_than(const std::string& left, const std::string& right)
  {
    // l > r is equivalent to r < l
    return bitwise_signed_less_than(right,left);
  }

  bool bitwise_signed_greater_than_or_equal(const std::string& left, const std::string& right)
  {
    // l >= r is equivalent to !(l < r)
    return !bitwise_signed_less_than(left,right);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // arithmetic operations

  std::string bitwise_signed_negate(const std::string& argument, unsigned size)
  {
    unsigned negate_size = argument.size()+1;
    std::string value = bitwise_signed_resize(argument, negate_size);
    std::string result = bitwise_signed_resize("0",negate_size);
    char borrow = '0';
    for (unsigned i = negate_size; i--; )
    {
      // negation is zero minus the argument, which I have optimised to the following:
      result[i] = bit_xor(value[i], borrow);
      borrow = bit_or(value[i], borrow);
    }
    return bitwise_signed_resize(result,size);
  }

  std::string bitwise_signed_abs(const std::string& argument, unsigned size)
  {
    return bitwise_signed_is_negative(argument) ? bitwise_signed_negate(argument, size) : bitwise_signed_resize(argument, size);
  }

  std::string bitwise_signed_add(const std::string& left, const std::string& right, unsigned size)
  {
    unsigned add_size = std::max(left.size(),right.size())+1;
    std::string left_value = bitwise_signed_resize(left, add_size);
    std::string right_value = bitwise_signed_resize(right, add_size);
    std::string result = bitwise_signed_resize("0",add_size);
    char carry = '0';
    for (unsigned i = add_size; i--; )
    {
      result[i] = bit_sum(left_value[i], right_value[i], carry);
      carry = bit_carry(left_value[i], right_value[i], carry);
    }
    return bitwise_signed_resize(result,size);
  }

  std::string bitwise_signed_subtract(const std::string& left, const std::string& right, unsigned size)
  {
    unsigned sub_size = std::max(left.size(),right.size())+1;
    std::string left_value = bitwise_signed_resize(left, sub_size);
    std::string right_value = bitwise_signed_resize(right, sub_size);
    std::string result = bitwise_signed_resize("0",sub_size);
    char borrow = '0';
    for (unsigned i = sub_size; i--; )
    {
      result[i] = bit_sum(left_value[i], right_value[i], borrow);
      borrow = bit_carry(bit_not(left_value[i]), right_value[i], borrow);
    }
    return bitwise_signed_resize(result,size);
  }

  std::string bitwise_signed_multiply(const std::string& left, const std::string& right, unsigned size)
  {
    // based on numeric_xxx.vhdl
    std::string result = "0";
    std::string add = right;
    for (unsigned i = left.size(); i--; )
    {
      if (left[i] == '1')
        result = bitwise_signed_add(result, add);
      add = bitwise_signed_shift_left(add, 1);
    }
    if (left[0] == '1')
      result = bitwise_signed_subtract(result,add);
    return bitwise_signed_resize(result,size);
  }

  std::string bitwise_signed_exponent(const std::string& left, const std::string& right, unsigned size)
  {
    std::string result = "01";
    for (std::string count = right; bitwise_signed_is_positive(count); count = bitwise_signed_subtract(count,"01"))
      result = bitwise_signed_multiply(result, left);
    return bitwise_signed_resize(result,size);
  }

  std::string bitwise_signed_divide(const std::string& left, const std::string& right, unsigned size)
  {
    // do unsigned division on the absolute values
    std::pair<std::string,std::string> div_result = divrem(bitwise_signed_abs(left),bitwise_signed_abs(right));
    // the result is negated if the signs are different - note also the unsigned to signed conversion
    std::string result = bitwise_unsigned_resize(div_result.first,div_result.first.size()+1);
    if (left[0] != right[0]) result = bitwise_signed_negate(result);
    return bitwise_signed_resize(result,size);
  }

  std::string bitwise_signed_modulus(const std::string& left, const std::string& right, unsigned size)
  {
    // Note: unlike remainder, which cannot be bigger than the left argument, the modulus can be as big as the absolute value of the right too
    //       the solution is to allow the result to expand its own way
    // to convert from remainder to modulus, you add the divisor iff the result is non-zero and signs are different:
    //   3 rem 4 = 3    :  3 mod 4 = 3
    //  -3 rem 4 = -3   : -3 mod 4 = 1 = (-3 rem 4) + 4
    //   3 rem -4 = 3   :  3 mod -4 = -1 = (3 rem -4) + -4
    //  -3 rem -4 = -3  : -3 mod -4 = -3
    std::string result = bitwise_signed_remainder(left,right);
    if (!bitwise_signed_is_zero(result) && (right[0] != left[0]))
      result = bitwise_signed_add(result,right);
    return bitwise_signed_resize(result,size);
  }

  std::string bitwise_signed_remainder(const std::string& left, const std::string& right, unsigned size)
  {
    // do unsigned division on the absolute values
    std::pair<std::string,std::string> div_result = divrem(bitwise_signed_abs(left),bitwise_signed_abs(right));
    // the sign of the result is the same as the left argument
    std::string result = bitwise_unsigned_resize(div_result.second,div_result.second.size()+1);
    if (left[0] == '1')
      result = bitwise_signed_negate(result);
    return bitwise_signed_resize(result,size);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // logical operations

  std::string bitwise_signed_not(const std::string& argument, unsigned size)
  {
    if (!size) size = argument.size();
    return bitwise_not(bitwise_signed_resize(argument,size));
  }

  std::string bitwise_signed_and(const std::string& left, const std::string& right, unsigned size)
  {
    if (!size) size = std::max(left.size(),right.size());
    return bitwise_and(bitwise_signed_resize(left,size), bitwise_signed_resize(right,size));
  }

  std::string bitwise_signed_nand(const std::string& left, const std::string& right, unsigned size)
  {
    if (!size) size = std::max(left.size(),right.size());
    return bitwise_nand(bitwise_signed_resize(left,size), bitwise_signed_resize(right,size));
  }

  std::string bitwise_signed_or(const std::string& left, const std::string& right, unsigned size)
  {
    if (!size) size = std::max(left.size(),right.size());
    return bitwise_or(bitwise_signed_resize(left,size), bitwise_signed_resize(right,size));
  }

  std::string bitwise_signed_nor(const std::string& left, const std::string& right, unsigned size)
  {
    if (!size) size = std::max(left.size(),right.size());
    return bitwise_nor(bitwise_signed_resize(left,size), bitwise_signed_resize(right,size));
  }

  std::string bitwise_signed_xor(const std::string& left, const std::string& right, unsigned size)
  {
    if (!size) size = std::max(left.size(),right.size());
    return bitwise_xor(bitwise_signed_resize(left,size), bitwise_signed_resize(right,size));
  }

  std::string bitwise_signed_xnor(const std::string& left, const std::string& right, unsigned size)
  {
    if (!size) size = std::max(left.size(),right.size());
    return bitwise_xnor(bitwise_signed_resize(left,size), bitwise_signed_resize(right,size));
  }

  ////////////////////////////////////////////////////////////////////////////////

  std::string bitwise_signed_shift_left(const std::string& argument, unsigned shift, unsigned size)
  {
    return bitwise_signed_resize(bitwise_shift_left(argument,shift),size);
  }

  std::string bitwise_signed_shift_right(const std::string& argument, unsigned shift, unsigned size)
  {
    return bitwise_signed_resize(bitwise_shift_right(argument,shift),size);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // integer conversions

  long bitwise_signed_to_long(const std::string& argument)
  {
    bool negative = bitwise_signed_is_negative(argument);
    long result = 0;
    std::string value = negative ? bitwise_signed_not(argument) : argument;
    for (unsigned i = 0; i < value.size(); i++)
    {
      result *= 2;
      if (value[i] == '1') ++result;
    }
    if (negative)
      result = (-result)-1;
    return result;
  }

  inf bitwise_signed_to_inf(const std::string& argument)
  {
    bool negative = bitwise_signed_is_negative(argument);
    inf result;
    std::string value = negative ? bitwise_signed_not(argument) : argument;
    for (unsigned i = 0; i < value.size(); i++)
    {
      result *= inf(2);
      if (value[i] == '1') ++result;
    }
    if (negative)
      result = (-result)-inf(1);
    return result;
  }

  std::string long_to_bitwise_signed(long argument, unsigned size)
  {
    bool negative = argument < 0;
    if (negative) argument = -(argument+1);
    std::string result = "";
    while(argument)
    {
      result.insert((std::string::size_type)0u,1u,(argument%2 ? '1' : '0'));
      argument /= 2;
    }
    result.insert((std::string::size_type)0u,1u,'0');
    if (negative) result = bitwise_signed_not(result);
    return bitwise_signed_resize(result,size);
  }

  std::string inf_to_bitwise_signed(const inf& argument, unsigned size)
  {
    inf value = argument;
    bool negative = value.negative();
    if (negative) value = -(value+inf(1));
    std::string result = "";
    while(value.non_zero())
    {
      result.insert((std::string::size_type)0u,1u,((value % inf(2)).non_zero() ? '1' : '0'));
      value /= inf(2);
    }
    result.insert((std::string::size_type)0u,1u,'0');
    if (negative) result = bitwise_signed_not(result);
    return bitwise_signed_resize(result,size);
  }

} // end namespace stlplus

////////////////////////////////////////////////////////////////////////////////
