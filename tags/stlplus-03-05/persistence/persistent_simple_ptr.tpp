////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Southampton University 1999-2004
//              (c) Andy Rushton           2004-2009
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////
#include "persistent_int.hpp"
#include "persistent_pointer.hpp"
#include "persistent_callback.hpp"
#include "persistent_interface.hpp"

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////

  template<typename  T, typename DE>
  void dump_simple_ptr(dump_context& context, const simple_ptr<T>& data,
                      DE dump_element)
    throw(persistent_dump_failed)
  {
    // Many smart pointers can point to the same object.
    // I could have used the address of the object to differentiate, 
    // but that would not have differentiated between different null smart pointers
    // so I use the address of the count to differentiate between different objects.
    // get a magic key for the substructure - this also returns a flag saying whether its been seen before
    std::pair<bool,unsigned> mapping = context.pointer_map(data._count());
    // dump the magic key for the count
    dump_unsigned(context,mapping.second);
    // dump the contents always - this is because I need to rely on the pointer routines dumping a second magic key
    // use the existing routines for ordinary pointers to dump the contents
    dump_pointer(context,data._pointer(),dump_element);
  }

  template<typename T, typename RE>
  void restore_simple_ptr(restore_context& context, simple_ptr<T>& data,
                         RE restore_element)
    throw(persistent_restore_failed)
  {
    // get the old counter magic key
    unsigned magic = 0;
    restore_unsigned(context,magic);
    // lookup this magic number to see if we have seen this already
    std::pair<bool,void*> mapping = context.pointer_map(magic);
    if (mapping.first)
    {
      // this holder has already been restored
      // now restore the object and rely on the pointer routines to return the existing object
      T* value = 0;
      restore_pointer(context,value,restore_element);
      // dealias the existing holder and replace it with the seen-before holder to make this object an alias of it
      data._make_alias(value, (unsigned*)mapping.second);
    }
    else
    {
      // this is the first contact with this holder
      // make sure this smart pointer is unique to prevent side-effects
      data.clear_unique();
      // map the magic key onto this structure's holder
      // do this before restoring the object so that self-referential structures restore correctly
      context.pointer_add(magic,data._count());
      // now restore the object
      T* value = 0;
      restore_pointer(context,value,restore_element);
      // and add it to the pointer
      data.set(value);
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  // simple_ptr_clone using callbacks

  template<typename T>
  void dump_simple_ptr_clone_callback(dump_context& context, const simple_ptr_clone<T>& data)
    throw(persistent_dump_failed)
  {
    std::pair<bool,unsigned> mapping = context.pointer_map(data._count());
    dump_unsigned(context,mapping.second);
    dump_callback(context,data._pointer());
  }

  template<typename T>
  void restore_simple_ptr_clone_callback(restore_context& context, simple_ptr_clone<T>& data)
    throw(persistent_restore_failed)
  {
    unsigned magic = 0;
    restore_unsigned(context,magic);
    std::pair<bool,void*> mapping = context.pointer_map(magic);
    if (mapping.first)
    {
      T* value = 0;
      restore_callback(context,value);
      data._make_alias(value, (unsigned*)mapping.second);
    }
    else
    {
      data.clear_unique();
      context.pointer_add(magic,data._count());
      T* value = 0;
      restore_callback(context,value);
      data.set(value);
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  // simple_ptr_clone using interface

  template<typename T>
  void dump_simple_ptr_clone_interface(dump_context& context, const simple_ptr_clone<T>& data)
    throw(persistent_dump_failed)
  {
    std::pair<bool,unsigned> mapping = context.pointer_map(data._count());
    dump_unsigned(context,mapping.second);
    dump_interface(context,data._pointer());
  }

  template<typename T>
  void restore_simple_ptr_clone_interface(restore_context& context, simple_ptr_clone<T>& data)
    throw(persistent_restore_failed)
  {
    unsigned magic = 0;
    restore_unsigned(context,magic);
    std::pair<bool,void*> mapping = context.pointer_map(magic);
    if (mapping.first)
    {
      T* value = 0;
      restore_interface(context,value);
      data._make_alias(value, (unsigned*)mapping.second);
    }
    else
    {
      data.clear_unique();
      context.pointer_add(magic,data._count());
      T* value = 0;
      restore_interface(context,value);
      data.set(value);
    }
  }

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus
