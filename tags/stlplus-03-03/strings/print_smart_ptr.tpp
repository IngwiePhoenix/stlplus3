////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Southampton University 1999-2004
//              (c) Andy Rushton           2004-2008
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  template<typename T, typename C, typename S>
  void print_smart_ptr(std::ostream& device,
                       const smart_ptr_base<T,C>& value,
                       S print_fn,
                       const std::string& null_string,
                       const std::string& prefix,
                       const std::string& suffix)
  {
    if (value)
    {
      device << prefix;
      print_fn(device, *value);
      device << suffix;
    }
    else
    {
      device << null_string;
    }
  }

} // end namespace stlplus

