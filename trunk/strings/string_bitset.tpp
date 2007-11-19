////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton, 2007
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<size_t N>
  std::string bitset_to_string(const std::bitset<N>& data)
  {
    std::string result;
    for (unsigned i = data.size(); i--; )
      result += data[i] ? '1' : '0';
    return result;
  }

} // end namespace stlplus
