////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Southampton University 1999-2004
//              (c) Andy Rushton           2004 onwards
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
  void dump_smart_ptr(dump_context& context, const smart_ptr<T>& data,
                      DE dump_element)
    throw(persistent_dump_failed)
  {
    // similar to the simple pointer routines, but use the address of the holder to tell which objects are aliases
    // Many smart pointers can point to the same object.
    // I could have used the address of the object to differentiate, 
    // but that would not have differentiated between different null smart pointers
    // so I use the address of the substructure to differentiate between different objects.
    // get a magic key for the substructure - this also returns a flag saying whether its been seen before
    std::pair<bool,unsigned> mapping = context.pointer_map(data._handle());
    // dump the magic key
    dump_unsigned(context,mapping.second);
    // dump the contents but only if this is the first time this object has been seen
    // use the existing routines for ordinary pointers to dump the contents
    if (!mapping.first)
      dump_pointer(context,data.pointer(),dump_element);
  }

  template<typename T, typename RE>
  void restore_smart_ptr(restore_context& context, smart_ptr<T>& data,
                         RE restore_element)
    throw(persistent_restore_failed)
  {
    // get the old substructure magic key
    unsigned magic = 0;
    restore_unsigned(context,magic);
    // lookup this magic number to see if we have seen this already
    std::pair<bool,void*> mapping = context.pointer_map(magic);
    if (mapping.first)
    {
      // this holder has already been restored
      // dealias the existing holder and replace it with the seen-before holder to make this object an alias of it
      data._make_alias((smart_ptr_holder<T>*)mapping.second);
    }
    else
    {
      // this is the first contact with this holder
      // make sure this smart pointer is unique to prevent side-effects
      data.clear_unique();
      // map the magic key onto this structure's holder
      // do this before restoring the object so that self-referential structures restore correctly
      context.pointer_add(magic,data._handle());
      // now restore the object
      T* value = 0;
      restore_pointer(context,value,restore_element);
      data.set(value);
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  // smart_ptr_clone using callbacks

  template<typename T>
  void dump_smart_ptr_clone_callback(dump_context& context, const smart_ptr_clone<T>& data)
    throw(persistent_dump_failed)
  {
    // similar to the simple pointer routines, but use the address of the holder to tell which objects are aliases
    // Many smart pointers can point to the same object.
    // I could have used the address of the object to differentiate, 
    // but that would not have differentiated between different null smart pointers
    // so I use the address of the substructure to differentiate between different objects.
    // get a magic key for the substructure - this also returns a flag saying whether its been seen before
    std::pair<bool,unsigned> mapping = context.pointer_map(data._handle());
    // dump the magic key
    dump_unsigned(context,mapping.second);
    // dump the contents but only if this is the first time this object has been seen
    // use the existing routines for ordinary pointers to dump the contents
    if (!mapping.first)
      dump_callback(context,data.pointer());
  }

  template<typename T>
  void restore_smart_ptr_clone_callback(restore_context& context, smart_ptr_clone<T>& data)
    throw(persistent_restore_failed)
  {
    // get the old substructure magic key
    unsigned magic = 0;
    restore_unsigned(context,magic);
    // lookup this magic number to see if we have seen this already
    std::pair<bool,void*> mapping = context.pointer_map(magic);
    if (mapping.first)
    {
      // this holder has already been restored
      // dealias the existing holder and replace it with the seen-before holder to make this object an alias of it
      data._make_alias((smart_ptr_holder<T>*)mapping.second);
    }
    else
    {
      // this is the first contact with this holder
      // make sure this smart pointer is unique to prevent side-effects
      data.clear_unique();
      // map the magic key onto this structure's holder
      // do this before restoring the object so that self-referential structures restore correctly
      context.pointer_add(magic,data._handle());
      // now restore the object
      T* value = 0;
      restore_callback(context,value);
      data.set(value);
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  // smart_ptr_clone using interface

  template<typename T>
  void dump_smart_ptr_clone_interface(dump_context& context, const smart_ptr_clone<T>& data)
    throw(persistent_dump_failed)
  {
    // similar to the simple pointer routines, but use the address of the holder to tell which objects are aliases
    // Many smart pointers can point to the same object.
    // I could have used the address of the object to differentiate, 
    // but that would not have differentiated between different null smart pointers
    // so I use the address of the substructure to differentiate between different objects.
    // get a magic key for the substructure - this also returns a flag saying whether its been seen before
    std::pair<bool,unsigned> mapping = context.pointer_map(data._handle());
    // dump the magic key
    dump_unsigned(context,mapping.second);
    // dump the contents but only if this is the first time this object has been seen
    // use the existing routines for ordinary pointers to dump the contents
    if (!mapping.first)
      dump_interface(context,data.pointer());
  }

  template<typename T>
  void restore_smart_ptr_clone_interface(restore_context& context, smart_ptr_clone<T>& data)
    throw(persistent_restore_failed)
  {
    // get the old substructure magic key
    unsigned magic = 0;
    restore_unsigned(context,magic);
    // lookup this magic number to see if we have seen this already
    std::pair<bool,void*> mapping = context.pointer_map(magic);
    if (mapping.first)
    {
      // this holder has already been restored
      // dealias the existing holder and replace it with the seen-before holder to make this object an alias of it
      data._make_alias((smart_ptr_holder<T>*)mapping.second);
    }
    else
    {
      // this is the first contact with this holder
      // make sure this smart pointer is unique to prevent side-effects
      data.clear_unique();
      // map the magic key onto this structure's holder
      // do this before restoring the object so that self-referential structures restore correctly
      context.pointer_add(magic,data._handle());
      // now restore the object
      T* value = 0;
      restore_interface(context,value);
      data.set(value);
    }
  }

  ////////////////////////////////////////////////////////////////////////////////

} // end namespace stlplus
