#ifndef STLPLUS_TEMPLATE_FIXES_HPP
#define STLPLUS_TEMPLATE_FIXES_HPP
/*------------------------------------------------------------------------------

Author:    Andy Rushton
Copyright: (c) Andy Rushton, 2007
License:   BSD License, see ../docs/license.html

Contains work arounds for OS or Compiler specific problems with container
templates

------------------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////////
// Unnecessary compiler warnings
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
// Microsoft Visual Studio
// shut up the following irritating warnings
//   4786 - VC6, identifier string exceeded maximum allowable length and was truncated (only affects debugger)
//   4503 - VC6, decorated name was longer than the maximum the compiler allows (only affects debugger)
#pragma warning(disable: 4786 4503)
#endif

////////////////////////////////////////////////////////////////////////////////
// Problems with the typename keyword
////////////////////////////////////////////////////////////////////////////////

// There are problems with using the 'typename' keyword. Technically, if you
// use a type member of a template class (i.e. a type declared within the
// template class by a local typedef), you need to tell the compiler that it
// is a type name. This is because the compiler cannot work out whether a
// member is a type, a method or a data field at compile time. However,
// support for the typename keyword has traditionally been incomplete in both
// gcc and Visual Studio. I have used macros to try to resolve this issue. The
// macros add the keyword for compiler versions that require it and omit it
// for compiler versions that do not support it

// There are five places where typename keywords cause problems:
//
//   1) in a typedef where a template class's member type is being mapped onto
//      a type definition within another template class or function 
//      e.g. template<typename T> fn () {
//             typedef typename someclass<T>::member_type local_type;
//                     ^^^^^^^^
//      Note that the typename keyword is only required when the type is of this form - a member of a template class
//
//   2) in a function parameter declaration, with similar rules to the above
//      e.g. template<typename T> fn (typename someclass<T>::member_type)
//                                    ^^^^^^^^
//      Note that the typename keyword is only required when the type is of this form - a member of a template class
//
//   3) in instantiating a template, the parameter to the template, with similar rules to the above
//      e.g. template_class<typename someclass<T>::member_type>
//                          ^^^^^^^^
//      Note that the typename keyword is only required when the type is of this form - a member of a template class
//
//   4) Return expressions
//      e.g. return typename ntree<T>::const_iterator(this,m_root);
//                  ^^^^^^^^
//      Note that this typename is only required when the return type is a member of a template class
//
//   5) Creating temporary objects when passing arguments to a function or constructor
//      e.g. return typename ntree<T>::const_prefix_iterator(typename ntree<T>::const_iterator(this,m_root));
//                                                           ^^^^^^^^
//      Note that the typename keyword is only required when the temporary's type is a member of a template class
//
// So far it *seems* as if all compilers either require all of them or none of
// them, so this set of situations can be handled by a single macro

// default values, overridden for individual problem cases below
#define TYPENAME typename

#if defined(__GNUC__)
// GCC 
//   - pre-version 3 didn't handle typename in any of these cases
//   - version 3 onwards, typename is required for all three cases as per default
#if __GNUC__ < 3
// gcc prior to v3
#undef TYPENAME
#define TYPENAME
#endif
#endif

#if defined(_MSC_VER)
// Visual Studio
//   - version 6 (compiler v.12) cannot handle typename in any of these cases
//   - version 7 (.NET) (compiler v.13) requires a typename in a parameter specification but supports all
//   - version 8 (2005) (compiler v.14) requires parameters and templates, supports all
#if _MSC_VER < 1300
// compiler version 12 and earlier
#undef TYPENAME
#define TYPENAME
#endif
#endif

////////////////////////////////////////////////////////////////////////////////
#endif
