////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton, 2007
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

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


} // end namespace stlplus
