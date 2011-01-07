////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton           2011 onwards
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////

#include "persistent_int.hpp"

////////////////////////////////////////////////////////////////////////////////

template<typename  T, typename DE>
void stlplus::dump_shared_ptr(stlplus::dump_context& context, const std::shared_ptr<T>& data, DE dump_element)
  throw(stlplus::persistent_dump_failed)
{
  // Many shared pointers can point to the same object and they will be dumped as aliases
  // The problem with this approach is that all pointers to null will end up being aliases or unique
  // I cannot see a solution to this, but I also cannot think of a problem with it

  // I have to handle empty and null shared pointers as a special case, which
  // means the file format is different from other pointer types
  unsigned classification = (data.use_count() == 0) ? 0 : (data.get() == 0) ? 1 : 2;
  stlplus::dump_unsigned(context, classification);
  if (classification == 2)
  {
    // get a magic key for the object - this also returns a flag saying whether its been seen before
    std::pair<bool,unsigned> mapping = context.pointer_map(data.get());
    // dump the magic key
    stlplus::dump_unsigned(context,mapping.second);
    // dump the contents but only if this is the first time this object has been seen
    // use the existing routines for ordinary pointers to dump the contents
    if (!mapping.first)
      dump_element(context,*data);
  }
}

template<typename T, typename RE>
void stlplus::restore_shared_ptr(stlplus::restore_context& context, std::shared_ptr<T>& data, RE restore_element)
  throw(stlplus::persistent_restore_failed)
{
  // get the classification
  unsigned classification = 0;
  stlplus::restore_unsigned(context, classification);
  switch(classification)
  {
  case 0:
  {
    // empty pointer
    data.reset();
    break;
  }
  case 1:
  {
    // null pointer
    data.reset((T*)0);
    break;
  }
  case 2:
  {
    // pointer to an object
    // get the magic key
    unsigned magic = 0;
    stlplus::restore_unsigned(context,magic);
    // lookup this magic number to see if we have seen this already
    std::pair<bool,void*> mapping = context.pointer_map(magic);
    if (!mapping.first)
    {
      // this is the first contact with this object
      // map the magic key onto this shared pointer which becomes the master pointer
      // do this before restoring the object so that self-referential structures restore correctly
      context.pointer_add(magic,&data);
      // now restore the object
      data.reset(new T());
      restore_element(context,*data);
    }
    else
    {
      // this object has already been restored
      // the mapping contains the address of the master shared pointer, so make data an alias of it
      data = *(std::shared_ptr<T>*)mapping.second;
    }
    break;
  }
  default:
  {
    throw stlplus::persistent_restore_failed("Illegal pointer classification");
    break;
  }
  }
}

////////////////////////////////////////////////////////////////////////////////
